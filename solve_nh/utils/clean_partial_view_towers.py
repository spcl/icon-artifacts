import dace
import copy

def _clean_partial_view_towers_impl(sdfg: dace.SDFG):
    nsdfgs = set()
    num_applied = 0
    for state in sdfg.all_states():
        for node in state.nodes():
            if isinstance(node, dace.nodes.AccessNode):
                # If data is a view and out degree is 0 and data is a struct or container array then rm
                if state.out_degree(node) == 0:
                    datadesc = sdfg.arrays[node.data]
                    if isinstance(datadesc, dace.data.View):
                        if (
                            isinstance(datadesc, dace.data.Structure) or isinstance(datadesc, dace.data.ContainerArray)
                        ):

                            state.remove_node(node)
                            num_applied += 1
            if isinstance(node, dace.nodes.NestedSDFG):
                nsdfgs.add(node.sdfg)
    for nsdfg in nsdfgs:
        num_applied += _clean_partial_view_towers_impl(nsdfg)
    return num_applied

def clean_partial_view_towers(sdfg: dace.SDFG):
    num_applied = _clean_partial_view_towers_impl(sdfg)
    while num_applied > 0:
        num_applied = _clean_partial_view_towers_impl(sdfg)

def clean_trivial_view_pattern(sdfg: dace.SDFG):
    """
    Cleans up trivial view patterns in the SDFG by removing nodes that are views with no outgoing edges.

    Pattern: array -> view -> any_node
    """
    nsdfgs = set()
    for state in sdfg.all_states():
        snodes = state.nodes()
        for node in snodes:
            if node not in state.nodes():
                continue
            if isinstance(node, dace.nodes.NestedSDFG):
                nsdfgs.add(node.sdfg)
            if isinstance(node, dace.nodes.AccessNode):
                # AccessNode -> AccessNode
                if (state.out_degree(node) == 1 and
                   isinstance(state.out_edges(node)[0].dst, dace.nodes.AccessNode)):
                    to_view_edge = state.out_edges(node)[0]
                    dst_node = state.out_edges(node)[0].dst
                    src_desc = sdfg.arrays[node.data]
                    dst_desc = sdfg.arrays[dst_node.data]
                    # Non-view -> View
                    if ((not isinstance(src_desc, dace.data.View)) and
                        isinstance(dst_desc, dace.data.View)):
                        out_edges = state.out_edges(dst_node)
                        if len(out_edges) == 1:
                            out_edge = out_edges[0]
                            if out_edge.data is not None:
                                # Memlet going out from the view is [0,1(exl),1]
                                if out_edge.data.subset == dace.subsets.Range([(0, 0, 1) for _ in dst_desc.shape]):
                                    # Rm to view node, reroute the edge
                                    assert out_edge.src_conn is None
                                    assert to_view_edge.src_conn is None
                                    state.add_edge(node, out_edge.src_conn, out_edge.dst, out_edge.dst_conn, copy.deepcopy(to_view_edge.data))
                                    state.remove_node(dst_node)

    for nsdfg in nsdfgs:
        clean_trivial_view_pattern(nsdfg)