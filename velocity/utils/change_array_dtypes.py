import dace
import typing

from dace.codegen.control_flow import CodeBlock

def change_array_dtypes(sdfg: dace.SDFG, array_names: typing.Set[str], new_type, level: int = 0):
    for name in array_names:
        if name in sdfg.arrays:
            array = sdfg.arrays[name]
            if array.dtype != new_type:
                if (level == 0 and array.transient) or level > 0:
                    print(f'Changing dtype of {name} from {array.dtype} to {new_type}')
                    array.dtype = new_type

    for state in sdfg.all_states():
        for node in state.nodes():
            if isinstance(node, dace.nodes.NestedSDFG):
                nsdfg_names = set()
                for name in array_names:
                    for ie in state.in_edges(node):
                        if ie.data.data == name:
                            nsdfg_names.add(ie.dst_conn)
                    for oe in state.out_edges(node):
                        if oe.data.data == name:
                            nsdfg_names.add(oe.src_conn)
                change_array_dtypes(node.sdfg, nsdfg_names, new_type, level+1)

def setzero_to_memset(sdfg: dace.SDFG):
    map_entries = set()
    for node, graph in sdfg.all_nodes_recursive():
        if isinstance(node, dace.nodes.MapEntry):
            map_entries.add((node, graph))

    maps_to_rm = set()
    for map_entry, graph in map_entries:
        assert isinstance(graph, dace.SDFGState)
        assert isinstance(map_entry, dace.nodes.MapEntry)
        map_exit = graph.exit_node(map_entry)
        # No inputs single output map
        if (graph.in_degree(map_entry) == 0 and
            graph.out_degree(map_exit) == 1):
            an_edge = next(iter(graph.out_edges(map_exit)))
            # One access node as output
            if isinstance(an_edge.dst, dace.nodes.AccessNode):
                # Write set is the same as the array (not necessarily, sometimes some lines are not written to?)
                shape_subset = [(0, m-1, 1) for m in graph.sdfg.arrays[an_edge.data.data].shape]
                if an_edge.data.subset == shape_subset:
                    nodelist = list(graph.all_nodes_between(map_entry, map_exit))
                    if len(nodelist) == 1:
                        node = nodelist[0]
                        if isinstance(node, dace.nodes.Tasklet):
                            if len(node.out_connectors) == 1:
                                out_conn = next(iter(node.out_connectors))
                                cb = CodeBlock(f"{out_conn} = 0")
                                if node.code == cb or node.code == f"{out_conn} = 0":
                                    maps_to_rm.add((map_entry, graph, an_edge.dst.data))
                                    raise Exception("uwu")
                                if out_conn == "levmask_out_0":
                                    raise Exception("owo")

    for map_entry, graph, array_name in maps_to_rm:
        assert isinstance(graph, dace.SDFGState)
        assert isinstance(map_entry, dace.nodes.MapEntry)
        all_nodes = graph.all_nodes_between(map_entry, graph.exit_node(map_entry))
        an = None
        for oe in graph.out_edges(graph.exit_node(map_entry)):
            graph.remove_edge(oe)
            assert an is None
            an = oe.dst
        for n in all_nodes:
            graph.remove_node(n)

        t = graph.add_tasklet(
            f'set_zero_{array_name}',
            {},
            {"_out"},
            f'cudaMemsetAsync((void*)_out, 0, sizeof({graph.sdfg.arrays[array_name].dtype.ctype}) * {graph.sdfg.arrays[array_name].total_size}, __state->gpu_context->streams[0]);',
            dace.dtypes.Language.CPP
        )
        t.schedule = dace.ScheduleType.GPU_Device
        graph.add_edge(t, "_out", an, None, dace.memlet.Memlet.from_array(array_name, graph.sdfg.arrays[array_name]))


