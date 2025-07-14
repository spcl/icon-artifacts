import dace

def add_missing_symbols_to_nsdfgs(sdfg: dace.SDFG):
    nsdfgs = set()
    for state in sdfg.all_states():
        for node in state.nodes():
            if isinstance(node, dace.nodes.NestedSDFG):
                nsdfg = node
                inner_sdfg = node.sdfg
                nsdfgs.add(inner_sdfg)
                symbols = set(k for k in nsdfg.free_symbols if k not in nsdfg.in_connectors and k not in nsdfg.out_connectors)
                missing_symbols = [s for s in symbols if s not in nsdfg.symbol_mapping]
                for ms in missing_symbols:
                    nsdfg.symbol_mapping[ms] = ms

    for nsdfg in nsdfgs:
        add_missing_symbols_to_nsdfgs(nsdfg)