import ast
import typing

import re
import dace
from dace.codegen.control_flow import ConditionalBlock
from dace.sdfg.sdfg import ControlFlowBlock
import copy

def simplify_state_if_if_pattern(sdfg: dace.SDFG):
    nodes = list(sdfg.bfs_nodes())
    [s1, cfg1, cfg2] = nodes[0:3]
    if (
        isinstance(s1, dace.SDFGState) and
        isinstance(cfg1, ConditionalBlock) and
        isinstance(cfg2, ConditionalBlock) and
        len(s1.nodes()) == 0 and
        len(sdfg.out_edges(s1)) == 1 and
        sdfg.out_edges(s1)[0].dst == cfg1
    ):
        assignments = sdfg.out_edges(s1)[0].data.assignments
        # We have something like var_1 = expr
        # In the further steps we want to replace all var_1 with expr
        # And remove this state
        syms = copy.deepcopy(list(assignments.keys()))
        sdfg.replace_dict(assignments)
        sdfg.remove_node(s1)
        for sym in syms:
            sdfg.remove_symbol(sym)
            assert sym not in sdfg.parent_nsdfg_node.symbol_mapping

def untangle_if(cfg: ConditionalBlock):
    # Pattern to untanble is:
    # if (startblk) {
    #  startidx = A
    #  if (endblk) {
    #   endidx = B
    #  } else {
    #   endidx = C
    #  }
    # } else {
    #  if (endblk) {
    #   endidx = B
    #  } else {
    #   endidx = C
    #  }
    # }
    #
    # make it into to seperate if blocks
    copy_cfg = copy.deepcopy(cfg)

    rmed_symbols = set()

    graph = cfg.parent_graph

    startidx_name = None
    for condition, body in copy_cfg.branches:
        if condition is not None: # if (startblk)
            for node in body.nodes():
                if isinstance(node, dace.SDFGState):
                    # Since we remove and add things
                    if node not in body.nodes():
                        continue
                    oe = body.out_edges(node)[0]
                    new_assignments = { k: v for k, v in oe.data.assignments.items() if "endidx" not in k}
                    rmed_symbols = rmed_symbols.union(set(oe.data.assignments.keys()))
                    oe.data.assignments = new_assignments
                    assert len(new_assignments) == 1
                    startidx_name = list(new_assignments.keys())[0]
                    body.remove_node(oe.dst)
                    node2 = body.add_state("assign_endidx")
                    body.add_edge(node, node2, copy.deepcopy(oe.data))

    # Need the startidx name
    end_cond = None
    for condition, body in copy_cfg.branches:
        if condition is None: # else
            assert len(body.nodes()) == 1, f"{body.nodes()}"
            for node in body.nodes():
                end_cond = copy.deepcopy(node)
                body.remove_node(node)

            a1 = body.add_state("assign_startidx_1")
            a2 = body.add_state("assign_startidx_2")
            body.add_edge(a1, a2, dace.InterstateEdge(assignments={startidx_name: "int(1)"}))

    for edge, g in end_cond.all_edges_recursive():
        if (isinstance(edge.dst, dace.SDFGState) and
            isinstance(edge.src, dace.SDFGState)):
            g.remove_edge(edge)
            edge2 = copy.deepcopy(edge)
            edge2.data.assignments = {k: v for k, v in edge2.data.assignments.items() if "startidx" not in k}
            g.add_edge(edge.src, edge.dst, copy.deepcopy(edge2.data))

    graph.add_node(copy_cfg)
    graph.add_node(end_cond)
    graph.add_edge(copy_cfg, end_cond, dace.InterstateEdge())

    for oe in graph.out_edges(cfg):
        graph.add_edge(end_cond, oe.dst, copy.deepcopy(oe.data))
        graph.remove_edge(oe)

    graph.remove_node(cfg)

    #for sym in rmed_symbols:
    #    if sym in sdfg.free_symbols:
    #        sdfg.remove_symbol(sym)
    #        parent_nsdfg_node = sdfg.parent_nsdfg_node
    #        assert parent_nsdfg_node is not None
    #        parent_nsdfg_node.symbol_mapping.pop(sym)



def parse_range_dict_from_if(sdfg: dace.SDFG, cfg1: ConditionalBlock, cfg2: ConditionalBlock):
    global split_ranges

    _split_ranges = {
        "beg": {
            "beg": "1",
            "end": "1",
        },
        "middle": {
            "beg": "1",
            "end": "1",
        },
        "end": {
            "beg": "1",
            "end": "1"
        },
        "old_ranges": {
            "beg": "1",
            "end": "1",
        },
    }
    def remove_int_wrapper(expr):
        # Regular expression to match int() and capture what's inside
        match = re.match(r"int\((.*)\)", expr)
        return match.group(1) if match else expr

    for cfg, part in zip([cfg1, cfg2], ["startblk", "endblk"]):
        for condition, body in cfg.branches:
            if condition is not None: # True
                for edge in body.edges():
                    assert len(edge.data.assignments) == 1
                    k, v = list(edge.data.assignments.items())[0]
                    if part == "startblk": # Assigning start offset
                        # Is start block
                        _split_ranges["beg"]["beg"] = remove_int_wrapper(v)
                    else: # Assigning end offset
                        # Is end block
                        _split_ranges["end"]["end"] = remove_int_wrapper(v)
                        pass
                    if part == "startblk":
                        _split_ranges["old_ranges"]["beg"] = remove_int_wrapper(k)
                    else:
                        _split_ranges["old_ranges"]["end"] = remove_int_wrapper(k)
            else:
                for edge in body.edges():
                    assert len(edge.data.assignments) == 1
                    k, v = list(edge.data.assignments.items())[0]
                    # Else branches
                    if part == "startblk": # Assigning start offset
                        # Is not start block
                        _split_ranges["middle"]["beg"] = remove_int_wrapper(v)
                        _split_ranges["end"]["beg"] = remove_int_wrapper(v)
                    else: # Assigning end offset
                        # Is not end block
                        _split_ranges["beg"]["end"] = remove_int_wrapper(v)
                        _split_ranges["middle"]["end"] = remove_int_wrapper(v)

    return _split_ranges

def split_map(cfg: dace.SDFG | ControlFlowBlock, state: dace.SDFGState,
              map_entry: dace.nodes.MapEntry, range_dict: typing.Dict,
              gpu: bool = True):

    sym_names = ["beg_blk_range_beg", "beg_blk_range_end",
                 "middle_blk_range_beg", "middle_blk_range_end",
                 "end_blk_range_beg", "end_blk_range_end"]

    sdfg = cfg if isinstance(cfg, dace.SDFG) else cfg.sdfg
    for sym_name in sym_names:
        if sym_name not in sdfg.symbols:
            sdfg.add_symbol(sym_name, dace.int64)

    d = {}
    for part in ["beg", "middle", "end"]:
        assert part + "_blk_range_beg" not in d
        assert part + "_blk_range_end" not in d
        d[part + "_blk_range_beg"] = range_dict[part]["beg"]
        d[part + "_blk_range_end"] = range_dict[part]["end"]

    symbol_define_state = state.parent_graph.add_state_before(state, assignments=d)

    inner_nodes = list(state.all_nodes_between(map_entry, state.exit_node(map_entry)))
    assert len(inner_nodes) == 1
    inner_sdfg = inner_nodes[0].sdfg

    found_cfg = False
    found_state_after_cfg = False
    for inner_node in inner_sdfg.bfs_nodes():
        if isinstance(inner_node, ConditionalBlock):
            found_cfg = True
        if found_cfg and isinstance(inner_node, dace.SDFGState):
            found_state_after_cfg = True
        if found_state_after_cfg:
            break
        inner_sdfg.remove_node(inner_node)

    # Duplicate it 2 times
    duplicates = []
    for i in range(2):
        node_map = dict()
        inner_nodes = list(state.all_nodes_between(map_entry, state.exit_node(map_entry))) + [map_entry, state.exit_node(map_entry)]
        inner_edges = state.all_edges(*inner_nodes)
        for n in inner_nodes:
            node_map[n] = copy.deepcopy(n)
            state.add_node(node_map[n])
        for e in inner_edges:
            if e.src not in node_map:
                if state.in_degree(e.src) == 0:
                    node_map[e.src] = copy.deepcopy(e.src)
                    state.add_node(node_map[e.src])
            if e.dst not in node_map:
                if state.out_degree(e.dst) == 0:
                    node_map[e.dst] = copy.deepcopy(e.dst)
                    state.add_node(node_map[e.dst])
            src = e.src if e.src not in node_map else node_map[e.src]
            dst = e.dst if e.dst not in node_map else node_map[e.dst]
            state.add_edge(src, e.src_conn, dst, e.dst_conn, copy.deepcopy(e.data))

        duplicates.append(node_map[map_entry])

    duplicates.append(map_entry)

    i = 0
    for map_entry, part in zip(duplicates, ["beg", "middle", "end"]):
        map_entry._cuda_stream = i
        map_entry._cs_childpath = False
        inner_nodes = list(state.all_nodes_between(map_entry, state.exit_node(map_entry))) + [map_entry, state.exit_node(map_entry)]
        for n in inner_nodes:
            if isinstance(n, dace.nodes.NestedSDFG):
                old_beg = range_dict["old_ranges"]["beg"]
                old_end = range_dict["old_ranges"]["end"]
                # Keep the symbol name in the nested SDFG same - to make it easier with multiple nested SDFGs
                #n.sdfg.replace_dict({old_beg: part + "_blk_range_beg", old_end: part + "_blk_range_end"})
                """
                if old_beg in n.symbol_mapping.keys():
                    n.symbol_mapping.pop(old_beg)
                if old_beg in n.symbol_mapping.values():
                    k = list(n.symbol_mapping.keys())[list(n.symbol_mapping.values()).index(old_beg)]
                    n.symbol_mapping.pop(k)
                if old_end in n.symbol_mapping.keys():
                    n.symbol_mapping.pop(old_end)
                if old_end in n.symbol_mapping.values():
                    k = list(n.symbol_mapping.keys())[list(n.symbol_mapping.values()).index(old_end)]
                    n.symbol_mapping.pop(k)"
                """
                #if old_beg not in n.sdfg.symbols:
                #    n.sdfg.add_symbol(old_beg, dace.int64)
                #if old_end not in n.sdfg.symbols:
                #    n.sdfg.add_symbol(old_end, dace.int64)
                if old_beg not in n.sdfg.symbols:
                    n.sdfg.add_symbol(old_beg, dace.int64)
                if old_end not in n.sdfg.symbols:
                    n.sdfg.add_symbol(old_end, dace.int64)
                n.symbol_mapping[old_beg] = part + "_blk_range_beg" #part + "_blk_range_beg"
                n.symbol_mapping[old_end] = part + "_blk_range_end" #part + "_blk_range_end"
                #n.sdfg.add_symbol(part + "_blk_range_beg", dace.int64)
                #n.sdfg.add_symbol(part + "_blk_range_end", dace.int64)
                #symbols = set(k for k in n.sdfg.free_symbols if k not in n.in_connectors and k not in n.out_connectors)
                #missing_symbols = [s for s in symbols if s not in n.symbol_mapping]
                #print("MissingSymbols: ", missing_symbols, [old_beg, old_end])
        i += 1

    unused_inputs = set()
    for part in ["beg", "middle", "end"]:
        for _, expr in range_dict[part].items():
            if expr.isdigit():
                continue
            else:
                def get_variable_name(expr):
                    # Hack for max(1, var[]) case
                    expr = expr.split(",")[-1]
                    match = re.match(r"^\s*([a-zA-Z_]\w*)\s*\[", expr)
                    return match.group(1) if match else expr
                var_name = get_variable_name(expr)
                unused_inputs.add(var_name)

    # Clean the map edge connections
    for map_entry, part in zip(duplicates, ["beg", "middle", "end"]):
        inner_nodes = list(state.all_nodes_between(map_entry, state.exit_node(map_entry))) + [map_entry, state.exit_node(map_entry)]
        for n in inner_nodes:
            if isinstance(n, dace.nodes.NestedSDFG):
                for conn in unused_inputs:
                    edges = list(state.in_edges_by_connector(n, conn))
                    assert len(edges) == 1, f"{edges}, {n}, {conn}"
                    edge = edges[0]
                    state.remove_edge(edge)
                    inedges = list(state.in_edges_by_connector(edge.src, edge.src_conn.replace("OUT_", "IN_")))
                    edge.src.remove_out_connector(edge.src_conn)
                    edge.dst.remove_in_connector(edge.dst_conn)
                    n.sdfg.remove_data(edge.dst_conn)
                    assert len(inedges) == 1
                    inedge = inedges[0]
                    inedge.dst.remove_in_connector(inedge.dst_conn)
                    if inedge.src_conn is not None:
                        inedge.src.remove_out_connector(inedge.src_conn)
                    state.remove_edge(inedge)
                    if state.in_degree(inedge.src) == 0 and state.out_degree(inedge.src) == 0:
                        state.remove_node(inedge.src)

    i = 0
    for map_entry, part in zip(duplicates, ["beg", "middle", "end"]):
        new_range = []
        assert len(map_entry.map.range) == 1
        b, e, s = map_entry.map.range[0]
        if part == "beg":
            assert s == 1
            new_range = [(b, b, s)]
        elif part == "middle":
            new_range = [(b+1, e-1, s)]
        elif part == "end":
            new_range = [(e, e, s)]
        map_entry.map.range = dace.subsets.Range(new_range)
        if gpu:
            map_entry._cuda_stream = i
            map_entry._cs_childpath = False
        i += 1


def move_in_if(sdfg: dace.SDFG, n: dace.nodes.NestedSDFG):
    # Super-specific If map -> nested SDFG with 1 state and CFG If goes into a -> another nested
    # SDFG with 1 state and CFG If then move the outside if inside.
    nodes = list(sdfg.bfs_nodes())
    if len(nodes) == 2:
        [s0, cfg0] = nodes
        if (
            isinstance(cfg0, ConditionalBlock) and
            isinstance(s0, dace.SDFGState) and
            len(s0.nodes()) == 0 and
            len(sdfg.out_edges(s0)) == 1 and
            sdfg.out_edges(s0)[0].dst == cfg0
        ):
            edges = sdfg.edges()
            assert len(edges) == 1
            edge = edges[0]

            move_in_assignments = {k + "_m1": v for k,v in edge.data.assignments.items()}

            if len(cfg0.branches) == 1:
                condition, body = cfg0.branches[0]
                if len(body.nodes()) == 1:
                    [s1] = list(body.bfs_nodes())
                    if isinstance(s1, dace.SDFGState):
                        # Move if inside
                        nested = [n for n in s1.nodes() if isinstance(n, dace.nodes.NestedSDFG)][0]
                        inner_sdfg = nested.sdfg
                        if len(inner_sdfg.nodes()) == 2:
                            [s2, cfg2] = inner_sdfg.nodes()
                            assignments_to_rm = copy.deepcopy(list(inner_sdfg.in_edges(cfg2)[0].data.assignments.keys()))
                        elif len(inner_sdfg.nodes()) > 2:
                            for inner_node in inner_sdfg.nodes():
                                if (isinstance(inner_node, ConditionalBlock) and
                                    inner_sdfg.in_degree(inner_node) == 1 and
                                    isinstance(inner_sdfg.in_edges(inner_node)[0].src, dace.SDFGState)):
                                    cfg2 = inner_node
                                    s2 = inner_sdfg.in_edges(inner_node)[0].src
                                    assignments_to_rm = copy.deepcopy(list(inner_sdfg.in_edges(inner_node)[0].data.assignments.keys()))
                                    break
                        else:
                            return
                        assert isinstance(cfg2, ConditionalBlock)
                        if isinstance(cfg2, ConditionalBlock):
                            if len(cfg2.branches) == 1:
                                for k in move_in_assignments.keys():
                                    #s = ast.unparse(condition.code[-1])
                                    #print(s)
                                    s = ast.unparse(cfg2.branches[0][0].code[-1])
                                    cfg2.branches[0][0].code[-1] = ast.parse(f"({s}) and ({k} == 1)", mode="eval")

                                edge = inner_sdfg.edges()[0]
                                edge.data.assignments.update(move_in_assignments)

                                # Mv state up
                                s2 = copy.deepcopy(s1)
                                sdfg.add_node(s2)

                                sdfg.remove_node(s1)
                                sdfg.remove_node(cfg0)
                                sdfg.remove_node(s0)
                                nested = [n for n in s2.nodes() if isinstance(n, dace.nodes.NestedSDFG)][0]

                                # Pass outside data passed from outer sdfg to inner sdfg
                                for in_conn in n.in_connectors:
                                    if in_conn not in nested.in_connectors:
                                        nested.add_in_connector(in_conn)
                                        src = list(set([e.src for e in s2.in_edges(nested)]))
                                        assert len(src) == 1
                                        src = src[0]
                                        arr = sdfg.arrays[in_conn]
                                        s2.add_edge(src, "OUT_" + in_conn, nested, in_conn, dace.memlet.Memlet.from_array(in_conn, arr))
                                        src.add_out_connector("OUT_" + in_conn)
                                        src.add_in_connector("IN_" + in_conn)
                                        an = s2.add_access(in_conn)
                                        s2.add_edge(an, None, src, "IN_" + in_conn, dace.memlet.Memlet.from_array(in_conn, arr))
                                        if in_conn not in nested.sdfg.arrays:
                                            copy_desc = copy.deepcopy(arr)
                                            copy_desc.transient = False
                                            nested.sdfg.add_datadesc(in_conn, copy_desc)

                                for _n in s2.nodes():
                                    if isinstance(_n, dace.nodes.NestedSDFG):
                                        _n.sdfg.parent_graph = s2.parent_graph
                                        _n.sdfg.parent_sdfg = sdfg
                                        _n.sdfg.parent = s2

                                #print("SymMap", n.symbol_mapping)
                                #print("FreeSym", n.sdfg.free_symbols)
                                # DANGEROUS TODO: WHY MISSING SYMBOLS APPEAR AND WHY DOES IT COMPILE AFTER REMOVING THEM?
                                symbols = set(k for k in n.sdfg.free_symbols if k not in n.in_connectors and k not in n.out_connectors)
                                missing_symbols = [s for s in symbols if s not in n.symbol_mapping]
                                for sym in missing_symbols:
                                    n.sdfg.remove_symbol(sym)


def untangle_if_sdfg(sdfg: dace.SDFG, verbose: bool):
    for state, graph in sdfg.all_nodes_recursive():
        if isinstance(state, dace.SDFGState):
            for n in state.nodes():
                if isinstance(n, dace.nodes.NestedSDFG):
                    nested_nodes = list(n.sdfg.bfs_nodes())
                    if len(nested_nodes) > 3:
                        simplify_state_if_if_pattern(n.sdfg)
                    if len(nested_nodes) >= 2:
                        [n1, n2] = nested_nodes[0:2]
                        if isinstance(n1, ConditionalBlock):
                            if isinstance(n2, dace.SDFGState):
                                untangle_if(n1)
                            elif isinstance(n2, ConditionalBlock):
                                s = ""
                                for i in range(len(n2.branches[0][0].code)):
                                    s += " " + ast.unparse(n2.branches[0][0].code[i])
                                if ((n1.label == "Conditional_l_0_c_0_4_0_0" or
                                    n1.label == "Conditional_l_0_c_0_4")):
                                    #raise Exception("A")
                                    untangle_if(n1)

    sdfg.validate()

    for _n, _ in sdfg.all_nodes_recursive():
        if isinstance(_n, dace.nodes.NestedSDFG):
            move_in_if(_n.sdfg, _n)

    if verbose:
        sdfg.save("ifs_untangled.sdfgz", compress=True)
    sdfg.validate()

def remove_empty_kernel(sdfg: dace.SDFG):
    for n, graph in sdfg.all_nodes_recursive():
        nodes_to_rm = set()
        if isinstance(n, dace.nodes.MapEntry):
            all_nodes = list(graph.all_nodes_between(n, graph.exit_node(n)))
            if len(all_nodes) == 1:
                n = all_nodes[0]
                if isinstance(n, dace.nodes.NestedSDFG):
                    if len(n.sdfg.nodes()) == 1:
                        inner_state = n.sdfg.nodes()[0]
                        if len(inner_state.nodes()) == 0:
                            nodes_to_rm.add(n)
                            for _n in all_nodes:
                                nodes_to_rm.add(_n)
                            for _n in [e.src for e in graph.in_edges(n)]:
                                nodes_to_rm.add(_n)
                                for __n in [e.src for e in graph.in_edges(_n)]:
                                    nodes_to_rm.add(__n)
                            for _n in [e.dst for e in graph.out_edges(n)]:
                                nodes_to_rm.add(_n)
                                for __n in [e.dst for e in graph.out_edges(_n)]:
                                    nodes_to_rm.add(__n)
        if isinstance(n, dace.nodes.NestedSDFG):
            remove_empty_kernel(n.sdfg)
        for _n in nodes_to_rm:
            graph.remove_node(_n)

def remove_empty_cfg(sdfg: dace.SDFG):
    for n, graph in sdfg.all_nodes_recursive():
        nodes_to_rm = set()
        if isinstance(n, ControlFlowBlock):
            if n in graph.nodes():
                if len(n.nodes()) == 1:
                    _n = list(n.nodes())[0]
                    if isinstance(_n, dace.SDFGState):
                        _n2 = copy.deepcopy(_n)
                        graph.add_node(_n2)

                        for _n3 in _n2.nodes():
                            if isinstance(_n3, dace.nodes.NestedSDFG):
                                _n3.sdfg.parent_graph = _n2.parent_graph
                                _n3.sdfg.parent_sdfg = _n2.sdfg
                                _n3.sdfg.parent = _n2

                        for e in graph.in_edges(n):
                            graph.add_edge(e.src, _n2, copy.deepcopy(e.data))
                        for e in graph.out_edges(n):
                            graph.add_edge(_n2, e.dst, copy.deepcopy(e.data))
                        nodes_to_rm.add(n)
        for _n in nodes_to_rm:
            graph.remove_node(_n)

        if isinstance(n, dace.nodes.NestedSDFG):
            remove_empty_cfg(n.sdfg)



def split_map_sdfg(sdfg: dace.SDFG, gpu: bool, verbose: bool):
    applied = 0
    remove_empty_kernel(sdfg)
    remove_empty_cfg(sdfg)

    for sn, parent in sdfg.all_nodes_recursive():
        if isinstance(sn, dace.SDFGState):
            state = sn
            for n in state.bfs_nodes():
                if isinstance(n, dace.nodes.NestedSDFG):
                    nested_nodes = list(n.sdfg.bfs_nodes())
                    if len(nested_nodes) >= 3:
                        [cfg1, cfg2, s1] = nested_nodes[0:3]
                        if (isinstance(cfg1, ConditionalBlock) and
                            isinstance(cfg2, ConditionalBlock) and
                            isinstance(s1, dace.SDFGState)):
                            isrcs = list(set([e.src for e in state.in_edges(n)]))
                            #print(isrcs)
                            if len(isrcs) == 1 and isinstance(isrcs[0], dace.nodes.MapEntry):
                                map_entry = isrcs[0]
                                range_dict = parse_range_dict_from_if(n.sdfg, cfg1, cfg2)
                                split_map(state.parent_graph, state, map_entry, range_dict, gpu)
                                applied += 1

    if verbose:
        print(f"Applied, split-map {applied} times.")

    remove_empty_kernel(sdfg)
    remove_empty_cfg(sdfg)
    sdfg.reset_sdfg_list()
    if verbose:
        sdfg.save("maps_split.sdfgz", compress=True)
    sdfg.validate()
    return applied
