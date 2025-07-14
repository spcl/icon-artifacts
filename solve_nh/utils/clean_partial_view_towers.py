import dace

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

