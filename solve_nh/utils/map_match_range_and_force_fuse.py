from copy import deepcopy
from typing import Any
from dace import SDFG, symbolic
from dace.sdfg.state import SDFGState
from dace.sdfg.nodes import Map, MapEntry, MapExit, AccessNode, Node
from dace.frontend.fortran.ast_utils import singular, atmost_one
from dace.transformation.helpers import redirect_edge


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


def map_force_fuse(st: SDFGState, mE1: MapEntry, mX1: MapExit, mE2: MapEntry, mX2: MapExit):
    # g = st.sdfg
    # tCounter = 0  # Counter to disambiguate names
    rename_map_parameters(st, mE1.map, mE2.map, mE2)
    disambiguate_connectors(st, mE1, mX1, mE2, mX2)
    P1 = [e.dst for e in st.out_edges(mX1)]
    P2 = [e.dst for e in st.out_edges(mX2)]
    P3 = [e.src for e in st.in_edges(mE2)]
    inb_accs = [n for n in P1 if n in P3]
    for acc in inb_accs:
        # while f"{acc.data}_transified_{tCounter}" in g.arrays:
        #     tCounter += 1
        # acc_local, _ = g.add_scalar(f"{acc.data}_ffused_{tCounter}", acc.desc(g).dtype, transient=True)
        # acc_local = st.add_access(acc_local)

        wed = singular(ed for ed in st.in_edges(acc))
        assert wed.src is mX1
        pwed = singular(ed for ed in st.in_edges_by_connector(mX1, flip_connector(wed.src_conn)))
        # if acc.data not in [n.data for n in P2]:
        #     redirect_edge(st, wed, new_src=mX2)
        # else:
        st.remove_edge(wed)
        redirect_edge(st, pwed, new_dst=acc)

        for red in st.out_edges(acc):
            assert red.dst is mE2
            for nred in st.out_edges_by_connector(mE2, flip_connector(red.dst_conn)):
                redirect_edge(st, nred, new_src=acc)
            st.remove_edge(red)
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


PRESCRIBED_FUSIONS = {
    "solve_nh_corrector_pre": [
        (("_for_it_55", "_for_it_56"), ("_for_it_57", "_for_it_58")),
    ],
    "solve_nh_corrector_post": [
        (("_for_it_5", "_for_it_6"), ("_for_it_7", "_for_it_8")),
        (("_for_it_42",), ("_for_it_44",)),
        (("_for_it_9", "_for_it_10"), ("_for_it_11", "_for_it_12")),
        (("_for_it_17",), ("_for_it_18",))
    ],
    "solve_nh_predictor_pre": [
        (("_for_it_104", "_for_it_105"), ("_for_it_106", "_for_it_107")),
    ],
    "solve_nh_predictor_post": [
        (("_for_it_1", "_for_it_2"), ("_for_it_3", "_for_it_4")),
        (("_for_it_35",), ("_for_it_37",)),
    ],
}


def map_force_fuse_prescibed(g: SDFG, what_to_fuse=PRESCRIBED_FUSIONS):
    if g.name not in what_to_fuse:
        print(f"No forced-fusion specified for {g.name}.")
        return

    for u, v in what_to_fuse[g.name]:
        mE1_st = atmost_one(
            (n, st) for n, st in g.all_nodes_recursive() if isinstance(n, MapEntry) and tuple(n.params) == u
        )
        assert mE1_st, f"Missing map {u} specified for forced fusion."
        mE1, st = mE1_st
        mE2 = singular(n for n, _ in g.all_nodes_recursive() if isinstance(n, MapEntry) and tuple(n.params) == v)

        print(f"Attempting a forced fusion of maps: {mE1} & {mE2}")
        map_force_fuse(st, mE1, st.exit_node(mE1), mE2, st.exit_node(mE2))

        g.validate()
