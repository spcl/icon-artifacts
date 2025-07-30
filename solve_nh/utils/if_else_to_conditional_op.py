import dace
from dace.sdfg.state import CodeBlock, ConditionalBlock
from typing import Tuple
import copy

def if_else_to_conditional_op(cfg: ConditionalBlock,
                             cond: CodeBlock,
                             true_data: str,
                             false_data: str,
                             dst_data: str,
                             true_memlet: dace.Memlet,
                            false_memlet: dace.Memlet,
                            dst_memlet: dace.Memlet):
    parent_graph = cfg.parent_graph
    ies = parent_graph.in_edges(cfg)
    oes = parent_graph.out_edges(cfg)

    parent_graph.remove_node(cfg)

    is_start_state = len(ies) == 0

    state = parent_graph.add_state(
        label=cfg.label + "_cond_state",
        is_start_block=is_start_state,
    )

    for ie in ies:
        parent_graph.add_edge(ie.src, state, copy.deepcopy(ie.data))
    for oe in oes:
        parent_graph.add_edge(state, oe.dst, copy.deepcopy(oe.data))

    td = state.add_access(true_data)
    fd = state.add_access(false_data)

    dst_data = state.add_access(dst_data)

    t = state.add_tasklet(
        name=cfg.label + "_cond_tasklet",
        inputs={"_in_true", "_in_false"},
        outputs={"_out"},
        code=f"_out = ({cond.as_string}) ? _in_true : _in_false;",
        language=dace.dtypes.Language.CPP,
    )

    state.add_edge(td, None, t, "_in_true", copy.deepcopy(true_memlet) if true_memlet is not None else dace.Memlet())
    state.add_edge(fd, None, t, "_in_false", copy.deepcopy(false_memlet) if false_memlet is not None else dace.Memlet())
    state.add_edge(t, "_out", dst_data, None, copy.deepcopy(dst_memlet) if dst_memlet is not None else dace.Memlet())


def if_else_to_coditional_op_pass(sdfg: dace.SDFG):
    num_converted = 0
    for n, g in sdfg.all_nodes_recursive():
        if not isinstance(n, ConditionalBlock):
            continue
        if len(n.branches) != 2:
            continue
        branch1 = n.branches[0]
        branch2 = n.branches[1]
        cond1 = branch1[0]
        cond2 = branch2[0]
        if not ((cond1 is not None and "lvn_pos" in cond1.as_string) or (cond2 is not None and "lvn_pos" in cond2.as_string)):
            continue
        if cond1 != None and cond2 != None:
            #print(f"Converting if-else to ? operator in {n.label} with conditions {cond1} and {cond2}")
            raise Exception("Cannot convert if-else to ? operator with both conditions defined")
            continue
        body1, body2 = branch1[1], branch2[1]
        if len(body1.nodes()) != 1 or len(body2.nodes()) != 1:
            #print(f"Cannot convert if-else to ? operator in {n.label} with bodies {body1} and {body2}")
            continue
        node1: dace.SDFGState = body1.nodes()[0]
        node2: dace.SDFGState = body2.nodes()[0]
        if not isinstance(node1, dace.SDFGState):
            #print(f"Cannot convert if-else to ? operator in {n.label} with body {node1}")
            continue
        if not isinstance(node2, dace.SDFGState):
            #print(f"Cannot convert if-else to ? operator in {n.label} with body {node2}")
            continue
        state_nodes1 = node1.bfs_nodes()
        state_nodes2 = node2.bfs_nodes()
        if len(state_nodes1) != 3 or len(state_nodes2) != 3:
            #print(f"Cannot convert if-else to ? operator in {n.label} with bodies {node1} and {node2}, expected 3 nodes, got {len(state_nodes1)} and {len(state_nodes2)}")
            continue
        an1, t1, an2 = state_nodes1
        an3, t2, an4 = state_nodes2
        if an2.data != an4.data:
            #print(f"Cannot convert if-else to ? operator in {n.label} with bodies {node1} and {node2}, expected same output data, got {an2.data} and {an4.data}")
            continue
        if not isinstance(t1, dace.nodes.Tasklet) or not isinstance(t2, dace.nodes.Tasklet):
            #print(f"Cannot convert if-else to ? operator in {n.label} with bodies {node1} and {node2}, expected tasklets, got {type(t1)} and {type(t2)}")
            continue
        if len(t1.in_connectors) != 1 or len(t1.out_connectors) != 1:
            #print(f"Cannot convert if-else to ? operator in {n.label} with bodies {node1} and {node2}, expected single input and output connectors, got {len(t1.in_connectors)} and {len(t1.out_connectors)}")
            continue
        if len(t2.in_connectors) != 1 or len(t2.out_connectors) != 1:
            #print(f"Cannot convert if-else to ? operator in {n.label} with bodies {node1} and {node2}, expected single input and output connectors, got {len(t2.in_connectors)} and {len(t2.out_connectors)}")
            continue
        if t1.code.as_string != f"{next(iter(t1.out_connectors.keys()))} = {next(iter(t1.in_connectors.keys()))}" or \
           t2.code.as_string != f"{next(iter(t2.out_connectors.keys()))} = {next(iter(t2.in_connectors.keys()))}":
            #print(f"Cannot convert if-else to ? operator in {n.label} with bodies {node1} and {node2}, expected simple assignment tasklets, got {t1.code.as_string} and {t2.code.as_string}")
            continue
        memlet1 = [e for e in node1.edges() if e.src == an1 and e.dst == t1][0].data
        memlet3 = [e for e in node2.edges() if e.src == an3 and e.dst == t2][0].data
        dst_memlet = [e for e in node1.edges() if e.src == t1 and e.dst == an2][0].data
        # We can convert this to a ? operator
        if cond1 is None:
            if_else_to_conditional_op(cfg=n, cond=cond2,
                                     true_data=an3.data, false_data=an1.data,
                                     dst_data=an2.data, true_memlet=memlet3,
                                     false_memlet=memlet1, dst_memlet=dst_memlet)
        else:
            if_else_to_conditional_op(cfg=n, cond=cond1,
                                     true_data=an1.data, false_data=an3.data,
                                     dst_data=an2.data, true_memlet=memlet1,
                                     false_memlet=memlet3, dst_memlet=dst_memlet)
        num_converted += 1
    print(f"Converted {num_converted} if-else statements to ? operators")
    return num_converted