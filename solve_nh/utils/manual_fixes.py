import dace
import copy

def connect_ishift_to_map(sdfg: dace.SDFG, state_label:str):
    state, parent_graph = None, None
    for n, g in sdfg.all_nodes_recursive():
        if isinstance(n, dace.SDFGState) and n.label == state_label:
            state = n
            parent_graph = g
            break

    if state is None or parent_graph is None:
        raise ValueError(f"State with label '{state_label}' not found in the SDFG.")

    ishift_access = [n for n in state.nodes() if isinstance(n, dace.nodes.AccessNode) and n.data == "ishift_local"][0]
    map_entry = [n for n in state.nodes() if isinstance(n, dace.nodes.MapEntry)][0]
    assert len([n for n in state.nodes() if isinstance(n, dace.nodes.MapEntry)]) == 1, "Expected exactly one MapEntry node in the state."

    ishift_desc = state.sdfg.arrays["ishift_local"]
    assert len(set([e.dst for e in state.out_edges(map_entry)])) == 1, "Expected exactly one output edge from the MapEntry node."
    nsdfg_node: dace.nodes.NestedSDFG = [e.dst for e in state.out_edges(map_entry)][0]

    state.add_edge(ishift_access, None, map_entry, "IN_ishift_local", dace.Memlet.from_array("ishift_local", ishift_desc))
    state.add_edge(map_entry, "OUT_ishift_local", nsdfg_node, "ishift_local", dace.Memlet.from_array("ishift_local", ishift_desc))
    map_entry.add_in_connector("IN_ishift_local")
    map_entry.add_out_connector("OUT_ishift_local")
    nsdfg_node.add_in_connector("ishift_local")

    inner_sdfg: dace.SDFG = nsdfg_node.sdfg
    if "ishift_local" in inner_sdfg.arrays:
        assert "ishift_local" not in inner_sdfg.symbols
        assert inner_sdfg.arrays["ishift_local"].transient, "Expected 'ishift_local' to be transient in the inner SDFG."
    if "ishift_local" in inner_sdfg.symbols:
        assert "ishift_local" not in inner_sdfg.arrays
    if "ishift_local" in inner_sdfg.symbols:
        inner_sdfg.remove_symbol("ishift_local")
        copydesc = copy.deepcopy(ishift_desc)
        copydesc.transient = False
        inner_sdfg.add_datadesc(
            "ishift_local",
            copydesc,
        )
    elif "ishift_local" in inner_sdfg.arrays:
        inner_sdfg.arrays["ishift_local"].transient = False
    else:
        raise ValueError("Expected 'ishift_local' to be either in arrays or symbols of the inner SDFG.")