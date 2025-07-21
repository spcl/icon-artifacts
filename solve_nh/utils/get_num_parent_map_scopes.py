import dace

def _find_parent_state(root_sdfg: dace.SDFG, node: dace.nodes.NestedSDFG):
    if node is not None:
        # Find parent state of that node
        for n, g in root_sdfg.all_nodes_recursive():
            if n == node:
                parent_state = g
                return parent_state
    return None

def get_num_parent_map_scopes(root_sdfg: dace.SDFG, node: dace.nodes.MapEntry,
                                parent_state: dace.SDFGState):
    scope_dict = parent_state.scope_dict()
    num_parent_maps = 0
    cur_node = node
    while scope_dict[cur_node] is not None:
        if isinstance(scope_dict[cur_node], dace.nodes.MapEntry):
            num_parent_maps += 1
        cur_node = scope_dict[cur_node]

    # Check parent nsdfg
    parent_nsdfg_node = parent_state.sdfg.parent_nsdfg_node
    parent_nsdfg_parent_state = _find_parent_state(root_sdfg, parent_nsdfg_node)

    while parent_nsdfg_node is not None:
        scope_dict = parent_nsdfg_parent_state.scope_dict()
        cur_node = parent_nsdfg_node
        while scope_dict[cur_node] is not None:
            if isinstance(scope_dict[cur_node], dace.nodes.MapEntry):
                num_parent_maps += 1
            cur_node = scope_dict[cur_node]
        parent_nsdfg_node = parent_nsdfg_parent_state.sdfg.parent_nsdfg_node
        parent_nsdfg_parent_state = _find_parent_state(root_sdfg, parent_nsdfg_node)

    return num_parent_maps
