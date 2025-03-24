import dace
from dace.sdfg.state import LoopRegion


def count_loops(sdfg: dace.SDFG, verbose: bool = False, assert_loops: bool = False):
    loops_post = 0
    for node, state in sdfg.all_nodes_recursive():
        if isinstance(node, LoopRegion):
            if verbose:
                print(f"Loop: {node.label}")
            loops_post += 1

    if verbose:
        print(f"Loops remaining: {loops_post}")

    if assert_loops:
        assert loops_post == 0, f"Loops remaining: {loops_post}"


def count_max_maps_per_state(sdfg: dace.SDFG, verbose: bool = False, assert_maps: bool = False):
    max_maps_per_state = 0
    for state in sdfg.nodes():
        maps = [
            n
            for n in state.nodes()
            if isinstance(n, dace.nodes.MapEntry) and state.entry_node(n) is None
        ]
        max_maps_per_state = max(max_maps_per_state, len(maps))
    
    if verbose:
        print(f"Max maps per state: {max_maps_per_state}")
    
    if assert_maps:
        assert max_maps_per_state <= 1, f"Max maps per state: {max_maps_per_state}"
