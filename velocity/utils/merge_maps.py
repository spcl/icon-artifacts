import dace
import re
from dace.sdfg.nodes import MapEntry, MapExit

def merge_maps(state: dace.SDFGState, m1b: MapEntry, m2b: MapEntry) -> dace.nodes.MapEntry:
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

    # Change the parameter names
    for node in state.all_nodes_between(m1b, m1e):
        for e in state.out_edges(node) + state.in_edges(node):
            e.data.replace(dict(zip(m2_params, m1_params)))

            for s1, s2 in zip(m1_params, m2_params):
              repl_pattern = r"\b" + re.escape(s2) + r"\b"
              e.data.data = re.sub(repl_pattern, s1, e.data.data)
        

