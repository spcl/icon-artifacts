import sympy
import ast
from collections import deque
from dace import SDFG
from dace.sdfg.state import ConditionalBlock
from dace.properties import CodeBlock
from sympy.logic.boolalg import BooleanTrue, BooleanFalse
from dace.transformation.passes.simplification.prune_empty_conditional_branches import PruneEmptyConditionalBranches
from dace.transformation.passes.simplification.control_flow_raising import ControlFlowRaising
from dace.sdfg.nodes import AccessNode, Tasklet
from dace.sdfg.sdfg import InterstateEdge
from dace.frontend.fortran.ast_utils import singular, atmost_one


def str_to_sympy(expr_str: str):
    expr_str = expr_str.replace("== 1", "== true").replace("== 0", "false")
    return sympy.sympify(expr_str, evaluate=False).simplify()


def cleanup_conditionals(g: SDFG):
    ControlFlowRaising().apply_pass(g, {})
    for node, _ in g.all_nodes_recursive():
        if not isinstance(node, ConditionalBlock):
            continue
        for c, _ in node.branches:
            if not isinstance(c, CodeBlock):
                continue
            csym = str_to_sympy(c.as_string)
            if isinstance(csym, BooleanTrue):
                print(f"Node {node}: Evaluating {c.as_string} to True, replacing with 1")
                c.code = [ast.Expr(value=ast.Constant(value=1))]
            elif isinstance(csym, BooleanFalse):
                print(f"Node {node}: Evaluating {c.as_string} to False, replacing with 0")
                c.code = [ast.Expr(value=ast.Constant(value=0))]
            else:
                continue
    PruneEmptyConditionalBranches().apply_pass(g, {})
    g.validate()


def push_interstate_edges_early(g: SDFG):
    # Go through all interstate edges (and push the assignments earlier).
    edge_queue = deque((edge, st) for edge, st in g.all_edges_recursive())
    while len(edge_queue) > 0:
        edge, st = edge_queue.popleft()
        # Only works for interstate edges.
        if not isinstance(edge.data, InterstateEdge):
            continue
        # Only matters if we have assignments.
        iedge = edge.data
        if not iedge.assignments:
            continue
        # Only works when we have only one earlier edge to push towards.
        if st.in_degree(edge.src) != 1:
            continue
        iedge_before = singular(ed for ed in st.in_edges(edge.src))
        if not isinstance(iedge_before.data, InterstateEdge):
            continue
        rset, wset = edge.src.read_and_write_sets()
        # If the produced symbols are being read by the preceding state (at their previous version), we cannot push.
        if any(k in rset for k in iedge.assignments.keys()):
            continue
        # If the required symbols are being written by the preceding state, we cannot push.
        if any(k in wset for k in iedge.free_symbols):
            continue
        # Replace all the required symbols set in the preceding edge into the current edge to avoid ambiguity.
        iedge.replace_dict(iedge_before.data.assignments, replace_keys=False)
        remove_keys = set()
        for k in iedge.assignments.keys():
            if k in iedge_before.data.used_symbols():
                continue
            print(
                f"Node {edge.src}: Pushing interstate edge assignment of {k}: {iedge.assignments[k]} to the preceding edge."
            )
            iedge_before.data.assignments[k] = iedge.assignments[k]
            remove_keys.add(k)
        # Remove the pushed keys from the current edge.
        for k in remove_keys:
            del iedge.assignments[k]
        # If we pushed something to the preceding edge, we need to (re-)queue that one.
        if remove_keys:
            edge_queue.append((iedge_before, st))
    g.validate()


def dead_code_cleanup(g: SDFG):
    # Potentially all transient access nodes are dead code, so we start with all of them as candidates.
    no_readers = set(
        node.data for node, _ in g.all_nodes_recursive() if isinstance(node, AccessNode) and node.desc(sdfg=g).transient
    )
    for node, st in g.all_nodes_recursive():
        if not isinstance(node, AccessNode) or node.data not in no_readers:
            continue
        # If the access node has a reader, we cannot remove it.
        if st.out_degree(node) > 0:
            no_readers.remove(node.data)
    for edge, _ in g.all_edges_recursive():
        if not isinstance(edge.data, InterstateEdge):
            continue
        iedge = edge.data
        for sym in iedge.used_symbols():
            # If the interstate edge reads from a data container into symbol, that's still considered a reader.
            if sym in no_readers:
                no_readers.remove(sym)
    for node, st in g.all_nodes_recursive():
        if not isinstance(node, ConditionalBlock):
            continue
        for x in node.free_symbols:
            # If the conditional block reads from a data container into symbol, that's still considered a reader.
            if x in no_readers:
                no_readers.remove(x)
    if "lvn_pos_local" in no_readers:
        breakpoint()

    # Now we can remove all the access nodes that have no readers.
    for node, st in g.all_nodes_recursive():
        if not isinstance(node, AccessNode) or node.data not in no_readers:
            continue
        in_edge = atmost_one(ed for ed in st.in_edges(node))
        if not in_edge:
            print(f"Node {node}: Removing dead access node {node.data}.")
            st.remove_node(node)
        # We leave the "transified" access nodes alone, to pass validation.
        if isinstance(in_edge.src, AccessNode) and f"{in_edge.src.data}_transified" == node.data:
            continue
        print(f"Node {node}: Removing dead access node {node.data} and dangling path.")
        st.remove_edge_and_connectors(in_edge)
        st.remove_node(node)

    # Clean up empty tasklets.
    for node, st in g.all_nodes_recursive():
        if not isinstance(node, Tasklet):
            continue
        if st.in_degree(node) == 0 and st.out_degree(node) == 0:
            print(f"Node {node}: Removing dead tasklet {node.label}.")
            st.remove_node(node)
    g.validate()
