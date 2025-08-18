import sympy
import dace
import typing

from dace.sdfg.state import ConditionalBlock, LoopRegion
from dace.sdfg.nodes import NestedSDFG, MapEntry
from itertools import chain
from dace.frontend.fortran.ast_utils import singular, atmost_one

def get_nsdfg_nestedness(sdfg: dace.SDFG) -> typing.List[typing.Tuple[NestedSDFG, dace.SDFGState, int]]:
    nestedness_list = get_nsdfg_nestedness_impl(sdfg, 1)
    sorted_list = sorted(nestedness_list, key=lambda x: x[2], reverse=True)
    return sorted_list


def get_nsdfg_nestedness_impl(sdfg: dace.SDFG, num_nestedness: int) -> typing.List[typing.Tuple[NestedSDFG, dace.SDFGState, int]]:
    # Get current NSDFGs
    result = [(n, s, num_nestedness) for s in sdfg.all_states() for n in s.nodes() if isinstance(n, NestedSDFG)]
    for n, s, _ in result:
        result += get_nsdfg_nestedness_impl(n.sdfg, num_nestedness + 1)

    return result


def _get_used_data(sdfg: dace.SDFG) -> typing.Set[str]:
    read_set, write_set = sdfg.read_and_write_sets()
    # Also need take interstate edges into account
    # Read-write sets do not take interstate edges into account
    for edge in sdfg.all_interstate_edges():
        if edge.data is None:
            continue
        for k, v in edge.data.assignments.items():
            assert isinstance(v, str), f"Expected assignment value to be a string, got {type(v)}."
            if k in sdfg.arrays:
                write_set.add(k)
            v_expr = dace.symbolic.SymExpr(v)
            def _get_all_symbols(expr):
                symbols = {s for s in expr.atoms(sympy.Symbol)}
                functions = {f.func for f in expr.atoms(sympy.Function)}
                return symbols.union(functions)
            for sym_v in _get_all_symbols(v_expr):
                sym_v_str = str(sym_v)
                if sym_v_str in sdfg.arrays:
                    read_set.add(sym_v_str)
    # Also need to take map ranges into account
    for m, st in sdfg.all_nodes_recursive():
        if not isinstance(m, MapEntry):
            continue
        for s in chain(m.new_symbols(st.sdfg, st, False), m.free_symbols):
            if s in st.sdfg.arrays:
                read_set.add(s)
    return read_set.union(write_set)


def rm_connection_of_desc_to_nsdfg_node(nsdfg_node: NestedSDFG, state: dace.SDFGState, desc_name: str):
    input_path, output_path = [], []

    # Get in-edges in to the parent SDFG node
    if desc_name in nsdfg_node.in_connectors:
        assert len(list(state.in_edges_by_connector(nsdfg_node, desc_name))) == 1, f"Multiple edges found for {nsdfg_node} with connector {desc_name}."
        cur_edge = singular(e for e in state.in_edges_by_connector(nsdfg_node, desc_name))
        while not isinstance(cur_edge.src, dace.nodes.AccessNode):
            input_path.append(cur_edge)
            cur_edge = singular(e for e in state.in_edges_by_connector(cur_edge.src, cur_edge.src_conn.replace("OUT_", "IN_")))
        input_path.append(cur_edge)

    # Get out-edges out from the parent SDFG node
    if desc_name in nsdfg_node.out_connectors:
        assert len(list(state.out_edges_by_connector(nsdfg_node, desc_name))) == 1, f"Multiple edges found for {nsdfg_node} with connector {desc_name}."
        cur_edge = singular(e for e in state.out_edges_by_connector(nsdfg_node, desc_name))
        while not isinstance(cur_edge.dst, dace.nodes.AccessNode):
            output_path.append(cur_edge)
            cur_edge = singular(e for e in state.out_edges_by_connector(cur_edge.dst, cur_edge.dst_conn.replace("IN_", "OUT_")))
        output_path.append(cur_edge)

    # Remove all edges in the input and output paths
    for edge in input_path:
        state.remove_edge(edge)
        if edge.src_conn in edge.src.out_connectors:
            edge.src.remove_out_connector(edge.src_conn)
        if edge.dst_conn in edge.dst.in_connectors:
            edge.dst.remove_in_connector(edge.dst_conn)
        if edge == input_path[-1]:
            if state.degree(edge.src) == 0:
                state.remove_node(edge.src)
    for edge in output_path:
        state.remove_edge(edge)
        if edge.src_conn in edge.src.out_connectors:
            edge.src.remove_out_connector(edge.src_conn)
        if edge.dst_conn in edge.dst.in_connectors:
            edge.dst.remove_in_connector(edge.dst_conn)
        if edge == output_path[-1]:
            if state.degree(edge.dst) == 0:
                state.remove_node(edge.dst)

def clean_unused_data_from_nsdfg(sdfg: dace.SDFG, verbose: bool = False):
    nestedness_list = get_nsdfg_nestedness(sdfg=sdfg)

    # A list of (nsdfg_node, state, nestedness)
    # Nestedness is the number of parent SDFGs
    # Sorted by nestedness (descending), such that outer NSDFGs will not think
    # data is used because it is being passed to child NSDFGs

    for nsdfg_node, nsdfg_state, nestedness in nestedness_list:
        inner_sdfg = nsdfg_node.sdfg
        used_data = _get_used_data(inner_sdfg)
        assert all((data_name in inner_sdfg.arrays) for data_name in used_data), "Expected all used data to be in the inner SDFG."
        unused_data = set(inner_sdfg.arrays.keys()) - used_data
        if not unused_data:
            continue

        print(f"nsdfg '{nsdfg_node.label}' (nestedness {nestedness}) has {len(unused_data)} unused data descriptor(s): {unused_data}")
        # Rm transient unused data from the nsdfg
        for data_name in unused_data:
            sdfg.validate()
            assert data_name in inner_sdfg.arrays
            if not inner_sdfg.arrays[data_name].transient:
                rm_connection_of_desc_to_nsdfg_node(
                    nsdfg_node=nsdfg_node,
                    state=nsdfg_state,
                    desc_name=data_name,
                )
            inner_sdfg.remove_data(name=data_name, validate=True)
            sdfg.validate()

def clean_unused_symbols_from_nsdfg(sdfg: dace.SDFG, verbose: bool = False):
    nestedness_list = get_nsdfg_nestedness(sdfg=sdfg)

    # A list of (nsdfg_node, state, nestedness)
    # Nestedness is the number of parent SDFGs
    # Sorted by nestedness (descending), such that outer NSDFGs will not think
    # data is used because it is being passed to child NSDFGs

    for nsdfg_node, nsdfg_state, nestedness in nestedness_list:
        inner_sdfg = nsdfg_node.sdfg
        all_symbols = inner_sdfg.used_symbols(all_symbols=True)
        used_symbols = inner_sdfg.used_symbols(all_symbols=False)

        unused_symbols = all_symbols - used_symbols
        if not unused_symbols:
            continue

        print(f"nsdfg '{nsdfg_node.label}' (nestedness {nestedness}) has {len(unused_symbols)} unused symbol(s): {unused_symbols}")
        for unused_sym in unused_symbols:
            if unused_sym in inner_sdfg.symbols:
                inner_sdfg.remove_symbol(unused_sym)
            if unused_sym in nsdfg_node.symbol_mapping:
                del nsdfg_node.symbol_mapping[unused_sym]