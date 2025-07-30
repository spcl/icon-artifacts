import dace
from typing import Set
import copy
import sympy


def _get_missing_symbols(nsdfg_node: dace.nodes.NestedSDFG) -> Set[str]:
    nsdfg = nsdfg_node.sdfg
    connectors = nsdfg_node.in_connectors.keys() | nsdfg_node.out_connectors.keys()
    #symbols = set(k for k in nsdfg.free_symbols if k not in connectors)
    #missing_symbols = [s for s in symbols if s not in nsdfg_node.symbol_mapping]
    #symbols = nsdfg.symbols
    #symbol_mapping = nsdfg_node.symbol_mapping
    symbols = set(k for k in nsdfg.used_symbols(all_symbols=False) if k not in connectors)
    missing_symbols = [s for s in symbols if s not in nsdfg_node.symbol_mapping]
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
                                               parent_sdfg: dace.SDFG,
                                               descs: Set[dace.data.Data] | None = None):
    # For each data access added, add the data descriptor and connecto to the parent NSDFG node
    descs = set()
    if descs is None:
        for _ in missing_data:
            descs.add(None)
    for data_access, desc in zip(missing_data, descs):
        # If array is not in parent graphs's sdfg's data containers add it
        if desc is not None:
            datadesc = desc
        else:
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
            if len(list(parent_nsdfg_node_state.in_edges_by_connector(nsdfg_node, data_access))) > 0:
                #print(f"Data {data_access} already in NSDFG {nsdfg_node.label}, skipping")
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

def _insert_missing_data_through_parent_out_scopes(missing_data: Set[str],
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
        # multiple edges to the same nSDFG outconnector is invalid.
        if data_access in nsdfg_node.out_connectors:
            if len(list(parent_nsdfg_node_state.out_edges_by_connector(nsdfg_node, data_access))) > 0:
                #print(f"Data {data_access} already in NSDFG {nsdfg_node.label}, skipping")
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

        # Need to add to exit only this time
        an = parent_nsdfg_node_state.add_access(
            data_access
        )
        dst = an
        for parent_scope in reversed(parent_scopes):
            parent_exit_scope = parent_nsdfg_node_state.exit_node(parent_scope)
            src = parent_exit_scope
            parent_nsdfg_node_state.add_edge(
                src,
                data_access if isinstance(src, dace.nodes.NestedSDFG) else f"OUT_{data_access}",
                dst,
                None if isinstance(dst, dace.nodes.AccessNode) else f"IN_{data_access}",
                dace.memlet.Memlet.from_array(
                    data_access,
                    datadesc
                )
            )
            if not isinstance(dst, dace.nodes.AccessNode):
                dst.add_in_connector(f"IN_{data_access}")
            if isinstance(src, dace.nodes.NestedSDFG):
                src.add_out_connector(data_access)
            else:
                src.add_out_connector(f"OUT_{data_access}")
            dst = parent_exit_scope
        src = nsdfg_node
        parent_nsdfg_node_state.add_edge(
            src,
            data_access,
            dst,
            None if isinstance(dst, dace.nodes.AccessNode) else f"IN_{data_access}",
            dace.memlet.Memlet.from_array(
                data_access,
                datadesc
            )
        )
        dst.add_in_connector(f"IN_{data_access}" if not isinstance(dst, dace.nodes.AccessNode) else None)

def add_missing_data_and_symbols(root: dace.SDFG, _parent_graph, _parent_sdfg: dace.SDFG, sdfg: dace.SDFG):
    # Get parent NSDFG node
    parent_nsdfg_node = sdfg.parent_nsdfg_node
    missing_symbols = _get_missing_symbols(parent_nsdfg_node)
    # Filter the missing data
    missing_data = set()
    for symbol in missing_symbols:
        if symbol in root.arrays or symbol in _parent_sdfg.arrays or symbol in sdfg.arrays:
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

    cp_missing_symbols = set() #copy.deepcopy(missing_symbols)
    for ms in missing_symbols:
        if "tmp_index" in ms:
            continue

        # Should not need this hack
        #if "__f2dace_SOA" in str(ms):
        #    SA_ms = ms.replace("__f2dace_SOA", "__f2dace_SA")
        #    cp_missing_symbols.add(SA_ms)

        if str(ms).lower() != "and" and str(ms).lower() != "or":
            cp_missing_symbols.add(ms)
    missing_symbols = cp_missing_symbols

    for ms in missing_symbols:
        if ms in _parent_sdfg.symbols:
            assert ms in _parent_sdfg.symbols, f"Symbol {ms} not found in parent SDFG {parent_sdfg.name}"
            parent_nsdfg_node.symbol_mapping[ms] = ms
            sdfg.add_symbol(ms, _parent_sdfg.symbols[ms])
        else:
            if ms not in sdfg.symbols:
                sdfg.add_symbol(ms, dace.int32)

def add_missing_data_and_symbols_to_all_nsdfgs(sdfg: dace.SDFG):
    for node, graph in sdfg.all_nodes_recursive():
        if isinstance(node, dace.nodes.NestedSDFG):
            add_missing_data_and_symbols(sdfg, graph, graph.sdfg, node.sdfg)