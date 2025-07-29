import sympy
import ast
from dace import SDFG
from dace.sdfg.state import ConditionalBlock
from dace.properties import CodeBlock
from sympy.logic.boolalg import BooleanTrue, BooleanFalse
from dace.transformation.passes.simplification.prune_empty_conditional_branches import PruneEmptyConditionalBranches


def str_to_sympy(expr_str: str):
    return sympy.sympify(expr_str, locals=sympy.__dict__.copy(), evaluate=False).simplify()


def cleanup_conditionals(g: SDFG):
    for node, _ in g.all_nodes_recursive():
        if not isinstance(node, ConditionalBlock):
            continue
        # yep, nope = None, []
        for i, (c, _) in enumerate(node.branches):
            if not isinstance(c, CodeBlock):
                continue
            csym = str_to_sympy(c.as_string)
            if isinstance(csym, BooleanTrue):
                print(f"Node {node}: Evaluating {c.as_string} to True, replacing with 1")
                c.code = [ast.Expr(value=ast.Constant(value=1))]
                # if yep is None:
                #     yep = i
            elif isinstance(csym, BooleanFalse):
                print(f"Node {node}: Evaluating {c.as_string} to False, replacing with 0")
                c.code = [ast.Expr(value=ast.Constant(value=0))]
                # nope.append(i)
            else:
                continue
    PruneEmptyConditionalBranches().apply_pass(g, {})
    g.validate()
