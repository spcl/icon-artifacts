from itertools import chain
import re

from dace import SDFG
from dace.sdfg.nodes import MapEntry, NestedSDFG, Tasklet
from dace.sdfg.state import SDFGState
from dace.sdfg.graph import MultiConnectorEdge
from dace.frontend.fortran.ast_utils import singular, atmost_one
from dace.properties import CodeBlock
from dace import dtypes


def drop_numerical_suffix_from_connectors(
    st: SDFGState, ng: NestedSDFG | Tasklet
) -> None:
    var_pattern = re.compile(r"_var_\d+$")

    conn_remap = {}
    for c in chain(ng.in_connectors, ng.out_connectors):
        if var_pattern.search(c):
            conn_remap[c] = var_pattern.sub("", c)

    for e in st.in_edges(ng):
        if e.dst_conn in conn_remap:
            e.dst_conn = conn_remap[e.dst_conn]
    for c, nc in conn_remap.items():
        if c in ng.in_connectors:
            ng.remove_in_connector(c)
            ng.add_in_connector(conn_remap[c])

    for e in st.out_edges(ng):
        if e.src_conn in conn_remap:
            e.src_conn = conn_remap[e.src_conn]
    for c, nc in conn_remap.items():
        if c in ng.out_connectors:
            ng.remove_out_connector(c)
            ng.add_out_connector(conn_remap[c])


def replace_nested_sdfg_with_empty_tasklet(st: SDFGState, ng: NestedSDFG) -> Tasklet:
    """
    Replace the nested SDFG with an empty tasklet, keeping the connectors.
    """
    tasklet = st.add_tasklet(f"{ng.label}", {}, {}, "pass", location=ng.location)
    for c in ng.in_connectors.keys():
        tasklet.add_in_connector(f"in_{c}")
    for c in ng.out_connectors.keys():
        tasklet.add_out_connector(f"out_{c}")
    for e in st.in_edges(ng):
        st.add_edge(e.src, e.src_conn, tasklet, f"in_{e.dst_conn}", e.data)
    for e in st.out_edges(ng):
        st.add_edge(tasklet, f"out_{e.src_conn}", e.dst, e.dst_conn, e.data)
    st.remove_node(ng)
    drop_numerical_suffix_from_connectors(st, tasklet)
    return tasklet


def inject_velocity_shim(g: SDFG) -> None:
    vtst = atmost_one(
        st
        for st, _ in g.all_nodes_recursive()
        if isinstance(st, SDFGState) and "velocity_tendencies" in st.label
    )
    if not vtst:
        return
    vtng = singular(
        ng
        for ng in vtst.nodes()
        if isinstance(ng, NestedSDFG) and "velocity_tendencies" in ng.label
    )
    t: Tasklet = replace_nested_sdfg_with_empty_tasklet(vtst, vtng)
    if "in_lvn_only" in t.in_connectors:
        in_lvn_only = f"in_lvn_only"
    else:
        in_lvn_only = f"0"
    if "predictor" in g.name:
        in_istep = f"1"
    else:
        in_istep = f"2"

    t.code = CodeBlock(
        f"""
velocity_tendencies(in_global_data, in_p_diag, in_p_int, in_p_metrics, in_p_patch, in_p_prog, in_z_kin_hor_e, in_z_vt_ie, in_z_w_concorr_me,
  tmp_struct_symbol_24 /* = __f2dace_A_z_kin_hor_e_d_0_s*/,
  tmp_struct_symbol_25 /* = __f2dace_A_z_kin_hor_e_d_1_s*/,
  tmp_struct_symbol_21 /* = __f2dace_A_z_vt_ie_d_0_s*/,
  tmp_struct_symbol_22 /* = __f2dace_A_z_vt_ie_d_1_s*/,
  tmp_struct_symbol_39 /* = __f2dace_A_z_w_concorr_me_d_0_s*/,
  tmp_struct_symbol_40 /* = __f2dace_A_z_w_concorr_me_d_1_s*/,
  1 /* = __f2dace_OA_z_kin_hor_e_d_0_s*/,
  1 /* = __f2dace_OA_z_kin_hor_e_d_1_s*/,
  1 /* = __f2dace_OA_z_kin_hor_e_d_2_s*/,
  1 /* = __f2dace_OA_z_vt_ie_d_0_s*/,
  1 /* = __f2dace_OA_z_vt_ie_d_1_s*/,
  1 /* = __f2dace_OA_z_vt_ie_d_2_s*/,
  1 /* = __f2dace_OA_z_w_concorr_me_d_0_s*/,
  1 /* = __f2dace_OA_z_w_concorr_me_d_1_s*/,
  1 /* = __f2dace_OA_z_w_concorr_me_d_2_s*/,
  in_dt_linintp_ubc, in_dtime,
  {in_istep} /* = in_istep*/,
  in_ldeepatmo,
  {in_lvn_only} /* = in_lvn_only*/,
  in_ntnd);
out_global_data = in_global_data;
out_p_diag = in_p_diag;
out_p_int = in_p_int;
out_p_patch = in_p_patch;
out_p_prog = in_p_prog;
""".strip(),
        language=dtypes.Language.CPP,
    )


#     t.code = CodeBlock(
#         f"""
# velocity_tendencies(
#   in_global_data, in_p_diag, in_p_int, in_p_metrics, in_p_patch, in_p_prog,
#   in_z_kin_hor_e, in_z_vt_ie, in_z_w_concorr_me,
#   tmp_struct_symbol_24,  # __f2dace_A_z_kin_hor_e_d_0_s
#   tmp_struct_symbol_25,  # __f2dace_A_z_kin_hor_e_d_1_s
#   tmp_struct_symbol_21,  # __f2dace_A_z_vt_ie_d_0_s
#   tmp_struct_symbol_22,  # __f2dace_A_z_vt_ie_d_1_s
#   tmp_struct_symbol_39,  # __f2dace_A_z_w_concorr_me_d_0_s
#   tmp_struct_symbol_40,  # __f2dace_A_z_w_concorr_me_d_1_s
#   0,  # __f2dace_OA_z_kin_hor_e_d_0_s
#   0,  # __f2dace_OA_z_kin_hor_e_d_1_s
#   0,  # __f2dace_OA_z_kin_hor_e_d_2_s
#   0,  # __f2dace_OA_z_vt_ie_d_0_s
#   0,  # __f2dace_OA_z_vt_ie_d_1_s
#   0,  # __f2dace_OA_z_vt_ie_d_2_s
#   0,  # __f2dace_OA_z_w_concorr_me_d_0_s
#   0,  # __f2dace_OA_z_w_concorr_me_d_1_s
#   0,  # __f2dace_OA_z_w_concorr_me_d_2_s
#   in_dt_linintp_ubc, in_dtime,
#   {in_istep},  # in_istep
#   in_ldeepatmo,
#   {in_lvn_only},  # in_lvn_only
#   in_ntnd
# )
# out_global_data = in_global_data
# out_p_diag = in_p_diag
# out_p_int = in_p_int
# out_p_patch = in_p_patch
# out_p_prog = in_p_prog
#   """.strip(),
#         language=dtypes.Language.Python,
#     )
