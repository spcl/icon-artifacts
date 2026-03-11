import dace
from utils.rename_on_if import rename_on_if

def rm_segmented_reduce(sdfg: dace.SDFG):
    # Detect and remove segmented reduction
    lib_node = None
    parent_graph = None
    for node, graph in sdfg.all_nodes_recursive():
        if "segmented_reduce" in node.label:
            lib_node = node
            parent_graph = graph
            break
    assert lib_node is not None, "No segmented_reduce node found in the SDFG."

    src_nodes = set()
    for ie in parent_graph.in_edges(lib_node):
        if not( isinstance(ie.src, dace.nodes.AccessNode) and not parent_graph.sdfg.arrays[ie.src.data].transient):
            src_nodes.add(ie.src)
            for ieie in parent_graph.in_edges(ie.src):
                src_nodes.add(ieie.src)
    for oe in parent_graph.out_edges(lib_node):
        src_nodes.add(oe.dst)

    for node in src_nodes:
        parent_graph.remove_node(node)
    parent_graph.remove_node(lib_node)

    # Replace all out_val_0 accessed+h
    next_state = parent_graph.sdfg.out_edges(parent_graph)[0].dst
    for edge in next_state.edges():
        if edge.data.data == "out_val_0":
            src_conn = edge.src_conn
            dst_conn = edge.dst_conn
            next_state.remove_edge(edge)
            edge.src.remove_out_connector(src_conn)
            edge.dst.remove_in_connector(dst_conn)
            if isinstance(edge.dst, dace.nodes.NestedSDFG):
                dst = edge.dst
                dst.remove_in_connector(dst_conn)
                dst.sdfg.remove_data("out_val_0", False)
                src_str = "not (out_val_0 == 0) == 1"
                for cfg_nodes in dst.sdfg.nodes():
                    rename_on_if(cfg_nodes, src_str, "1 == 1", False, False)
    for node in next_state.nodes():
        if isinstance(node, dace.nodes.AccessNode) and node.data == "out_val_0":
            next_state.remove_node(node)

    next_state.sdfg.remove_data("out_val_0", False)
    for n, g in sdfg.all_nodes_recursive():
        if isinstance(n, dace.nodes.AccessNode):
            if g.in_degree(n) == 0 and g.out_degree(n) == 0:
                g.remove_node(n)
    sdfg.validate()
    sdfg.simplify()
    sdfg.validate()