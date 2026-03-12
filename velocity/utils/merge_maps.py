import dace
import re
from dace.sdfg.nodes import MapEntry, MapExit, NestedSDFG
from dace.sdfg import SDFGState
from dace.sdfg.state import ConditionalBlock, LoopRegion


def merge_maps_in_sdfg(sdfg: dace.SDFG) -> None:
    """
    Merge maps in a SDFG. If two maps have the same parameters and ranges and are in the same state, merge them into one.
    """
    processed_states = set()
    for node, parent in sdfg.all_nodes_recursive():
        if not isinstance(parent, SDFGState):
            continue
        if parent in processed_states:
            continue
        processed_states.add(parent)

        # Since during merging we delete maps, we track the original map and the replacement map
        maps = {}
        for n in parent.nodes():
            if isinstance(n, MapEntry):
                maps[n] = n

        # Find pairs of maps to merge
        for k1 in maps.keys():
            for k2 in maps.keys():
                m1 = maps[k1]
                m2 = maps[k2]
                if m1 is m2:
                    continue
                if len(m1.map.params) != len(m2.map.params):
                    continue
                if m1.map.range != m2.map.range:
                    continue
                if ("_for_it_23" in m1.map.params or
                    "_for_it_23" in m2.map.params or
                    "_for_it_29" in m1.map.params or
                    "_for_it_29" in m2.map.params):
                    continue

                # Check if the maps are independent
                preds = set([m1])
                succs = set([m1])
                changed = True
                while changed:
                    changed = False
                    new_preds = preds.copy()
                    new_succs = succs.copy()
                    for pas in preds:
                        new_preds.update(parent.predecessors(pas))
                    for pas in succs:
                        new_succs.update(parent.successors(pas))
                    if new_preds != preds or new_succs != succs:
                        changed = True
                        preds = new_preds
                        succs = new_succs

                if m2 in preds or m2 in succs:
                    continue

                # Merge the maps
                print(f"Merging maps {m1.guid} and {m2.guid}")
                merge_maps(parent, m1, m2)
                maps[k2] = m1


def merge_maps(state: dace.SDFGState, m1b: MapEntry, m2b: MapEntry) -> None:
    """
    Merge two maps in a SDFG. Eliminate the second one. Both maps must have the same parameters and ranges.
    """

    m1_params = m1b.map.params
    m1_range = m1b.map.range
    m2_params = m2b.map.params
    m2_range = m2b.map.range

    # Sanity check
    assert len(m1_params) == len(m2_params)
    assert m1_range == m2_range
    assert m1b in state.nodes()
    assert m2b in state.nodes()

    # Need to be on two independent subgraphs (i.e. not depend on eachother)
    preds = set([m1b])
    succs = set([m1b])
    changed = True
    while changed:
        changed = False
        new_preds = preds.copy()
        new_succs = succs.copy()
        for pas in preds:
            new_preds.update(state.predecessors(pas))
        for pas in succs:
            new_succs.update(state.successors(pas))
        if new_preds != preds or new_succs != succs:
            changed = True
            preds = new_preds
            succs = new_succs
    assert m2b not in preds and m2b not in succs

    # Get exits
    m1e = state.exit_node(m1b)
    m2e = state.exit_node(m2b)

    # Add accesses from the second map to the first one
    m2b_m1b_map = {}
    for con, t in m2b.in_connectors.items():
        m1_name = f"{con}_2"
        m1b.add_in_connector(m1_name, t)
        m2b_m1b_map[con] = m1_name
    for con, t in m2b.out_connectors.items():
        m1_name = f"{con}_2"
        m1b.add_out_connector(m1_name, t)
        assert con not in m2b_m1b_map
        m2b_m1b_map[con] = m1_name

    m2e_m1e_map = {}
    for con, t in m2e.in_connectors.items():
        m1_name = f"{con}_2"
        m1e.add_in_connector(m1_name, t)
        m2e_m1e_map[con] = m1_name
    for con, t in m2e.out_connectors.items():
        m1_name = f"{con}_2"
        m1e.add_out_connector(m1_name, t)
        assert con not in m2e_m1e_map
        m2e_m1e_map[con] = m1_name

    # Change the edges
    for e in list(state.in_edges(m2b)):
        state.remove_edge(e)
        state.add_edge(e.src, e.src_conn, m1b, m2b_m1b_map[e.dst_conn], e.data)
    for e in list(state.out_edges(m2b)):
        state.remove_edge(e)
        state.add_edge(m1b, m2b_m1b_map[e.src_conn], e.dst, e.dst_conn, e.data)
    for e in list(state.in_edges(m2e)):
        state.remove_edge(e)
        state.add_edge(e.src, e.src_conn, m1e, m2e_m1e_map[e.dst_conn], e.data)
    for e in list(state.out_edges(m2e)):
        state.remove_edge(e)
        state.add_edge(m1e, m2e_m1e_map[e.src_conn], e.dst, e.dst_conn, e.data)

    # Remove the second map
    state.remove_nodes_from([m2b, m2e])

    # FIXME: What if m1_params = [a,b] and m2_params = [b,a]?
    assert set(m1_params) & set(m2_params) == set()

    # Change the parameter names
    for node in state.all_nodes_between(m1b, m1e):
        for e in state.out_edges(node) + state.in_edges(node):
            e.data.replace(dict(zip(m2_params, m1_params)))

            if e.data.data is not None:
                for s1, s2 in zip(m1_params, m2_params):
                    repl_pattern = r"\b" + re.escape(s2) + r"\b"
                    e.data.data = re.sub(repl_pattern, s1, e.data.data)

        if isinstance(node, NestedSDFG):
            for s1, s2 in zip(m1_params, m2_params):
                if s2 in node.symbol_mapping:
                    node.symbol_mapping[s2] = s1
