import dace
from dace.sdfg.state import LoopRegion, SDFGState, MultiConnectorEdge
from dace.sdfg.nodes import NestedSDFG, MapExit
from dace.memlet import Memlet
from dace import symbolic


def _reannotate_memlet_pair(
    loop_var,
    in_edge: MultiConnectorEdge,
    out_edge: MultiConnectorEdge,
    state: SDFGState,
    loop_name: str,
):
    # Find the dimension of the in_edge that is dependent on the loop variable
    loop_var_dim = None
    dim_expr = None
    in_edge_memlet: Memlet = in_edge.data
    for i, (irb, ire, _) in enumerate(in_edge_memlet.get_dst_subset(in_edge, state)):
        if loop_var in irb.free_symbols or loop_var in ire.free_symbols:
            loop_var_dim = i
            dim_expr = in_edge_memlet.get_dst_subset(in_edge, state)[i]
            break
    assert (
        loop_var_dim is not None
    ), f"Loop variable '{loop_var}' not found in the input memlet for {loop_name}."

    # Replace the output memlet's subset in the same dimension with the input memlet's subset
    out_edge.data.dst_subset[i] = dim_expr

    # Now we also want to set the volume to a fixed size
    out_edge.data.volume = 100  # Arbitrary value
    out_edge.data.dynamic = False


def reannotate_map_memlets(sdfg: dace.SDFG, loop_name: str):
    """
    This function reannotates the outgoing memlets of a map as a preprocessing step for LoopToMap. Because some memlets are overapproximated.

    Args:
        sdfg (dace.SDFG): The SDFG to modify.
        loop_name (str): The name of the surrounding for loop.
    """

    # First, find the for loop node in the SDFG
    loop_region: LoopRegion = None
    for node, parent in sdfg.all_nodes_recursive():
        if node.label == loop_name and isinstance(node, LoopRegion):
            loop_region = node
            break

    # As a sanity check, the loop region should only contain a single state with a map node in it
    assert loop_region is not None, f"Loop '{loop_name}' not found in the SDFG."
    assert (
        len(list(loop_region.all_states())) == 1
    ), f"Loop '{loop_name}' should contain exactly one state."

    state: SDFGState = list(loop_region.all_states())[0]
    map_exit = None
    for node in state.nodes():
        if isinstance(node, MapExit):
            map_exit = node
            break

    assert map_exit is not None, f"Map node not found in the loop region '{loop_name}'."

    # If the map contains a nested SDFG, first propagate the nested SDFGs memlet
    loop_var = symbolic.pystr_to_symbolic(loop_region.loop_variable)
    nested_sdfg: NestedSDFG = None
    for node, parent in state.all_nodes_recursive():
        if isinstance(node, NestedSDFG):
            nested_sdfg = node
            break
    if nested_sdfg is not None:
        assert (
            len(nested_sdfg.sdfg.sink_nodes()) == 1
        ), f"Nested SDFG in loop '{loop_name}' should have exactly one sink node."
        assert (
            state.out_degree(nested_sdfg) == 1
        ), f"Nested SDFG in loop '{loop_name}' should have exactly one outgoing edge."
        last_state = nested_sdfg.sdfg.sink_nodes()[0]
        last_write_edge = None
        for node in last_state.nodes():
            if last_state.in_degree(node) != 0 and last_state.out_degree(node) == 0:
                for e, _ in last_state.all_edges_recursive():
                    if e.dst == node:
                        last_write_edge = e
                        break
                break
        assert (
            last_write_edge is not None
        ), f"Last state in nested SDFG of loop '{loop_name}' should have at least one incoming edge."

        # Reannotate the memlet pair
        _reannotate_memlet_pair(
            loop_var, last_write_edge, state.out_edges(nested_sdfg)[0], state, loop_name
        )

    # Now for each in/out pair of the exit, check which input is dependent on the loop variable, copy that to the output memlet.
    for in_conn, _ in map_exit.in_connectors.items():
        # Should only have one incomming memlet
        assert (
            len(list(state.in_edges_by_connector(map_exit, in_conn))) == 1
        ), f"Map exit '{map_exit.label}' has multiple incoming edges for connector '{in_conn}' for {loop_name}."

        # Find the corresponding out connector (replace first 2 "IN" characters with "OUT")
        out_conn = in_conn.replace("IN", "OUT", 1)
        assert (
            out_conn in map_exit.out_connectors
        ), f"Output connector '{out_conn}' not found in map exit '{map_exit.label}' for {loop_name}."
        assert (
            len(list(state.out_edges_by_connector(map_exit, out_conn))) == 1
        ), f"Map exit '{map_exit.label}' has multiple outgoing edges for connector '{out_conn}' for {loop_name}."

        # Reannotate the memlet pair
        in_edge: MultiConnectorEdge = list(
            state.in_edges_by_connector(map_exit, in_conn)
        )[0]
        out_edge: MultiConnectorEdge = list(
            state.out_edges_by_connector(map_exit, out_conn)
        )[0]
        _reannotate_memlet_pair(loop_var, in_edge, out_edge, state, loop_name)
