import dace
from typing import Set

openacc_data_names = """
   !$ACC DATA CREATE(z_kin_hor_e, z_vt_ie, z_w_concorr_me, z_theta_v_fl_e) &
    !$ACC   CREATE(z_dexner_dz_c, z_exner_ex_pr, z_gradh_exner, z_rth_pr, z_grad_rth) &
    !$ACC   CREATE(z_theta_v_pr_ic, z_th_ddz_exner_c, z_w_concorr_mc) &
    !$ACC   CREATE(z_vn_avg, z_rho_e, z_theta_v_e, z_dwdz_dd, z_mflx_top) &
    !$ACC   CREATE(z_exner_ic, z_alpha, z_beta, z_q, z_contr_w_fl_l, z_exner_expl) &
    !$ACC   CREATE(z_flxdiv_mass, z_flxdiv_theta, z_rho_expl, z_w_expl) &
    !$ACC   CREATE(z_rho_v, z_theta_v_v, z_graddiv_vn, z_hydro_corr, z_graddiv2_vn) &
    !$ACC   COPYIN(nflatlev, nflat_gradp, kstart_dd3d, kstart_moist, nrdmax) &
    !$ACC   COPYIN(z_raylfac, ndyn_substeps_var, scal_divdamp, bdy_divdamp) &
    !$ACC   PRESENT(prep_adv, p_int, p_patch, p_nh) &
    !$ACC   PRESENT(icidx, icblk, ividx, ivblk, ieidx, ieblk, ikidx, iqidx, iqblk) &
    !$ACC   PRESENT(ipeidx, ipeblk, iplev)
"""

ptr_assignments = """
    ! Set pointers to neighbor cells
    icidx => p_patch%edges%cell_idx
    icblk => p_patch%edges%cell_blk

    ! Set pointers to neighbor edges
    ieidx => p_patch%cells%edge_idx
    ieblk => p_patch%cells%edge_blk

    ! Set pointers to vertices of an edge
    ividx => p_patch%edges%vertex_idx
    ivblk => p_patch%edges%vertex_blk

    ! Set pointer to vertical neighbor indices for pressure gradient
    ikidx => p_nh%metrics%vertidx_gradp

    ! Set pointers to quad edges
    iqidx => p_patch%edges%quad_idx
    iqblk => p_patch%edges%quad_blk

    ! DA: moved from below to here to get into the same ACC data section
    iplev  => p_nh%metrics%pg_vertidx
    ipeidx => p_nh%metrics%pg_edgeidx
    ipeblk => p_nh%metrics%pg_edgeblk
"""

data_names_gpu = """
   z_kin_hor_e, z_vt_ie, z_w_concorr_me, z_theta_v_fl_e,
   z_dexner_dz_c, z_exner_ex_pr, z_gradh_exner, z_rth_pr, z_grad_rth,
   z_theta_v_pr_ic, z_th_ddz_exner_c, z_w_concorr_mc,
    z_vn_avg, z_rho_e, z_theta_v_e, z_dwdz_dd, z_mflx_top,
    z_exner_ic, z_alpha, z_beta, z_q, z_contr_w_fl_l, z_exner_expl,
    z_flxdiv_mass, z_flxdiv_theta, z_rho_expl, z_w_expl,
    z_rho_v, z_theta_v_v, z_graddiv_vn, z_hydro_corr, z_graddiv2_vn,
"""

data_names_both = """
    nflatlev, nflat_gradp, kstart_dd3d, kstart_moist, nrdmax,
    z_raylfac, ndyn_substeps_var, scal_divdamp, bdy_divdamp,
"""

def gpu_offloading_wo_host_dev_copiesl():
    names_gpu = set(data_names_gpu.replace("\n", "").strip().split(", "))
    names_both = set(data_names_both.replace("\n", "").strip().split(", "))
    parent_map_count = 0

    _gpu_offloading_wo_host_dev_copies_impl(
        gpu_only_arrays=names_gpu,
        duplicated_arrays=names_both,
        parent_map_count=parent_map_count
    )

def _check_arrays_are_constant(sdfg: dace.SDFG, array_names: Set[str]):
    writes_to_access_nodes = dict()
    for graph in sdfg.all_states():
        for node in graph.nodes():
            if isinstance(node, dace.nodes.AccessNode):
                if (
                    graph.in_degree(node) > 0 and
                    any([ie.data is not None for ie in graph.in_edges(node)])
                ):
                    if node.data not in writes_to_access_nodes:
                        writes_to_access_nodes[node.data] = 0
                    writes_to_access_nodes[node.data] += 1
    for array_name in array_names:
        assert writes_to_access_nodes.get(array_name, 0) <= 1

def _gpu_offloading_wo_host_dev_copies_impl(sdfg: dace.SDFG,
                                            gpu_only_arrays: Set[str],
                                            duplicated_arrays: Set[str],
                                            parent_map_count: int):
    """
    Offloads data to GPU, depending on transient / non-transient data it is copied over to GPU in the beginning
    or allocated directly on the GPU. Offloads only maps with N-parent maps and does not copy data back to host.
    """
    _check_arrays_are_constant(sdfg, duplicated_arrays)


    pass