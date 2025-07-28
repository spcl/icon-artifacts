import dace
from typing import Set
import copy
import sympy


def _get_missing_symbols(nsdfg_node: dace.nodes.NestedSDFG) -> Set[str]:
    nsdfg = nsdfg_node
    symbols = set(k for k in nsdfg.free_symbols if k not in nsdfg.in_connectors and k not in nsdfg.out_connectors)
    missing_symbols = [s for s in symbols if s not in nsdfg.symbol_mapping]

    #print(list(nsdfg_node.sdfg.all_interstate_edges()))
    #print(nsdfg_node.sdfg.nodes())
    for e in nsdfg_node.sdfg.all_interstate_edges():
        #print(e, e.data, e.data is None)
        if e.data is not None:
            def _get_all_symbols(expr):
                symbols = {s for s in expr.atoms(sympy.Symbol)}
                functions = {f.func for f in expr.atoms(sympy.Function)}
                return symbols.union(functions)
            for k, v in e.data.assignments.items():
                syms = _get_all_symbols(dace.symbolic.SymExpr(v))
                #print(v)
                for sym in syms:
                    sym_v_str = str(sym)
                    if sym_v_str not in nsdfg.symbol_mapping and sym_v_str not in nsdfg_node.in_connectors and sym_v_str not in nsdfg_node.out_connectors:
                        missing_symbols.append(sym_v_str)
                if k not in nsdfg.symbol_mapping and k not in nsdfg_node.in_connectors and k not in nsdfg_node.out_connectors:
                    missing_symbols.append(k)
    return set(missing_symbols)

def add_missing_symbols_to_nsdfgs(sdfg: dace.SDFG):
    nsdfgs = set()
    for state in sdfg.all_states():
        for node in state.nodes():
            if isinstance(node, dace.nodes.NestedSDFG):
                nsdfg = node
                inner_sdfg = node.sdfg
                nsdfgs.add(inner_sdfg)
                missing_symbols = _get_missing_symbols(nsdfg)
                for ms in missing_symbols:
                    nsdfg.symbol_mapping[ms] = ms

    for nsdfg in nsdfgs:
        add_missing_symbols_to_nsdfgs(nsdfg)

def _insert_missing_data_through_parent_scopes(missing_data: Set[str],
                                               nsdfg_node: dace.nodes.NestedSDFG,
                                               parent_graph,
                                               parent_sdfg: dace.SDFG):
    # For each data access added, add the data descriptor and connecto to the parent NSDFG node
    for data_access in missing_data:
        # If array is not in parent graphs's sdfg's data containers add it
        datadesc = parent_sdfg.arrays[data_access]
        assert isinstance(parent_graph, dace.SDFGState), "Parent graph must be a SDFGState"
        inner_sdfg: dace.SDFG = nsdfg_node.sdfg
        # If data access is already in the parent graph's sdfg, we can continue
        # Make it flow into the map entry, for it find the state the NSDFG node is in
        parent_nsdfg_node_state: dace.SDFGState = parent_graph

        # If this array has been already added to the nSDFG, we can skip, since
        # this transformation adds the complete array, this will be redundant, and
        # multiple edges to the same nSDFG inconnector is invalid.
        if data_access in nsdfg_node.in_connectors:
            continue

        if data_access in inner_sdfg.symbols:
            inner_sdfg.remove_symbol(data_access)
        if data_access not in inner_sdfg.arrays:
            copydesc = copy.deepcopy(datadesc)
            copydesc.transient = False
            inner_sdfg.add_datadesc(
                name=data_access,
                datadesc=copydesc,
            )
        if data_access not in nsdfg_node.sdfg.arrays:
            copydesc = copy.deepcopy(datadesc)
            copydesc.transient = False
            inner_sdfg.add_datadesc(
                name=data_access,
                datadesc=copydesc,
            )


        # Get all parent scopes to detect how the data needs to flow (MapEntry -> NSDFG means AccessNode -> MapEntry -> NestedSDFG)
        parent_scopes = []
        cur_parent_scope = nsdfg_node
        scope_dict = parent_nsdfg_node_state.scope_dict()
        while scope_dict[cur_parent_scope] is not None:
            parent_scopes.append(scope_dict[cur_parent_scope])
            cur_parent_scope = scope_dict[cur_parent_scope]

        an = parent_nsdfg_node_state.add_access(
            data_access
        )
        src = an
        for parent_scope in reversed(parent_scopes):
            dst = parent_scope
            parent_nsdfg_node_state.add_edge(
                src,
                None if isinstance(src, dace.nodes.AccessNode) else f"OUT_{data_access}",
                dst,
                data_access if isinstance(dst, dace.nodes.NestedSDFG) else f"IN_{data_access}",
                dace.memlet.Memlet.from_array(
                    data_access,
                    datadesc
                )
            )
            if not isinstance(src, dace.nodes.AccessNode):
                src.add_out_connector(f"OUT_{data_access}")
            if isinstance(dst, dace.nodes.NestedSDFG):
                dst.add_in_connector(data_access)
            else:
                dst.add_in_connector(f"IN_{data_access}")
            src = parent_scope
        dst = nsdfg_node
        parent_nsdfg_node_state.add_edge(
            src,
            None if isinstance(src, dace.nodes.AccessNode) else f"OUT_{data_access}",
            dst,
            data_access if isinstance(dst, dace.nodes.NestedSDFG) else f"IN_{data_access}",
            dace.memlet.Memlet.from_array(
                data_access,
                datadesc
            )
        )
        src.add_out_connector(
            f"OUT_{data_access}" if not isinstance(src, dace.nodes.AccessNode) else None
        )
        dst.add_in_connector(data_access if isinstance(dst, dace.nodes.NestedSDFG) else f"IN_{data_access}")

def add_missing_data_and_symbols(root: dace.SDFG, _parent_graph, _parent_sdfg: dace.SDFG, sdfg: dace.SDFG):
    # Get parent NSDFG node
    parent_nsdfg_node = sdfg.parent_nsdfg_node
    missing_symbols = _get_missing_symbols(parent_nsdfg_node)
    # Filter the missing data
    missing_data = set()
    for symbol in missing_symbols:
        if symbol in root.arrays:
            missing_data.add(symbol)

    # Get parent SDFG and parent graph of the nested SDFG node
    parent_sdfg = None
    parent_graph = None
    for node, graph in root.all_nodes_recursive():
        if node == parent_nsdfg_node:
            parent_graph = graph
            parent_sdfg = graph.sdfg
            break
    assert parent_sdfg is not None, "Parent SDFG not found"
    assert parent_graph == _parent_graph, "Parent graph mismatch"
    assert parent_sdfg == _parent_sdfg, "Parent SDFG mismatch"

    if missing_data != set():
        print(f"Adding missing data {missing_data} and symbols {missing_symbols} to NSDFG {parent_nsdfg_node.label}")

    # Add missing data
    _insert_missing_data_through_parent_scopes(missing_data,
                                               parent_nsdfg_node,
                                               parent_graph,
                                               parent_sdfg)

    # Try to add the remaining missing symbols
    missing_symbols = missing_symbols - missing_data

    def _find_state(sdfg: dace.SDFG, node: dace.nodes.Node):
        for n, g in sdfg.all_nodes_recursive():
            if n == node:
                return g
        return None

    cp_missing_symbols = set() #copy.deepcopy(missing_symbols)
    for ms in missing_symbols:
        if "__f2dace_SOA" in str(ms):
            SA_ms = ms.replace("__f2dace_SOA", "__f2dace_SA")
            cp_missing_symbols.add(SA_ms)

        if str(ms).lower() != "and" and str(ms).lower() != "or":
            cp_missing_symbols.add(ms)
    missing_symbols = cp_missing_symbols

    for ms in missing_symbols:
        parent_nsdfg_node.symbol_mapping[ms] = ms
        sdfg.add_symbol(ms, stype=dace.int32)

        cur_parent_sdfg = _parent_sdfg
        while cur_parent_sdfg is not None:
            if ms not in cur_parent_sdfg.symbols:
                cur_parent_sdfg.add_symbol(ms, stype=dace.int32)
                if cur_parent_sdfg.parent_nsdfg_node is not None:
                    cur_parent_sdfg.parent_nsdfg_node.symbol_mapping[ms] = ms

            cur_parent_sdfg = _find_state(sdfg, cur_parent_sdfg.parent_nsdfg_node)

def add_missing_data_and_symbols_to_all_nsdfgs(sdfg: dace.SDFG):
    for node, graph in sdfg.all_nodes_recursive():
        if isinstance(node, dace.nodes.NestedSDFG):
            add_missing_data_and_symbols(sdfg, graph, graph.sdfg, node.sdfg)