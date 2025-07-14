import dace

def unique_state_names(sdfg: dace.SDFG):
    state_names = dict()
    for node, parent_graph in sdfg.all_nodes_recursive():
        if isinstance(node, dace.SDFGState):
            state_name = node.name # name has no setter
            if state_name not in state_names:
                state_names[state_name] = 0
                new_name = f"{state_name}_{state_names[state_name]}"
            else:
                state_names[state_name] += 1
                new_name = f"{state_name}_{state_names[state_name]}"
            node.label = new_name