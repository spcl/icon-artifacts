# named_empty: all arrays level-first, connectivity N-first with [2,0,1]
PERMUTE_CONFIGS["nlev_first"] = _make_config({
    # Work arrays [1,0,2]: (nlev, nproma, nblks)
    "gpu_z_ekinh":                                  [1, 0, 2],
    "gpu_z_kin_hor_e":                              [1, 0, 2],
    "gpu_z_v_grad_w":                               [1, 0, 2],
    "gpu_z_w_v":                                    [1, 0, 2],
    "gpu_zeta":                                     [1, 0, 2],
    "gpu_z_vt_ie":                                  [1, 0, 2],
    "gpu_z_w_concorr_me":                           [1, 0, 2],
    "gpu_z_w_concorr_mc":                           [1, 0],
    "gpu_z_w_con_c_full":                           [1, 0, 2],
    "gpu_z_w_con_c":                                [1, 0],
    "gpu_maxvcfl_arr":                              [1, 0, 2],
    "gpu_cfl_clipping":                             [1, 0],
    "gpu_levmask":                                  [1, 0],
    # Prognostic / diagnostic [1,0,2]
    "gpu___CG_p_prog__m_vn":                        [1, 0, 2],
    "gpu___CG_p_prog__m_w":                         [1, 0, 2],
    "gpu___CG_p_diag__m_vt":                        [1, 0, 2],
    "gpu___CG_p_diag__m_vn_ie":                     [1, 0, 2],
    "gpu___CG_p_diag__m_vn_ie_ubc":                 [1, 0, 2],
    "gpu___CG_p_diag__m_w_concorr_c":               [1, 0, 2],
    "gpu___CG_p_diag__m_ddt_vn_apc_pc":             [1, 0, 2, 3],
    "gpu___CG_p_diag__m_ddt_w_adv_pc":              [1, 0, 2, 3],
    "gpu___CG_p_diag__m_ddt_vn_cor_pc":             [1, 0, 2, 3],
    # Metrics [1,0,2]
    "gpu___CG_p_metrics__m_wgtfac_e":               [1, 0, 2],
    "gpu___CG_p_metrics__m_wgtfacq_e":              [1, 0, 2],
    "gpu___CG_p_metrics__m_wgtfac_c":               [1, 0, 2],
    "gpu___CG_p_metrics__m_ddxn_z_full":            [1, 0, 2],
    "gpu___CG_p_metrics__m_ddxt_z_full":            [1, 0, 2],
    "gpu___CG_p_metrics__m_ddqz_z_half":            [1, 0, 2],
    "gpu___CG_p_metrics__m_ddqz_z_full_e":          [1, 0, 2],
    "gpu___CG_p_metrics__m_coeff1_dwdz":            [1, 0, 2],
    "gpu___CG_p_metrics__m_coeff2_dwdz":            [1, 0, 2],
    "gpu___CG_p_metrics__m_coeff_gradekin":         [1, 0, 2],
    # Interp: (nproma, N, nblks) → [1,0,2] → (N, nproma, nblks)
    "gpu___CG_p_int__m_e_bln_c_s":                  [1, 0, 2],
    "gpu___CG_p_int__m_c_lin_e":                    [1, 0, 2],
    "gpu___CG_p_int__m_geofac_n2s":                 [1, 0, 2],
    "gpu___CG_p_int__m_geofac_grdiv":               [1, 0, 2],
    "gpu___CG_p_int__m_cells_aw_verts":             [1, 0, 2],
    "gpu___CG_p_int__m_geofac_rot":                 [1, 0, 2],
    # Connectivity: (nproma, nblks, N) → [2,0,1] → (N, nproma, nblks)
    # [2,1,0] was WRONG: gives (N, nblks, nproma), stride for jc = N*nblks
    "gpu___CG_p_patch__CG_verts__m_cell_blk":       [2, 0, 1],
    "gpu___CG_p_patch__CG_edges__m_cell_idx":       [2, 0, 1],
    "gpu___CG_p_patch__CG_edges__m_cell_blk":       [2, 0, 1],
    "gpu___CG_p_patch__CG_cells__m_edge_idx":       [2, 0, 1],
    "gpu___CG_p_patch__CG_cells__m_edge_blk":       [2, 0, 1],
    "gpu___CG_p_patch__CG_edges__m_vertex_idx":     [2, 0, 1],
    "gpu___CG_p_patch__CG_edges__m_vertex_blk":     [2, 0, 1],
    "gpu___CG_p_patch__CG_edges__m_quad_idx":       [2, 0, 1],
    "gpu___CG_p_patch__CG_edges__m_quad_blk":       [2, 0, 1],
    "gpu___CG_p_patch__CG_cells__m_neighbor_idx":   [2, 0, 1],
    "gpu___CG_p_patch__CG_cells__m_neighbor_blk":   [2, 0, 1],
})

# index_only: only connectivity + interp get N-first, everything else identity
PERMUTE_CONFIGS["index_only"] = _make_config({
    # Work/prog/diag: no neighbor dim, identity = no change needed
    # Metrics: (nproma, nlev, nblks) — no neighbor dim, identity
    # Interp: (nproma, N, nblks) → [1,0,2] → (N, nproma, nblks)
    # [0,1,2] was WRONG: identity leaves nproma first, N not first
    "gpu___CG_p_int__m_e_bln_c_s":                  [1, 0, 2],
    "gpu___CG_p_int__m_c_lin_e":                    [1, 0, 2],
    "gpu___CG_p_int__m_geofac_n2s":                 [1, 0, 2],
    "gpu___CG_p_int__m_geofac_grdiv":               [1, 0, 2],
    "gpu___CG_p_int__m_cells_aw_verts":             [1, 0, 2],
    "gpu___CG_p_int__m_geofac_rot":                 [1, 0, 2],
    # Connectivity: (nproma, nblks, N) → [2,0,1] → (N, nproma, nblks) ✓
    "gpu___CG_p_patch__CG_verts__m_cell_blk":       [2, 0, 1],
    "gpu___CG_p_patch__CG_edges__m_cell_idx":       [2, 0, 1],
    "gpu___CG_p_patch__CG_edges__m_cell_blk":       [2, 0, 1],
    "gpu___CG_p_patch__CG_cells__m_edge_idx":       [2, 0, 1],
    "gpu___CG_p_patch__CG_cells__m_edge_blk":       [2, 0, 1],
    "gpu___CG_p_patch__CG_edges__m_vertex_idx":     [2, 0, 1],
    "gpu___CG_p_patch__CG_edges__m_vertex_blk":     [2, 0, 1],
    "gpu___CG_p_patch__CG_edges__m_quad_idx":       [2, 0, 1],
    "gpu___CG_p_patch__CG_edges__m_quad_blk":       [2, 0, 1],
    "gpu___CG_p_patch__CG_cells__m_neighbor_idx":   [2, 0, 1],
    "gpu___CG_p_patch__CG_cells__m_neighbor_blk":   [2, 0, 1],
})