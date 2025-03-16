from pathlib import Path
import dace
import shutil
import os
import math
import ast
import copy
from dace.transformation.interstate import LoopToMap, ContinueToCondition
from dace.transformation.dataflow import MapCollapse
from dace.transformation.passes import (
    SymbolPropagation,
    StructToContainerGroups,
    DuplicateConstArrays,
)
from dace.sdfg.state import LoopRegion, ConditionalBlock, ControlFlowRegion
from dace.libraries.standard import CodeLibraryNode
from dace.properties import make_properties, Property

use_cache = True
run_benchmark = False
save_steps = False

# Load SDFG
sdfg = dace.SDFG.from_file("/home/primrose/Work/IconGrounds/icon-artifacts/velocity/velocity.sdfgz")
sdfg.validate()

################################################################################
### Fixing Functions
################################################################################


# Put host data back to CPU_Heap (library outputs are transient and are always put to GPU)
def put_host_prefixed_data_back_to_cpu(sdfg):
    #for arr_name, arr in sdfg.arrays.items():
    #    if arr_name.startswith("host_"):
    #        arr.storage = dace.dtypes.StorageType.CPU_Heap
    #    if not arr.transient and not isinstance(arr, dace.data.View):
    #        arr.storage = dace.dtypes.StorageType.CPU_Heap
    pass

def scalar_to_length_one_array(sdfg: dace.SDFG):
    scalar_to_arr_map = {}
    add_arrays = set()
    for arr_name, arr in sdfg.arrays.items():
        if isinstance(arr, dace.data.Scalar):
            arr.storage = dace.dtypes.StorageType.Register
            na = dace.data.Array(
                dtype=arr.dtype,
                shape=[1],
                storage=dace.dtypes.StorageType.GPU_Global,
                transient=True,
                allow_conflicts=arr.allow_conflicts,
                lifetime=arr.lifetime,
                strides=[1],
                offset=[0],
            )
            add_arrays.add(("gpu_" + arr_name, na))
            scalar_to_arr_map[arr_name] = "gpu_" + arr_name
            if arr.transient is False:
                sstate = sdfg.start_state
                an0 = sstate.add_access(arr_name)
                an1 = sstate.add_access("gpu_" + arr_name)
                sstate.add_edge(an0, None, an1, None, dace.memlet.Memlet(expr=arr_name))
    for arr_name, arr in add_arrays:
        if arr_name not in sdfg.arrays:
            sdfg.add_datadesc(arr_name, arr)
        else:
            sdfg.remove_data(arr_name, validate=False)
            sdfg.add_datadesc(arr_name, arr)
    return scalar_to_arr_map


def replace_connectors_and_data(
    state: dace.SDFGState, node: dace.nodes.MapExit, old_name: str, new_name: str
):
    map_entry = [
        n
        for n in state.nodes()
        if isinstance(n, dace.nodes.MapEntry) and n.map == node.map
    ][0]
    edges_to_rm = set()
    edges_to_add = set()
    for e in state.all_edges(*state.all_nodes_between(map_entry, node)):
        if e.src == map_entry:
            continue
        edges_to_rm.add(e)

        if e.src_conn == "IN_" + old_name:
            src_conn = "IN_" + new_name
        else:
            src_conn = e.src_conn

        if e.dst_conn == "OUT_" + old_name:
            dst_conn = "OUT_" + new_name
        else:
            dst_conn = e.dst_conn

        if e.data.data == old_name:
            mem = dace.memlet.Memlet(expr=new_name)
        else:
            mem = copy.deepcopy(e.data)

        dst = e.dst
        edges_to_add.add((e.src, src_conn, dst, dst_conn, mem))

    for e in edges_to_rm:
        state.remove_edge(e)
    for e in edges_to_add:
        state.add_edge(*e)


def replace_gpu_scalar_outputs(sdfg: dace.SDFG, scalar_to_arr_map: dace.Dict[str, str]):
    for state in sdfg.states():
        for node in state.nodes():
            if isinstance(node, dace.nodes.NestedSDFG):
                replace_gpu_scalar_outputs(node.sdfg, scalar_to_arr_map)
            edges_to_rm = set()
            edges_to_add = set()
            d = dict()
            if (
                isinstance(node, dace.nodes.MapExit)
                and node.map.schedule == dace.ScheduleType.GPU_Device
            ):
                for e in state.out_edges(node):
                    if isinstance(e.dst, dace.nodes.AccessNode):
                        if (
                            isinstance(sdfg.arrays[e.dst.data], dace.data.Scalar)
                            and e.dst.data in scalar_to_arr_map
                        ):
                            an = state.add_access(scalar_to_arr_map[e.dst.data])
                            edges_to_add.add(
                                (
                                    e.src,
                                    e.src_conn,
                                    an,
                                    None,
                                    dace.memlet.Memlet(
                                        expr=scalar_to_arr_map[e.dst.data]
                                    ),
                                )
                            )
                            edges_to_add.add(
                                (
                                    an,
                                    None,
                                    e.dst,
                                    e.dst_conn,
                                    dace.memlet.Memlet(expr=e.dst.data),
                                )
                            )
                            edges_to_rm.add(e)
                            d[node, e.dst.data] = scalar_to_arr_map[e.dst.data]

            for e in edges_to_rm:
                state.remove_edge(e)
            for e in edges_to_add:
                state.add_edge(*e)

            for (node, src), dst in d.items():
                replace_connectors_and_data(state, node, src, dst)


def make_array_loop_local(sdfg: dace.SDFG, array_name, loop_name):
    """
    Renames an array in the loop, so it's only accessed in the loop. You need to make sure that the array is not accessed outside of the loop (or written before read outside of the loop).
    """
    # Find the loop
    loop = None
    for node, _ in sdfg.all_nodes_recursive():
        if isinstance(node, LoopRegion) and node.label == loop_name:
            loop = node
            break
    assert loop is not None
    # Creat a new array
    #if array_name in sdfg.arrays:
    array = sdfg.arrays[array_name]
    new_name, _ = sdfg.add_array(
        f"{array_name}_local",
        shape=array.shape,
        dtype=array.dtype,
        storage=array.storage,
        location=array.location,
        transient=array.transient,
        strides=array.strides,
        offset=array.offset,
        lifetime=array.lifetime,
        debuginfo=array.debuginfo,
        allow_conflicts=array.allow_conflicts,
        total_size=array.total_size,
        find_new_name=True,
        alignment=array.alignment,
        may_alias=array.may_alias,
    )
    # Replace each occurrence of the array in the loop
    loop.replace(array_name, new_name)


# Does what the title says
def if_map_has_direct_view_access_nodes_inside_put_into_nested_sdfg(
    sdfg: dace.SDFG, labels
):
    for state in sdfg.states():
        for node in state.nodes():
            if (state.label, node.label) in labels:
                if isinstance(node, dace.nodes.MapEntry):
                    nodes = list(state.all_nodes_between(node, state.exit_node(node)))
                    in_data = set()
                    out_data = set()
                    hasviews = False
                    for oe in state.out_edges(node):
                        if isinstance(oe.dst, dace.nodes.AccessNode) and isinstance(
                            sdfg.arrays[oe.dst.data], dace.data.View
                        ):
                            hasviews = True
                    if not hasviews:
                        continue

                    for oe in state.out_edges(node):
                        in_data.add(oe.data.data)
                    for ie in state.in_edges(state.exit_node(node)):
                        out_data.add(ie.data.data)

                    nested_sdfg = dace.SDFG("nested")
                    nested_state = nested_sdfg.add_state("nested_state")

                    for id in set.union(in_data, out_data):
                        desc = copy.deepcopy(sdfg.arrays[id])
                        if not isinstance(desc, dace.data.View):
                            desc.transient = False
                        nested_sdfg.add_datadesc(id, desc)

                    node_map = dict()
                    for _n in nodes:
                        if _n != node and _n != state.exit_node(node):
                            if _n not in node_map:
                                __n = copy.deepcopy(_n)
                                nested_state.add_node(__n)
                                node_map[_n] = __n

                    for edge in state.out_edges(node):
                        nnode = node_map[edge.dst]
                        an = nested_state.add_access(edge.data.data)
                        nested_state.add_edge(
                            an, None, nnode, edge.dst_conn, copy.deepcopy(edge.data)
                        )

                    for edge in state.in_edges(state.exit_node(node)):
                        nnode = node_map[edge.src]
                        an = nested_state.add_access(edge.data.data)
                        nested_state.add_edge(
                            nnode, edge.src_conn, an, None, copy.deepcopy(edge.data)
                        )

                    for e in state.all_edges(*nodes):
                        if e.src != node and e.dst != state.exit_node(node):
                            nsrc = node_map[e.src]
                            ndst = node_map[e.dst]
                            nested_state.add_edge(
                                nsrc,
                                e.src_conn,
                                ndst,
                                e.dst_conn,
                                copy.deepcopy(e.data),
                            )
                            if isinstance(nsrc, dace.nodes.AccessNode):
                                if nsrc.data not in nested_sdfg.arrays:
                                    nested_sdfg.add_datadesc(
                                        nsrc.data, copy.deepcopy(sdfg.arrays[nsrc.data])
                                    )
                            if isinstance(ndst, dace.nodes.AccessNode):
                                if ndst.data not in nested_sdfg.arrays:
                                    nested_sdfg.add_datadesc(
                                        ndst.data, copy.deepcopy(sdfg.arrays[ndst.data])
                                    )

                    nsdfg = state.add_nested_sdfg(nested_sdfg, state, in_data, out_data)
                    edges_to_add = set()
                    for oe in state.out_edges(node):
                        edges_to_add.add(
                            (
                                oe.src,
                                oe.src_conn,
                                nsdfg,
                                oe.data.data,
                                dace.memlet.Memlet(expr=oe.data.data),
                            )
                        )
                    for ie in state.in_edges(state.exit_node(node)):
                        edges_to_add.add(
                            (
                                nsdfg,
                                ie.data.data,
                                ie.dst,
                                ie.dst_conn,
                                dace.memlet.Memlet(expr=ie.data.data),
                            )
                        )

                    for e in edges_to_add:
                        state.add_edge(*e)
                    for n in nodes:
                        state.remove_node(n)
            if isinstance(node, dace.nodes.NestedSDFG):
                if_map_has_direct_view_access_nodes_inside_put_into_nested_sdfg(
                    node.sdfg, labels
                )
            if isinstance(node, dace.nodes.MapEntry):
                pass


# Set default map schedules to GPU device on top-level SDFG
def set_default_map_to_gpu(sdfg):
    for s in sdfg.states():
        for n in s.nodes():
            if isinstance(n, dace.nodes.NestedSDFG):
                pass
            if isinstance(n, dace.nodes.MapEntry):
                if n.map.schedule == dace.ScheduleType.Default:
                    n.map.schedule = dace.ScheduleType.GPU_Device


# Pass levmask as an argument if it is a symbol in the SDFG but not passed as an array
def pass_name_as_array_not_as_symbol(
    rootsdfg, sdfg: dace.SDFG, nested_sdfg_node: dace.nodes.Node, name: str
):
    has_name = False
    for s in sdfg.states():
        for n in s.nodes():
            if isinstance(n, dace.nodes.NestedSDFG):
                pass_name_as_array_not_as_symbol(rootsdfg, n.sdfg, n, name)
        for n in s.nodes():
            if isinstance(n, dace.nodes.AccessNode):
                if n.data == name:
                    has_name = True
        for e in s.edges():
            if isinstance(e.data, dace.memlet.Memlet):
                if e.data.data == name:
                    has_name = True

    if has_name:
        assert name in sdfg.arrays
    if not has_name:
        # If does not have the name but is defined as a symbol
        # Then it is sued on interstate edge prob and need to pass it
        if name in sdfg.arrays:
            sdfg.remove_data(name)
        if name in sdfg.symbols:
            assert sdfg != rootsdfg
            arr = copy.deepcopy(rootsdfg.arrays[name])
            arr.transient = False
            sdfg.remove_symbol(name)
            sdfg.add_datadesc(name, arr)
            an = sdfg.parent.add_access(name)
            # sdfg.parent.add_edge(an, None, _n, name, dace.memlet.Memlet(expr=name))
            entry_nodes = []
            enode = nested_sdfg_node
            while enode is not None:
                entry_nodes.append(enode)
                enode = sdfg.parent.entry_node(enode)

            entry_chain = list(reversed(entry_nodes))

            sdfg.parent.add_edge(
                an, None, entry_chain[0], f"IN_{name}", dace.memlet.Memlet(expr=name)
            )
            entry_chain[0].add_in_connector(f"IN_{name}")

            for i in range(len(entry_chain) - 2):
                sdfg.parent.add_edge(
                    entry_chain[i],
                    f"OUT_{name}",
                    entry_chain[i + 1],
                    f"IN_{name}",
                    dace.memlet.Memlet(expr=name),
                )
                entry_chain[i].add_out_connector(f"OUT_{name}")
                entry_chain[i + 1].add_in_connector(f"IN_{name}")

            # Last node is the nested SDFG
            sdfg.parent.add_edge(
                entry_chain[-2],
                f"OUT_{name}",
                entry_chain[-1],
                f"{name}",
                dace.memlet.Memlet(expr=name),
            )
            entry_chain[-2].add_out_connector(f"OUT_{name}")
            entry_chain[-1].add_in_connector(f"{name}")

            if save_steps:
                sdfg.save(f"{name}_passed.sdfgz", compress=True)


def set_scalar_storage_to_register(sdfg: dace.SDFG):
    for arr_name, arr in sdfg.arrays.items():
        if isinstance(arr, dace.data.Scalar):
            arr.storage = dace.dtypes.StorageType.Register


# Also iterates to nested SDFGs if scope is None and storage default, put to GPU global
def set_top_level_default_storage_to_gpu_global(sdfg):
    for state in sdfg.states():
        for n in state.nodes():
            if isinstance(n, dace.nodes.NestedSDFG):
                set_top_level_default_storage_to_gpu_global(n.sdfg)
            if isinstance(n, dace.nodes.AccessNode):
                arr = sdfg.arrays[n.data]
                if (
                    arr.storage == dace.dtypes.StorageType.Default
                    and state.scope_dict()[n] is None
                ):
                    arr.storage = dace.dtypes.StorageType.GPU_Global


# Pad access node between map and view
def pad_access_node_between_map_and_view(sdfg):
    for state in sdfg.states():
        for n in state.nodes():
            if isinstance(n, dace.nodes.NestedSDFG):
                pad_access_node_between_map_and_view(n.sdfg)
            if isinstance(n, dace.nodes.AccessNode) and isinstance(
                sdfg.arrays[n.data], dace.data.View
            ):
                assert state.in_degree(n) == 1
                for ie in state.in_edges(n):
                    if isinstance(ie.src, dace.nodes.MapEntry):
                        d = ie.data.data
                        an = state.add_access(d)
                        state.add_edge(an, None, n, "views", copy.deepcopy(ie.data))
                        state.add_edge(
                            ie.src, ie.src_conn, an, None, dace.memlet.Memlet(expr=d)
                        )
                        state.remove_edge(ie)


def rename_symbol_connector(sdfg: dace.SDFG, name: str):
    for state in sdfg.states():
        for n in state.nodes():
            if isinstance(n, dace.nodes.NestedSDFG):
                rename_symbol_connector(n.sdfg, name)
            # If AccessNode -> MapEntry, where the data is scalar and is used to create a symbol
            # Then change the in connector name and change all occurences within the area
            if isinstance(n, dace.nodes.AccessNode):
                for oe in state.out_edges(n):
                    if (
                        isinstance(oe.dst, dace.nodes.MapEntry)
                        and name in oe.dst.in_connectors
                        and n.data == name
                        and isinstance(sdfg.arrays[oe.data.data], dace.data.Scalar)
                    ):
                        oe.dst.remove_in_connector(name)
                        oe.dst.add_in_connector("__" + name)
                        oe.dst_conn = "__" + name

                        # If state.replace does not work, change this
                        for _n in list(
                            state.all_nodes_between(oe.dst, state.exit_node(oe.dst))
                        ) + [oe.dst, state.exit_node(oe.dst)]:
                            if isinstance(_n, dace.nodes.MapEntry):
                                new_params = [
                                    "__" + name if p == name else p
                                    for p in _n.map.params
                                ]
                                new_subsets = [
                                    (
                                        (
                                            b.subs(name, "__" + name)
                                            if isinstance(b, dace.symbolic.SymExpr)
                                            else b
                                        ),
                                        (
                                            e.subs(name, "__" + name)
                                            if isinstance(e, dace.symbolic.SymExpr)
                                            else e
                                        ),
                                        (
                                            s.subs(name, "__" + name)
                                            if isinstance(s, dace.symbolic.SymExpr)
                                            else s
                                        ),
                                    )
                                    for (b, e, s) in _n.map.range
                                ]
                                _n.map.params = new_params
                                _n.map.range = dace.subsets.Range(new_subsets)
                            if (
                                isinstance(_n, dace.nodes.AccessNode)
                                and _n.data == name
                            ):
                                _n.data = "__" + name

                        # for _e in list(*state.all_nodes_between(oe.dst, state.exit_node(oe.dst))):
                        # If it used in interstate edges it will crash, implement it here.

                        if save_steps:
                            sdfg.save("reconnectored_velocity.sdfgz", compress=True)


def set_view_lifetime_to_scope(sdfg: dace.SDFG):
    for state in sdfg.states():
        for n in state.nodes():
            if isinstance(n, dace.nodes.NestedSDFG):
                set_view_lifetime_to_scope(n.sdfg)
    for arr in sdfg.arrays.values():
        if isinstance(arr, dace.data.View):
            arr.lifetime = dace.dtypes.AllocationLifetime.Scope


def symbollify_gpu_scalars(sdfg: dace.SDFG):
    gpu_scalars = [
        k
        for k, v in sdfg.arrays.items()
        if isinstance(v, dace.data.Scalar)
        and v.storage == dace.dtypes.StorageType.GPU_Global
    ]

    for _cfg in sdfg.nodes():
        if isinstance(_cfg, ControlFlowRegion):
            for cfg in _cfg.nodes():
                if isinstance(cfg, ConditionalBlock):
                    print("CB", cfg.label)
                    if cfg.label == "Conditional_l_467_c_467":
                        assert "_if_cond_16" in gpu_scalars, f"{gpu_scalars}"
                        raise Exception("uwu")
                    for codeblock, region in cfg.branches:
                        needed_syms = set()
                        if codeblock is not None:
                            if codeblock.code is not None:
                                for gs in gpu_scalars:

                                    if gs in codeblock.code:
                                        codeblock.code = codeblock.code.replace(
                                            gs, f"__{gs}"
                                        )
                                        needed_syms.add(gs, f"__{gs}")

                        if cfg.label == "Conditional_l_467_c_467":
                            assert len(needed_syms) > 0, f"{needed_syms}"

                        if len(needed_syms) > 0:
                            assignments = {}
                            for src, dst in needed_syms:
                                assignments[dst] = f"{src}[0]"
                            sdfg.add_state_before(
                                region, "map_views", assignments=assignments
                            )
                else:
                    print("N", cfg.label)
                    if cfg.label == "Conditional_l_467_c_467":
                        raise Exception(f"uwu, {type(cfg)}")
        cfg = _cfg
        if isinstance(cfg, ConditionalBlock):
            print("CB2", cfg.label)
            if cfg.label == "Conditional_l_467_c_467":
                assert "_if_cond_16" in gpu_scalars, f"{gpu_scalars}"
                raise Exception("uwu")
            for codeblock, region in cfg.branches:
                needed_syms = set()
                if codeblock is not None:
                    if codeblock.code is not None:
                        for gs in gpu_scalars:

                            if gs in codeblock.code:
                                codeblock.code = codeblock.code.replace(gs, f"__{gs}")
                                needed_syms.add(gs, f"__{gs}")

                if cfg.label == "Conditional_l_467_c_467":
                    assert len(needed_syms) > 0, f"{needed_syms}"

                if len(needed_syms) > 0:
                    assignments = {}
                    for src, dst in needed_syms:
                        assignments[dst] = f"{src}[0]"
                    sdfg.add_state_before(region, "map_views", assignments=assignments)
        else:
            print("N2", cfg.label)
            if cfg.label == "Conditional_l_467_c_467":
                raise Exception(f"uwu, {type(cfg)}")

    for e in sdfg.edges():
        needed_syms = set()
        if e.data is not None:
            for dst, src in e.data.assignments.items():
                for gs in gpu_scalars:
                    if gs in src.split():
                        needed_syms.add((gs, f"__{gs}"))
                        e.data.assignments[dst] = e.data.assignments[dst].replace(
                            gs, f"__{gs}"
                        )
            codeblock = e.data.condition
            if codeblock is not None:
                if codeblock.code is not None:
                    for gs in gpu_scalars:
                        if gs in codeblock.code:
                            codeblock.code = codeblock.code.replace(gs, f"__{gs}")
                            needed_syms.add(gs, f"__{gs}")
        if len(needed_syms) > 0:
            assignments = {}
            for src, dst in needed_syms:
                assignments[dst] = f"{src}[0]"
            sdfg.add_state_after(e.src, "map_views", assignments=assignments)

    for s in sdfg.states():
        for n in s.nodes():
            if isinstance(n, dace.nodes.NestedSDFG):
                symbollify_gpu_scalars(n.sdfg)


def rename_on_if_conds(sdfg: dace.SDFG, src: str, dst: str):
    gpu_host_name_map = {src: dst}

    for node, parent in sdfg.all_nodes_recursive():
        if not isinstance(node, ConditionalBlock):
            continue

        for b in node.branches:
            if b[0] is None:
                continue
            if isinstance(b[0].code, list):
                for i, el in enumerate(b[0].code):
                    if isinstance(el, str):
                        for src, dst in gpu_host_name_map.items():
                            b[0].code[i] = b[0].code[i].replace(src, dst)
                    else:

                        def replace_x_with_y(expr: ast.Expr, repl_dict) -> ast.Expr:
                            expr_str = ast.unparse(expr).strip()
                            for src, dst in repl_dict.items():
                                modified_str = expr_str.replace(src, dst)
                            return ast.parse(modified_str, mode="eval").body

                        b[0].code[i] = replace_x_with_y(b[0].code[i], gpu_host_name_map)
            else:
                assert isinstance(b[0].code, str)
                for src, dst in gpu_host_name_map.items():
                    b[0].code = b[0].code.replace(src, dst)


def move_map_to_cpu(
    sdfg: dace.SDFG,
    state: dace.SDFGState,
    map_exit: dace.nodes.MapExit,
    node: dace.nodes.AccessNode,
):
    return
    map_entry = [
        v
        for v in state.nodes()
        if isinstance(v, dace.nodes.MapEntry) and v.map == map_exit.map
    ][0]
    if map_entry.map.schedule == dace.ScheduleType.GPU_Device:
        map_entry.map.schedule = dace.ScheduleType.Sequential
        diff_map = {}
        for e in state.in_edges(map_entry):
            if isinstance(e.src, dace.nodes.AccessNode):
                # 1. For all input of MapEntry update the in and out connectors to be
                #    Host prefixed of the data
                if (
                    sdfg.arrays[e.src.data].storage
                    == dace.dtypes.StorageType.GPU_Global
                ):
                    diff_map[e.src.data] = "host_" + e.src.data

                src = e.src
                while src is not None:
                    srcdata = src.data
                    # If storage is GPU storage, and host not in array add
                    if (
                        sdfg.arrays[srcdata].storage
                        == dace.dtypes.StorageType.GPU_Global
                    ):
                        if f"host_{src.data}" not in sdfg.arrays:
                            arr2 = copy.deepcopy(sdfg.arrays[src.data])
                            arr2.storage = dace.dtypes.StorageType.CPU_Heap
                            sdfg.add_datadesc(f"host_{src.data}", arr2)

                    if (
                        sdfg.arrays[srcdata].storage
                        == dace.dtypes.StorageType.GPU_Global
                    ):
                        if (
                            isinstance(src, dace.nodes.AccessNode)
                            and not isinstance(sdfg.arrays[src.data], dace.data.View)
                            and state.in_degree(src) != 0
                        ):
                            # Insert a copy
                            for __e in state.out_edges(src):
                                assert __e.src_conn is None
                                an = state.add_access(f"host_{src.data}")

                                state.add_edge(
                                    src, None, an, None, copy.deepcopy(__e.data)
                                )
                                state.add_edge(
                                    an,
                                    None,
                                    __e.dst,
                                    __e.dst_conn,
                                    copy.deepcopy(__e.data),
                                )
                                state.remove_edge(__e)
                        else:
                            if isinstance(sdfg.arrays[src.data], dace.data.View):
                                for __e in state.out_edges(src):
                                    if __e.data.data == srcdata:
                                        assert __e.src_conn is None
                                        an = state.add_access(f"host_{src.data}")

                                        d = copy.deepcopy(__e.data)
                                        d.data = an.data
                                        ke = state.add_edge(
                                            an, None, __e.dst, __e.dst_conn, d
                                        )
                                        for ie in state.in_edges(src):
                                            state.add_edge(
                                                ie.src,
                                                ie.src_conn,
                                                an,
                                                ie.dst_conn,
                                                copy.deepcopy(ie.data),
                                            )
                                            if ie.dst_conn not in an.in_connectors:
                                                an.add_in_connector(ie.dst_conn)
                                            state.remove_edge(ie)
                                        ke.data.data = f"host_{src.data}"
                                        state.remove_edge(__e)
                                        state.remove_node(src)
                                        src = an
                            else:
                                for __e in state.out_edges(src):
                                    if __e.data.data == srcdata:
                                        assert __e.src_conn is None
                                        an = state.add_access(f"host_{src.data}")

                                        d = copy.deepcopy(__e.data)
                                        d.data = an.data
                                        state.add_edge(src, None, an, None, d)
                                        d = copy.deepcopy(__e.data)
                                        d.data = an.data
                                        state.add_edge(
                                            an, None, __e.dst, __e.dst_conn, d
                                        )
                                        state.remove_edge(__e)

                    if len(state.in_edges(src)) == 1 and isinstance(
                        state.in_edges(src)[0].src, dace.nodes.AccessNode
                    ):
                        src = state.in_edges(src)[0].src
                    else:
                        src = None

        for e in state.all_edges(*state.all_nodes_between(map_entry, map_exit)):
            if e.data.data in diff_map:
                e.data.data = diff_map[e.data.data]

        # Hack, fix the memlets that have been turned incorrect
        if state.label == "_state_l328_c328":
            for e in state.edges():
                src, src_conn, dst, dst_conn, data = e
                if (
                    state.out_degree(dst) == 0
                    and isinstance(sdfg.arrays[dst.data], dace.data.View)
                    and dst_conn == "views"
                ):
                    e.data = dace.memlet.Memlet(expr=e.data.data)
                    state.remove_node(dst)
                    if state.out_degree(src) == 0:
                        state.remove_node(src)


def put_scalars_to_host(sdfg: dace.SDFG):
    return
    for arr in sdfg.arrays.values():
        if isinstance(arr, dace.data.Scalar):
            if arr.transient:
                arr.storage = dace.dtypes.StorageType.Register
            else:
                arr.storage = dace.dtypes.StorageType.CPU_Heap
    for state in sdfg.states():
        for node in state.nodes():
            if isinstance(node, dace.nodes.NestedSDFG):
                put_scalars_to_host(node.sdfg)
            if isinstance(node, dace.nodes.AccessNode):
                arr = sdfg.arrays[node.data]
                if isinstance(arr, dace.data.Scalar):
                    for e in state.in_edges(node):
                        if isinstance(e.src, dace.nodes.MapExit):
                            # Map writing to scalar
                            move_map_to_cpu(sdfg, state, e.src, node)


@make_properties
class MaxReduce(CodeLibraryNode):
    code = Property(dtype=str, default="", allow_none=False)

    def __init__(self, name, input_names, output_names, code):
        super().__init__(name=name, input_names=input_names, output_names=output_names)
        self.code = code

    def generate_code(self, inputs, outputs):
        return self.code


def replace_loop_with_max_reduction(sdfg: dace.SDFG, loop_name: str):
    loop_node = None
    for node, state in sdfg.all_nodes_recursive():
        if node.label == loop_name:
            loop_node = node
            break
    assert loop_node is not None
    red_state = sdfg.add_state_before(loop_node)
    red_lib_node = MaxReduce(
        name="max_reduce",
        input_names=["in_arr"],
        output_names=[],
        code="""
        // Max reduce
        // TODO: Implement max reduce
        // End of max reduce
        """,
    )
    red_lib_node.schedule = dace.ScheduleType.GPU_Device
    red_state.add_node(red_lib_node)
    red_state.add_edge(
        red_state.add_read("vcflmax"),
        None,
        red_lib_node,
        "in_arr",
        dace.Memlet("vcflmax"),
    )

    post_state = sdfg.add_state_after(loop_node)
    sdfg.remove_node(loop_node)
    sdfg.add_edge(red_state, post_state, dace.InterstateEdge())


# Replace cpp with cu
def replace_cpp_with_cu(directory):
    directory = Path(directory)  # Convert to Path object
    for file in directory.rglob("*.cpp"):  # Find all .cpp files
        new_name = file.with_suffix(".cu")  # Change the suffix to .cu
        file.rename(new_name)  # Rename the file
        print(f"Renamed: {file} -> {new_name}")
    for file in directory.rglob("*.cc"):
        new_name = file.with_suffix(".cu")  # Change the suffix to .cu
        file.rename(new_name)  # Rename the file
        print(f"Renamed: {file} -> {new_name}")


################################################################################
### Apply Optimizations
################################################################################


# Apply transformations
if Path("gpu_pipe_stage1.sdfg").exists() and use_cache:
    sdfg = dace.SDFG.from_file("gpu_pipe_stage1.sdfg")
else:
    if Path("A.sdfgz").exists() and use_cache:
        sdfg = dace.SDFG.from_file("A.sdfgz")
    else:
        sdfg.apply_transformations_repeated(ContinueToCondition)
        sdfg.simplify(skip=["ArrayElimination"])  # w/o ArrayElimination
        # sdfg.apply_transformations_repeated(LoopNormalize)
        # sdfg.simplify(skip=["ArrayElimination"]) # w/o ArrayElimination
        SymbolPropagation().apply_pass(sdfg, {})
        sdfg.simplify(skip=["ArrayElimination"])  # w/o ArrayElimination

        # scalar_to_length_one_array(sdfg)
        sdfg.validate()

        StructToContainerGroups(validate=False,
                                        save_steps=False,
                                        verbose=False,
                                        simplify=True,
                                        interface_with_struct_copy=True,
                                        interface_to_gpu=True).apply_pass(sdfg, {})
        sdfg.simplify(skip=[ "ArrayElimination"])  # w/o ArrayElimination

        sdfg.save("A.sdfgz", compress=True)

    # XXX: Order is important!
    make_array_loop_local(sdfg, "difcoef", "FOR_l_505_c_505")
    make_array_loop_local(sdfg, "_if_cond_27", "FOR_l_553_c_553")
    #make_array_loop_local(sdfg, "_if_cond_23", "FOR_l_505_c_505")
    #make_array_loop_local(sdfg, "_if_cond_23", "FOR_l_503_c_503")
    sdfg.simplify(skip=[ "ArrayElimination"])  # w/o ArrayElimination
    if use_cache:
        sdfg.save("gpu_pipe_stage1.sdfg")

if Path("gpu_pipe_stage2.sdfg").exists() and use_cache:
    sdfg = dace.SDFG.from_file("gpu_pipe_stage2.sdfg")
else:
    sdfg.apply_transformations_repeated(LoopToMap)
    sdfg.simplify(skip=[ "ArrayElimination", "InlineSDFG"], validate=False)  # w/o ArrayElimination & InlineSDFGs
    if_map_has_direct_view_access_nodes_inside_put_into_nested_sdfg(sdfg,labels=[ ("single_state_body", "single_state_body_map"),
                    ("single_state_body_1", "single_state_body_map"  ),
                    ("single_state_body_0", "single_state_body_map"  ),
                    ("single_state_body_1", "single_state_body_1_map"),
                    ("single_state_body",   "single_state_body_0_map"),
                    ("single_state_body_0", "single_state_body_0_map"),
                    ("single_state_body_1", "single_state_body_2_map")])
    sdfg.validate()
    sdfg.apply_transformations_repeated(MapCollapse)
    sdfg.simplify(skip=["ArrayElimination", "InlineSDFG"])  # w/o ArrayElimination & InlineSDFGs

    #s_a_map = scalar_to_length_one_array(sdfg)
    #sdfg.apply_gpu_transformations(
    #    validate=False,
    #    simplify=False,
    #    dont_copy_structs=True,
    #    host_data=[
    #        k for k, v in sdfg.arrays.items() if isinstance(v, dace.data.Scalar)
    #    ],
    #)
    n = sdfg.apply_transformations_repeated(MapCollapse, validate=True)
    #replace_gpu_scalar_outputs(sdfg, s_a_map)
    #put_host_prefixed_data_back_to_cpu(sdfg)
    from dace.transformation.passes.to_gpu import ToGPU
    ToGPU().apply_pass(sdfg, {})
    if use_cache:
        sdfg.save("gpu_pipe_stage2.sdfg")

if Path("gpu_pipe_stage3.sdfg").exists() and use_cache:
    sdfg = dace.SDFG.from_file("gpu_pipe_stage3.sdfg")
else:
    #for arr_name, arr in sdfg.arrays.items():
    #    if "gpu_" + arr_name in sdfg.arrays:
    #        arr.storage = dace.dtypes.StorageType.CPU_Heap
    # The task lists are the tasklets that need to be wrapped in a single-state GPU map even after applying array duplication
    #DuplicateConstArrays().apply_pass(
    #    sdfg, {"wrap_list": ["T_l467_c467", "T_l472_c472"]}
    #)

    # if_map_has_direct_view_access_nodes_inside_put_into_nested_sdfg(
    #     sdfg,
    #     labels=[
    #         ("single_state_body", "single_state_body_map"),
    #         ("single_state_body_1", "single_state_body_map"),
    #         ("single_state_body_0", "single_state_body_map"),
    #         ("single_state_body_1", "single_state_body_1_map"),
    #         ("single_state_body", "single_state_body_0_map"),
    #         ("single_state_body_0", "single_state_body_0_map"),
    #         ("single_state_body_1", "single_state_body_2_map"),
    #     ],
    # )
    # set_default_map_to_gpu(sdfg)
    # pass_name_as_array_not_as_symbol(sdfg, sdfg, None, "levmask")
    # set_scalar_storage_to_register(sdfg)
    # rename_symbol_connector(sdfg, "nflatlev_jg")
    # set_view_lifetime_to_scope(sdfg)
    # rename_on_if_conds(sdfg, "vcflmax", "host_vcflmax")
    #replace_loop_with_max_reduction(sdfg, "FOR_l_568_c_568")

    if use_cache:
        sdfg.save("gpu_pipe_stage3.sdfg")

# How many loops?
loops_post = 0
for node, state in sdfg.all_nodes_recursive():
    if isinstance(node, LoopRegion):
        loops_post += 1
print(f"Loops remaining: {loops_post}")

sdfg.validate()
sdfg.instrument = dace.InstrumentationType.Timer

################################################################################
### Compile the (optimized) SDFG with alterations
################################################################################

# get build location and dace location
build_loc = sdfg.build_folder
sdfg_name = sdfg.name
dace_include = os.path.dirname(dace.__file__) + "/runtime/include/"

# remove the .dacecache folder
shutil.rmtree(build_loc, ignore_errors=True)

# Generate code
try:
    sdfg.compile()
except Exception as e:
    pass

# TODO: Make manual changes to the generated code if necessary

# compile the SDFG
sdfg._regenerate_code = False
sdfg.compile()
sdfg.save("final.sdfgz", compress=True)

# copy main_cpp_file to .dacecache/<name>/src/cpu/
shutil.copy(f"main_gpu.cc", f"{build_loc}/src/cpu/main.cu")

# copy header to .dacecache/<name>/include/
shutil.copy(f"serde_velocity.h", f"{build_loc}/include/serde_velocity.h")

# To avoid link issues fastly for CUDA libs and have cuda compiler definition
replace_cpp_with_cu(build_loc)

# compile nvcc <SDFG cpp file> <SDFG cuda file> <main file> -I../../include -I/<pathtodace>/dace/runtime/include/ -Xcompiler=-faligned-new --expt-relaxed-constexpr -std=c++20 -arch=native -O0 -w
exit_code = os.system(
    f"nvcc {build_loc}/src/cpu/{sdfg_name}.cu {build_loc}/src/cuda/{sdfg_name}_cuda.cu {build_loc}/src/cpu/main.cu -I {build_loc}/include -I {dace_include} -Xcompiler=-faligned-new --expt-relaxed-constexpr -std=c++20 -arch=native -O3 -Xcompiler=-O3 -Xcompiler=-fopenmp -lineinfo -w -o {sdfg_name}"
)

# check if compilation was successful
if exit_code != 0:
    print("Compilation failed")
    exit(1)


################################################################################
### Execute and compare .got and .want files
################################################################################

# execute the compiled program
exit_code = os.system(f"compute-sanitizer --tool=memcheck ./{sdfg_name}")

# check if execution was successful
if exit_code != 0:
    print("Execution failed")
    exit(1)

# Get list of .got and .want files
got_files = [f for f in os.listdir() if f.endswith(".got")]
want_files = [f.replace(".got", ".want") for f in got_files]
assert len(got_files) == len([f for f in os.listdir() if f.endswith(".want")]), "Number of .got and .want files do not match"

# Compare each .got file with its corresponding .want file
found_diff_all = False
for got, want in zip(got_files, want_files):
    found_diff = False
    with open(got, "r") as got_file, open(want, "r") as want_file:
        got_lines = got_file.readlines()
        want_lines = want_file.readlines()

        if len(got_lines) != len(want_lines):
            print(f"{got} and {want} have different number of lines ❌")
            found_diff = True
            continue

        # lines containing text should be identical, lines containing numbers should be close
        for got_line, want_line in zip(got_lines, want_lines):
            # Are the lines floating point numbers?
            try:
                got_num = float(got_line)
                want_num = float(want_line)
                # TODO: Adjust rel_tol and abs_tol
                if not math.isclose(got_num, want_num, rel_tol=0, abs_tol=1e-12):
                    print(f"{got} and {want} have numerical differences ❌")
                    found_diff = True
                    break

            except ValueError:
                # If not, they should be identical
                if got_line != want_line:
                    print(f"{got} and {want} have different text ❌")
                    found_diff = True
                    break
    if not found_diff:
        print(f"{got} and {want} are identical ✅")
    found_diff_all = found_diff_all or found_diff


if not found_diff_all:
    print("No numerical differences found ✅")
else:
    print("Numerical differences found ❌")


################################################################################
### Measure performance
################################################################################

if run_benchmark:
    # Warmup
    for i in range(10):
        os.system(f"./{sdfg_name}")

    # Measure
    times = []
    for i in range(10):
        sdfg.clear_instrumentation_reports()
        os.system(f"./{sdfg_name}")
        report = sdfg.get_latest_report()
        assert report.events[-1].name == f"SDFG {sdfg.name}"
        time = report.events[-1].duration  # in us
        times.append(time)

    for time in times:
        print(f"GPU,{time}")

################################################################################
### Cleanup
################################################################################

# remove the compiled program
os.remove(sdfg_name)

# remove the .got files
for got in got_files:
    os.remove(got)

# remove the .want files
for want in want_files:
    os.remove(want)

# remove the .dacecache folder
shutil.rmtree(build_loc)
