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
