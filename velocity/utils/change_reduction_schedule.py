import dace
from utils.reductions import LibNode
import copy

_type = "maxZ_to_address"
lib_node = LibNode(
    name=f"reduce_{_type}",
    input_names=["in_arr", "in_size"],
    output_names=["out"],
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
    for node, graph in sdfg.all_nodes_recursive():
        if isinstance(node, dace.nodes.LibraryNode):
            in_edges = graph.in_edges(node)
            out_edges = graph.out_edges(node)
            if len(out_edges) == 1 and len(in_edges) == 2:
                dst = out_edges[0].dst
                if graph.out_degree(dst) > 1:
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
                                #new_access = graph.add_access("vcflmax")
                                new_memlet = copy.deepcopy(graph.out_edges(dst_dst)[0])
                                graph.add_node(new_lib_node)
                                for ie in in_edges:
                                    graph.add_edge(ie.src, ie.src_conn, new_lib_node, ie.dst_conn, ie.data)
                                graph.add_edge(new_lib_node, out_edges[0].src_conn, dst_dst_dst, None, new_memlet.data)
                                graph.remove_node(dst)
                                graph.remove_node(node)
                                graph.remove_node(dst_dst)
                                break

    # move vcflmax name to gpu_vcflmax
    # add copy gpu_vcflmax to vcflmax later
    sdfg.replace(name="vcflmax", new_name="gpu_vcflmax")

    # add copy gpu_vcflmax to vcflmax later
    # if a map exit writes to gpu_vcflmax add a copy to vcflmax
    for node, graph in sdfg.all_nodes_recursive():
        if isinstance(node, dace.nodes.AccessNode) and node.data == "gpu_vcflmax":
            if graph.in_degree(node) == 1:
                src = graph.in_edges(node)[0].src
                src_conn = graph.in_edges(node)[0].src_conn
                dst = graph.add_access("vcflmax")
                graph.add_edge(node, None, dst, None, dace.Memlet.from_array(
                    dataname="gpu_vcflmax",
                    datadesc=graph.sdfg.arrays["gpu_vcflmax"],
                ))
                if "vcflmax" not in sdfg.arrays:
                    desc = copy.deepcopy(graph.sdfg.arrays["gpu_vcflmax"])
                    desc.storage = dace.StorageType.CPU_Heap
                    sdfg.add_datadesc("vcflmax", desc)

    # On the last state if fix the reduction node
    last_state = [node for node in sdfg.nodes() if sdfg.out_degree(node) == 0][0]
    for node in last_state.nodes():
        if isinstance(node, dace.nodes.AccessNode) and node.data == "gpu_vcflmax":
            node.data = "vcflmax"
            for oe in last_state.out_edges(node):
                if oe.data.data == "gpu_vcflmax":
                    oe.data.data = "vcflmax"
