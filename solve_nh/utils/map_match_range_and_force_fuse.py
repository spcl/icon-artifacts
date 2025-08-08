from copy import deepcopy
from typing import Any
from dace import SDFG, symbolic, Memlet
from dace.properties import CodeBlock
from dace.sdfg.state import SDFGState, ConditionalBlock, ControlFlowRegion
from dace.sdfg.nodes import Map, MapEntry, MapExit, AccessNode, Node, NestedSDFG
from dace.frontend.fortran.ast_utils import singular, atmost_one
from dace.transformation.helpers import redirect_edge
from dace.sdfg.propagation import propagate_memlets_sdfg
from utils.state_fusion_without_copyin_and_copyout import state_fusion_without_copyin_and_copyout
from utils.conditional_pruning import push_interstate_edges_early
from utils.move_if_cfg_inside_map import move_map_body_into_nsdfg
from dace.transformation.passes.constant_propagation import ConstantPropagation


def find_parameter_remapping(
    first_map: Map,
    second_map: Map,
) -> dict[str, str]:
    # The parameter names
    first_params: list[str] = first_map.params
    second_params: list[str] = second_map.params
    assert len(first_params) == len(second_params)

    first_rngs: dict[str, tuple[Any, Any, Any]] = {
        param: tuple(r for r in rng) for param, rng in zip(first_params, first_map.range)
    }
    second_rngs: dict[str, tuple[Any, Any, Any]] = {
        param: tuple(r for r in rng) for param, rng in zip(second_params, second_map.range)
    }

    # Parameters of the second map that have not yet been matched to a parameter
    #  of the first map and the parameters of the first map that are still free.
    #  That we use a `list` instead of a `set` is intentional, because it counter
    #  acts the issue that is described in the doc string. Using a list ensures
    #  that they indexes are matched in order. This assume that in real world
    #  code the order of the loop is not arbitrary but kind of matches.
    unmapped_second_params: list[str] = list(second_params)
    unused_first_params: list[str] = list(first_params)

    # This is the result (`second_param -> first_param`), note that if no renaming
    #  is needed then the parameter is not present in the mapping.
    final_mapping: dict[str, str] = {}

    # First we identify the parameters that already have the correct name.
    for param in set(first_params).intersection(second_params):
        first_rng = first_rngs[param]
        second_rng = second_rngs[param]

        if first_rng == second_rng:
            # They have the same name and the same range, this is already a match.
            #  Because the names are already the same, we do not have to enter them
            #  in the `final_mapping`
            unmapped_second_params.remove(param)
            unused_first_params.remove(param)

    # Check if no remapping is needed.
    if len(unmapped_second_params) == 0:
        return {}

    # Now we go through all the parameters that we have not mapped yet.
    #  All of them will result in a remapping.
    for unmapped_second_param in unmapped_second_params:
        second_rng = second_rngs[unmapped_second_param]
        assert unmapped_second_param not in final_mapping

        # Now look in all not yet used parameters of the first map which to use.
        for candidate_param in list(unused_first_params):
            candidate_rng = first_rngs[candidate_param]
            if candidate_rng == second_rng:
                final_mapping[unmapped_second_param] = candidate_param
                unused_first_params.remove(candidate_param)
                break
        else:
            raise ValueError("We did not find a candidate, so the remapping does not exist")

    assert len(unused_first_params) == 0
    assert len(final_mapping) == len(unmapped_second_params)
    return final_mapping


def rename_map_parameters(
    st: SDFGState,
    first_map: Map,
    second_map: Map,
    second_map_entry: MapEntry,
):
    # Compute the replacement dict.
    repl_dict: dict[str, str] = find_parameter_remapping(
        first_map=first_map,
        second_map=second_map,
    )

    if repl_dict is None:
        raise RuntimeError("The replacement does not exist")
    if len(repl_dict) == 0:
        return

    second_map_scope = st.scope_subgraph(entry_node=second_map_entry)
    # Why is this thing in symbolic and not in replace?
    symbolic.safe_replace(
        mapping=repl_dict,
        replace_callback=second_map_scope.replace_dict,
    )

    # For some odd reason the replace function does not modify the range and
    #  parameter of the map, so we will do it the hard way.
    second_map.params = deepcopy(first_map.params)
    second_map.range = deepcopy(first_map.range)


def flip_connector(c: str) -> str:
    if c.startswith("IN_"):
        return f"OUT_{c.removeprefix('IN_')}"
    elif c.startswith("OUT_"):
        return f"IN_{c.removeprefix('OUT_')}"
    return c


def disambiguate_connectors(st: SDFGState, mE1: MapEntry, mX1: MapExit, mE2: MapEntry, mX2: MapExit):
    def recon(m: MapEntry | MapExit, cID=0) -> int:
        drops = set(m.in_connectors)
        for c in drops:
            cID += 1
            while f"IN_rc{cID}" in m.in_connectors:
                cID += 1
            assert f"OUT_rc{cID}" not in m.out_connectors
            m.add_in_connector(f"IN_rc{cID}")
            for e in st.in_edges(m):
                if e.dst_conn == c:
                    redirect_edge(st, e, new_dst_conn=f"IN_rc{cID}")
            c = flip_connector(c)
            m.add_out_connector(f"OUT_rc{cID}")
            for e in st.out_edges(m):
                if e.src_conn == c:
                    redirect_edge(st, e, new_src_conn=f"OUT_rc{cID}")
        for c in drops:
            m.remove_in_connector(c)
            m.remove_out_connector(flip_connector(c))
        return cID

    cID = 0
    for m in [mE1, mX1, mE2, mX2]:
        cID = recon(m, cID)


def extend_range(st: SDFGState, mE1: MapEntry, mX1: MapExit, mE2: MapEntry, mX2: MapExit):
    if mE1.range == mE2.range:
        return
    assert mE1.range.covers_precise(mE2.range) or mE2.range.covers_precise(mE1.range)
    if not mE2.range.covers_precise(mE1.range):
        return extend_range(st, mE2, mX2, mE1, mX1)
    assert mE2.range.covers_precise(mE1.range)
    move_map_body_into_nsdfg(st, mE1)
    nodes_inside = [n for n in st.all_nodes_between(mE1, mX1)]
    assert len(nodes_inside) == 1 and isinstance(nodes_inside[0], NestedSDFG)
    (ng,) = nodes_inside

    conds = []
    for x, r1, r2 in zip(mE1.params, mE1.range, mE2.range):
        rb1, re1, stride1 = r1
        rb2, re2, stride2 = r2
        assert stride1 == stride2
        if rb1 != rb2:
            conds.append(f"({x} >= {rb1})")
        if re1 != re2:
            conds.append(f"({x} <= {re1})")
    assert conds
    cblok = ConditionalBlock("range_extension")
    cblok.add_branch(CodeBlock(f"{' and '.join(conds)}"), ControlFlowRegion("re_body"))
    re_body = cblok.branches[0][1]
    for x in ng.sdfg.nodes():
        re_body.add_node(x)
    for x in ng.sdfg.edges():
        re_body.add_edge(x)
    for x in ng.sdfg.nodes():
        ng.sdfg.remove_node(x)
    ng.sdfg.add_node(cblok)
    mE1.range = deepcopy(mE2.range)


def map_force_fuse(st: SDFGState, mE1: MapEntry, mX1: MapExit, mE2: MapEntry, mX2: MapExit):
    # g = st.sdfg
    # tCounter = 0  # Counter to disambiguate names
    extend_range(st, mE1, mX1, mE2, mX2)
    rename_map_parameters(st, mE1.map, mE2.map, mE2)
    disambiguate_connectors(st, mE1, mX1, mE2, mX2)
    P1 = [e.dst for e in st.out_edges(mX1)]
    P2 = [e.dst for e in st.out_edges(mX2)]
    P3 = [e.src for e in st.in_edges(mE2)]
    inb_accs = [n for n in P1 if n in P3]
    for acc in inb_accs:
        # while f"{acc.data}_ffused_{tCounter}" in g.arrays:
        #     tCounter += 1
        # acc_local, _ = g.add_scalar(f"{acc.data}_ffused_{tCounter}", acc.desc(g).dtype, transient=True)
        # acc_local = st.add_access(acc_local)

        wed = singular(ed for ed in st.in_edges(acc))
        assert wed.src is mX1
        pwed = singular(ed for ed in st.in_edges_by_connector(mX1, flip_connector(wed.src_conn)))
        st.add_edge(pwed.src, pwed.src_conn, acc, None, Memlet.from_memlet(pwed.data))
        st.remove_edge(pwed)

        for red in st.out_edges(acc):
            assert red.dst is mE2
            for nred in st.out_edges_by_connector(mE2, flip_connector(red.dst_conn)):
                st.add_edge(acc, None, nred.dst, nred.dst_conn, Memlet.from_memlet(nred.data))
                st.remove_edge(nred)
            st.remove_edge(red)

        # if acc.data in [n.data for n in P2]:
        #     st.remove_node(acc)
        # else:
        # redirect_edge(st, wed, new_src=mX2)
        st.remove_edge(wed)

    for ed in st.in_edges(mX1):
        mX2.add_in_connector(ed.dst_conn)
        redirect_edge(st, ed, new_dst=mX2)
    for ed in st.out_edges(mX1):
        mX2.add_out_connector(ed.src_conn)
        redirect_edge(st, ed, new_src=mX2)
    for ed in st.in_edges(mE2):
        mE1.add_in_connector(ed.dst_conn)
        redirect_edge(st, ed, new_dst=mE1)
    for ed in st.out_edges(mE2):
        mE1.add_out_connector(ed.src_conn)
        redirect_edge(st, ed, new_src=mE1)
    assert len(st.in_edges(mX1)) == 0
    assert len(st.out_edges(mE2)) == 0
    st.remove_node(mX1)
    st.remove_node(mE2)


def map_force_fuse_prescibed(g: SDFG, what_to_fuse: list[tuple[tuple, tuple]]):
    for u, v in what_to_fuse:
        push_interstate_edges_early(g)
        ConstantPropagation().apply_pass(g, {})
        state_fusion_without_copyin_and_copyout(g)
        mE1_st = atmost_one(
            (n, st) for n, st in g.all_nodes_recursive() if isinstance(n, MapEntry) and tuple(n.params) == u
        )
        assert mE1_st, f"Missing map {u} specified for forced fusion."
        mE1, st = mE1_st
        mE2_st = singular(
            (n, st) for n, st in g.all_nodes_recursive() if isinstance(n, MapEntry) and tuple(n.params) == v
        )
        mE2, ost = mE2_st
        assert st is ost, f"Expected the two maps to be in the same state; got {st} and {ost} / {g}"

        print(f"Attempting a forced fusion of maps: {mE1} & {mE2}")
        map_force_fuse(st, mE1, st.exit_node(mE1), mE2, st.exit_node(mE2))

        g.validate()
