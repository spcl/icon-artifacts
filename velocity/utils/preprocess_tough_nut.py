import ast
import copy
import dace
from dace.codegen.control_flow import ControlFlowBlock, ControlFlowRegion
from dace.properties import CodeBlock
from dace.sdfg.sdfg import ConditionalBlock

# We have IfBlock1.
# not (lvn_only == 1)
# Inside directly nested IfBlock2
# not (((_for_it_22 < i_startblk_2) or (_for_it_22 > i_endblk_2)) == 1)
# Then we have index assignment
# and kernels as usual

# If detected,
# Copy the CFG out
# Remove ifBlock 2 with the map
# (Map is the first node connecting to the SDFG)
# rest is the same
#outer_cond_str = "not lvn_only == 1"
inner_cond_str = "not (_for_it_22 < i_startblk_2 or _for_it_22 > i_endblk_2) == 1"
oldsym1 = dace.symbolic.symbol("i_startblk_var_146")
oldsym2 = dace.symbolic.symbol("i_endblk_var_147")
newsym1 = dace.symbolic.symbol("i_startblk_2")
newsym2 = dace.symbolic.symbol("i_endblk_2")

def find_tough_nut(sdfg: dace.SDFG):
    for node, parent in sdfg.all_nodes_recursive():
        if (isinstance(node, ConditionalBlock) and
            len(node.branches) == 1):
            cond0, body0 = node.branches[0]
            if len(cond0.code) == 1:
                cond0_str = ast.unparse(cond0.code[0])
                #print(cond0_str, outer_cond_str, cond0_str == outer_cond_str)
                if cond0_str == inner_cond_str:
                    return node, body0, parent
    return None, None, None

def preprocess_tough_nut(sdfg: dace.SDFG):
    outer_node, node, parent = find_tough_nut(sdfg)
    if node is None:
        print("Warning: the if condition and index reassignment not found (possible lvn_only is False)")
        return

    inner_sdfg: dace.SDFG = node.sdfg
    nsdfg: dace.nodes.NestedSDFG = inner_sdfg.parent_nsdfg_node
    #print(node)
    #print(inner_sdfg.label)
    #print(nsdfg)

    parent_graph = [v for v in sdfg.states() if nsdfg in v.nodes()][0]
    assert len([v for v in sdfg.states() if nsdfg in v.nodes()]) == 1

    parent_sdfg = sdfg

    entry_map = list(set([e.src for e in parent_graph.in_edges(nsdfg)]))[0]
    exit_map = parent_graph.exit_node(entry_map)

    c = ConditionalBlock(label="extract_conditional", sdfg=parent_sdfg, parent=parent_graph)
    for oe in parent_sdfg.out_edges(parent_graph):
        for ie in parent_sdfg.in_edges(oe.dst):
            parent_sdfg.remove_edge(ie)
        parent_sdfg.add_edge(c, oe.dst, copy.deepcopy(oe.data))
    #for ie in parent_sdfg.in_edges(parent_graph):
    parent_sdfg.add_edge(parent_graph, c, dace.InterstateEdge())

    cfg = ControlFlowRegion(label="extract_cfg", sdfg=sdfg, parent=c)
    after_state = dace.SDFGState(label="extract_state", sdfg=sdfg)
    cfg.add_node(after_state)
    c.add_branch(condition=CodeBlock(code="1 == 1"), branch=cfg)

    #after_state = parent_sdfg.add_state_after(parent_graph, "extract")

    node_map = dict()

    node_map[entry_map] = copy.deepcopy(entry_map)
    node_map[exit_map] = copy.deepcopy(exit_map)

    em1: dace.nodes.MapEntry = node_map[entry_map]
    newranges = []
    for b,e,s in em1.map.range:
        _b = b
        _e = e
        _s = s
        for osym, nsym in [(oldsym1, newsym1), (oldsym2, newsym2)]:
            #print(_b, _e, _s)
            _b = _b.subs(osym, nsym)
            _e = _e.subs(osym, nsym)
            _s = _s.subs(osym, nsym)
            #print(_b, _e, _s)
        newranges.append((_b, _e, _s))
    em1.map.range = dace.subsets.Range(newranges)
    #raise Exception(em1.map.range, [(oldsym1, newsym1), (oldsym2, newsym2)], newranges)


    after_state.add_node(node_map[entry_map])
    after_state.add_node(node_map[exit_map])

    for src in set([ie.src for ie in parent_graph.in_edges(entry_map)]):
        if src not in node_map:
            node_map[src] = copy.deepcopy(src)
            after_state.add_node(node_map[src])
    for dst in set([e.dst for e in parent_graph.out_edges(entry_map)]):
        if dst in node_map:
            continue
        node_map[dst] = copy.deepcopy(dst)
        after_state.add_node(node_map[dst])
    for dst in set([oe.dst for oe in parent_graph.out_edges(exit_map)]):
        if dst in node_map:
            continue
        node_map[dst] = copy.deepcopy(dst)
        after_state.add_node(node_map[dst])
    for src in set([ie.src for ie in parent_graph.in_edges(exit_map)]):
        if src in node_map:
            continue
        node_map[src] = copy.deepcopy(src)
        after_state.add_node(node_map[src])

    for e in parent_graph.in_edges(entry_map):
        after_state.add_edge(node_map[e.src], e.src_conn, node_map[e.dst], e.dst_conn, copy.deepcopy(e.data))
    for e in parent_graph.out_edges(entry_map):
        after_state.add_edge(node_map[e.src], e.src_conn, node_map[e.dst], e.dst_conn, copy.deepcopy(e.data))
    for e in parent_graph.out_edges(exit_map):
        after_state.add_edge(node_map[e.src], e.src_conn, node_map[e.dst], e.dst_conn, copy.deepcopy(e.data))
    for e in parent_graph.in_edges(exit_map):
        after_state.add_edge(node_map[e.src], e.src_conn, node_map[e.dst], e.dst_conn, copy.deepcopy(e.data))

    #for n in after_state.nodes():
    #    if isinstance(n, dace.nodes.NestedSDFG):
    #        #n.sdfg.parent_sdfg = sdfg
    #        for _n in n.sdfg.nodes():
    #            n.sdfg.remove_node(_n)
    for n in after_state.nodes():
        if isinstance(n, dace.nodes.NestedSDFG):
            n.sdfg.parent_sdfg = sdfg
            #n.sdfg.parent_graph =
            for _n in n.sdfg.nodes():
                n.sdfg.remove_node(_n)
            #n.sdfg.add_state("empt")
            #node2 = copy.deepcopy(node)
            node_map2 = dict()
            for _n in node.nodes():
                node_map2[_n] = copy.deepcopy(_n)
                n.sdfg.add_node(node_map2[_n])
            for e in node.edges():
                n.sdfg.add_edge(node_map2[e.src], node_map2[e.dst], copy.deepcopy(e.data))
            for _s in n.sdfg.states():
                for _n in _s.nodes():
                    if isinstance(_n, dace.nodes.NestedSDFG):
                        _n.sdfg.parent_sdfg = n.sdfg
            symbols = set(k for k in n.sdfg.free_symbols if k not in n.in_connectors and k not in n.out_connectors)
            missing_symbols = [s for s in symbols if s not in n.symbol_mapping]
            # print("MissingSymbols: ", missing_symbols)
            for ms in missing_symbols:
                n.symbol_mapping[ms] = ms

    sdfg.reset_cfg_list()
    parent.remove_node(outer_node)

    # Remove index calculation and then add empty state and cfg to be able to use my other function
    if len(parent.nodes()) == 1:
        if isinstance(parent.nodes()[0], ConditionalBlock):
            parent.remove_node(parent.nodes()[0])
            #c = ControlFlowRegion(label="empty", sdfg=parent.sdfg, parent=parent)
            #c.add_state("empty_state")
            parent.add_state("empty_state")

    sdfg.validate()
    from .split_maps import remove_empty_kernel
    from .propagate_if_cond import propagate_if_cond
    remove_empty_kernel(sdfg)
    propagate_if_cond(sdfg, sdfg, None, None, False)
    sdfg.validate()
