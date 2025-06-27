import dace
from utils.reductions import LibNode
import copy

_type = "maxZ_to_address"
lib_node = LibNode(
    name=f"reduce_{_type}",
    input_names=["in_arr", "out", "in_size"],
    output_names=[],
    code=f"""
    #ifdef __REDUCE_DEVICE__
        out = reduce_{_type}_device(in_arr, in_size);
    #elif defined(__REDUCE_GPU__)
        out = reduce_{_type}_gpu(in_arr, in_size, __dace_current_stream);
    #else
        out = reduce_{_type}_cpu(in_arr, in_size);
    #endif
    """ if "address" not in _type else f"""
    #ifdef __REDUCE_DEVICE__
        reduce_{_type}_device(in_arr, out, in_size);
    #elif defined(__REDUCE_GPU__)
        reduce_{_type}_gpu(in_arr, out, in_size, __dace_current_stream);
    #else
        reduce_{_type}_cpu(in_arr, out, in_size);
    #endif
    """,
)

def change_reduction_schedule(sdfg: dace.SDFG):
    # In access node "gpu_maxvcfl_arr", out access node "maxvcfl"
    #lib_node_to_replace =
    b = False
    for node, graph in sdfg.all_nodes_recursive():
        if isinstance(node, LibNode):
            in_edges = graph.in_edges(node)
            out_edges = graph.out_edges(node)
            if len(out_edges) == 1 and len(in_edges) == 2:
                dst = out_edges[0].dst
                if graph.out_degree(dst) == 1:
                    dst_dst = graph.out_edges(dst)[0].dst
                    if graph.out_degree(dst_dst) == 1:
                        dst_dst_dst = graph.out_edges(dst_dst)[0].dst
                        if isinstance(dst, dace.nodes.AccessNode) and dst.data == "maxvcfl":
                            src = in_edges[0].src
                            src2 = in_edges[1].src
                            if ((isinstance(src, dace.nodes.AccessNode) and src.data == "gpu_maxvcfl_arr") or (
                                isinstance(src2, dace.nodes.AccessNode) and src2.data == "gpu_maxvcfl_arr"
                            )):
                                # Pattern found
                                assert "maxZ_to_scalar" in node.label or "maxZ_to_scalar" in node.name
                                new_lib_node = lib_node
                                new_lib_node.schedule = dace.ScheduleType.GPU_Device
                                #new_access = graph.add_access("vcflmax")
                                new_edge = copy.deepcopy(graph.out_edges(dst_dst)[0])
                                subset = copy.deepcopy(new_edge.data.subset)
                                new_subset = [(b,e+1,s) for b, e, s in subset]
                                new_memlet = dace.memlet.Memlet(data=new_edge.data.data,
                                                                subset= dace.subsets.Range(new_subset))
                                graph.add_node(new_lib_node)
                                for ie in in_edges:
                                    graph.add_edge(ie.src, ie.src_conn, new_lib_node, ie.dst_conn, ie.data)
                                #graph.add_edge(new_lib_node, out_edges[0].src_conn, dst_dst_dst, None, new_memlet.data)
                                #print(node.out_connectors.items())
                                src_conn = out_edges[0].src_conn
                                conntype = node.out_connectors[src_conn]
                                _t = lib_node.remove_out_connector(src_conn)
                                assert _t
                                graph.remove_node(dst)
                                graph.remove_node(node)
                                graph.remove_node(dst_dst)
                                #tt = new_lib_node.remove_out_connector(src_conn)
                                #assert src_conn == "out"
                                #ttt= new_lib_node.add_in_connector(connector_name=src_conn, dtype=dace.float64, force=True)
                                #assert tt
                                #assert ttt
                                graph.add_edge(dst_dst_dst, None, new_lib_node, src_conn, new_memlet)
                                #an = graph.add_access("gpu_vcflmax")
                                #graph.add_edge(new_lib_node, None, an, None, dace.Memlet())
                                b = True
                                break
    assert b, "Pattern not found in SDFG"

    # move vcflmax name to gpu_vcflmax
    # add copy gpu_vcflmax to vcflmax later
    sdfg.replace(name="vcflmax", new_name="gpu_vcflmax")
    for state in sdfg.all_states():
        for node in state.nodes():
            if isinstance(node, dace.nodes.NestedSDFG):
                node.sdfg.replace(name="vcflmax", new_name="gpu_vcflmax")

    for node, graph in sdfg.all_nodes_recursive():
        if isinstance(node, dace.nodes.NestedSDFG):
            if "vcflmax" in node.symbol_mapping:
                node.symbol_mapping["gpu_vcflmax"] = node.symbol_mapping["vcflmax"]
                del node.symbol_mapping["vcflmax"]
            if "vcflmax" in node.in_connectors:
                for ie in graph.in_edges(node):
                    if ie.dst_conn == "vcflmax":
                        ie.dst_conn = "gpu_vcflmax"
                node.in_connectors["gpu_vcflmax"] = node.in_connectors["vcflmax"]
                del node.in_connectors["vcflmax"]
            if "vcflmax" in node.out_connectors:
                for oe in graph.out_edges(node):
                    if oe.src_conn == "vcflmax":
                        oe.src_conn = "gpu_vcflmax"
                node.out_connectors["gpu_vcflmax"] = node.out_connectors["vcflmax"]
                del node.out_connectors["vcflmax"]

        if "gpu_vcflmax" in graph.sdfg.arrays:
            graph.sdfg.arrays["gpu_vcflmax"].storage = dace.dtypes.StorageType.GPU_Global

    # add copy gpu_vcflmax to vcflmax later
    # if a map exit writes to gpu_vcflmax add a copy to vcflmax
    for node, graph in sdfg.all_nodes_recursive():
        if isinstance(node, dace.nodes.AccessNode) and node.data == "gpu_vcflmax":
            if graph.in_degree(node) == 1:
                src = graph.in_edges(node)[0].src
                if isinstance(src, dace.nodes.MapExit):
                    src_conn = graph.in_edges(node)[0].src_conn
                    graph.in_edges(node)[0].dynamic = False
                    dst = graph.add_access("vcflmax")
                    e = graph.add_edge(node, None, dst, None, dace.Memlet.from_array(
                        dataname="gpu_vcflmax",
                        datadesc=graph.sdfg.arrays["gpu_vcflmax"],
                    ))
                    e.dynamic = False
                    if "vcflmax" not in graph.sdfg.arrays:
                        desc = copy.deepcopy(graph.sdfg.arrays["gpu_vcflmax"])
                        desc.storage = dace.dtypes.StorageType.CPU_Heap
                        graph.sdfg.add_datadesc("vcflmax", desc)
                    else:
                        graph.sdfg.arrays["vcflmax"].storage = dace.dtypes.StorageType.CPU_Heap

    # On the last state if fix the reduction node
    last_state = [node for node in sdfg.nodes() if sdfg.out_degree(node) == 0][0]
    for node in last_state.nodes():
        if isinstance(node, dace.nodes.AccessNode) and node.data == "gpu_vcflmax":
            node.data = "vcflmax"
            for oe in last_state.out_edges(node):
                if oe.data.data == "gpu_vcflmax":
                    oe.data.data = "vcflmax"

    for node, graph in sdfg.all_nodes_recursive():
        if "vcflmax" in graph.sdfg.arrays:
            graph.sdfg.arrays["vcflmax"].storage = dace.dtypes.StorageType.CPU_Heap
            assert graph.sdfg.arrays["vcflmax"].storage == dace.dtypes.StorageType.CPU_Heap
        if "gpu_vcflmax" in graph.sdfg.arrays:
            graph.sdfg.arrays["gpu_vcflmax"].storage = dace.dtypes.StorageType.GPU_Global
            assert graph.sdfg.arrays["gpu_vcflmax"].storage == dace.dtypes.StorageType.GPU_Global

    sdfg.save("a.sdfg")
    sdfg.validate()