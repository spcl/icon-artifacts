import sympy
import ast
from collections import deque
from dace import SDFG
from dace.sdfg.state import ConditionalBlock
from dace.properties import CodeBlock
from sympy.logic.boolalg import BooleanTrue, BooleanFalse
from dace.transformation.passes.simplification.prune_empty_conditional_branches import PruneEmptyConditionalBranches
from dace.sdfg.nodes import AccessNode
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
        for k in remove_keys:
            del iedge.assignments[k]
        if remove_keys:
            edge_queue.append((iedge_before, st))
    g.validate()
