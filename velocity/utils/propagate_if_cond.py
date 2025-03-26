import dace
from dace.codegen.control_flow import ConditionalBlock, ControlFlowRegion
from dace.codegen.targets.unroller import product
from dace.transformation.passes import DeadStateElimination
from dace.transformation.passes.constant_propagation import ConstantPropagation
import ast
import operator as op
#lextra_diffu = 1
#ldeepatmo = 0

def extract_variables_from_ast(expr_str):
    """
    Extracts all variable names from the provided expression string using AST.
    :param expr_str: The expression string to analyze.
    :return: A set of variable names (strings).
    """
    # Parse the expression string into an AST
    tree = ast.parse(expr_str, mode='eval')

    # Set to store variable names
    variables = set()

    # Define a helper function to recursively visit AST nodes
    def visit_node(node):
        if isinstance(node, ast.Name):  # Variables are represented by ast.Name
            variables.add(node.id)
        # Recursively visit children nodes
        for child in ast.iter_child_nodes(node):
            visit_node(child)

    # Visit the root node of the AST
    visit_node(tree.body)

    return variables

# Example usage
expr_str = "((1 - lvn_only) and 0)"

# Define environment with some variables
def eval_expr_any_value(expr_str, env=None):
    """
    Evaluates a string expression where undefined variables can have any value.
    :param expr_str: The expression to evaluate.
    :param env: The environment (dictionary) of variables with their values.
    :return: Evaluated result or symbolic result for undefined variables.
    """
    if env is None:
        env = {}

    # Parse the expression string into an AST
    tree = ast.parse(expr_str, mode='eval')

    # Define a helper function to safely evaluate the AST
    def eval_node(node, env):
        if isinstance(node, ast.Expression):
            return eval_node(node.body, env)

        elif isinstance(node, ast.UnaryOp):
            operand = eval_node(node.operand, env)
            return op.neg(operand) if isinstance(node.op, ast.UAdd) else op.pos(operand)

        elif isinstance(node, ast.BinOp):
            left = eval_node(node.left, env)
            right = eval_node(node.right, env)

            # Check if any operand is an undefined variable (symbolic placeholder)
            if left == "undefined_var" or right == "undefined_var":
                return "undefined_var"  # Return a symbolic placeholder

            if isinstance(node.op, ast.Add):
                return op.add(left, right)
            elif isinstance(node.op, ast.Sub):
                return op.sub(left, right)
            elif isinstance(node.op, ast.Mult):
                return op.mul(left, right)
            elif isinstance(node.op, ast.Div):
                return op.truediv(left, right)

        elif isinstance(node, ast.BoolOp):  # Handling boolean operations (and, or)
            values = [eval_node(value, env) for value in node.values]
            if isinstance(node.op, ast.And):
                return all(values)
            elif isinstance(node.op, ast.Or):
                return any(values)

        elif isinstance(node, ast.Name):  # Handling variables
            # Check if variable is in the environment
            if node.id in env:
                return env[node.id]
            else:
                # If the variable is not defined, assume it can take any value
                return "undefined_var"  # Symbolic placeholder for an undefined variable

        elif isinstance(node, ast.Constant):  # Handling constants (numbers, strings)
            return node.value

        else:
            raise TypeError(f"Unsupported AST node type: {type(node)}")

    return eval_node(tree.body, env)

def evaluate_with_0_and_1(expr_str):
    # Extract variables from the expression
    variables = extract_variables_from_ast(expr_str)

    # Create all combinations of 0 and 1 for the variables
    all_combinations = list(product([0, 1], repeat=len(variables)))

    # Store the results for each combination
    results = {}

    # Iterate over all combinations of 0 and 1
    for combination in all_combinations:
        # Create an environment with the current combination
        env = dict(zip(variables, combination))

        # Evaluate the expression for the current environment
        result = eval_expr_any_value(expr_str, env)

        # Store the result for the current combination of variables
        results[tuple(combination)] = result

    results_eval = set(results.values())
    return results_eval

def evaluate_interstate_assignments_and_ifs(graph : dace.SDFG | ControlFlowRegion, verbose):
    for e in graph.edges():
        if isinstance(e.data, dace.InterstateEdge):
            new_assignments = dict()
            for assignment, expr_str in e.data.assignments.items():
                try:
                    variables = extract_variables_from_ast(expr_str)
                    if len(variables) == 0:
                        raise Exception("No variables")
                    simplified = evaluate_with_0_and_1(expr_str)
                    if len(simplified) == 1:
                        simplified = simplified.pop()
                        if isinstance(simplified, int):
                            simplified = bool(simplified)
                    else:
                        raise ValueError("Eval Error")
                except Exception as ex:
                    simplified = expr_str
                if "(1 - 0)" == simplified:
                    simplified = "1"
                if simplified is False:
                    simplified = "0"
                if simplified is True:
                    simplified = "1"
                if simplified == "False":
                    simplified = "0"
                if simplified == "True":
                    simplified = "1"
                if simplified != expr_str:
                    if verbose:
                        print(f"{assignment}: {expr_str} ({type(expr_str)}) -> {simplified}")


                if simplified == False or simplified == 0:
                    new_assignments[assignment] = "0"
                else:
                    new_assignments[assignment] = str(simplified)

            e.data.assignments = new_assignments

def rename_on_if_conds(node: ConditionalBlock, src: str, dst: str):
    gpu_host_name_map = {src: dst}

    for b in node.branches:
        if b[0] is None:
            continue
        if isinstance(b[0].code, list):
            for i, el in enumerate(b[0].code):
                if isinstance(el, str):
                    for src,dst in gpu_host_name_map.items():
                        b[0].code[i] = b[0].code[i].replace(src,dst)
                else:
                    def replace_x_with_y(expr: ast.Expr, repl_dict) -> ast.Expr:
                        expr_str = ast.unparse(expr).strip()
                        for src, dst in repl_dict.items():
                            modified_str = expr_str.replace(src, dst)
                        return ast.parse(modified_str, mode="eval").body
                    b[0].code[i] = replace_x_with_y(b[0].code[i], gpu_host_name_map)
        else:
            assert isinstance(b[0].code, str)
            for src,dst in gpu_host_name_map.items():
                b[0].code = b[0].code.replace(src, dst)

# I think I will just detect the "AccessNode -> Tasklet -> AccessNode"
# with memlet.data having the name we want and the destination node
# having the name "if*" in this case we can be pretty sure it is if
# access on what we want then I can assign the value on the interstate
# edge and rely on simplify, I hope this will work
def propagate_if_cond(root: dace.SDFG, sdfg: dace.SDFG, replace_dict: dict, verbose):
    sdfg.validate()

    sdfg.replace_dict(replace_dict)

    # It makes global_data.lextra_diffu
    # to global_data.1 on an edge fix that
    for s in sdfg.states():
        for e in s.edges():
            for src, dst in replace_dict.items():
                if e.data.data.endswith(f".{dst}"):
                    e.data.data = e.data.data.replace(f".{dst}", f".{src}")

    def repl_assign_if(sdfg: dace.SDFG):
        for s in sdfg.states():
            for n in s.nodes():
                if n not in s.nodes():
                    continue
                if isinstance(n, dace.nodes.AccessNode):
                    if len(s.out_edges(n)) == 1:
                        dst1 = s.out_edges(n)[0].dst
                        if (len(s.out_edges(dst1)) == 1 and
                            isinstance(dst1, dace.nodes.Tasklet)):
                            dst2 = s.out_edges(dst1)[0].dst
                            if (len(s.out_edges(dst2)) == 0 and
                                isinstance(dst2, dace.nodes.AccessNode) and
                                dst2.label.startswith("_if")):
                                # We have a match
                                # Access node -> Tasklet -> Access node
                                for name, dstexpr in replace_dict.items():
                                    if name in n.data:
                                        if verbose:
                                            print(f"Matched: {n.data} -> {dst1.label} -> {dst2.data} on name {name}")
                                        s.remove_node(dst1)
                                        s.remove_node(dst2)
                                        ies = s.in_edges(n)
                                        s.remove_node(n)
                                        oes = s.parent_graph.out_edges(s)
                                        oe = oes[0]
                                        assert dst2.data not in oe.data.assignments
                                        oe.data.assignments[dst2.data + "_sym"] = dstexpr
                                        for ie in ies:
                                            if s.in_degree(ie.src) == 0 and s.out_degree(ie.src) == 0:
                                                s.remove_node(ie.src)
                                        d = sdfg.arrays[dst2.data]
                                        #sdfg.remove_data(dst2.data, validate=False)
                                        sdfg.add_symbol(name=dst2.data + "_sym", stype=d.dtype)

                                        for oe in oes:
                                            dst_node = oe.dst
                                            if isinstance(dst_node, ConditionalBlock):
                                                rename_on_if_conds(dst_node, dst2.data, dst2.data + "_sym")
    if root == sdfg:
        repl_assign_if(sdfg)
    #for state in sdfg.states():
    #    for node in state.nodes():
    #        if isinstance(node, dace.nodes.NestedSDFG):
    #            repl_assign_if(node.sdfg)

    sdfg.validate()

    for state in sdfg.states():
        for node in state.nodes():
            if isinstance(node, dace.nodes.NestedSDFG):
                propagate_if_cond(sdfg, node.sdfg, replace_dict, verbose)
    sdfg.validate()

    # Evaluate interstate assignments everywhere
    evaluate_interstate_assignments_and_ifs(sdfg, verbose)
    for node, graph in sdfg.all_nodes_recursive():
        if isinstance(node, ControlFlowRegion):
            evaluate_interstate_assignments_and_ifs(node, verbose)
        if isinstance(node, dace.nodes.NestedSDFG):
            evaluate_interstate_assignments_and_ifs(node.sdfg, verbose)
    sdfg.validate()

    sdfg.simplify()


    ConstantPropagation().apply_pass(sdfg, {})
    sdfg.validate()

    # Remove all cfg nodes that are 0 == 1
    DeadStateElimination().apply_pass(sdfg, {})
    sdfg.validate()


    # All non trurthy ifs have been removed, now copy-out the body of trurthy ifs
    # e.g. cond is 1 == 1

    #for cfg in sdfg.all_control_flow_blocks():
    #    if isinstance(cfg, ConditionalBlock):
    #        print(cfg.label, len(cfg.branches))
    #        s = ""
    #        for i in range(len(cfg.branches[0][0].code)):
    #        s += " " + ast.unparse(cfg.branches[0][0].code[i]) + "\n"