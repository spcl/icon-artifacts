import copy
import dace

from dace.codegen.common import sym2cpp
from dace.properties import CodeBlock
from dace.sdfg.state import ConditionalBlock
from dace.symbolic import SymExpr, evaluate, sympy_to_dace
from sympy import sstr

def sym2py(sym_expr):
    return sym2cpp(sym_expr).replace("&&", " and ").replace("||", " or ").replace("== true", "== 1").replace("== false", "== 0")

def simplify_expressions(sdfg: dace.SDFG):
    """
    for node, parent_graph in sdfg.all_nodes_recursive():
        if isinstance(node, ConditionalBlock):
            for i, (cond, body) in enumerate(node.branches):
                if cond is None:
                    continue
                cond_sympy = dace.symbolic.SymExpr(cond.as_string)
                is_const = True

                try:
                    evaled = evaluate(cond_sympy, {})
                except Exception as e:
                    print(f"Error evaluating condition {cond.as_string}: {e}")
                    is_const = False
                if is_const:
                    cond_simplified = dace.symbolic.SymExpr(str(evaled))
                else:
                    cond_simplified = cond_sympy.simplify()
                new_cond = CodeBlock(code=sym2py(cond_simplified),
                                 language=cond.language)
                assert isinstance(new_cond, CodeBlock), "New condition must be a CodeBlock"
                node.branches[i] = (new_cond, body)
    """

    for edge, _ in sdfg.all_edges_recursive():
        if isinstance(edge.data, dace.InterstateEdge):
            for k, v in edge.data.assignments.items():
                if v == "((((1 > 1) and (__CG_global_data__m_grf_intmethod_e == 6)) and (jstep == 0)) and 1)":
                    print("AAA")
                    try:
                        evaled = evaluate(dace.symbolic.SymExpr(v), {})
                    except Exception as e:
                        print(f"Error evaluating condition {v.as_string}: {e}")
                        raise Exception("Failed to evaluate condition")
                    print(evaled)
                    raise Exception("Evaled")
                
                if isinstance(v, CodeBlock):
                    v_str = v.as_string
                    v_lang = v.language
                    v_sympy = dace.symbolic.SymExpr(v_str)
                    v_simplified = v_sympy.simplify()
                    edge.data.assignments[k] = CodeBlock(
                        code=sym2py(v_simplified),
                        language=v_lang
                    )
                    assert isinstance(edge.data.assignments[k], CodeBlock), "New assignment must be a CodeBlock"
                else:
                    v_str = v
                    v_sympy = dace.symbolic.SymExpr(v_str)
                    v_simplified = v_sympy.simplify()
                    edge.data.assignments[k] = sym2py(v_simplified)
                    assert isinstance(edge.data.assignments[k], str), "New assignment must be a string"


    sdfg.validate()
    #simplify_truthy_ifs()

def simplify_truthy_ifs(sdfg: dace.SDFG):
    for node, parent_graph in sdfg.all_nodes_recursive():
        if isinstance(node, ConditionalBlock):
            # Allowed is if (true) {} else {}
            # or if (false) {} else {}
            if len(node.branches) > 2:
                continue

            br1, bdy1 = node.branches[0]
            br2, bdy2 = node.branches[1] if len(node.branches) > 1 else (None, None)

            if len(node.branches) == 1:
                try:
                    is_true = bool(evaluate(br1, {}))
                    body_to_keep = bdy1
                    if is_true is True:
                        body_to_keep = bdy1
                    else:
                        body_to_keep = bdy2
                except Exception as e:
                    continue
            else:
                assert br1 is None and br2 is not None or \
                        br1 is not None and br2 is None, \
                    f"Unexpected condition evaluation error: {e}"
                
                if br1 is None:
                    is_true = bool(evaluate(br2, {}))
                    if is_true is True:
                        body_to_keep = bdy2
                    else:
                        body_to_keep = bdy1
                elif br2 is None:
                    is_true = bool(evaluate(br1, {}))
                    if is_true is True:
                        body_to_keep = bdy1
                    else:
                        body_to_keep = bdy2

            assert body_to_keep is not None, "Body to keep should not be None"

            node_map = dict()
            beg_node = None
            end_node = None
            for node in body_to_keep.bfs_nodes():
                if body_to_keep.in_degree(node) == 0:
                    assert beg_node is None, "There should be only one beg node"
                    beg_node = node
                if body_to_keep.out_degree(node) == 0:
                    assert end_node is None, "There should be only one end node"
                    end_node = node
                new_node = copy.deepcopy(node)
                node_map[node] = new_node
                parent_graph.add_node(new_node)
            
            for edge in body_to_keep.edges():
                src = node_map[edge.src]
                dst = node_map[edge.dst]
                parent_graph.add_edge(
                    src,
                    dst,
                    copy.deepcopy(edge.data)
                )
            
            for ie in parent_graph.in_edges(node):
                src = ie.src
                parent_graph.add_edge(src, beg_node, copy.deepcopy(ie.data))
            for oe in parent_graph.out_edges(node):
                dst = oe.dst
                parent_graph.add_edge(end_node, dst, copy.deepcopy(oe.data))
            
                
