import dace
from dace.sdfg import InterstateEdge
from dace.sdfg.state import ConditionalBlock, ControlFlowRegion
from dace.sdfg.nodes import MapEntry, MapExit, NestedSDFG
import copy


def swap_map_condition(sdfg: dace.SDFG, cond_block_name):
    """
    If one or multiple maps are surrounded by a conditional block, moves the conditional block into the nested SDFG of maps.
    """
    # Find the conditional block
    cond_block: ConditionalBlock = None
    for node, _ in sdfg.all_nodes_recursive():
        if node.label == cond_block_name:
            cond_block = node
            break
    assert (
        cond_block is not None
    ), f"Conditional block {cond_block_name} not found in SDFG {sdfg.name}"

    # The conditional block should only contain one condition
    assert (
        len(cond_block.branches) == 1
    ), f"Conditional block {cond_block_name} has multiple branches"
    branch: ControlFlowRegion = cond_block.branches[0][1]
    branch_cond = cond_block.branches[0][0]

    # Make sure that each state in the branch is either empty or only contains maps
    for state in branch.all_states():
        for node in state.nodes():
            if isinstance(node, (MapEntry, MapExit)):
                continue
            if state.entry_node(node) is not None:
                continue  # Node is part of a map
            if all(
                [
                    isinstance(n, (MapEntry, MapExit))
                    for n in set(state.successors(node)) | set(state.predecessors(node))
                ]
            ):
                continue

            raise ValueError(
                f"State {state.label} in branch {branch.label} of conditional block {cond_block_name} contains nodes other than maps"
            )

    # Make sure that the condition symbol is not overwritten in the branch
    cond_syms = set(branch_cond.get_free_symbols())
    for iedge in branch.all_interstate_edges():
        for k in iedge.data.assignments.keys():
            if str(k) in cond_syms:
                raise ValueError(
                    f"Condition symbol {k} is overwritten in branch {branch.label} of conditional block {cond_block_name}"
                )

    # Ensure that each map contains a single nested SDFG
    # TODO: If the map does not contain a nested SDFG, we can wrap the body into one
    for state in branch.all_states():
        for node in state.nodes():
            if not isinstance(node, MapEntry):
                continue
            assert (
                len(list(state.all_nodes_between(node, state.exit_node(node)))) == 1
            ), f"Map {node.label} in state {state.label} of branch {branch.label} does not contain a single nested SDFG"
            nsdfg = list(state.all_nodes_between(node, state.exit_node(node)))[0]
            if not isinstance(nsdfg, NestedSDFG):
                raise ValueError(
                    f"Map {node.label} in state {state.label} of branch {branch.label} does not contain a single nested SDFG"
                )

    # Wrap all states in the nested SDFGs with the conditional block
    for state in branch.all_states():
        for node in state.nodes():
            if not isinstance(node, MapEntry):
                continue
            nsdfg = list(state.all_nodes_between(node, state.exit_node(node)))[0]
            if not isinstance(nsdfg, NestedSDFG):
                raise ValueError(
                    f"Map {node.label} in state {state.label} of branch {branch.label} does not contain a single nested SDFG"
                )

            new_cond_branch = ControlFlowRegion()
            new_cond_branch.add_nodes_from(nsdfg.sdfg.all_control_flow_blocks())

            new_cond_block = ConditionalBlock()
            new_cond_block.add_branch(branch_cond, new_cond_branch)

            nsdfg.sdfg.remove_nodes_from(nsdfg.sdfg.all_control_flow_blocks())
            nsdfg.sdfg.add_node(new_cond_block)

    # Move all states in the branch before the conditional block
    src_state = sdfg.add_state_before(cond_block)
    dst_state = sdfg.add_state_after(cond_block)
    copy_mapping = {}
    for state in branch.all_states():
        new_state = copy.deepcopy(state)
        sdfg.add_node(new_state)
        copy_mapping[state] = new_state

    for state in branch.all_states():
        for edge in branch.in_edges(state):
            sdfg.add_edge(
                copy_mapping[edge.src], copy_mapping[state], copy.deepcopy(edge.data)
            )

    sdfg.add_edge(src_state, copy_mapping[branch.start_block], InterstateEdge())
    for sink in branch.sink_nodes():
        sdfg.add_edge(copy_mapping[sink], dst_state, InterstateEdge())

    # Remove the conditional block
    sdfg.remove_node(cond_block)
