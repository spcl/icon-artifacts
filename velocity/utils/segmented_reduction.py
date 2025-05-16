import dace
from dace.data import ListProperty
from dace.memlet import LambdaProperty

import ast
from copy import deepcopy as dcpy
import dace
import itertools
import functools
import platform
import dace.serialize
import dace.library
from typing import Any, Dict, Set
from dace.config import Config
from dace.sdfg import SDFG, SDFGState, devicelevel_block_size, propagation
from dace.sdfg import graph
from dace.frontend.python.astutils import unparse
from dace.properties import (Property, CodeProperty, LambdaProperty, RangeProperty, DebugInfoProperty, SetProperty,
                             make_properties, indirect_properties, DataProperty, SymbolicProperty, ListProperty,
                             SDFGReferenceProperty, DictProperty, LibraryImplementationProperty)
from dace.frontend.operations import detect_reduction_type
from dace import data, subsets as sbs, dtypes
from dace import registry, subsets
import pydoc
import warnings
from dace.sdfg import nodes, scope
from dace.transformation import transformation as pm
from dace.symbolic import symstr, issymbolic
from dace.libraries.standard.environments.cuda import CUDA

from dace.libraries.standard import CodeLibraryNode, reduction_planner as red_planner
import copy

seg_reduction = f"""

"""

@make_properties
class SegmentedReduceLibNode(CodeLibraryNode):
    code = Property(dtype=str, default="", allow_none=False)

    def __init__(self, name, input_names, output_names, code):
        super().__init__(name=name, input_names=input_names, output_names=output_names)
        self.code = code

    def generate_code(self, inputs, outputs):
        return self.code

def to_segmented_reduction(sdfg: dace.SDFG):
    all_maps = [(v, g) for v, g in sdfg.all_nodes_recursive() if isinstance(v, dace.sdfg.nodes.MapEntry)]
    for map_entry, graph in all_maps:
        all_nodes = list(graph.all_nodes_between(map_entry, graph.exit_node(map_entry)))
        # 3 nodes, 1 library node, 1 tasklet, 1 access node
        # reduce_ in lib node label
        if len(all_nodes) == 3:
            print(all_nodes)
            types = [type(node) for node in all_nodes]
            print(types)
            lib_nodes = [node for node in all_nodes if isinstance(node, dace.sdfg.nodes.LibraryNode)]
            tasklets = [node for node in all_nodes if isinstance(node, dace.sdfg.nodes.Tasklet)]
            access_nodes = [node for node in all_nodes if isinstance(node, dace.sdfg.nodes.AccessNode)]
            if len(lib_nodes) > 0 and len(tasklets) > 0 and len(access_nodes) > 0:
                lib_node = lib_nodes[0]
                tasklet = tasklets[0]
                access_node = access_nodes[0]
                # check if the library node is a reduce
                if 'reduce_sum_to_address' in lib_node.label:
                    # Replace map with segmented reduce
                    print(f"Found reduce node {lib_node.label} in map {map_entry.label}")
                    inputs = [v for v in graph.in_edges(map_entry)]
                    outputs = [v for v in graph.out_edges(graph.exit_node(map_entry))]
                    assert len(inputs) == 1
                    assert len(outputs) == 1
                    input_edge = inputs[0]
                    output_edge = outputs[0]
                    print(input_edge, output_edge)
                    assert len(map_entry.range) == 1
                    b,e,s = map_entry.range[0]
                    in_arr = sdfg.arrays[input_edge.data.data]
                    if input_edge.data.data != "gpu_cfl_clipping":
                        continue
                    segment_size = in_arr.shape[0]
                    batch_size = (e+1-b)
                    #raise Exception(segment_size, batch_size)
                    batch_offset = b

                    for r in  input_edge.data.subset.ranges:
                        print(r, type(r))

                    in_memlet_ranges = [r for r in input_edge.data.subset.ranges]
                    in_memlet_ranges[-1] = [b-1, e, 1]

                    out_memlet_ranges = [r for r in output_edge.data.subset.ranges]
                    out_memlet_ranges[-1] = [b-1, e, 1]

                    srln = SegmentedReduceLibNode(
                        name="segmented_reduce_sum_to_address",
                        #schedule=dace.dtypes.ScheduleType.GPU_Device,
                        input_names=["in_arr", "in_segment_size", "in_batch_size"],
                        output_names=["out_arr"],
                        code = f"""
reduce_segmented_to_address_gpu(in_arr, out_arr, in_segment_size, in_batch_size, __dace_current_stream);
"""
                    )
                    srln.schedule=dace.dtypes.ScheduleType.GPU_Device

                    graph.add_node(srln)
                    in_an = input_edge.src
                    out_an = output_edge.dst
                    graph.add_edge(in_an, input_edge.src_conn, srln, "in_arr", dace.memlet.Memlet(data=input_edge.data.data, subset=dace.subsets.Range(in_memlet_ranges)))
                    graph.add_edge(srln, "out_arr", out_an, output_edge.dst_conn, dace.memlet.Memlet(data=output_edge.data.data, subset=dace.subsets.Range(out_memlet_ranges)))

                    t1 = graph.add_tasklet(name="t_segment_size", inputs=set(), outputs={"_out"}, code=f"_out = {segment_size}")
                    t2 = graph.add_tasklet(name="t_batch_size", inputs=set(), outputs={"_out"}, code=f"_out = {batch_size}")
                    s1name, s1 = graph.sdfg.add_scalar(name="segment_size", dtype=dace.int32, storage=dace.StorageType.Register, find_new_name=True, transient=True)
                    s2name, s2 = graph.sdfg.add_scalar(name="batch_size", dtype=dace.int32, storage=dace.StorageType.Register, find_new_name=True, transient=True)
                    s1an = graph.add_access(s1name)
                    s2an = graph.add_access(s2name)
                    graph.add_edge(t1, "_out", s1an, None, dace.memlet.Memlet(data=s1name, subset="0"))
                    graph.add_edge(t2, "_out", s2an, None, dace.memlet.Memlet(data=s2name, subset="0"))

                    graph.add_edge(s1an, None, srln, "in_segment_size", dace.memlet.Memlet(data=s1name, subset="0"))
                    graph.add_edge(s2an, None, srln, "in_batch_size", dace.memlet.Memlet(data=s2name, subset="0"))
                    #graph.add_edge(srln, "out_arr", output_edge.dst, None, d)

                    for n in all_nodes + [map_entry, graph.exit_node(map_entry)]:
                        graph.remove_node(n)
                    #sdfg.save("uwu.sdfg")
                    #raise Exception(segment_size, batch_size)
                    return
                    #assert len(input_edge.data.subset) == 2
                    #assert len(output_edge.data.subset) == 1

                    # Pass

                    """
                    sr = SegmentedReduce(name=map_entry.label,
                                    wcr='lambda a, b: a + b')
                    ies = graph.in_edges(map_entry)
                    assert len(ies) == 1
                    oes = graph.out_edges(graph.exit_node(map_entry))
                    assert len(oes) == 1
                    in_edge = ies[0]
                    out_edge = oes[0]
                    graph.remove_node(graph.exit_node(map_entry))
                    graph.remove_node(map_entry)
                    for n in all_nodes:
                        graph.remove_node(n)
                    graph.add_node(sr)
                    graph.add_edge(in_edge.src, in_edge.src_conn, sr, "_in", copy.deepcopy(in_edge.data))
                    graph.add_edge(sr, '_out', out_edge.dst, out_edge.dst_conn, copy.deepcopy(out_edge.data))
                    """

@dace.library.expansion
class ExpandGPU(pm.ExpandTransformation):
    environments = []

    @staticmethod
    def expansion(node: 'SegmentedReduce', state: SDFGState, sdfg: SDFG):
        node.validate(sdfg, state)
        inedge: graph.MultiConnectorEdge = state.in_edges(node)[0]
        outedge: graph.MultiConnectorEdge = state.out_edges(node)[0]
        insubset = dcpy(inedge.data.subset)
        isqdim = insubset.squeeze()
        outsubset = dcpy(outedge.data.subset)
        osqdim = outsubset.squeeze()
        input_dims = len(insubset)
        output_dims = len(outsubset)
        input_data = sdfg.arrays[inedge.data.data]
        output_data = sdfg.arrays[outedge.data.data]

        if len(osqdim) == 0:  # Fix for scalars
            osqdim = [0]

        # Standardize and squeeze axes
        axes = node.axes if node.axes is not None else [i for i in range(len(inedge.data.subset))]
        axes = [axis for axis in axes if axis in isqdim]

        # Create nested SDFG
        nsdfg = SDFG('reduce')

        nsdfg.add_array('_in',
                        insubset.size(),
                        input_data.dtype,
                        strides=[s for i, s in enumerate(input_data.strides) if i in isqdim],
                        storage=input_data.storage)

        nsdfg.add_array('_out',
                        outsubset.size(),
                        output_data.dtype,
                        strides=[s for i, s in enumerate(output_data.strides) if i in osqdim],
                        storage=output_data.storage)

        # Rename outer connectors and add to node
        inedge._dst_conn = '_in'
        outedge._src_conn = '_out'
        node.add_in_connector('_in')
        node.add_out_connector('_out')

        if len(axes) == 0:
            # Degenerate reduction, do nothing
            nstate = nsdfg.add_state()
            r = nstate.add_read('_in')
            w = nstate.add_write('_out')
            nstate.add_edge(
                r, None, w, None,
                dace.Memlet(data='_in',
                            subset=dace.subsets.Range.from_array(nsdfg.arrays['_in']),
                            other_subset=dace.subsets.Range.from_array(nsdfg.arrays['_out'])))
            return nsdfg

        # If identity is defined, add an initialization state
        if node.identity is not None:
            init_state = nsdfg.add_state()
            nstate = nsdfg.add_state()
            nsdfg.add_edge(init_state, nstate, dace.InterstateEdge())

            # Add initialization as a map
            init_state.add_mapped_tasklet(
                'reduce_init', {'_o%d' % i: '0:%s' % symstr(d)
                                for i, d in enumerate(outedge.data.subset.size())}, {},
                '__out = %s' % node.identity,
                {'__out': dace.Memlet.simple('_out', ','.join(['_o%d' % i for i in osqdim]))},
                external_edges=True)
        else:
            nstate = nsdfg.add_state()
        # END OF INIT

        # (If axes != all) Add outer map, which corresponds to the output range
        if len(axes) != input_dims:
            # Interleave input and output axes to match input memlet
            ictr, octr = 0, 0
            input_subset = []
            for i in isqdim:
                if i in axes:
                    input_subset.append('_i%d' % ictr)
                    ictr += 1
                else:
                    input_subset.append('_o%d' % octr)
                    octr += 1

            ome, omx = nstate.add_map('reduce_output',
                                      {'_o%d' % i: '0:%s' % symstr(sz)
                                       for i, sz in enumerate(outsubset.size())})
            outm = dace.Memlet.simple('_out', ','.join(['_o%d' % i for i in range(output_dims)]), wcr_str=node.wcr)
            inmm = dace.Memlet.simple('_in', ','.join(input_subset))
        else:
            ome, omx = None, None
            outm = dace.Memlet.simple('_out', '0', wcr_str=node.wcr)
            inmm = dace.Memlet.simple('_in', ','.join(['_i%d' % i for i in range(len(axes))]))

        # Add inner map, which corresponds to the range to reduce, containing
        # an identity tasklet
        ime, imx = nstate.add_map(
            'reduce_values',
            {'_i%d' % i: '0:%s' % symstr(insubset.size()[isqdim.index(axis)])
             for i, axis in enumerate(sorted(axes))})

        # Add identity tasklet for reduction
        t = nstate.add_tasklet('identity', {'__inp'}, {'__out'}, '__out = __inp')

        # Connect everything
        r = nstate.add_read('_in')
        w = nstate.add_read('_out')
        if ome:
            nstate.add_memlet_path(r, ome, ime, t, dst_conn='__inp', memlet=inmm)
            nstate.add_memlet_path(t, imx, omx, w, src_conn='__out', memlet=outm)
        else:
            nstate.add_memlet_path(r, ime, t, dst_conn='__inp', memlet=inmm)
            nstate.add_memlet_path(t, imx, w, src_conn='__out', memlet=outm)

        from dace.transformation import dataflow
        nsdfg.apply_transformations_repeated(dataflow.MapCollapse)

        return nsdfg


@dace.library.node
class SegmentedReduce(dace.sdfg.nodes.LibraryNode):
    """ An SDFG node that reduces an N-dimensional array to an
        (N-k)-dimensional array, with a list of axes to reduce and
        a reduction binary function. """

    # Global properties
    implementations = {
        'GPU': ExpandGPU
    }

    default_implementation = 'pure'

    # Properties
    axes = ListProperty(element_type=int, allow_none=True)
    wcr = LambdaProperty(default='lambda a, b: a')

    def __init__(self,
                 name,
                 wcr='lambda a, b: a',
                 axes=None,
                 schedule=dace.dtypes.ScheduleType.GPU_Device,
                 debuginfo=None,
                 **kwargs):
        super().__init__(name=name, **kwargs)
        self.wcr = wcr
        self.axes = axes
        self.debuginfo = debuginfo
        self.schedule = schedule

    @staticmethod
    def from_json(json_obj, context=None):
        ret = SegmentedReduce('reduce', 'lambda a, b: a', None)
        dace.serialize.set_properties_from_json(ret, json_obj, context=context)
        return ret

    def __str__(self):
        return f'SegmentedReduce'

    def __label__(self, sdfg, state):
        return str(self)

    def validate(self, sdfg, state):
        if len(state.in_edges(self)) != 1:
            raise ValueError('Reduce node must have one input')
        if len(state.out_edges(self)) != 1:
            raise ValueError('Reduce node must have one output')
