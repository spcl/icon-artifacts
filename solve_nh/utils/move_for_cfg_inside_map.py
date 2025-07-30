from tabnanny import verbose
import dace
import copy

from dace.sdfg.state import ControlFlowRegion, LoopRegion

from typing import Set
from utils.add_missing_symbols import add_missing_data_and_symbols_to_all_nsdfgs, _get_missing_symbols

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
    label_counter += 1

    # If write -> An -> read, then the An does not have to be in the in/out edges
    for n in state.nodes():
        if isinstance(n, dace.nodes.AccessNode) and (not state.sdfg.arrays[n.data].transient):
            if state.in_degree(n) > 0:
                srcs.add(n.data)
            if state.out_degree(n) > 0:
                dsts.add(n.data)

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
                src = map_inner_state.add_access(e.data.data)
                map_entry_accesses[e.data.data] = src
            else:
                src = map_entry_accesses[e.data.data]
            assert e.src_conn is not None, "Expected no src conn for the map entry"
            src_conn = None
        if e.dst != map_exit:
            dst = node_map[e.dst]
            dst_conn = e.dst_conn
        else:
            if e.data.data not in map_exit_accesses:
                dst = map_inner_state.add_access(e.data.data)
                map_exit_accesses[e.data.data] = dst
            else:
                dst = map_exit_accesses[e.data.data]
            assert e.dst_conn is not None, "Expected no dst conn for the map exit"
            dst_conn = None
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

    # Remove all the original nodes
    for nd in all_inner_map_nodes:
        state.remove_node(nd)

    return map_inner_nsdfg

def _copy_nodes(state_src: dace.SDFGState, state_dst: dace.SDFGState):
    node_map = dict()
    assert len(state_dst.nodes()) == 0, "Expected the destination CFG to be empty"
    for n in state_src.nodes():
        cpynd = copy.deepcopy(n)
        if not isinstance(cpynd, dace.nodes.AccessNode) and not isinstance(cpynd, dace.nodes.MapEntry) and not isinstance(cpynd, dace.nodes.MapExit):
            cpynd.label += "_copy"
        assert n not in node_map, f"Node {n} already in node map"
        node_map[n] = cpynd
        state_dst.add_node(cpynd)
    for n in node_map.values():
        if isinstance(n, dace.nodes.NestedSDFG):
            n.sdfg.parent_graph = state_dst
            n.sdfg.parent_sdfg = state_dst.sdfg
    for e in state_src.edges():
        src = node_map[e.src]
        dst = node_map[e.dst]
        assert src in state_dst.nodes(), f"Source node {src} not in destination CFG"
        assert dst in state_dst.nodes(), f"Destination node {dst} not in destination CFG"
        state_dst.add_edge(
            src, e.src_conn,
            dst, e.dst_conn,
            copy.deepcopy(e.data)
        )


cfg_call_id = 0
def move_for_cfg_inside_map(sdfg: dace.SDFG, cfg: LoopRegion):
    global cfg_call_id
    cfg_call_id += 1
    if len(cfg.nodes()) != 1:
        print("Expected only one node in the loop region")
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
    new_state = cfg.parent_graph.add_state(
        label=f"{state.label}_cfg_{cfg_call_id}",
        is_start_block=cfg.parent_graph.in_degree(cfg) == 0
    )
    assert new_state is not None, "Expected to create a new state for the ForCFG"

    # Copy over the map Nodes
    #_copy_nodes(state, new_state)

    # Create the new nestedSDFG with the ForCFG inside
    # NSDFGP
    new_for, for_inner_state = _copy_for_cfg_with_a_new_inner_state(
        state=new_state,
        cfg=cfg,
        cfg_call_id=cfg_call_id,
        inputs=set(nsdfg.in_connectors.keys()),
        outputs=set(nsdfg.out_connectors.keys()),
        scope_entry_state=state,
        scope_entry=map_entry,
    )
    _copy_in_nsdfg_to_state(nsdfg, for_inner_state, scope_entry=map_entry, scope_state=state)

    # The new nested SDFG is now fully connected
    cfg_ies = cfg.parent_graph.in_edges(cfg)
    cfg_oes = cfg.parent_graph.out_edges(cfg)
    # Rm the previous map entry and exit
    cfg.parent_graph.remove_node(cfg)
    for e in cfg_ies:
        cfg.parent_graph.add_edge(
            e.src, new_state, copy.deepcopy(e.data)
        )
    for e in cfg_oes:
        cfg.parent_graph.add_edge(
            new_state, e.dst, copy.deepcopy(e.data)
        )

    sdfg.validate()


def move_for_cfg_inside_map_from_iterator_set(sdfg: dace.SDFG, iterator_names: Set[str]):
    cfg_candidates = {n for n, g in sdfg.all_nodes_recursive() if isinstance(n, LoopRegion) and n.loop_variable in iterator_names}
    for n in cfg_candidates:
        move_for_cfg_inside_map(n.sdfg, n)

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


def _copy_for_cfg_with_a_new_inner_state(state: dace.SDFGState, cfg: LoopRegion, cfg_call_id: int, inputs: Set[str], outputs: Set[str],
                                         scope_entry_state: dace.SDFGState, scope_entry: dace.nodes.MapEntry):

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

    new_for = LoopRegion(
        label=f"{cfg.label}_cfg_{cfg_call_id}",
        condition_expr=copy.deepcopy(cfg.loop_condition),
        loop_var=copy.deepcopy(cfg.loop_variable),
        initialize_expr=copy.deepcopy(cfg.init_statement),
        update_expr=copy.deepcopy(cfg.update_statement),
        inverted=copy.deepcopy(cfg.inverted),
        sdfg=new_sdfg,
        update_before_condition=copy.deepcopy(cfg.update_before_condition),
    )
    new_sdfg.add_node(new_for, is_start_block=True)

    nsdfg = state.add_nested_sdfg(
        sdfg=new_sdfg,
        inputs=inputs,
        outputs=outputs,
        parent=state
    )

    for_inner_state = new_for.add_state(
        label=f"{state.label}_for_cfg_{cfg_call_id}_state",
        is_start_block=True
    )

    # Connect all data to the new nested SDFG
    new_map_entry, new_map_exit = state.add_map(
        name=f"{scope_entry.label}_for_cfg_{cfg_call_id}_map",
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

    return new_for, for_inner_state

def move_for_cfg_inside_map_from_iterator_set(sdfg: dace.SDFG, iterator_names: Set[str]):
    cfg_candidates = {n for n, g in sdfg.all_nodes_recursive() if isinstance(n, LoopRegion) and n.loop_variable in iterator_names}
    for n in cfg_candidates:
        move_for_cfg_inside_map(n.sdfg, n)

def move_for_cfg_inside_map_pass(sdfg: dace.SDFG, verbose: bool = False) -> int:
    num_applied = 0
    cfg_candidates = {n for n, g in sdfg.all_nodes_recursive() if isinstance(n, LoopRegion)}
    for n in cfg_candidates:
        # If nlev inside For
        # If map has startidx
        # Then we can do it
        if not ("nlev" in n.loop_variable or "nlev" not in str(n.loop_condition) or "nlev" not in str(n.init_statement) or "nlev" not in str(n.update_statement)):
            if verbose:
                print(f"Skipping {n.label} as it does not have nlev in the loop")
            continue
        states = list(n.all_states())
        if len(states) != 1:
            if verbose:
                print("Expected exactly one state in the loop region")
            continue
        state = states[0]
        if not isinstance(state, dace.SDFGState):
            if verbose:
                print("Expected a SDFG state")
            continue
        map_entries = {n for n in state.nodes() if isinstance(n, dace.nodes.MapEntry)}
        if len(map_entries) != 1:
            if verbose:
                print("Expected exactly one map entry in the state")
            continue
        map_entry: dace.nodes.MapEntry = map_entries.pop()
        # If it has an edge that is none and between map entry and tasklet continue
        for e in state.all_edges(*state.all_nodes_between(map_entry, state.exit_node(map_entry))):
            if e.data.data is None and isinstance(e.src, dace.nodes.MapEntry) and isinstance(e.dst, dace.nodes.Tasklet):
                if verbose:
                    print(f"Skipping {n.label} as it has an edge with None data between map entry and tasklet")
                continue

        has_startidx = any( {("startidx" in str(b) or "startidx" in str(e) or "startidx" in str(s)) for (b,e,s) in map_entry.map.range} )
        if not has_startidx:
            if verbose:
                print(f"Skipping {n.label} as it does not have startidx in the map range")
            continue
        num_applied += 1
        move_for_cfg_inside_map(n.sdfg, n)
    add_missing_data_and_symbols_to_all_nsdfgs(sdfg)
    sdfg.validate()
    return num_applied
