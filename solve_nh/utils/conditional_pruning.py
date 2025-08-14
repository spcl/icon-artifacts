from copy import deepcopy
import sympy
import ast
from collections import deque
from dace import SDFG, symbolic
from dace.sdfg.state import ConditionalBlock, SDFGState
from dace.properties import CodeBlock
from sympy.logic.boolalg import BooleanTrue, BooleanFalse
from dace.transformation.passes.simplification.prune_empty_conditional_branches import PruneEmptyConditionalBranches
from dace.transformation.passes.simplification.control_flow_raising import ControlFlowRaising
from dace.transformation.passes.dead_dataflow_elimination import DeadDataflowElimination
from dace.transformation.passes.analysis.analysis import ControlFlowBlockReachability
from dace.sdfg.nodes import AccessNode, Tasklet
from dace.sdfg.sdfg import InterstateEdge
from dace.frontend.fortran.ast_utils import singular, atmost_one
from dace.sdfg.utils import remove_edge_and_dangling_path
from dace.transformation.helpers import redirect_edge


class LiteralExpressionChecker(ast.NodeVisitor):
    """
    A visitor that checks if an AST is a "literal expression".
    """

    # Whitelist of safe AST node types.
    # We allow constants, basic operations, and comparisons.
    ALLOWED_NODE_TYPES = {
        ast.Constant,  # e.g., 1, 'string', True, None
        ast.BinOp,  # e.g., +, -, *, /
        ast.UnaryOp,  # e.g., -, not
        ast.BoolOp,  # e.g., and, or
        ast.Compare,  # e.g., ==, >, <
        ast.Expression,  # Top-level node for a single expression
        ast.Tuple,  # Tuples of constants are often safe
        ast.List,  # Lists of constants are often safe
        # Operations
        ast.Add,
        ast.Sub,
        ast.Mult,
        ast.Div,
        ast.FloorDiv,
        ast.Mod,
        ast.Pow,
        ast.USub,
        ast.UAdd,
        ast.Invert,
        # Comparisons
        ast.Eq,
        ast.NotEq,
        ast.Lt,
        ast.LtE,
        ast.Gt,
        ast.GtE,
        ast.Is,
        ast.IsNot,
        ast.In,
        ast.NotIn,
        # Boolean operations
        ast.And,
        ast.Or,
        ast.Not,
    }

    def __init__(self):
        self.is_safe = True

    def generic_visit(self, node):
        # If the node's type is not in our whitelist, it's not safe.
        if type(node) not in self.ALLOWED_NODE_TYPES:
            self.is_safe = False
            # We don't need to continue visiting, but we can't stop the traversal easily.
            # We'll just rely on the flag.
            return

        # Continue visiting the child nodes.
        super().generic_visit(node)


def is_literal_expression(node):
    checker = LiteralExpressionChecker()
    checker.visit(node)
    return checker.is_safe


def evaluate_literal_expression(node):
    # 1. First, get the actual expression node, regardless of the wrapper.
    if isinstance(node, ast.Expr):
        expression = node.value
    else:
        # If it's not an Expr, assume it's the expression itself.
        expression = node

    # 2. Perform the safety check on the expression.
    if not is_literal_expression(expression):
        return None, "Expression contains non-literal or unsafe elements."

    # 3. Compile and evaluate safely.
    try:
        safe_globals = {"__builtins__": {}}
        safe_locals = {}

        # Compile the expression node, using the 'eval' mode.
        compiled_code = compile(ast.Expression(expression), "<string>", "eval")

        result = eval(compiled_code, safe_globals, safe_locals)
        return result, "success"

    except Exception as e:
        return None, f"An error occurred during evaluation: {e}"


def cleanup_conditionals(g: SDFG):
    ControlFlowRaising().apply_pass(g, {})
    for node, st in g.all_nodes_recursive():
        if not isinstance(node, ConditionalBlock):
            continue
        yep, nope = None, []
        for i, (c, _) in enumerate(node.branches):
            if not isinstance(c, CodeBlock) or not is_literal_expression(ast.parse(c.as_string, mode="eval").body):
                continue
            cval, _ = evaluate_literal_expression(ast.parse(c.as_string, mode="eval").body)
            if cval is True:
                print(f"Node {node}: Evaluating {c.as_string} to True, replacing with 1")
                c.code = [ast.Expr(value=ast.Constant(value=1))]
                if yep is None:
                    yep = i
            elif cval is False:
                print(f"Node {node}: Evaluating {c.as_string} to False, replacing with 0")
                c.code = [ast.Expr(value=ast.Constant(value=0))]
                nope.append(i)
            else:
                continue
        if yep is not None:
            node._branches = node._branches[: yep + 1]
        for n in reversed(nope):
            if n < len(node._branches):
                node._branches = node._branches[:n] + node._branches[n + 1 :]
        if len(node._branches) == 0:
            # Replace with an empty state.
            dummyst = st.add_state("removed_conditional")
            for e in st.in_edges(node):
                st.add_edge(e.src, dummyst, e.data)
                st.remove_edge(e)
            for e in st.out_edges(node):
                st.add_edge(dummyst, e.dst, e.data)
                st.remove_edge(e)
            st.remove_node(node)
        if yep is not None and len(node._branches) == 1:
            print(f"Node {node}: Condition is always true, so inlining entirely.")
            node.inline()
    for e, st in g.all_edges_recursive():
        if not isinstance(e.data, InterstateEdge) or not e.data.condition:
            continue
        cval, _ = evaluate_literal_expression(ast.parse(e.data.condition.as_string, mode="eval").body)
        if cval is False:
            st.remove_edge(e)
    PruneEmptyConditionalBranches().apply_pass(g, {})
    g.validate()


def push_interstate_edges_early(g: SDFG):
    single_assignment_symbols: dict[str, int] = {}
    for edge, _ in g.all_edges_recursive():
        if not isinstance(edge.data, InterstateEdge):
            continue
        iedge = edge.data
        for k in iedge.assignments.keys():
            if k not in single_assignment_symbols:
                single_assignment_symbols[k] = 1
            else:
                single_assignment_symbols[k] += 1
    single_assignment_symbols: set[str] = {k for k, v in single_assignment_symbols.items() if v == 1}

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
        rset, wset = edge.src.read_and_write_sets()
        # If the required symbols are being written by the preceding state, we cannot push.
        if any(k in wset for k in iedge.free_symbols):
            continue
        if st.in_degree(edge.src) == 1:
            # This only works when we have only one earlier edge to push towards.
            iedge_before = singular(ed for ed in st.in_edges(edge.src))
            if not isinstance(iedge_before.data, InterstateEdge):
                continue
            if iedge_before.src.label == "entry_interface":
                continue
            # Replace all the required symbols set in the preceding edge into the current edge to avoid ambiguity.
            iedge.replace_dict(iedge_before.data.assignments, replace_keys=False)
            remove_keys = set()
            for k in iedge.assignments.keys():
                # If the produced symbols are being read by the preceding state (at their previous version), we cannot push.
                if k in iedge_before.data.used_symbols() or k in rset:
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
        elif st.in_degree(edge.src) == 0:
            # If we have no predecessors, we can try pushing above instead.
            pst = st
            while pst.parent_graph and pst.parent_graph.in_degree(pst) == 0:
                pst = pst.parent_graph
            # Again, this only works when we have only one earlier edge to push towards.
            if pst.parent_graph is None or pst.parent_graph.in_degree(pst) != 1:
                continue
            iedge_above = singular(ed for ed in pst.parent_graph.in_edges(pst))
            if not isinstance(iedge_above.data, InterstateEdge):
                continue
            # Replace all the required symbols set in the preceding edge into the current edge to avoid ambiguity.
            iedge.replace_dict(iedge_above.data.assignments, replace_keys=False)
            remove_keys = set()
            for k, v in iedge.assignments.items():
                access_less_arrays: set[str] = set(st.sdfg.arrays.keys()) - set(
                    n.data
                    for n, t in st.sdfg.all_nodes_recursive()
                    if isinstance(n, AccessNode)
                    if t.label not in {"entry_interface", "exit_interface"}
                )
                need_syms = set(symbolic.symbols_in_ast(ast.parse(v)))
                if not need_syms.issubset(access_less_arrays):
                    continue
                # If the produced symbols are being read by the preceding state (at their previous version), we cannot push.
                if k in iedge_above.data.used_symbols() or k in rset:
                    continue
                print(
                    f"Node {edge.src}: Pushing interstate edge assignment of {k}: {iedge.assignments[k]} to the preceding edge."
                )
                iedge_above.data.assignments[k] = iedge.assignments[k]
                remove_keys.add(k)
            # Remove the pushed keys from the current edge.
            for k in remove_keys:
                del iedge.assignments[k]
            # If we pushed something to the preceding edge, we need to (re-)queue that one.
            if remove_keys:
                edge_queue.append((iedge_above, pst.parent_graph))
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
