import dace
from dace.sdfg.state import LoopRegion


def count_loops(sdfg: dace.SDFG):
    loops_post = 0
    for node, state in sdfg.all_nodes_recursive():
        if isinstance(node, LoopRegion):
            print(f"Loop: {node.label}")
            loops_post += 1
    print(f"Loops remaining: {loops_post}")
