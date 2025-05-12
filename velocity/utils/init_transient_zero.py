import dace

def init_transient_zero(sdfg: dace.SDFG):
    for node, parent_graph in sdfg.all_nodes_recursive():
        if isinstance(node, dace.nodes.AccessNode):
            parent_sdfg = parent_graph.sdfg
            arr = parent_sdfg.arrays[node.data]
            if arr.transient:
                node.setzero = True