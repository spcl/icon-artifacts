import dace
import copy
from dace import SDFG
from dace.properties import CodeBlock
from dace.sdfg.state import ControlFlowRegion, LoopRegion, ConditionalBlock
from utils.add_missing_symbols import (
    add_missing_data_and_symbols_to_all_nsdfgs,
    _insert_missing_data_through_parent_scopes,
    _insert_missing_data_through_parent_out_scopes,
    _get_missing_symbols
)
from dace.frontend.fortran.ast_utils import singular, atmost_one

from typing import Set, Tuple

label_counter = 0

def _move_map_body_into_nsdfg(state: dace.SDFGState, map_entry: dace.nodes.MapEntry):
    global label_counter
    node_map = dict() # Used to deepcopy into the nested SDFG
    map_exit = state.exit_node(map_entry)

    # 1 Nested SDFG with 1 state
    map_inner_sdfg = dace.SDFG(
        name=f"{map_entry.label}_inner_sdfg_{label_counter}",
        parent=state
    )
    map_inner_state = map_inner_sdfg.add_state(
        label=f"{map_entry.label}_inner_state_{label_counter}",
        is_start_block=True
    )

    # Get all input and output data of the map
    srcs = {e.data.data for e in state.in_edges(map_entry)}
    dsts = {e.data.data for e in state.out_edges(map_exit)}

    # This data needs to explicitly be added through the parent scopes
    explicitly_add = set()  # Data that should be explicitly added to the map inner state

    # If write -> An -> read, then the An does not have to be in the in/out edges, but if in nsdfg, we still
    # will need to add it
    for n in state.all_nodes_between(map_entry, map_exit):
        if isinstance(n, dace.nodes.AccessNode):
            if state.in_degree(n) > 0 and state.out_degree(n) > 0:
                dsts.add(n.data)
                srcs.add(n.data)
                explicitly_add.add(n.data)
    #if explicitly_add:
    #    raise Exception(f"Explicitly adding {explicitly_add} data to the map inner state, this should not happen, check")
    label_counter += 1

    # Use later for removing the original nodes
    all_inner_map_nodes = set(state.all_nodes_between(map_entry, map_exit))

    # Genrated the map dict, copy nodes over, keep the mapping to be able to add edges later
    for nd in all_inner_map_nodes:
        cpynd = copy.deepcopy(nd)
        assert nd not in node_map, f"Node {nd} already in node map"
        node_map[nd] = cpynd
        map_inner_state.add_node(cpynd)
    #for data in srcs.union(dsts):
    #    an = map_inner_state.add_access(data)
    #    assert data not in node_map, f"Data {data} already in node map"
    #    node_map[data] = an
    # Copy over needed non-transient arrays
    for data in srcs.union(dsts):
        copydesc = copy.deepcopy(state.sdfg.arrays[data])
        copydesc.transient = False
        map_inner_sdfg.add_datadesc(
            name=data,
            datadesc=copydesc,
            find_new_name=False,
        )

    # Any data that has not been added so far, if array add as non-transient, if scalar add as transient
    for cpynd in all_inner_map_nodes:
        if isinstance(cpynd, dace.nodes.AccessNode):
            if cpynd.data not in map_inner_sdfg.arrays:
                copydesc = copy.deepcopy(state.sdfg.arrays[cpynd.data])
                if isinstance(copydesc, dace.data.Array):
                    copydesc.transient = False
                else:
                    copydesc.transient = True
                map_inner_sdfg.add_datadesc(
                    name=cpynd.data,
                    datadesc=copydesc,
                    find_new_name=False,
                )

    # Add all edges using the node mapping
    map_entry_accesses = dict()
    map_exit_accesses = dict()
    for e in state.all_edges(*all_inner_map_nodes):
        # If src or dst is a map entry/exit, use the data connection
        if e.src != map_entry:
            src = node_map[e.src]
            src_conn = e.src_conn
        else:
            if e.data.data not in map_entry_accesses:
                if e.data.data is not None:
                    src = map_inner_state.add_access(e.data.data)
                    map_entry_accesses[e.data.data] = src
                else:
                    src = None
            else:
                if e.data.data is not None:
                    src = map_entry_accesses[e.data.data]
            if src is not None:
                assert e.src_conn is not None, "Expected no src conn for the map entry"
            src_conn = None
        if e.dst != map_exit:
            dst = node_map[e.dst]
            dst_conn = e.dst_conn
        else:
            if e.data.data not in map_exit_accesses:
                if e.data.data is not None:
                    dst = map_inner_state.add_access(e.data.data)
                    map_exit_accesses[e.data.data] = dst
                else:
                    dst = None
            else:
                if e.data.data is not None:
                    dst = map_exit_accesses[e.data.data]
            if dst is not None:
                assert e.dst_conn is not None, "Expected no dst conn for the map exit"
            dst_conn = None
        if src is not None and dst is not None:
            map_inner_state.add_edge(
                src, src_conn,
                dst, dst_conn,
                copy.deepcopy(e.data)
            )



    # Add nested SDFG between the map entry and exit, make sure all symbols that might be used are defined
    needed_symbols = state.symbols_defined_at(map_entry)
    for sym_key, sym_val in needed_symbols.items():
        map_inner_sdfg.add_symbol(name=sym_key, stype=sym_val, find_new_name=False)


    map_inner_nsdfg = state.add_nested_sdfg(
        sdfg=map_inner_sdfg,
        parent=state,
        inputs=srcs,
        outputs=dsts,
        #symbol_mapping={k: k for k in needed_symbols},
    )

    # Connect maps to the nested SDFG (there might be multiple edges per out connector but we need to make it into one)
    for out_conn in map_entry.out_connectors:
        es = {e for e in state.out_edges_by_connector(map_entry, out_conn)}
        datas = {e.data.data for e in es}
        assert len(datas) == 1
        data = datas.pop()
        state.add_edge(
            map_entry,
            out_conn,
            map_inner_nsdfg,
            data,
            dace.memlet.Memlet.from_array(
                data,
                state.sdfg.arrays[data]
            )
        )
    for in_conn in map_exit.in_connectors:
        es = {e for e in state.in_edges_by_connector(map_exit, in_conn)}
        datas = {e.data.data for e in es}
        assert len(datas) == 1
        data = datas.pop()
        state.add_edge(
            map_inner_nsdfg,
            data,
            map_exit,
            in_conn,
            dace.memlet.Memlet.from_array(
                data,
                state.sdfg.arrays[data]
            )
        )

    for src in srcs:
        if src not in map_inner_nsdfg.in_connectors:
            map_inner_nsdfg.add_in_connector(src)

    # Remove all the original nodes
    for nd in all_inner_map_nodes:
        state.remove_node(nd)

    if explicitly_add:
        print(f"Explicitly adding {len(explicitly_add)} ({explicitly_add}) data through parent scopes")
        _insert_missing_data_through_parent_scopes(explicitly_add,
                                                    map_inner_nsdfg,
                                                    state,
                                                    state.sdfg)
        _insert_missing_data_through_parent_out_scopes(explicitly_add,
                                                    map_inner_nsdfg,
                                                    state,
                                                    state.sdfg)

    map_inner_sdfg.validate()

    return map_inner_nsdfg

cfg_call_id = 0
def move_if_cfg_inside_map(sdfg: dace.SDFG, if_block: ConditionalBlock):
    global cfg_call_id
    cfg_call_id += 1
    if not isinstance(if_block, ConditionalBlock):
        print("Expected a ConditionalBlock")
        return
    if len(if_block.branches) != 1:
        print("Expected exactly one branch in the conditional block")
        return
    cfg = if_block.branches[0][1]
    if len(cfg.nodes()) != 1:
        print("Expected only one node in the conditional block")
        return
    state: dace.SDFGState = cfg.nodes()[0]
    if not isinstance(state, dace.SDFGState):
        print("Expected a SDFG state")
        return
    map_entries = {n for n in state.nodes() if isinstance(n, dace.nodes.MapEntry)}
    if len(map_entries) != 1:
        print("Expected exactly one map entry in the state")
        return
    map_entry: dace.nodes.MapEntry = map_entries.pop()
    # Map entry either should have only 1 nsdfg or no nested SDFG
    nsdfgs = {n for n in state.all_nodes_between(map_entry, state.exit_node(map_entry)) if isinstance(n, dace.nodes.NestedSDFG)}
    if len(nsdfgs) > 1:
        print("Expected at most one nested SDFG in the map entry")
        return
    if len(nsdfgs) == 0:
        # No nested SDFG, move the body into a new nested SDFG
        nsdfg = _move_map_body_into_nsdfg(state, map_entry)
    else:
        nsdfg = nsdfgs.pop()
    nsdfgs = {n for n in state.all_nodes_between(map_entry, state.exit_node(map_entry)) if isinstance(n, dace.nodes.NestedSDFG)}
    assert len(nsdfgs) == 1, "Expected exactly one nested SDFG in the map entry after moving map body to a nested SDFG"

    # Now we have a a ForCFG [State]
    # In the state we have Map [NSDFG]
    # We want it to be Map [NSDFGP] and in NSDFGP [ForCFG [NSDFG]]

    # We will do this by adding a new block
    #previous_block = cfg.parent_graph.in_edges(cfg)[0].src if len(cfg.parent_graph.in_edges(cfg)) > 0 else None
    #next_block = cfg.parent_graph.out_edges(cfg)[0].dst if len(cfg.parent_graph.out_edges(cfg)) > 0 else None

    # Nested State will have the NSDFGP [ForCFG [NSDFG]] inside
    new_state = if_block.parent_graph.add_state(
        label=f"{state.label}_cfg_{cfg_call_id}",
        is_start_block=if_block.parent_graph.in_degree(if_block) == 0
    )
    assert new_state is not None, "Expected to create a new state for the ForCFG"
    # The new nested SDFG is now fully connected
    if_block_ies = if_block.parent_graph.in_edges(if_block)
    if_block_oes = if_block.parent_graph.out_edges(if_block)
    # Rm the previous map entry and exit
    if_block.parent_graph.remove_node(if_block)
    for e in if_block_ies:
        if_block.parent_graph.add_edge(
            e.src, new_state, copy.deepcopy(e.data)
        )
    for e in if_block_oes:
        if_block.parent_graph.add_edge(
            new_state, e.dst, copy.deepcopy(e.data)
        )

    # Copy over the map Nodes
    #_copy_nodes(state, new_state)

    # Create the new nestedSDFG with the ForCFG inside
    # NSDFGP
    ies = if_block_ies
    for e in ies:
        if e.data is not None:
            interstate_assignments = dict()
            for k, v in e.data.assignments.items():
                if k in interstate_assignments:
                    raise Exception(f"Duplicate interstate assignment {k} in {e.data}, check")
                interstate_assignments[k] = v
            e.data.assignments = dict()

    assert map_entry in state.nodes(), "Expected the map entry to be in the state"
    assert len(new_state.nodes()) == 0, "Expected the new state to be empty"
    new_if, if_nsdfg, if_inner_state = _copy_if_cfg_with_a_new_inner_state(
        state=new_state,
        old_if=if_block,
        cfg_call_id=cfg_call_id,
        inputs=set(nsdfg.in_connectors.keys()),
        outputs=set(nsdfg.out_connectors.keys()),
        scope_entry_state=state,
        scope_entry=map_entry,
        interstate_assignments=interstate_assignments
    )
    _copy_in_nsdfg_to_state(nsdfg, if_inner_state, scope_entry=map_entry, scope_state=state)

    missing_symbols = _get_missing_symbols(if_nsdfg)
    if missing_symbols:
        print(f"Missing symbols in the new nested SDFG: {missing_symbols}")
        add_missing_data_and_symbols_to_all_nsdfgs(
            sdfg
        )
        sdfg.validate()


def move_if_cfg_inside_map_from_labels(sdfg: dace.SDFG, labels: Set[str]):
    cfg_candidates = {n for n, g in sdfg.all_nodes_recursive() if isinstance(n, ConditionalBlock) and len(n.branches) == 1 and n.label in labels}
    for n in cfg_candidates:
        move_if_cfg_inside_map(n.sdfg, n)

def _copy_in_nsdfg_to_state(nsdfg: dace.nodes.NestedSDFG, state: dace.SDFGState, scope_entry: dace.nodes.MapEntry, scope_state: dace.SDFGState):
    map_body_copy_nsdfg = copy.deepcopy(nsdfg)
    state.add_node(
        map_body_copy_nsdfg
    )
    for arr_name, arr in map_body_copy_nsdfg.sdfg.arrays.items():
        state.sdfg.add_datadesc(
            name=arr_name,
            datadesc=copy.deepcopy(arr),
            find_new_name=False,
        )
    for sym_name, sym_type in map_body_copy_nsdfg.sdfg.symbols.items():
        state.sdfg.add_symbol(
            name=sym_name,
            stype=sym_type,
            find_new_name=False,
        )
    for sym_name, sym_type in scope_state.symbols_defined_at(scope_entry).items():
        state.sdfg.add_symbol(
            name=sym_name,
            stype=sym_type,
            find_new_name=False,
        )
    map_body_copy_nsdfg.sdfg.parent_graph = state
    map_body_copy_nsdfg.sdfg.parent_sdfg = state.sdfg

    # Connect all data to the new nested SDFG
    for in_conn in map_body_copy_nsdfg.in_connectors:
        an = state.add_access(in_conn)
        state.add_edge(
            an,
            None,
            map_body_copy_nsdfg,
            in_conn,
            dace.memlet.Memlet.from_array(
                in_conn,
                state.sdfg.arrays[in_conn]
            )
        )
    for out_conn in map_body_copy_nsdfg.out_connectors:
        an = state.add_access(out_conn)
        state.add_edge(
            map_body_copy_nsdfg,
            out_conn,
            an,
            None,
            dace.memlet.Memlet.from_array(
                out_conn,
                state.sdfg.arrays[out_conn]
            )
        )


def _copy_if_cfg_with_a_new_inner_state(state: dace.SDFGState, old_if: ConditionalBlock, cfg_call_id: int, inputs: Set[str], outputs: Set[str],
                                         scope_entry_state: dace.SDFGState, scope_entry: dace.nodes.MapEntry,
                                         interstate_assignments: dict):

    new_sdfg = dace.SDFG(
        name=f"for_cfg_{cfg_call_id}",
        parent=state
    )

    # Add symbols defined in the scope entry to the nsdfg
    for sym, stype in scope_entry_state.symbols_defined_at(scope_entry).items():
        new_sdfg.add_symbol(
            name=sym,
            stype=stype,
            find_new_name=False,
        )
    for param in scope_entry.map.params:
        new_sdfg.add_symbol(
            name=param,
            stype=dace.int32,
            find_new_name=False,
        )

    new_if = ConditionalBlock(
        label=f"{old_if.label}_if_{cfg_call_id}",
        sdfg=new_sdfg,
        parent=new_sdfg,
    )

    new_sdfg.add_node(new_if, is_start_block=True)

    new_if_cfg = ControlFlowRegion(
        label=f"{new_if.label}_if_body_{cfg_call_id}",
    )
    assert len(old_if.branches) == 1, "Expected exactly one branch in the if block"
    old_branch = old_if.branches[0]
    old_cond = old_branch[0]
    old_cfg = old_branch[1]
    new_if.add_branch(
        condition=old_cond,
        branch=new_if_cfg
    )

    nsdfg = state.add_nested_sdfg(
        sdfg=new_sdfg,
        inputs=inputs,
        outputs=outputs,
        parent=state
    )

    if_inner_state = new_if_cfg.add_state(
        label=f"{state.label}_if_cfg_{cfg_call_id}_state",
        is_start_block=False
    )

    # Connect all data to the new nested SDFG
    new_map_entry, new_map_exit = state.add_map(
        name=f"{scope_entry.label}_if_cfg_{cfg_call_id}_map",
        ndrange={p: dace.subsets.Range([(b,e,s)]) for p, (b,e,s) in zip(scope_entry.map.params, scope_entry.map.range)},
        schedule=scope_entry.map.schedule,
        unroll= scope_entry.map.unroll,
        debuginfo=scope_entry.map.debuginfo,
    )
    for in_conn in nsdfg.in_connectors:
        an = state.add_access(in_conn)
        state.add_edge(
            an,
            None,
            new_map_entry,
            "IN_" + an.data,
            dace.memlet.Memlet.from_array(
                in_conn,
                state.sdfg.arrays[in_conn]
            )
        )
        state.add_edge(
            new_map_entry,
            "OUT_" + an.data,
            nsdfg,
            in_conn,
            dace.memlet.Memlet.from_array(
                in_conn,
                state.sdfg.arrays[in_conn]
            )
        )
        assert in_conn == an.data
        new_map_entry.add_in_connector("IN_" + an.data)
        new_map_entry.add_out_connector("OUT_" + an.data)
    for out_conn in nsdfg.out_connectors:
        an = state.add_access(out_conn)
        state.add_edge(
            nsdfg,
            out_conn,
            new_map_exit,
            "IN_" + an.data,
            dace.memlet.Memlet.from_array(
                out_conn,
                state.sdfg.arrays[out_conn]
            )
        )
        state.add_edge(
            new_map_exit,
            "OUT_" + an.data,
            an,
            None,
            dace.memlet.Memlet.from_array(
                out_conn,
                state.sdfg.arrays[out_conn]
            )
        )
        assert out_conn == an.data
        new_map_exit.add_in_connector("IN_" + an.data)
        new_map_exit.add_out_connector("OUT_" + an.data)

    return new_if, nsdfg, if_inner_state

def move_if_cfg_inside_map_from_condition_var(g: SDFG, cond: set[str]):
    for cv in cond:
        co = singular(n for n, _ in g.all_nodes_recursive()
                          if isinstance(n, ConditionalBlock)
                          and any(b is not None and cv in b.as_string for b, _ in n.branches))
        move_if_cfg_inside_map(co.sdfg, co)

def move_if_cfg_inside_map_pass(sdfg: dace.SDFG, verbose: bool = False) -> int:
    num_applied = 0
    cfg_candidates = {n for n, g in sdfg.all_nodes_recursive() if isinstance(n, ConditionalBlock)}
    for n in cfg_candidates:
        if len(n.branches) != 1:
            #print(f"Skipping {n.label} as it has more than one branch")
            continue
        if not isinstance(n, ConditionalBlock):
            #print(f"Skipping {n.label} as it is not a ConditionalBlock")
            continue
        if_cfg_tup : Tuple[CodeBlock, ControlFlowRegion] = n.branches[0]
        if_cond = if_cfg_tup[0]
        if_cfg = if_cfg_tup[1]
        states = if_cfg.nodes()
        if "_if_cond_56" in if_cond.as_string:
            if verbose:
                print(f"Skipping {n.label} ({if_cond.as_string}) as it is handled in a special case")
            continue
        if len(states) != 1:
            if verbose:
                print(f"Skipping {n.label} ({if_cond.as_string}) as it has more than one state in the if body region {len(states)}")
            continue
        state = states[0]
        if not isinstance(state, dace.SDFGState):
            if verbose:
                print(f"Skipping {n.label} ({if_cond.as_string}) as the top level node in the body is not a SDFG state {state}: {type(state)}")
            continue
        map_entries = {n for n in state.nodes() if isinstance(n, dace.nodes.MapEntry)}
        if len(map_entries) != 1:
            if verbose:
                print(f"Skipping {n.label} ({if_cond.as_string})  as it has more/less than one map entry in the state got {len(map_entries)}")
            continue
        map_entry: dace.nodes.MapEntry = map_entries.pop()
        # If it has an edge that is none and between map entry and tasklet continue
        if any((e.data.data is None and isinstance(e.src, dace.nodes.MapEntry) and isinstance(e.dst, dace.nodes.Tasklet))
               for e in state.all_edges(*state.all_nodes_between(map_entry, state.exit_node(map_entry)))):
            if verbose:
                print(f"Skipping {n.label} ({if_cond.as_string}) as it has an edge with None data between map entry and tasklet")
            continue
        num_applied += 1
        if verbose:
            print(f"Moving {n.label} ({if_cond.as_string}) inside map {map_entry.label}")
        move_if_cfg_inside_map(n.sdfg, n)
    add_missing_data_and_symbols_to_all_nsdfgs(sdfg)
    sdfg.validate()
    return num_applied
