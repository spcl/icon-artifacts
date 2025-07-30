import dace
from dace.sdfg.state import CodeBlock, ConditionalBlock
from typing import Tuple

def if_else_to_question_mark(cfg: ConditionalBlock,
                             cond: CodeBlock,
                             true_data: str,
                             false_data: str,
                             dst_data: str):
    pass


def if_else_to_question_mark_pass(sdfg: dace.SDFG):
    for n, g in sdfg.all_nodes_recursive():
        if not isinstance(g, ConditionalBlock):
            continue
        if len(n.branches) != 2:
            continue
        branch1, branch2 = n.branches
        cond1, cond2 = branch1.condition, branch2.condition
        if cond1 != None and cond2 != None:
            print(f"Converting if-else to ? operator in {n.label} with conditions {cond1} and {cond2}")
            raise Exception("Cannot convert if-else to ? operator with both conditions defined")
            continue
        body1, body2 = branch1.body, branch2.body
        if len(body1.nodes()) != 1 or len(body2.nodes()) != 1:
            continue
        node1: dace.SDFGState = body1.nodes()[0]
        node2: dace.SDFGState = body2.nodes()[0]
        if not isinstance(node1, dace.SDFGSState):
            continue
        if not isinstance(node2, dace.SDFGSState):
            continue
        state_nodes1 = node1.bfs_nodes()
        state_nodes2 = node2.bfs_nodes()
        if len(state_nodes1) != 3 or len(state_nodes2) != 3:
            continue
        an1, t1, an2 = state_nodes1
        an3, t2, an4 = state_nodes2
        if an2.data != an4.data:
            continue
        if not isinstance(t1, dace.nodes.Tasklet) or not isinstance(t2, dace.nodes.Tasklet):
            continue
        if t1.code != t2.code:
            continue
        if len(t1.in_connectors) != 1 or len(t1.out_connectors) != 1:
            continue
        if len(t2.in_connectors) != 1 or len(t2.out_connectors) != 1:
            continue
        if t1.code.as_string != f"{next(iter(t1.out_connectors))} = {next(iter(t1.in_connectors))};" or \
           t2.code.as_string != f"{next(iter(t2.out_connectors))} = {next(iter(t2.in_connectors))};":
            continue
        # We can convert this to a ? operator
        if cond1 is None:
            if_else_to_question_mark(cfg=n, cond=cond2,
                                     true_data=an3.data, false_data=an1.data,
                                     dst_data=an2.data)
        else:
            if_else_to_question_mark(cfg=n, cond=cond1,
                                     true_data=an1.data, false_data=an3.data,
                                     dst_data=an2.data)


    pass