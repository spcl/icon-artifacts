from dace import SDFG, InterstateEdge
from dace.frontend.fortran.ast_utils import singular, atmost_one
from dace.sdfg.state import SDFGState, LoopRegion
from copy import deepcopy


def split_predictor_pre_omp_loop(g: SDFG) -> None:
    TARGET_LOOP = "FOR_l_990_c_990"
    PT1_STATES, PT2_STATES = 3, 2

    outerloop, box = singular((n, st) for n, st in g.all_nodes_recursive() if n.label == TARGET_LOOP)
    innerloop = singular(n for n in outerloop.nodes())
    assert len(innerloop.nodes()) == PT1_STATES + PT2_STATES, (
        f"Expected {PT1_STATES} + {PT2_STATES} nodes in the inner loop, found {innerloop.nodes()}"
    )
    outerloop_succ = singular(ed for ed in box.out_edges(outerloop)).dst

    outerloop_pt1: LoopRegion = outerloop
    outerloop_pt1.label = f"{outerloop.label}_pt1"
    outerloop_pt2: LoopRegion = deepcopy(outerloop)
    outerloop_pt2.label = f"{outerloop.label}_pt2"

    for n in outerloop_pt2.all_control_flow_regions(recursive=True):
        n.label = f"{n.label}_pt2"
    for n in outerloop_pt1.all_control_flow_regions(recursive=True):
        n.label = f"{n.label}_pt1"
    for n in outerloop_pt1.all_states():
        n.label = f"{n.label}_pt1"
    for n in outerloop_pt2.all_states():
        n.label = f"{n.label}_pt2"

    box.add_node(outerloop_pt2)
    for ed in box.out_edges(outerloop):
        box.remove_edge(ed)
    box.add_edge(outerloop_pt1, outerloop_pt2, InterstateEdge())
    box.add_edge(outerloop_pt2, outerloop_succ, InterstateEdge())

    innerloop_pt1 = singular(n for n in outerloop_pt1.nodes())
    for n in list(innerloop_pt1.bfs_nodes(innerloop_pt1.start_block))[PT1_STATES:]:
        innerloop_pt1.remove_node(n)

    innerloop_pt2: LoopRegion = singular(n for n in outerloop_pt2.nodes())
    start_state = list(innerloop_pt2.bfs_nodes(innerloop_pt2.start_block))[PT1_STATES]
    for n in list(innerloop_pt2.bfs_nodes(innerloop_pt2.start_block))[:PT1_STATES]:
        innerloop_pt2.remove_node(n)
    assert start_state is not None, "No start state found in the inner loop pt2"
    innerloop_pt2.start_block = innerloop_pt2.node_id(start_state)

    g.validate()
