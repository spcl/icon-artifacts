import ast
import copy
from itertools import product
import dace
from dace.codegen.control_flow import ConditionalBlock, ControlFlowBlock, ControlFlowRegion
from dace.properties import CodeBlock

# ((istep == 1) == 1)
# ((1 - ldeepatmo) == 1)
# (_if_cond_27 == 1) w. _if_cond_27=__CG_global_data__m_lextra_diffu in edge before

def _raise_loop_invariant_if(nested_sdfg: dace.SDFG, map_entry: dace.nodes.MapEntry, state: dace.SDFGState,
                             check_invariant_if_conds,
                             copy_edge_before):
    if_conds = []
    for node in nested_sdfg.nodes():
        if isinstance(node, ConditionalBlock):
            conds = []
            for cond, body in node.branches:
                if cond is None:
                    continue
                if isinstance(cond.code, list):
                    for i, el in enumerate(cond.code):
                       expr_str = ast.unparse(el).strip()
                       #print(expr_str)
                       conds.append(expr_str)
            if_conds.append((conds, node))

    # For all condition that is loop-invariant
    # For all combinations of conditions duplicate the inside accordingly

    #invariant_if_conds [([v for v in vlist if v in invariant_if_conds], node) for vlist, node in if_conds]
    invariant_if_conds = []
    for vlist, node in if_conds:
        invariant_ifs = [v for v in vlist if v in check_invariant_if_conds]
        if len(invariant_ifs) > 0:
            invariant_if_conds.append((invariant_ifs, node))
    #print(invariant_if_conds)

    # Supporting only 1 if-else per if block
    for vlist, node in invariant_if_conds:
        assert len(vlist) == 1

    # For each combination of conditions, duplicate the corresponding body
    conds = [vlist[0] for vlist, _ in invariant_if_conds]
    combinations = list(product([True, False], repeat=len(conds)))

    if len(conds) > 0:
        cfg = ConditionalBlock(label=state.label + "_if", sdfg=state.sdfg, parent=state.parent_graph)
        state.sdfg.add_node(cfg)
        cfg.parent_graph = state.parent_graph
        cfg.sdfg = state.sdfg
        additional_assignments = dict()


        for i, combo in enumerate(combinations):
            condition_str = " and ".join(f"({cond})" if val is True else f"(not ({cond}))"  for cond, val in zip(conds, combo))
            #print(f"if {condition_str}:")
            condition = CodeBlock(code=condition_str)

            body = ControlFlowRegion(label=state.label + f"_body_{i}", sdfg=cfg.sdfg, parent=cfg)
            cfg.add_branch(condition=condition, branch=body)
            s_main = body.add_state(f"main_{i}")

            # Copy all nodes in the state over
            # Remove all nodes inside the Nested SDFG
            node_map0 = dict()
            for node in state.nodes():
                node2 = copy.deepcopy(node)
                node_map0[node] = node2
                s_main.add_node(node2)
            for edge in state.edges():
                s_main.add_edge(node_map0[edge.src], edge.src_conn, node_map0[edge.dst], edge.dst_conn, copy.deepcopy(edge.data))

            nsdfgs = [n for n in s_main.nodes() if isinstance(n, dace.nodes.NestedSDFG)]
            assert len(nsdfgs) == 1
            _nsdfg = nsdfgs[0]
            for _n in _nsdfg.sdfg.nodes():
                _nsdfg.sdfg.remove_node(_n)
            nsdfg = _nsdfg.sdfg
            nsdfg.parent_sdfg = s_main.sdfg

            # Now go through states and add them to the body
            node_map = dict()
            cond_to_cfg = dict()
            for j, node in enumerate(nested_sdfg.nodes()):
                if not isinstance(node, ConditionalBlock):
                    node2 = copy.deepcopy(node)
                    node2.label += f"_{i}_{j}"
                    nsdfg.add_node(node2)
                    node_map[node] = node2
                    if not isinstance(node2, dace.SDFGState):
                        for _s in node2.all_states():
                            for _n in _s.nodes():
                                if isinstance(_n, dace.nodes.NestedSDFG):
                                    #print(_n.label, _n.guid)
                                    _n.sdfg.parent_sdfg = nsdfg
                    else:
                        for _n in node2.nodes():
                            if isinstance(_n, dace.nodes.NestedSDFG):
                                #print(_n.label, _n.guid)
                                _n.sdfg.parent_sdfg = nsdfg
                else:
                    cfg_to_take = None
                    assert len(node.branches) == 2 or len(node.branches) == 1
                    cond0, body0 = node.branches[0]
                    cond1, body1 = node.branches[1] if len(node.branches) == 2 else (None, None)

                    if len(node.branches) == 2:
                        assert cond0 is not None and cond1 is None
                        assert len(cond0.code) == 1
                        expr_str = ast.unparse(cond0.code[0]).strip()
                        #print(expr_str, expr_str in check_invariant_if_conds)
                        if expr_str in check_invariant_if_conds:
                            index = check_invariant_if_conds.index(expr_str)
                            # If we need to copy assignments do it now
                            if copy_edge_before[index]:
                                for ie in nested_sdfg.in_edges(node):
                                    additional_assignments.update(ie.data.assignments)
                            if combo[index] is True:
                                if len(body0.nodes()) == 1:
                                    body0 = body0.nodes()[0]
                                cfg_to_take = body0
                            else:
                                cfg_to_take = body1
                    if len(node.branches) == 1:
                        assert cond0 is not None and cond1 is None
                        assert len(cond0.code) == 1
                        expr_str = ast.unparse(cond0.code).strip()
                        #print(expr_str, expr_str in check_invariant_if_conds)
                        if expr_str in check_invariant_if_conds:
                            index = check_invariant_if_conds.index(expr_str)
                            # If we need to copy assignments do it now
                            if copy_edge_before[index]:
                                for ie in nested_sdfg.in_edges(node):
                                    additional_assignments.update(ie.data.assignments)
                            if combo[index] is True:
                                if len(body0.nodes()) == 1:
                                    body0 = body0.nodes()[0]
                                cfg_to_take = body0
                            else:
                                cfg_to_take = dace.SDFGState(label=f"empty_state")

                    # If we did not match any condition, then we need to duplicate the whole cfg
                    if cfg_to_take is None:
                        cfg_to_take = node
                    assert cfg_to_take is not None
                    node2 = copy.deepcopy(cfg_to_take)
                    node2.label += f"_{i}_{j}"
                    # Fix nested SDFGs' sdfg fields
                    nsdfg.add_node(node2)
                    if not isinstance(node2, dace.SDFGState):
                        for _s in node2.all_states():
                            for _n in _s.nodes():
                                if isinstance(_n, dace.nodes.NestedSDFG):
                                    #print(_n.label, _n.guid, nested_sdfg.label)
                                    _n.sdfg.parent_sdfg = nsdfg
                    else:
                        for _n in node2.nodes():
                            if isinstance(_n, dace.nodes.NestedSDFG):
                                #print(_n.label, _n.guid, nested_sdfg.label)
                                _n.sdfg.parent_sdfg = nsdfg
                    node_map[node] = node2
                    cond_to_cfg[node] = node2
            for edge in nested_sdfg.edges():
                src = node_map[edge.src]
                dst = node_map[edge.dst]
                nsdfg.add_edge(src, dst, copy.deepcopy(edge.data))

        i = 0
        for ie in state.sdfg.in_edges(state):
            state.sdfg.remove_edge(ie)
            iedata2 = copy.deepcopy(ie.data)
            if i == 0:
                iedata2.assignments.update(additional_assignments)
            state.sdfg.add_edge(ie.src, cfg, copy.deepcopy(iedata2))
            i += 1
        state.sdfg.add_edge(cfg, state, dace.InterstateEdge())
        for oe in state.sdfg.out_edges(state):
            state.sdfg.remove_edge(oe)
            state.sdfg.add_edge(cfg, oe.dst, copy.deepcopy(oe.data))
        state.sdfg.remove_node(state)

def raise_loop_invariant_if(sdfg: dace.SDFG,
                            check_invariant_if_conds = ["1 - ldeepatmo == 1", "_if_cond_27 == 1"],
                            copy_edge_before = [False, True]):
    for state in sdfg.states():
        for node in state.nodes():
            if isinstance(node, dace.nodes.NestedSDFG):
                srcs = list(set([e.src for e in state.in_edges(node)]))
                assert len(srcs) == 1
                if isinstance(srcs[0], dace.nodes.MapEntry):
                    _raise_loop_invariant_if(node.sdfg, srcs[0], state, check_invariant_if_conds, copy_edge_before)
    sdfg.validate()

