import dace
import copy
from copy import deepcopy
from typing import Any
from dace import SDFG, symbolic
from dace.memlet import Memlet
from dace.sdfg.state import SDFGState
from dace.sdfg.nodes import Map, MapEntry, MapExit, AccessNode, Node, Tasklet
from dace.frontend.fortran.ast_utils import singular, atmost_one
from dace.transformation.helpers import redirect_edge
from dace.sdfg.state import CodeBlock, ConditionalBlock, ControlFlowRegion

def flip_connector(c: str) -> str:
    if c.startswith("IN_"):
        return f"OUT_{c.removeprefix('IN_')}"
    elif c.startswith("OUT_"):
        return f"IN_{c.removeprefix('OUT_')}"
    return c

def connect_ishift_to_map(sdfg: dace.SDFG, state_label:str):
    state, parent_graph = None, None
    for n, g in sdfg.all_nodes_recursive():
        if isinstance(n, dace.SDFGState) and n.label == state_label:
            state = n
            parent_graph = g
            break

    if state is None or parent_graph is None:
        raise ValueError(f"State with label '{state_label}' not found in the SDFG.")

    ishift_access = [n for n in state.nodes() if isinstance(n, dace.nodes.AccessNode) and n.data == "ishift_local"][0]
    map_entry = [n for n in state.nodes() if isinstance(n, dace.nodes.MapEntry)][0]
    assert len([n for n in state.nodes() if isinstance(n, dace.nodes.MapEntry)]) == 1, "Expected exactly one MapEntry node in the state."

    ishift_desc = state.sdfg.arrays["ishift_local"]
    assert len(set([e.dst for e in state.out_edges(map_entry)])) == 1, "Expected exactly one output edge from the MapEntry node."
    nsdfg_node: dace.nodes.NestedSDFG = [e.dst for e in state.out_edges(map_entry)][0]

    state.add_edge(ishift_access, None, map_entry, "IN_ishift_local", dace.Memlet.from_array("ishift_local", ishift_desc))
    state.add_edge(map_entry, "OUT_ishift_local", nsdfg_node, "ishift_local", dace.Memlet.from_array("ishift_local", ishift_desc))
    map_entry.add_in_connector("IN_ishift_local")
    map_entry.add_out_connector("OUT_ishift_local")
    nsdfg_node.add_in_connector("ishift_local")

    inner_sdfg: dace.SDFG = nsdfg_node.sdfg
    if "ishift_local" in inner_sdfg.arrays:
        assert "ishift_local" not in inner_sdfg.symbols
        assert inner_sdfg.arrays["ishift_local"].transient, "Expected 'ishift_local' to be transient in the inner SDFG."
    if "ishift_local" in inner_sdfg.symbols:
        assert "ishift_local" not in inner_sdfg.arrays
    if "ishift_local" in inner_sdfg.symbols:
        inner_sdfg.remove_symbol("ishift_local")
        copydesc = copy.deepcopy(ishift_desc)
        copydesc.transient = False
        inner_sdfg.add_datadesc(
            "ishift_local",
            copydesc,
        )
    elif "ishift_local" in inner_sdfg.arrays:
        inner_sdfg.arrays["ishift_local"].transient = False
    else:
        raise ValueError("Expected 'ishift_local' to be either in arrays or symbols of the inner SDFG.")

def move_range_if_inside(sdfg: dace.SDFG, it_name: str):
    # =======
    # Collect all necessary nodes and do checks that we are in the right place
    map_entry = None
    map_state = None
    for n, g in sdfg.all_nodes_recursive():
        if (isinstance(n, dace.nodes.MapEntry) and len(n.map.params) == 1 and
            n.map.params[0] == it_name):
            map_entry = n
            map_state = g
            break

    assert map_entry is not None, f"MapEntry with parameter '{it_name}' not found in the SDFG."

    dst_nodes = {e.dst for e in map_state.out_edges(map_entry)}
    assert len(dst_nodes) == 1, "Expected exactly one output edge from the MapEntry node."
    nsdfg_node = next(iter(dst_nodes))

    inner_sdfg = nsdfg_node.sdfg
    assert len(inner_sdfg.nodes()) == 3 or len(inner_sdfg.nodes()) == 2

    empty_state, if_block, kernel_state = inner_sdfg.bfs_nodes(inner_sdfg.start_block)
    edge_from_empty_to_if = next(iter(inner_sdfg.out_edges(empty_state)))

    assert len(empty_state.nodes()) == 0, "Expected the first state to be empty."

    inner_kernel_map_entries = [n for n in kernel_state.nodes() if isinstance(n, dace.nodes.MapEntry)]
    assert len(inner_kernel_map_entries) == 1, "Expected exactly one MapEntry in the kernel state."
    inner_kernel_map_entry = inner_kernel_map_entries[0]
    inner_kernel_nsdfg = next(iter({e.dst for e in kernel_state.out_edges(inner_kernel_map_entry)}))
    inner_kernel_body_sdfg = inner_kernel_nsdfg.sdfg
    # =======

    # Need to add max_map_range = max(npromz_gradp, nproma_gradp) to the state before
    # Add npromz_gradp and nproma_gradp to map entry as dyn connectors
    map_state.sdfg.add_symbol("max_map_range", dace.int32)
    max_range_assign_state = map_state.parent_graph.add_state_before(
        map_state, "max_range_assign_state",
        assignments={
            "max_map_range": "max(npromz_gradp_transified, nproma_gradp_transified)"
        }
    )
    # Add the symbol to both SDFGs
    # Inner kernels hould not need this as a symbol
    #inner_kernel_nsdfg.symbol_mapping["max_map_range"] = "max_map_range"
    inner_sdfg.parent_nsdfg_node.symbol_mapping["max_map_range"] = "max_map_range"
    # inner kernel needs it for the if check
    inner_kernel_nsdfg.symbol_mapping["_for_it_101"] = "_for_it_101"
    # Copy over symbols from the parent
    inner_kernel_body_sdfg.add_symbol("_for_it_101",  inner_sdfg.symbols["_for_it_101"] )
    #inner_sdfg.symbol_mapping["max_map_range"] = "max_map_range"


    # Update map range of the inner kernel
    new_range_list = []
    for b,e,s in inner_kernel_map_entry.map.range:
        b_str = str(b).replace("nlen_gradp_local", "max_map_range")
        e_str = str(e).replace("nlen_gradp_local", "max_map_range")
        s_str = str(s).replace("nlen_gradp_local", "max_map_range")

        new_range_list.append((dace.symbolic.SymExpr(b_str),
                               dace.symbolic.SymExpr(e_str),
                               dace.symbolic.SymExpr(s_str)))
    inner_kernel_map_entry.map.range = dace.subsets.Range(new_range_list)

    # Remove nlengradp_local from the map
    edge_to_rm = []
    node_to_rm = []
    for ie in kernel_state.in_edges(inner_kernel_map_entry):
        if ie.data.data == "nlengradp_local":
            edge_to_rm.append(ie)
            inner_kernel_map_entry.remove_in_connector(ie.dst_conn)
            node_to_rm.append(ie.src)
    for oe in kernel_state.out_edges(inner_kernel_map_entry):
        if oe.data.data == "nlengradp_local":
            edge_to_rm.append(oe)
            inner_kernel_map_entry.remove_out_connector(oe.src_conn)
            oe.dst.remove_in_connector(oe.dst_conn)
    for e in edge_to_rm:
        kernel_state.remove_edge(e)
    for n in node_to_rm:
        if kernel_state.degree(n) == 0:
            kernel_state.remove_node(n)

    # Add the npromz_gradp, nproma_gradp to the map entry
    for arr_name in ["npromz_gradp_transified", "nproma_gradp_transified", "nblks_gradp_transified"]:
        if arr_name not in inner_kernel_body_sdfg.arrays:
            copydesc =  copy.deepcopy(map_state.sdfg.arrays[arr_name])
            copydesc.transient = False
            inner_kernel_body_sdfg.add_datadesc(
                arr_name,
                copydesc,
            )
        inner_kernel_map_entry.add_in_connector("IN_" + arr_name)
        inner_kernel_map_entry.add_out_connector("OUT_" + arr_name)
        an = kernel_state.add_access(arr_name)
        kernel_state.add_edge(
            an, None, inner_kernel_map_entry, f"IN_{arr_name}",
            dace.Memlet.from_array(arr_name, inner_sdfg.arrays[arr_name])
        )
        kernel_state.add_edge(
            inner_kernel_map_entry, f"OUT_{arr_name}", inner_kernel_nsdfg, arr_name,
            dace.Memlet.from_array(arr_name, inner_sdfg.arrays[arr_name])
        )
        inner_kernel_nsdfg.add_in_connector(arr_name)

    # Rm nlen_gradp_local from the inner kernel map entry (dynamic connector)
    for ie in kernel_state.in_edges(inner_kernel_map_entry):
        if ie.data.data == "nlen_gradp_local":
            kernel_state.remove_edge(ie)
            inner_kernel_map_entry.remove_in_connector(ie.dst_conn)
            ie.src.remove_out_connector(ie.src_conn)
            kernel_state.remove_node(ie.src)

    # Now put the states in the nsdfg inside an if block

    inner_kernel_bfs_nodes = inner_kernel_body_sdfg.bfs_nodes(inner_kernel_body_sdfg.start_block)
    if_check = ConditionalBlock(
        label="range_check",
        sdfg=inner_kernel_body_sdfg,
        parent=inner_kernel_body_sdfg
    )
    if_cfg = ControlFlowRegion(
        label="range_check_body",
        sdfg=inner_kernel_body_sdfg,
        parent=if_check
    )
    nlen_gradp_local = copy.deepcopy(kernel_state.sdfg.arrays["nlen_gradp_local"])
    nlen_gradp_local.transient = True
    inner_kernel_body_sdfg.add_datadesc(
        "nlen_gradp_local",
        nlen_gradp_local,
    )
    if_check.add_branch(
        condition=CodeBlock(code="_for_it_102 < nlen_gradp_local"),
        branch=if_cfg
    )

    # Copy nodes to inside of the IF
    assert len(inner_kernel_bfs_nodes) == 2, "Expected exactly 2 nodes in the inner kernel body SDFG."
    node_map = {n: copy.deepcopy(n) for n in inner_kernel_bfs_nodes}
    for n in inner_kernel_bfs_nodes:
        if_cfg.add_node(node_map[n])
    for e in inner_kernel_body_sdfg.edges():
        if_cfg.add_edge(
            node_map[e.src],
            node_map[e.dst],
            copy.deepcopy(e.data)
        )

    for n in inner_kernel_bfs_nodes:
        inner_kernel_body_sdfg.remove_node(n)

    # Now mode the assignment inside
    empty_state_cp = copy.deepcopy(empty_state)
    if_block_cp = copy.deepcopy(if_block)
    inner_kernel_body_sdfg.add_node(
        empty_state_cp,
        is_start_block=True
    )
    inner_kernel_body_sdfg.add_node(
        if_block_cp
    )
    inner_kernel_body_sdfg.add_edge(
        empty_state_cp,
        if_block_cp,
        copy.deepcopy(edge_from_empty_to_if.data)
    )
    inner_kernel_body_sdfg.add_edge(
        if_block_cp,
        if_check,
        dace.InterstateEdge()
    )

    # Remove if and stuff previous
    kernel_state.parent_graph.remove_node(if_block)
    kernel_state.parent_graph.remove_node(empty_state)

    # ===================
    # Let's move the ishift local too
    # Pattern is AN -> Tasklet -> AN (ishift_local), it goes into the nested
    ishift_access = None
    ishift_access_prev = None
    for node in kernel_state.nodes():
        if isinstance(node, dace.nodes.AccessNode) and node.data == "ishift_local":
            ishift_access_prev = node
            ishift_access = copy.deepcopy(node)
            break
    assert ishift_access is not None, "Expected ishift_local to be an AccessNode in the kernel state."

    ishift_tasklet_prev = next(iter({e.src for e in kernel_state.in_edges(ishift_access_prev)}))
    ishift_tasklet = copy.deepcopy(ishift_tasklet_prev)
    tasklet_ishift_edge = next(iter(kernel_state.in_edges(ishift_access_prev)))
    ishift_src_an_prev = next(iter({e.src for e in kernel_state.in_edges(ishift_tasklet_prev)}))
    ishift_src_an = copy.deepcopy(ishift_src_an_prev)
    src_tasklet_edge = next(iter(kernel_state.in_edges(ishift_tasklet_prev)))

    first_state_inside = inner_kernel_body_sdfg.start_block
    assert isinstance(first_state_inside, dace.SDFGState), "Expected the first state inside the inner kernel body SDFG to be a state."

    first_state_inside.add_node(ishift_access)
    first_state_inside.add_node(ishift_tasklet)
    first_state_inside.add_node(ishift_src_an)
    first_state_inside.add_edge(
        ishift_src_an, None, ishift_tasklet, src_tasklet_edge.dst_conn,
        copy.deepcopy(src_tasklet_edge.data)
    )
    first_state_inside.add_edge(
        ishift_tasklet, tasklet_ishift_edge.src_conn, ishift_access, None,
        copy.deepcopy(tasklet_ishift_edge.data)
    )
    # Now ensure ishift_local is transient
    inner_kernel_body_sdfg.arrays["ishift_local"].transient = True

    # Rm connection
    kernel_state.remove_node(ishift_access_prev)
    kernel_state.remove_node(ishift_tasklet_prev)
    kernel_state.remove_node(ishift_src_an_prev)

    inner_kernel_map_entry.remove_in_connector("IN_ishift_local")
    inner_kernel_map_entry.remove_out_connector("OUT_ishift_local")
    for ie in kernel_state.in_edges(inner_kernel_map_entry):
        if ie.data.data == "ishift_local":
            kernel_state.remove_edge(ie)
            inner_kernel_map_entry.remove_in_connector(ie.dst_conn)
            ie.src.remove_out_connector(ie.src_conn)
    for oe in kernel_state.out_edges(inner_kernel_map_entry):
        if oe.data.data == "ishift_local":
            kernel_state.remove_edge(oe)
            inner_kernel_map_entry.remove_out_connector(oe.src_conn)
            oe.dst.remove_in_connector(oe.dst_conn)
    inner_kernel_nsdfg.remove_in_connector("ishift_local")

    #==================
    sdfg.validate()


def mapentry_copy_mapentry_cleanup(g: SDFG):
    for mE1, st in g.all_nodes_recursive():
        if not isinstance(mE1, MapEntry):
            continue
        cts = [ed.dst for ed in st.out_edges(mE1)
               if isinstance(ed.dst, Tasklet)
               and len(ed.dst.in_connectors) == 1
               and len(ed.dst.out_connectors) == 1
               and st.out_degree(ed.dst) == 1]
        cts = [t for t in cts
               if t.code.as_string.strip() == f"{singular(k for k in t.out_connectors.keys())} = {singular(k for k in t.in_connectors.keys())}"]
        for ct in cts:
            acc = singular(ed.dst for ed in st.out_edges(ct))
            if not isinstance(acc, AccessNode) or not acc.desc(g).transient:
                continue
            if st.out_degree(acc) != 1:
                continue
            mE2_ed = singular(ed for ed in st.out_edges(acc))
            mE2 = mE2_ed.dst
            if not isinstance(mE2, MapEntry):
                continue
            ct_ed = singular(ed for ed in st.in_edges(ct))
            mE2_ed_fwd = singular(e for e in st.out_edges_by_connector(mE2, flip_connector(mE2_ed.dst_conn)))
            print(f"Clearing the path: {mE1} => {ct} => {acc} => {mE2} => ?? :: {mE1} => {mE2} => {ct} => {acc} => ??")
            st.add_edge(mE1, ct_ed.src_conn, mE2, mE2_ed.dst_conn, Memlet.from_memlet(ct_ed.data))
            st.add_edge(mE2, flip_connector(mE2_ed.dst_conn), ct, ct_ed.dst_conn, Memlet.from_memlet(ct_ed.data))
            st.add_edge(acc, None, mE2_ed_fwd.dst, mE2_ed_fwd.dst_conn, Memlet.from_memlet(mE2_ed_fwd.data))
            st.remove_edge(ct_ed)
            st.remove_edge(mE2_ed)
            st.remove_edge(mE2_ed_fwd)
    g.validate()
