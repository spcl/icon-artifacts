import warnings
import dace
from dace.sdfg.utils import set_nested_sdfg_parent_references
from dace.sdfg import InterstateEdge
from dace.sdfg.state import ConditionalBlock, ControlFlowRegion
from dace.sdfg.nodes import MapEntry, MapExit, NestedSDFG
import copy

from utils.add_missing_symbols import add_missing_data_and_symbols, add_missing_data_and_symbols_to_all_nsdfgs


def make_map_body_nested(sdfg: dace.SDFG, cond_block_name):
    """
    If one or multiple maps are surrounded by a conditional block, moves the conditional block into the nested SDFG of maps.
    """
    # Find the conditional block
    cond_block: ConditionalBlock = None
    psdfg: dace.SDFG = None
    for node, p in sdfg.all_nodes_recursive():
        if node.label == cond_block_name:
            cond_block = node
            psdfg = p.sdfg
            break
    assert (
        cond_block is not None
    ), f"Conditional block {cond_block_name} not found in SDFG {sdfg.name}"

    # The conditional block should only contain one condition
    assert (
        len(cond_block.branches) == 1
    ), f"Conditional block {cond_block_name} has multiple branches"
    branch: ControlFlowRegion = cond_block.branches[0][1]
    branch_cond = cond_block.branches[0][0]

    # Make sure that each state in the branch is either empty or only contains maps
    for state in branch.all_states():
        for node in state.nodes():
            if isinstance(node, (MapEntry, MapExit)):
                continue
            if state.entry_node(node) is not None:
                continue  # Node is part of a map
            if all(
                [
                    isinstance(n, (MapEntry, MapExit))
                    for n in set(state.successors(node)) | set(state.predecessors(node))
                ]
            ):
                continue

            raise ValueError(
                f"State {state.label} in branch {branch.label} of conditional block {cond_block_name} contains nodes other than maps"
            )

    # Make sure that the condition symbol is not overwritten in the branch
    cond_syms = set(branch_cond.get_free_symbols())
    for iedge in branch.all_interstate_edges(recursive=True):
        for k in iedge.data.assignments.keys():
            if str(k) in cond_syms:
                raise ValueError(
                    f"Condition symbol {k} is overwritten in branch {branch.label} of conditional block {cond_block_name}"
                )

    # Ensure that each map contains a single nested SDFG
    # TODO: If the map does not contain a nested SDFG, we can wrap the body into one
    label_counter = 0
    for state in branch.all_states():
        for node in state.nodes():
            if not isinstance(node, MapEntry):
                continue

            map_inner_nodes = list(state.all_nodes_between(node, state.exit_node(node)))
            if (len(map_inner_nodes) != 1) or (
                len(map_inner_nodes) == 1 and not isinstance(map_inner_nodes[0], NestedSDFG)
            ):
                warnings.warn(
                    f"Map {node.label} in state {state.label} of branch {branch.label} does not contain a single nested SDFG, putting it into one"
                )
                map_inner_sdfg = dace.SDFG(
                    name=f"{node.label}_inner_sdfg_{label_counter}",
                )
                map_inner_state = map_inner_sdfg.add_state(
                    label=f"{node.label}_inner_state_{label_counter}",
                    is_start_block=True
                )
                label_counter += 1
                srcs = {e.data.data for e in state.in_edges(node)}
                dsts = {e.data.data for e in state.out_edges(state.exit_node(node))}

                node_map = dict()
                # Use later for removing the original nodes
                all_inner_map_nodes = set(state.all_nodes_between(node, state.exit_node(node)))
                for nd in state.all_nodes_between(node, state.exit_node(node)):
                    cpynd = copy.deepcopy(nd)
                    node_map[nd] = cpynd
                    map_inner_state.add_node(cpynd)
                for src in srcs.union(dsts):
                    an = map_inner_state.add_access(src)
                    node_map[src] = an
                for src in srcs.union(dsts):
                    copydesc = copy.deepcopy(state.sdfg.arrays[src])
                    copydesc.transient = False
                    map_inner_sdfg.add_datadesc(
                        name=src,
                        datadesc=copydesc,
                        find_new_name=False,
                    )

                # Ad all edges using the node mapping
                for e in state.all_edges(*state.all_nodes_between(node, state.exit_node(node))):
                    if e.src != node:
                        src = node_map[e.src]
                        src_conn = e.src_conn
                    else:
                        src = node_map[e.data.data]
                        src_conn = None
                    if e.dst != state.exit_node(node):
                        dst = node_map[e.dst]
                        dst_conn = e.dst_conn
                    else:
                        dst = node_map[e.data.data]
                        dst_conn = None
                    map_inner_state.add_edge(
                        src, src_conn,
                        dst, dst_conn,
                        copy.deepcopy(e.data)
                    )

                map_inner_nsdfg = state.add_nested_sdfg(
                    sdfg=map_inner_sdfg,
                    parent=state,
                    inputs=srcs,
                    outputs=dsts,
                )

                # Connections from map nsdfg
                for e in state.out_edges(node):
                    state.add_edge(
                        e.src,
                        e.src_conn,
                        map_inner_nsdfg,
                        e.data.data,
                        dace.memlet.Memlet.from_array(
                            e.data.data,
                            state.sdfg.arrays[e.data.data]
                        )
                    )
                for e in state.in_edges(state.exit_node(node)):
                    state.add_edge(
                        map_inner_nsdfg,
                        e.data.data,
                        e.dst,
                        e.dst_conn,
                        dace.memlet.Memlet.from_array(
                            e.data.data,
                            state.sdfg.arrays[e.data.data]
                        )
                    )

                # Remove all the original nodes
                for nd in all_inner_map_nodes:
                    state.remove_node(nd)

def _find_state(sdfg: dace.SDFG, node: dace.nodes.Node):
    for n, g in sdfg.all_nodes_recursive():
        if n == node:
            return g
    return None

# Copyright 2019-2025 ETH Zurich and the DaCe authors. All rights reserved.
"""Interchange conditional blocks with nested map regions."""

from dace import sdfg as sd
from dace import dtypes
from dace.sdfg import utils as sdutil
from dace.sdfg.state import ControlFlowRegion, ConditionalBlock
from dace.properties import CodeBlock
from dace.sdfg.nodes import MapEntry, MapExit, NestedSDFG
from dace.memlet import Memlet
from dace.transformation import transformation
from dace.sdfg.sdfg import InterstateEdge
from dace.sdfg.utils import set_nested_sdfg_parent_references
import copy


@transformation.explicit_cf_compatible
class ConditionMapInterchange(transformation.MultiStateTransformation):
    """
    If one or multiple maps are surrounded by a conditional block, moves the conditional block into the nested SDFG of maps.
    """

    cond_block = transformation.PatternNode(ConditionalBlock)

    @classmethod
    def expressions(cls):
        return [sdutil.node_path_graph(cls.cond_block)]

    def can_be_applied(self, graph, expr_index, sdfg, permissive=False):
        # The conditional block should only contain one condition
        # Empty else branches can be preprocessed away
        if len(self.cond_block.branches) != 1:
            return False
        branch: ControlFlowRegion = self.cond_block.branches[0][1]

        # Each state in the branch is either empty or only contains maps
        for state in branch.all_states():
            for node in state.nodes():
                if (not isinstance(node, (MapEntry, MapExit)) and state.entry_node(node) is None and any([
                        not isinstance(n, (MapEntry, MapExit)) for n in set(state.successors(node))
                        | set(state.predecessors(node))
                ])):
                    return False

        return True

    def apply(self, graph: ControlFlowRegion, sdfg: sd.SDFG):
        branch: ControlFlowRegion = self.cond_block.branches[0][1]
        branch_cond = self.cond_block.branches[0][0]
        cond_syms = set(branch_cond.get_free_symbols())
        all_states = list(branch.all_states())

        # Prepend the condition computation
        cond_sym = graph.sdfg.add_symbol(f"{self.cond_block.label}_cond", dtypes.bool, find_new_name=True)
        graph.sdfg.add_state_before(self.cond_block, assignments={cond_sym: branch_cond.as_string})
        cond_syms = [cond_sym]
        branch_cond = CodeBlock(cond_sym)

        # Wrap any map where the body does not contain a single nested SDFG
        for state in all_states:
            for node in state.nodes():
                if not isinstance(node, MapEntry):
                    continue

                body = list(state.all_nodes_between(node, state.exit_node(node)))
                if len(body) == 1 and isinstance(body[0], NestedSDFG):
                    continue

                # Get inputs and outputs of the nested SDFG
                map_exit = state.exit_node(node)
                inputs = set()
                outputs = set()
                for edge in state.out_edges(node):
                    if edge.data.data is not None:
                        inputs.add(edge.data.data)
                for edge in state.in_edges(map_exit):
                    if edge.data.data is not None:
                        outputs.add(edge.data.data)

                # Create the nested SDFG and add all symbols
                sym_mapping = {s: s for s in list(state.sdfg.symbols.keys()) + node.map.params}
                nsdfg = state.add_nested_sdfg(
                    sd.SDFG("map_body", parent=state),
                    inputs=inputs,
                    outputs=outputs,
                    parent=state,
                    symbol_mapping=sym_mapping,
                )
                for sym, dt in state.sdfg.symbols.items():
                    if sym not in nsdfg.sdfg.symbols:
                        nsdfg.sdfg.add_symbol(sym, dt)
                for a, desc in state.sdfg.arrays.items():
                    if desc.transient:
                        nsdfg.sdfg.add_datadesc(a, desc)

                start_state = nsdfg.sdfg.add_state(is_start_block=True)
                copy_mapping = {}
                for n in body:
                    new_n = copy.deepcopy(n)
                    start_state.add_node(new_n)
                    copy_mapping[n] = new_n

                param_lb_map = {}
                for i in range(len(node.map.params)):
                    param_lb_map[node.map.params[i]] = node.map.range[i][0]
                for n in body + [map_exit]:
                    for edge in state.in_edges(n):
                        src = None
                        src_conn = edge.src_conn
                        dst = None
                        dst_conn = edge.dst_conn
                        memlet = copy.deepcopy(edge.data)

                        if edge.src in copy_mapping:
                            src = copy_mapping[edge.src]
                        elif edge.src is node:
                            if edge.data.data is None:
                                continue
                            src = start_state.add_access(edge.data.data)
                            src_conn = None
                            memlet.replace(param_lb_map)
                        if edge.dst in copy_mapping:
                            dst = copy_mapping[edge.dst]
                        elif edge.dst is map_exit:
                            if edge.data.data is None:
                                continue
                            dst = start_state.add_access(edge.data.data)
                            dst_conn = None
                            memlet.replace(param_lb_map)
                        start_state.add_edge(src, src_conn, dst, dst_conn, memlet)

                for edge in state.out_edges(node):
                    if edge.data.data not in nsdfg.sdfg.arrays and edge.data.data is not None:
                        desc = copy.deepcopy(state.sdfg.arrays[edge.data.data])
                        desc.shape = edge.data.subset.size()
                        nsdfg.sdfg.add_datadesc(edge.data.data, desc)
                    state.add_edge(
                        edge.src,
                        edge.src_conn,
                        nsdfg,
                        edge.data.data,
                        copy.deepcopy(edge.data),
                    )
                for edge in state.in_edges(state.exit_node(node)):
                    if edge.data.data not in nsdfg.sdfg.arrays and edge.data.data is not None:
                        desc = copy.deepcopy(state.sdfg.arrays[edge.data.data])
                        desc.shape = edge.data.subset.size()
                        nsdfg.sdfg.add_datadesc(edge.data.data, desc)
                    state.add_edge(
                        nsdfg,
                        edge.data.data,
                        edge.dst,
                        edge.dst_conn,
                        copy.deepcopy(edge.data),
                    )

                state.remove_nodes_from(body)

        # Wrap all states in the nested SDFGs with the conditional block
        application_number = 0
        cfg_application_number = 0
        for state in all_states:
            for node in state.nodes():
                if not isinstance(node, MapEntry):
                    continue
                nsdfg: NestedSDFG = list(state.all_nodes_between(node, state.exit_node(node)))[0]
                assert isinstance(nsdfg, NestedSDFG)
                new_cond_branch = ControlFlowRegion(
                    label=f"{node.label}_cfg_c{cfg_application_number}",
                )
                cfg_application_number += 1
                body = list(nsdfg.sdfg.nodes())

                copy_mapping = {}
                for b in body:
                    new_b = copy.deepcopy(b)
                    new_cond_branch.add_node(new_b)
                    copy_mapping[b] = new_b
                for edge in nsdfg.sdfg.edges():
                    new_cond_branch.add_edge(
                        copy_mapping[edge.src],
                        copy_mapping[edge.dst],
                        copy.deepcopy(edge.data),
                    )

                new_cond_block = ConditionalBlock(
                    label=f"{node.label}_cond_block_{application_number}",
                )
                application_number += 1
                new_cond_block.add_branch(branch_cond, new_cond_branch)

                nsdfg.sdfg.remove_nodes_from(body)
                nsdfg.sdfg.add_node(new_cond_block, ensure_unique_name=True)

                # Pass the symbols used in the condition
                for sym in cond_syms:
                    if sym in state.sdfg.arrays:
                        if sym in nsdfg.sdfg.arrays:  # Already added
                            continue
                        nsdfg.sdfg.add_datadesc(sym, state.sdfg.arrays[sym])
                        nsdfg.add_in_connector(sym)
                        sym_access = state.add_access(sym)
                        conn_name = node.next_connector(sym)
                        node.add_in_connector(f"IN_{conn_name}")
                        node.add_out_connector(f"OUT_{conn_name}")
                        state.add_edge(
                            sym_access,
                            None,
                            node,
                            f"IN_{conn_name}",
                            Memlet.from_array(sym, state.sdfg.arrays[sym]),
                        )
                        state.add_edge(
                            node,
                            f"OUT_{conn_name}",
                            nsdfg,
                            sym,
                            Memlet.from_array(sym, state.sdfg.arrays[sym]),
                        )

                    else:
                        nsdfg.symbol_mapping[sym] = sym
                        if sym not in nsdfg.sdfg.symbols:
                            nsdfg.sdfg.add_symbol(sym, state.sdfg.symbols[sym])

        # Move all states in the branch before the conditional block
        src_state = graph.add_state_before(self.cond_block)
        dst_state = graph.add_state_after(self.cond_block)
        copy_mapping = {}
        for state in all_states:
            new_state = copy.deepcopy(state)
            graph.add_node(new_state, ensure_unique_name=True)
            copy_mapping[state] = new_state

        for edge in branch.edges():
            graph.add_edge(
                copy_mapping[edge.src],
                copy_mapping[edge.dst],
                copy.deepcopy(edge.data),
            )

        graph.add_edge(src_state, copy_mapping[branch.start_block], InterstateEdge())
        for sink in branch.sink_nodes():
            graph.add_edge(copy_mapping[sink], dst_state, InterstateEdge())

        # Remove the conditional block
        graph.remove_node(self.cond_block)

        # Set the parent references of nested SDFGs
        set_nested_sdfg_parent_references(graph)

def rename(sdfg: dace.SDFG, conflict_counter=0, seen_names=set()):
    for cfg in sdfg.all_control_flow_regions():
        if isinstance(cfg, dace.SDFG):
            continue
        #print(cfg.name)
        if cfg.name in seen_names:
            oldn = cfg.name
            newn = oldn + f"_{conflict_counter}"
            while newn in seen_names:
                conflict_counter += 1
                newn = oldn + f"_{conflict_counter}"
            cfg._label = newn
            cfg.label = newn
            assert cfg.name == cfg.label and cfg.name == newn
            #print(f"Renamed {oldn} to {newn} ({cfg.name})")
        seen_names.add(cfg.name)

    for state in sdfg.all_states():
        for node in state.nodes():
            if isinstance(node, NestedSDFG):
                rename(node.sdfg, conflict_counter, seen_names)



def move_if_to_innermost_map(g: dace.SDFG):
    map_swap_candidates = []
    for node, graph in g.all_nodes_recursive():
        if isinstance(node, ConditionalBlock) and len(graph.nodes()) <= 2:
            # If it has a map inside
            inner_sdfg = graph.sdfg
            parent_nsdfg = inner_sdfg.parent_nsdfg_node
            if parent_nsdfg is not None:
                # Direct src needs to be a map entry
                parent_state = _find_state(g, parent_nsdfg)
                assert parent_state is not None, "Parent state not found"
                srcs = {e.src for e in parent_state.in_edges(parent_nsdfg)}
                if len(srcs) == 1 and isinstance(next(iter(srcs)), dace.nodes.MapEntry):
                    # Parent is map, now check that we have a map inside
                    if len(node.branches) == 1:
                        branch = node.branches[0][1]
                        for state in branch.all_states():
                            for n in state.nodes():
                                if isinstance(n, dace.nodes.MapEntry):
                                    # Move the condition inside the map
                                    candidate = (node, graph.sdfg, n)
                                    map_swap_candidates.append(candidate)

    for if_node, if_sdfg, inner_map_entry in map_swap_candidates:
        #print(f"Moving if {if_node.label} inside {inner_map_entry}")
        make_map_body_nested(if_sdfg, if_node.label)
        ConditionMapInterchange().apply_to(if_sdfg, cond_block=if_node)

        # All empty states before the map entry should be moved inside
        states = list(if_sdfg.bfs_nodes(if_sdfg.start_block))
        # All state except should be empty, and inner_maP_entry should be the only one with nodes
        empty_states = [s for s in states if len(s.nodes()) == 0]
        non_empty_states = [s for s in states if len(s.nodes()) > 0]
        #print(non_empty_states)
        non_empty_states_with_map_entries = [s for s in non_empty_states if any(isinstance(n, dace.nodes.MapEntry) for n in s.nodes())]
        assert len(non_empty_states_with_map_entries) == 1, f"There should be only one non-empty state with map entries {non_empty_states_with_map_entries}"
        non_empty_state = non_empty_states_with_map_entries[0]
        inner_map_entries = [n for n in non_empty_state.nodes() if isinstance(n, dace.nodes.MapEntry)]
        #print(inner_map_entries)
        assert len(inner_map_entries) == 1, "Inner map entry should be in the non-empty state"
        inner_map_entry: dace.nodes.MapEntry = inner_map_entries[0]

        inner_map_nodes = list(non_empty_state.all_nodes_between(inner_map_entry, non_empty_state.exit_node(inner_map_entry)))
        assert len(inner_map_nodes) == 1, "There should be only one node inside the inner map"
        inner_map_node: dace.nodes.NestedSDFG = inner_map_nodes[0]
        inner_map_sdfg: dace.SDFG = inner_map_node.sdfg
        if_block = inner_map_sdfg.start_block

        # Move the if block inside the inner map
        path = [if_sdfg.out_edges(n)[0] for n in states[:-1]]
        state_map = dict()
        for i, state in enumerate(states):
            if state is non_empty_state:
                state_map[state] = if_block
                continue
            #print("Add state", state.label, "to inner map SDFG")
            ns = copy.deepcopy(state)
            state_map[state] = ns
            inner_map_sdfg.add_node(ns, is_start_block=True if i == 0 else False)

        for e in path:
            src = state_map[e.src]
            dst = state_map[e.dst]
            #print(f"Add edge from {src.label} to {dst.label} in inner map SDFG")
            assert src in inner_map_sdfg.nodes(), f"Source {src} not in inner map SDFG"
            assert dst in inner_map_sdfg.nodes(), f"Destination {dst} not in inner map SDFG"
            inner_map_sdfg.add_edge(src, dst, copy.deepcopy(e.data))

        for state in empty_states:
            if_sdfg.remove_node(state)

        non_empty_state.is_start_block = True
        #s  = _find_state(g, if_sdfg.parent_nsdfg_node)
        add_missing_data_and_symbols(g, non_empty_state, non_empty_state.sdfg, inner_map_sdfg)




    g.save("g.sdfgz", compress=True)
    #add_missing_data_and_symbols_to_all_nsdfgs(g)

    #rename(g)