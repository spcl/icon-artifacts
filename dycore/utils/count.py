import dace
from dace.sdfg.state import LoopRegion
from typing import Dict, Set


def count_loops(sdfg: dace.SDFG, verbose: bool = False, use_assert: bool = False):
    loops_post = 0
    for node, state in sdfg.all_nodes_recursive():
        if isinstance(node, LoopRegion):
            if verbose:
                print(f"Loop: {node.label}")
            loops_post += 1

    if verbose:
        print(f"Loops remaining: {loops_post}")

    if use_assert and loops_post > 0:
        import warnings
        warnings.warn(f"Loops remaining: {loops_post}")


def count_max_maps_per_state(
    sdfg: dace.SDFG, verbose: bool = False, use_assert: bool = False
):
    max_maps_per_state = 0
    for state in sdfg.all_states():
        maps = [
            n
            for n in state.nodes()
            if isinstance(n, dace.nodes.MapEntry) and state.entry_node(n) is None
        ]
        max_maps_per_state = max(max_maps_per_state, len(maps))

        if verbose and len(maps) > 1:
            print(f"State: {state.label}, Maps: {len(maps)}")

    if verbose:
        print(f"Max maps per state: {max_maps_per_state}")

    if use_assert:
        assert max_maps_per_state <= 1, f"Max maps per state: {max_maps_per_state}"


def count_symbols_use_defs(
    sdfg: dace.SDFG, verbose: bool = False, use_assert: bool = False
):
    """
    Counts how many symbols are defined in nested SDFGs and used outside.
    """
    # Build a map for used and defined symbols for each SDFG
    used_symbols = {}
    defined_symbols = {}
    # Map of SDFGs to all their parents (set)
    parents: Dict[dace.SDFG, Set[dace.SDFG]] = {}

    for node, parent in sdfg.all_nodes_recursive():
        if isinstance(node, dace.nodes.NestedSDFG):
            used_syms = node.sdfg.used_symbols(all_symbols=False)
            def_syms = set()
            for edge, p in node.sdfg.all_edges_recursive():
                if p.sdfg == node.sdfg:
                    if isinstance(edge.data, dace.InterstateEdge):
                        def_syms.update(edge.data.assignments.keys())

            used_symbols[node.sdfg] = used_syms - def_syms
            defined_symbols[node.sdfg] = def_syms - used_syms
            parents[node.sdfg] = set([parent.sdfg])

    used_syms = sdfg.used_symbols(all_symbols=False)
    def_syms = set()
    for edge, p in sdfg.all_edges_recursive():
        if p.sdfg == sdfg:
            if isinstance(edge.data, dace.InterstateEdge):
                def_syms.update(edge.data.assignments.keys())
    used_symbols[sdfg] = used_syms - def_syms
    defined_symbols[sdfg] = def_syms - used_syms
    parents[sdfg] = set()

    # Propagate parent mapping
    changed = True
    while changed:
        changed = False
        for nsdfg in parents.keys():
            for psdfg in list(parents[nsdfg]):
                psdfg_parents = parents[psdfg]
                if psdfg_parents.issubset(parents[nsdfg]):
                    continue
                parents[nsdfg].update(psdfg_parents)
                changed = True

    # Check if any symbol is defined in a nested SDFG and used outside
    count = 0
    for nsdfg, defed in defined_symbols.items():
        for parent in parents[nsdfg]:
            intersection = defed.intersection(used_symbols[parent])

            if intersection != set():
                if verbose:
                    print(
                        f"Symbols defined in nested SDFG {nsdfg.label} and used outside: {intersection}"
                    )
                count += 1

    if verbose:
        print(f"Symbols defined in nested SDFGs and used outside: {count}")

    if use_assert and count > 0:
        import warnings
        warnings.warn(
            f"Symbols defined in nested SDFGs and used outside: {count}"
        )
