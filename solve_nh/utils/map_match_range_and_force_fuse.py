from copy import deepcopy
import sympy
import dace
from dace import SDFG, symbolic, Memlet, subsets
from dace.subsets import Range
from dace.properties import CodeBlock
from dace.sdfg.sdfg import InterstateEdge
from dace.sdfg.state import SDFGState, ConditionalBlock, ControlFlowRegion
from dace.sdfg.nodes import Map, MapEntry, MapExit, AccessNode, Node, NestedSDFG
from dace.frontend.fortran.ast_utils import singular, atmost_one
from dace.transformation.helpers import redirect_edge
from dace.sdfg.propagation import propagate_memlets_sdfg
from utils.state_fusion_without_copyin_and_copyout import state_fusion_without_copyin_and_copyout
from utils.conditional_pruning import push_interstate_edges_early
from utils.move_if_cfg_inside_map import move_map_body_into_nsdfg
from dace.sdfg.replace import replace, replace_dict
from dace.sdfg.state import StateSubgraphView
from dace.transformation.passes.constant_propagation import ConstantPropagation


def rename_map_parameters(
    st: SDFGState,
    first_map: Map,
    second_map: Map,
    second_map_entry: MapEntry,
):
    # Compute the replacement dict.
    repl_dict = {k: v for k, v in zip(second_map.params, first_map.params)}

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
        drops = set(c for c in m.in_connectors if c.startswith("IN_") or c.startswith("OUT_"))
        for c in drops:
            cID += 1
            while f"IN_rc{cID}" in m.in_connectors:
                cID += 1
            assert f"OUT_rc{cID}" not in m.out_connectors
            m.add_in_connector(f"IN_rc{cID}")
            for e in st.in_edges_by_connector(m, c):
                redirect_edge(st, e, new_dst_conn=f"IN_rc{cID}")
            c = flip_connector(c)
            m.add_out_connector(f"OUT_rc{cID}")
            for e in st.out_edges_by_connector(m, c):
                redirect_edge(st, e, new_src_conn=f"OUT_rc{cID}")
        for c in drops:
            m.remove_in_connector(c)
            m.remove_out_connector(flip_connector(c))
        return cID

    cID = 0
    for m in [mE1, mX1, mE2, mX2]:
        cID = recon(m, cID)


def real_union(R1: Range, R2: Range) -> Range:
    assert R1.dims() == R2.dims()
    out = []
    for r1, r2 in zip(R1, R2):
        rb1, re1, stride1 = r1
        rb2, re2, stride2 = r2
        assert stride1 == stride2
        ob = rb1 if rb1 == rb2 else sympy.Min(rb1, rb2)
        oe = re1 if re1 == re2 else sympy.Max(re1, re2)
        out.append((ob, oe, stride1))
    return Range(out)


def extend_range(st: SDFGState, mE1: MapEntry, mE2: MapEntry):
    if mE1.range == mE2.range:
        return
    target_range = real_union(mE1.range, mE2.range)

    for mE in [mE1, mE2]:
        if target_range == mE.range:
            continue

        move_map_body_into_nsdfg(st, mE)
        nodes_inside = [n for n in st.all_nodes_between(mE, st.exit_node(mE))]
        assert len(nodes_inside) == 1 and isinstance(nodes_inside[0], NestedSDFG)
        (ng,) = nodes_inside

        conds = []
        for x, r1, r2 in zip(mE.params, mE.range, target_range):
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
        mE.range = deepcopy(target_range)


def map_force_fuse(st: SDFGState, mE1: MapEntry, mX1: MapExit, mE2: MapEntry, mX2: MapExit):
    g = st.sdfg
    # tCounter = 0  # Counter to disambiguate names
    extend_range(st, mE1, mE2)
    g.validate()
    rename_map_parameters(st, mE1.map, mE2.map, mE2)
    g.validate()
    disambiguate_connectors(st, mE1, mX1, mE2, mX2)
    g.validate()
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
        if ed.dst_conn in mE1.in_connectors:
            st.remove_edge(ed)
        else:
            mE1.add_in_connector(ed.dst_conn)
            redirect_edge(st, ed, new_dst=mE1)
    for ed in st.out_edges(mE2):
        mE1.add_out_connector(ed.src_conn)
        redirect_edge(st, ed, new_src=mE1)
    assert len(st.in_edges(mX1)) == 0
    assert len(st.out_edges(mE2)) == 0
    st.remove_node(mX1)
    st.remove_node(mE2)
    g.validate()


def map_parameters_should_be_at_most_symbols(g: SDFG):
    for mE, st in g.all_nodes_recursive():
        if not isinstance(mE, MapEntry):
            continue
        param_conns = set(c for c in mE.in_connectors.keys() if not c.startswith("IN_"))
        if not param_conns:
            continue
        print(f"Moving parameter connectors of {mE} to symbols: {param_conns}")
        # if "_for_it_102" in str(mE):
        #     g.save("foo.sdfgz", compress=True)
        #     breakpoint()
        for c in param_conns:
            ied = singular(st.in_edges_by_connector(mE, c))
            assert isinstance(ied.src, AccessNode)
            same_acc = [ac for ac in st.nodes() if isinstance(ac, AccessNode) and ac.data == ied.src.data]
            if any(len(st.in_edges(ac)) > 0 for ac in same_acc):
                print(f"...however, {ied.src.data} is being written at the same state {st}, so cannot move.")
                continue
            st_ieds = [e for e in st.parent_graph.in_edges(st) if isinstance(e.data, InterstateEdge)]
            if not st_ieds:
                pst = st.parent_graph.add_state("syminit", is_start_block=True)
                st_ieds.append(st.parent_graph.add_edge(pst, st, InterstateEdge()))

            tCounter = 0

            def _symname() -> str:
                return f"{ied.src.data}_tosym_{tCounter}"

            while any(_symname() in e.data.assignments for e in st_ieds) or _symname() in st.parent_graph.sdfg.symbols:
                tCounter += 1

            st.parent_graph.sdfg.add_symbol(_symname(), dace.int64)
            for e in st_ieds:
                e.data.assignments[_symname()] = ied.src.data
            replace(StateSubgraphView(st, [mE]), c, _symname())
            if st.out_degree(ied.src) == 1:
                st.remove_node(ied.src)
            else:
                st.remove_edge(ied)
            mE.remove_in_connector(c)
        g.validate()


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
        mE2_st = atmost_one(
            (n, st) for n, st in g.all_nodes_recursive() if isinstance(n, MapEntry) and tuple(n.params) == v
        )
        assert mE2_st, f"Missing map {v} specified for forced fusion."
        mE2, ost = mE2_st
        if not (st is ost):
            # POSSIBLY AN UNSTABLE ORDERING IN STATE FUSION PROBLEM
            print(f"Expected the two maps ({u}, {v}) to be in the same state; got {st} and {ost} / {g}")
            breakpoint()
            continue
        assert st is ost, f"Expected the two maps ({u}, {v}) to be in the same state; got {st} and {ost} / {g}"

        print(f"Attempting a forced fusion of maps: {mE1} & {mE2}")
        map_force_fuse(st, mE1, st.exit_node(mE1), mE2, st.exit_node(mE2))

        g.validate()
