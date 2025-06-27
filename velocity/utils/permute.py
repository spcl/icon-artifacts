from pathlib import Path
import dace
from typing import Dict, List

from dace.transformation.dataflow.map_dim_shuffle import MapDimShuffle

from dace.transformation.passes import GPUKernelLaunchRestructure
from dace.transformation.dataflow import MapCollapse, MapFusion, TrivialMapElimination
from dace.transformation.passes.to_gpu import ToGPU
from utils import *
from dace.sdfg import utils as sdutil
from utils.move_scalar_to_array import move_scalar_to_array, _tmp_difcoef
import dace
import sympy
from dace.sdfg import infer_types
from dace.sdfg.state import SDFGState, ControlFlowRegion
from dace.sdfg.graph import SubgraphView
from dace.sdfg.propagation import propagate_states
from dace.sdfg.scope import is_devicelevel_gpu_kernel
from dace import config, data as dt, dtypes, Memlet, symbolic
from dace.sdfg import SDFG, nodes, graph as gr
from typing import Set, Tuple, Union, List, Iterable, Dict
import warnings

# Transformations
from dace.transformation.dataflow import MapCollapse, TrivialMapElimination, MapFusion, ReduceExpansion
from dace.transformation.interstate import LoopToMap, RefineNestedAccess
from dace.transformation.subgraph.composite import CompositeFusion
from dace.transformation.subgraph import helpers as xfsh
from dace.transformation import helpers as xfh
from dace.libraries.standard.nodes import TensorTranspose
# Environments
from dace.libraries.blas.environments import intel_mkl as mkl, openblas

# Enumerator
from dace.transformation.estimator.enumeration import GreedyEnumerator
from dace.libraries.standard.nodes import TensorTranspose
# FPGA AutoOpt
from dace.transformation.auto import fpga as fpga_auto_opt

from utils.reductions import LibNode
import copy

import re
import itertools

processed_edges = set()
def _replace_on_lines(sdfg: SDFG, old_name:str, new_name:str, permute_list:List[int]):
    for iterator in [sdfg.all_control_flow_blocks(), sdfg.all_states()]:
        for no in iterator:
            for e in no.parent_graph.in_edges(no) + no.parent_graph.out_edges(no):
                if (old_name, new_name, e) in processed_edges:
                    continue
                processed_edges.add((old_name, new_name, e))
                if e.data is not None:
                    new_assignments = dict()
                    matchlen = len(permute_list)
                    for k, v in e.data.assignments.items():
                        _in = False
                        if old_name in v:
                            #print(f"Replacing {old_name} with {new_name} in {k} -> {v}")
                            _in = True
                        _v = copy.deepcopy(v)
                        pattern = r'(' + re.escape(old_name) + r')\[(.*?)\]'
                        #print(pattern, v)
                        assert k != old_name
                        replaced = False
                        for match in re.finditer(pattern, v):
                            assert match.group(1) == old_name, f"Expected {old_name}, got {match.group(1)}"
                            args_str = match.group(2)  # Get the arguments part as a string
                            old_pattern = re.escape(old_name) + r"\[" + re.escape(args_str) + r"\]"

                            # Split the arguments by commas, ignoring whitespace
                            args = [arg.strip() for arg in args_str.split(',')]

                            # Get permutations of the arguments (only if more than one argument exists)
                            assert len(args) == matchlen, f"Expected {matchlen} arguments, got {len(args), args, args_str, old_pattern, pattern, match}"
                            newargs = []
                            for i in range(len(args)):
                                newargs.append(args[permute_list[i]])

                            # For each permutation, rewrite the function
                            new_expr = f'{new_name}[{", ".join(newargs)}]'
                            _v = re.sub(old_pattern, new_expr, _v, count=1)
                            #print(f"Replaced {old_pattern} with {new_expr} in {k} -> {_v}")
                            replaced = True
                            if _in:
                                assert replaced
                            #raise Exception("UWU")
                        new_assignments[k] = _v
                    e.data.assignments = new_assignments

def _transpose_reduction(sdfg: SDFG, map_param:str = "_for_it_46"):
    for n, g in sdfg.all_nodes_recursive():
        if isinstance(n, dace.nodes.MapEntry) and n.map.params == [map_param]:
            t = g.add_tasklet("stride", inputs={}, outputs={"_out1"}, code="_out1 = 90")
            s = g.add_scalar("scan_reduce_stride", dtype=dace.int64, transient=True)
            g.add_edge(t, "_out1", s, "IN_" + "scan_reduce_stride",
                       dace.Memlet.from_array("scan_reduce_stride", g.sdfg.arrays["scan_reduce_stride"]))
            red_node = LibNode(
            name=f"reduce_{type}",
            input_names=["in_arr", "in_size", "in_stride"],
            output_names=["out"],
            code=f"""
            #ifdef __REDUCE_DEVICE__
            out = strided_reduce_{type}_device(in_arr, in_size, stride);
            #endif
            """ if "address" not in type else f"""
            #ifdef __REDUCE_DEVICE__
            strided_reduce_{type}_device(in_arr, out, in_size);
            #endif
            """,
            )
            l= [e.src for e in g.in_edges(g.exit_node())][0]
            assert isinstance(l, LibNode)
            g.add_node(red_node)
            for ie in g.in_edges(l):
                g.add_edge(ie.src, ie.src_conn, red_node, ie.dst_conn, copy.deepcopy(ie.data))
            for oe in g.out_edges(l):
                g.add_edge(red_node, oe.src_conn, oe.dst, oe.dst_conn, copy.deepcopy(oe.data))
            g.remove_node(l)
            g.add_edge(s, None, red_node, "in_stride", dace.Memlet.from_array("scan_reduce_stride", g.sdfg.arrays["scan_reduce_stride"]))



def permute_index(root: dace.SDFG, sdfg: dace.SDFG, permute_map : Dict[str, List[int]], parent_name_map, orig_map, orig_permute_map):
    if Path(sdfg.name + "_perm_1.sdfgz").exists() and root.label == sdfg.label:
        root = dace.SDFG.from_file(sdfg.name + "_perm_1.sdfgz")
        sdfg = root
    else:
        if root == sdfg:
            s1 = sdfg.add_state_after(sdfg.start_state, "transpose")
            permuted_arrays = dict()
            name_map = dict()
            for arr_name, _arr in list(sdfg.arrays.items()):
                if arr_name in permute_map:
                    permute_indices = permute_map[arr_name]
                    arr: dace.data.Data = _arr

                    arr_shape = arr.shape
                    arr_strides = arr.strides

                    per_shape = []
                    for i in permute_indices:
                        per_shape.append(arr_shape[i])
                    strides = [1]
                    for dim in per_shape[:-1]:
                        strides.append(strides[-1] * dim)
                    if per_shape[0] == 90:
                        #print(strides, per_shape, arr_shape)
                        pass
                    per_arr = dace.data.Array(
                        dtype=arr.dtype,
                        shape=per_shape,
                        strides=strides,
                        transient=True,
                        allow_conflicts=arr.allow_conflicts,
                        storage=arr.storage,
                        alignment=arr.alignment,
                        lifetime=arr.lifetime,
                    )
                    sdfg.add_datadesc("per_" + arr_name, per_arr)
                    assert arr.offset == tuple([0] * len(arr_shape)), f"{arr.offset}"
                    name_map[arr_name] = "per_" + arr_name
            # oldn -> newn is (not permuted) -> (permuted)
            for oldn, newn in name_map.items():
                if oldn == newn:
                    raise Exception(f"Array {oldn} is not permuted")
                olda = s1.add_access(oldn)
                olda.no_name_change = True
                newa = s1.add_access(newn)
                olda.no_name_change = True
                range_dict = dict()
                permute_indices = permute_map[oldn]
                arr_shape = sdfg.arrays[oldn].shape
                per_arr_shape = sdfg.arrays[newn].shape
                #print(oldn, newn, permute_indices, arr_shape)
                for i in range(len(permute_indices)):
                    range_dict[f"i{i}"] = f"0:{arr_shape[i]}"
                map_entry, map_exit = s1.add_map("transpose_impl", range_dict)
                src_access = ", ".join([f"i{i}" for i in range(len(permute_indices))])
                dst_access = ", ".join([f"i{permute_indices[i]}" for i in range(len(permute_indices))])
                map_entry.add_in_connector("IN_" + oldn)
                map_entry.add_out_connector("OUT_" + oldn)
                map_exit.add_in_connector("IN_" + newn)
                map_exit.add_out_connector("OUT_" + newn)
                s1.add_edge(olda, None, map_entry, "IN_" + oldn,
                        dace.Memlet.from_array(oldn, sdfg.arrays[oldn]))
                s1.add_edge(map_exit, "OUT_" + newn, newa, None,
                        dace.Memlet.from_array(newn, sdfg.arrays[newn]))
                t= s1.add_tasklet("assign", {"_in1"}, {"_out1"}, f"_out1 = _in1")
                s1.add_edge(map_entry, "OUT_" + oldn, t, "_in1",
                        dace.Memlet(expr=f"{oldn}[{src_access}]"))
                s1.add_edge(t, "_out1", map_exit, "IN_" + newn,
                        dace.Memlet(expr=f"{newn}[{dst_access}]"))
                # Reverse for rowMajor to columnMajor
                MapDimShuffle.apply_to(sdfg, map_entry=map_entry, options={"parameters": list(reversed(map_entry.map.params))})

                """
                per_shape = sdfg.arrays[newn].shape
                #print(f"To {arr_shape} -> {per_shape}")
                t=TensorTranspose(name=f"transpose_in_{oldn}", axes=permute_indices, alpha=1, beta=0)
                t.implementation = "cuTensor"
                t.schedule = dtypes.ScheduleType.GPU_Device
                #inputs={"_inp_tensor"}, outputs={"_out_tensor"}
                s.add_edge(olda, None, t, "_inp_tensor",
                        dace.Memlet.from_array(oldn, sdfg.arrays[oldn]))
                s.add_edge(t, "_out_tensor", newa, None,
                        dace.Memlet.from_array(newn, sdfg.arrays[newn]))
                """
            final_block = [v for v in sdfg.nodes() if sdfg.out_degree(v) == 0][0]
            s2 = sdfg.add_state_before(final_block, "transpose2")
            for oldn, newn in name_map.items():
                if oldn == newn:
                    raise Exception(f"Array {oldn} is not permuted")
                olda = s2.add_access(oldn)
                olda.no_name_change = True
                newa = s2.add_access(newn)
                newa.no_name_change = True
                range_dict = dict()
                permute_indices = permute_map[oldn]
                arr_shape = sdfg.arrays[oldn].shape
                per_arr_shape = sdfg.arrays[newn].shape
                #print(oldn, newn, permute_indices, arr_shape)
                for i in range(len(permute_indices)):
                    range_dict[f"i{i}"] = f"0:{arr_shape[i]}"
                map_entry, map_exit = s2.add_map("transpose_impl", range_dict)
                src_access = ", ".join([f"i{i}" for i in range(len(permute_indices))])
                dst_access = ", ".join([f"i{permute_indices[i]}" for i in range(len(permute_indices))])
                map_entry.add_in_connector("IN_" + newn)
                map_entry.add_out_connector("OUT_" + newn)
                map_exit.add_in_connector("IN_" + oldn)
                map_exit.add_out_connector("OUT_" + oldn)
                s2.add_edge(newa, None, map_entry, "IN_" + newn,
                        dace.Memlet.from_array(newn, sdfg.arrays[newn]))
                s2.add_edge(map_exit, "OUT_" + oldn, olda, None,
                        dace.Memlet.from_array(oldn, sdfg.arrays[oldn]))

                t= s2.add_tasklet("assign", {"_in1"}, {"_out1"}, f"_out1 = _in1")
                s2.add_edge(map_entry, "OUT_" + newn, t, "_in1",
                        dace.Memlet(expr=f"{newn}[{dst_access}]"))
                s2.add_edge(t, "_out1", map_exit, "IN_" + oldn,
                        dace.Memlet(expr=f"{oldn}[{src_access}]"))
                # Reverse for rowMajor to columnMajor
                MapDimShuffle.apply_to(sdfg, map_entry=map_entry, options={"parameters": list(reversed(map_entry.map.params))})

                """
                rev_permute_indices = list(range(len(permute_indices)))
                arr_shape = sdfg.arrays[oldn].shape
                #print(f"Back {per_shape} -> {arr_shape}")
                t=TensorTranspose(name=f"transpose_out_{oldn}",axes=rev_permute_indices, alpha=1, beta=0)

                #inputs={"_inp_tensor"}, outputs={"_out_tensor"}
                s.add_edge(newa, None, t, "_inp_tensor",
                        dace.Memlet.from_array(newn, sdfg.arrays[newn]))
                s.add_edge(t, "_out_tensor", olda, None,
                        dace.Memlet.from_array(oldn, sdfg.arrays[oldn]))
                """
        else:
            # Replace the array with shape
            name_map = dict()
            arr_add = dict()
            for arr_name, _arr in list(sdfg.arrays.items()):
                if arr_name in permute_map:
                    new_arr_name = parent_name_map[arr_name]
                    permute_indices = permute_map[arr_name]
                    arr: dace.data.Data = _arr
                    arr_shape = arr.shape

                    per_shape = []
                    if len(arr.shape) != len(permute_indices):
                        continue
                    for i in permute_indices:
                        #print(arr_shape, permute_indices, arr_name, permute_map)
                        per_shape.append(arr_shape[i])
                    strides = [1]
                    for dim in per_shape[:-1]:
                        strides.append(strides[-1] * dim)
                    per_arr = dace.data.Array(
                        dtype=arr.dtype,
                        shape=per_shape,
                        strides=strides,
                        transient=arr.transient,
                        allow_conflicts=arr.allow_conflicts,
                        storage=arr.storage,
                        alignment=arr.alignment,
                        lifetime=arr.lifetime,
                    )
                    sdfg.remove_data(arr_name, validate=False)
                    sdfg.add_datadesc(new_arr_name, per_arr)
                    assert arr.offset == tuple([0] * len(arr_shape)), f"{arr.offset}"

                    name_map[arr_name] = new_arr_name

        #sdfg.save("t1.sdfgz", compress=True)



        for g in sdfg.all_nodes_between(s1, s2) if sdfg == root else sdfg.all_control_flow_regions():
            for s in g.all_states() if not isinstance(g, SDFGState) else [g]:
                for n in s.nodes():
                    if isinstance(n, dace.nodes.NestedSDFG):
                        new_permute_map = dict()
                        for ie in s.in_edges(n):
                            src_name = ie.data.data
                            dst_name = ie.dst_conn
                            if src_name in permute_map:
                                new_permute_map[src_name] = permute_map[src_name]
                            if ie.dst_conn in name_map:
                                ie.dst.remove_in_connector(ie.dst_conn)
                                ie.dst.add_in_connector(name_map[ie.dst_conn], force=True)
                                ie.dst_conn = name_map[ie.dst_conn]
                                assert ie.dst == n
                                if ie.dst_conn not in n.in_connectors:
                                    n.add_out_connector(ie.dst_conn, force=True)

                        for oe in s.out_edges(n):
                            dst_name = oe.src_conn
                            src_name = oe.data.data
                            if dst_name in permute_map:
                                new_permute_map[dst_name] = permute_map[dst_name]
                            if oe.src_conn in name_map:
                                oe.src.remove_out_connector(oe.src_conn)
                                oe.src.add_out_connector(name_map[oe.src_conn], force=True)
                                oe.src_conn = name_map[oe.src_conn]
                                assert oe.src == n
                                if oe.src_conn not in n.out_connectors:
                                    n.add_out_connector(oe.src_conn, force=True)

                        permute_index(root, n.sdfg, new_permute_map, name_map, orig_map, orig_permute_map)



        final_block = [v for v in sdfg.nodes() if sdfg.out_degree(v) == 0][0]
        for g in sdfg.all_nodes_between(s1, s2) if sdfg == root else sdfg.all_control_flow_regions():
            if sdfg == root and (s == sdfg.start_block or s == final_block):
                continue
            for s in g.all_states() if not isinstance(g, SDFGState) else [g]:
                for n in s.nodes():
                    if isinstance(n, dace.nodes.AccessNode):
                        if n.data in name_map:
                            n.data = name_map[n.data]
                for e in s.edges():
                    if e.data.data in name_map:
                        if e.dst_conn == "IN_" + e.data.data:
                            e.dst_conn = "IN_" + name_map[e.data.data]
                            e.dst.remove_in_connector("IN_" + e.data.data)
                            e.dst.add_in_connector("IN_" + name_map[e.data.data], force=True)
                        if e.src_conn == "OUT_" + e.data.data:
                            e.src_conn = "OUT_" + name_map[e.data.data]
                            e.src.remove_out_connector("OUT_" + e.data.data)
                            e.src.add_out_connector("OUT_" + name_map[e.data.data], force=True)
                        oldn = e.data.data
                        e.data.data = name_map[e.data.data]
                        new_subset = []
                        permute_indices = permute_map[oldn]
                        #print(e.data.data, new_subset, e.data.subset)
                        try:
                            for i in range(len(permute_indices)):
                                new_subset.append(e.data.subset[permute_indices[i]])
                            e.data.subset = dace.subsets.Range(new_subset)
                        except Exception as e:
                            sdfg.save("uwu.sdfg")
                            raise e

    if root.label == sdfg.label:
        root.save(root.name + "_perm_1.sdfgz", compress=True)

    #print("Replacing names on interstate edges")

    for old_name, new_name in orig_map.items():
        assert old_name in orig_permute_map or new_name in orig_permute_map, f"Array {old_name} or {new_name} not in permute map"
        perm = orig_permute_map[old_name] if old_name in orig_permute_map else orig_permute_map[new_name]
        #print(old_name, " -> ", new_name)
        _replace_on_lines(sdfg, old_name, new_name, perm)

    for n, g in sdfg.all_nodes_recursive():
        if isinstance(n, dace.nodes.NestedSDFG):
            for old_name, new_name in orig_map.items():
                assert old_name in orig_permute_map or new_name in orig_permute_map, f"Array {old_name} or {new_name} not in permute map"
                perm = orig_permute_map[old_name] if old_name in orig_permute_map else orig_permute_map[new_name]
                #print(old_name, " -> ", new_name)
                _replace_on_lines(n.sdfg, old_name, new_name, perm)

    #raise Exception("UWU")
    # Need to fix node validation errors:
    # e.g.:
    # dace.sdfg.validation.InvalidSDFGNodeError: Node validation failed: Missing symbols on nested SDFG:
    # ['gpu___CG_p_patch__CG_verts__m_cell_blk', 'gpu___CG_p_patch__CG_verts__m_cell_idx'] (at state single_state_body, node loop_body)
    # This happens because connector missing or smth uwu :(

def permute_maps(sdfg: dace.SDFG, permute_map : Dict[str, List[int]]):
    for s, g in sdfg.all_nodes_recursive():
        if isinstance(s, dace.SDFGState):
            for n in s.nodes():
                if isinstance(n, dace.nodes.MapEntry):
                    old_params = n.map.params
                    new_params = []
                    if n.map.label in permute_map:
                        for j in range(len(permute_map[n.map.label])):
                            new_params.append(old_params[permute_map[n.map.label][j]])
                        MapDimShuffle.apply_to(sdfg, map_entry=n, options={"parameters": new_params})

def permute_all_maps(sdfg: dace.SDFG, permute_list):
    for s, g in sdfg.all_nodes_recursive():
        if isinstance(s, dace.SDFGState):
            for n in s.nodes():
                if isinstance(n, dace.nodes.MapEntry):
                    old_params = n.map.params
                    new_params = []
                    if len(n.map.range) == len(permute_list):
                        for j in range(len(permute_list)):
                            new_params.append(old_params[permute_list[j]])
                        MapDimShuffle.apply_to(sdfg, map_entry=n, options={"parameters": new_params})

def permute_all_maps_depending_on_input(sdfg: dace.SDFG, permute_list, inout_set):
    for n, g in sdfg.all_nodes_recursive():
        if isinstance(n, dace.nodes.MapEntry):
            if inout_set is not None:
                inputs_and_outputs = set([e.src.data for e in g.in_edges(n) if isinstance(e.src, dace.nodes.AccessNode)]) | set([e.dst.data for e in g.out_edges(g.exit_node(n)) if isinstance(e.dst, dace.nodes.AccessNode)])
                inout_match = inputs_and_outputs.intersection(inout_set)

                if len(inout_match) == 0:
                    continue

            old_params = n.map.params
            new_params = []
            local_permute_list = copy.deepcopy(permute_list)
            if len(n.map.range) == 1:
                continue
            if len(n.map.range) == len(local_permute_list):
                for j in range(len(local_permute_list)):
                    new_params.append(old_params[local_permute_list[j]])
                #print("Permuting map", n.map.label, "with", local_permute_list, "from", old_params, "to", new_params)
                MapDimShuffle.apply_to(g.sdfg, verify=True, map_entry=n, options={"parameters": new_params})
