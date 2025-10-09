MODULE mo_decomposition_tools
  IMPLICIT NONE
  TYPE :: t_grid_domain_decomp_info
    LOGICAL, ALLOCATABLE :: owner_mask(:, :)
  END TYPE
  CONTAINS
END MODULE mo_decomposition_tools
MODULE mo_init_vgrid
  IMPLICIT NONE
  INTEGER :: nflatlev(10)
  CONTAINS
END MODULE mo_init_vgrid
MODULE mo_intp_data_strc
  IMPLICIT NONE
  TYPE :: t_int_state
    REAL(KIND = 8), ALLOCATABLE :: c_lin_e(:, :, :)
    REAL(KIND = 8), ALLOCATABLE :: e_bln_c_s(:, :, :)
    REAL(KIND = 8), ALLOCATABLE :: cells_aw_verts(:, :, :)
    REAL(KIND = 8), ALLOCATABLE :: rbf_vec_coeff_e(:, :, :)
    REAL(KIND = 8), ALLOCATABLE :: geofac_grdiv(:, :, :)
    REAL(KIND = 8), ALLOCATABLE :: geofac_rot(:, :, :)
    REAL(KIND = 8), ALLOCATABLE :: geofac_n2s(:, :, :)
  END TYPE t_int_state
  CONTAINS
END MODULE mo_intp_data_strc
MODULE mo_model_domain
  USE mo_decomposition_tools, ONLY: t_grid_domain_decomp_info
  IMPLICIT NONE
  TYPE :: t_grid_cells
    INTEGER, ALLOCATABLE :: neighbor_idx(:, :, :)
    INTEGER, ALLOCATABLE :: neighbor_blk(:, :, :)
    INTEGER, ALLOCATABLE :: edge_idx(:, :, :)
    INTEGER, ALLOCATABLE :: edge_blk(:, :, :)
    REAL(KIND = 8), POINTER :: area(:, :)
    INTEGER, ALLOCATABLE :: start_index(:)
    INTEGER, ALLOCATABLE :: end_index(:)
    INTEGER, ALLOCATABLE :: start_block(:)
    INTEGER, ALLOCATABLE :: end_block(:)
    TYPE(t_grid_domain_decomp_info) :: decomp_info
  END TYPE t_grid_cells
  TYPE :: t_grid_edges
    INTEGER, ALLOCATABLE :: cell_idx(:, :, :)
    INTEGER, ALLOCATABLE :: cell_blk(:, :, :)
    INTEGER, ALLOCATABLE :: vertex_idx(:, :, :)
    INTEGER, ALLOCATABLE :: vertex_blk(:, :, :)
    REAL(KIND = 8), ALLOCATABLE :: tangent_orientation(:, :)
    INTEGER, ALLOCATABLE :: quad_idx(:, :, :)
    INTEGER, ALLOCATABLE :: quad_blk(:, :, :)
    REAL(KIND = 8), ALLOCATABLE :: inv_primal_edge_length(:, :)
    REAL(KIND = 8), ALLOCATABLE :: inv_dual_edge_length(:, :)
    REAL(KIND = 8), ALLOCATABLE :: area_edge(:, :)
    REAL(KIND = 8), ALLOCATABLE :: f_e(:, :)
    REAL(KIND = 8), ALLOCATABLE :: fn_e(:, :)
    REAL(KIND = 8), ALLOCATABLE :: ft_e(:, :)
    INTEGER, ALLOCATABLE :: start_index(:)
    INTEGER, ALLOCATABLE :: end_index(:)
    INTEGER, ALLOCATABLE :: start_block(:)
    INTEGER, ALLOCATABLE :: end_block(:)
  END TYPE t_grid_edges
  TYPE :: t_grid_vertices
    INTEGER, ALLOCATABLE :: cell_idx(:, :, :)
    INTEGER, ALLOCATABLE :: cell_blk(:, :, :)
    INTEGER, ALLOCATABLE :: edge_idx(:, :, :)
    INTEGER, ALLOCATABLE :: edge_blk(:, :, :)
    INTEGER, ALLOCATABLE :: start_index(:)
    INTEGER, ALLOCATABLE :: end_index(:)
    INTEGER, ALLOCATABLE :: start_blk(:, :)
    INTEGER, ALLOCATABLE :: start_block(:)
    INTEGER, ALLOCATABLE :: end_blk(:, :)
    INTEGER, ALLOCATABLE :: end_block(:)
  END TYPE t_grid_vertices
  TYPE :: t_patch
    INTEGER :: id
    INTEGER :: n_childdom
    INTEGER :: nblks_c
    INTEGER :: nblks_e
    INTEGER :: nblks_v
    INTEGER :: nlev
    INTEGER :: nlevp1
    INTEGER :: nshift
    TYPE(t_grid_cells) :: cells
    TYPE(t_grid_edges) :: edges
    TYPE(t_grid_vertices) :: verts
  END TYPE t_patch
  CONTAINS
END MODULE mo_model_domain
MODULE mo_nonhydro_types
  IMPLICIT NONE
  TYPE :: t_nh_prog
    REAL(KIND = 8), POINTER, CONTIGUOUS :: w(:, :, :), vn(:, :, :)
  END TYPE t_nh_prog
  TYPE :: t_nh_diag
    REAL(KIND = 8), POINTER, CONTIGUOUS :: vn_ie_ubc(:, :, :)
    REAL(KIND = 8), POINTER, CONTIGUOUS :: vt(:, :, :), vn_ie(:, :, :), w_concorr_c(:, :, :), ddt_vn_apc_pc(:, :, :, :), ddt_vn_cor_pc(:, :, :, :), ddt_w_adv_pc(:, :, :, :)
    LOGICAL :: ddt_vn_adv_is_associated = .FALSE., ddt_vn_cor_is_associated = .FALSE.
    REAL(KIND = 8) :: max_vcfl_dyn = 0.0D0
  END TYPE t_nh_diag
  TYPE :: t_nh_metrics
    REAL(KIND = 8), POINTER, CONTIGUOUS :: ddxn_z_full(:, :, :), ddxt_z_full(:, :, :), ddqz_z_full_e(:, :, :), ddqz_z_half(:, :, :), wgtfac_c(:, :, :), wgtfac_e(:, :, :), wgtfacq_e(:, :, :), coeff_gradekin(:, :, :), coeff1_dwdz(:, :, :), coeff2_dwdz(:, :, :)
    REAL(KIND = 8), POINTER, CONTIGUOUS :: deepatmo_gradh_mc(:), deepatmo_invr_mc(:), deepatmo_gradh_ifc(:), deepatmo_invr_ifc(:)
  END TYPE t_nh_metrics
  CONTAINS
END MODULE mo_nonhydro_types
MODULE mo_nonhydrostatic_config
  IMPLICIT NONE
  LOGICAL :: lextra_diffu
  CONTAINS
END MODULE mo_nonhydrostatic_config
MODULE mo_parallel_config
  IMPLICIT NONE
  INTEGER :: nproma = 1
  CONTAINS
END MODULE mo_parallel_config
MODULE mo_loopindices
  IMPLICIT NONE
  CONTAINS
  SUBROUTINE get_indices_c(p_patch_var_23, i_blk_var_24, i_startblk_var_25, i_endblk_var_26, i_startidx_var_29, i_endidx_var_30, irl_start_var_27, opt_rl_end_var_28)
    USE mo_model_domain, ONLY: t_patch
    USE mo_parallel_config, ONLY: nproma
    TYPE(t_patch), INTENT(IN) :: p_patch_var_23
    INTEGER, INTENT(IN) :: i_blk_var_24
    INTEGER, INTENT(IN) :: i_startblk_var_25
    INTEGER, INTENT(IN) :: i_endblk_var_26
    INTEGER, INTENT(IN) :: irl_start_var_27
    INTEGER, OPTIONAL, INTENT(IN) :: opt_rl_end_var_28
    INTEGER, INTENT(OUT) :: i_startidx_var_29, i_endidx_var_30
    INTEGER :: irl_end_var_31
    irl_end_var_31 = opt_rl_end_var_28
    IF (i_blk_var_24 == i_startblk_var_25) THEN
      i_startidx_var_29 = MAX(1, p_patch_var_23 % cells % start_index(irl_start_var_27))
      i_endidx_var_30 = nproma
      IF (i_blk_var_24 == i_endblk_var_26) i_endidx_var_30 = p_patch_var_23 % cells % end_index(irl_end_var_31)
    ELSE IF (i_blk_var_24 == i_endblk_var_26) THEN
      i_startidx_var_29 = 1
      i_endidx_var_30 = p_patch_var_23 % cells % end_index(irl_end_var_31)
    ELSE
      i_startidx_var_29 = 1
      i_endidx_var_30 = nproma
    END IF
  END SUBROUTINE get_indices_c
  SUBROUTINE get_indices_e(p_patch_var_32, i_blk_var_33, i_startblk_var_34, i_endblk_var_35, i_startidx_var_38, i_endidx_var_39, irl_start_var_36, opt_rl_end_var_37)
    USE mo_model_domain, ONLY: t_patch
    USE mo_parallel_config, ONLY: nproma
    TYPE(t_patch), INTENT(IN) :: p_patch_var_32
    INTEGER, INTENT(IN) :: i_blk_var_33
    INTEGER, INTENT(IN) :: i_startblk_var_34
    INTEGER, INTENT(IN) :: i_endblk_var_35
    INTEGER, INTENT(IN) :: irl_start_var_36
    INTEGER, OPTIONAL, INTENT(IN) :: opt_rl_end_var_37
    INTEGER, INTENT(OUT) :: i_startidx_var_38, i_endidx_var_39
    INTEGER :: irl_end_var_40
    irl_end_var_40 = opt_rl_end_var_37
    i_startidx_var_38 = MERGE(1, MAX(1, p_patch_var_32 % edges % start_index(irl_start_var_36)), i_blk_var_33 /= i_startblk_var_34)
    i_endidx_var_39 = MERGE(nproma, p_patch_var_32 % edges % end_index(irl_end_var_40), i_blk_var_33 /= i_endblk_var_35)
  END SUBROUTINE get_indices_e
  SUBROUTINE get_indices_v(p_patch_var_41, i_blk_var_42, i_startblk_var_43, i_endblk_var_44, i_startidx_var_47, i_endidx_var_48, irl_start_var_45, opt_rl_end_var_46)
    USE mo_model_domain, ONLY: t_patch
    USE mo_parallel_config, ONLY: nproma
    TYPE(t_patch), INTENT(IN) :: p_patch_var_41
    INTEGER, INTENT(IN) :: i_blk_var_42
    INTEGER, INTENT(IN) :: i_startblk_var_43
    INTEGER, INTENT(IN) :: i_endblk_var_44
    INTEGER, INTENT(IN) :: irl_start_var_45
    INTEGER, OPTIONAL, INTENT(IN) :: opt_rl_end_var_46
    INTEGER, INTENT(OUT) :: i_startidx_var_47, i_endidx_var_48
    INTEGER :: irl_end_var_49
    irl_end_var_49 = -5
    IF (i_blk_var_42 == i_startblk_var_43) THEN
      i_startidx_var_47 = p_patch_var_41 % verts % start_index(2)
      i_endidx_var_48 = nproma
      IF (i_blk_var_42 == i_endblk_var_44) i_endidx_var_48 = p_patch_var_41 % verts % end_index(-5)
    ELSE IF (i_blk_var_42 == i_endblk_var_44) THEN
      i_startidx_var_47 = 1
      i_endidx_var_48 = p_patch_var_41 % verts % end_index(-5)
    ELSE
      i_startidx_var_47 = 1
      i_endidx_var_48 = nproma
    END IF
  END SUBROUTINE get_indices_v
END MODULE mo_loopindices
MODULE mo_math_divrot
  IMPLICIT NONE
  CONTAINS
  SUBROUTINE rot_vertex_ri(vec_e, ptr_patch_var_50, ptr_int, rot_vec, opt_slev_var_51, opt_elev_var_52, opt_rlend_var_53, opt_acc_async_var_54)
    USE mo_model_domain, ONLY: t_patch
    USE mo_intp_data_strc, ONLY: t_int_state
    USE mo_loopindices, ONLY: get_indices_v
    TYPE(t_patch), TARGET, INTENT(IN) :: ptr_patch_var_50
    TYPE(t_int_state), INTENT(IN) :: ptr_int
    REAL(KIND = 8), INTENT(IN) :: vec_e(:, :, :)
    INTEGER, INTENT(IN), OPTIONAL :: opt_slev_var_51
    INTEGER, INTENT(IN), OPTIONAL :: opt_elev_var_52
    INTEGER, INTENT(IN), OPTIONAL :: opt_rlend_var_53
    LOGICAL, INTENT(IN), OPTIONAL :: opt_acc_async_var_54
    REAL(KIND = 8), INTENT(INOUT) :: rot_vec(:, :, :)
    INTEGER :: slev_var_55, elev_var_56
    INTEGER :: jv_var_57, jk_var_58, jb_var_59
    INTEGER :: rl_start_var_60, rl_end_var_61
    INTEGER :: i_startblk_var_62, i_endblk_var_63, i_startidx_var_64, i_endidx_var_65
    slev_var_55 = 1
    elev_var_56 = UBOUND(vec_e, 2)
    rl_start_var_60 = 2
    rl_end_var_61 = -5
    i_startblk_var_62 = ptr_patch_var_50 % verts % start_block(2)
    i_endblk_var_63 = ptr_patch_var_50 % verts % end_block(- 5)
    DO jb_var_59 = i_startblk_var_62, i_endblk_var_63
      CALL get_indices_v(ptr_patch_var_50, jb_var_59, i_startblk_var_62, i_endblk_var_63, i_startidx_var_64, i_endidx_var_65, 2, -5)
      DO jk_var_58 = slev_var_55, elev_var_56
        DO jv_var_57 = i_startidx_var_64, i_endidx_var_65
          rot_vec(jv_var_57, jk_var_58, jb_var_59) = vec_e(ptr_patch_var_50 % verts % edge_idx(jv_var_57, jb_var_59, 1), jk_var_58, ptr_patch_var_50 % verts % edge_blk(jv_var_57, jb_var_59, 1)) * ptr_int % geofac_rot(jv_var_57, 1, jb_var_59) + vec_e(ptr_patch_var_50 % verts % edge_idx(jv_var_57, jb_var_59, 2), jk_var_58, ptr_patch_var_50 % verts % edge_blk(jv_var_57, jb_var_59, 2)) * ptr_int % geofac_rot(jv_var_57, 2, jb_var_59) + vec_e(ptr_patch_var_50 % verts % edge_idx(jv_var_57, jb_var_59, 3), jk_var_58, ptr_patch_var_50 % verts % edge_blk(jv_var_57, jb_var_59, 3)) * ptr_int % geofac_rot(jv_var_57, 3, jb_var_59) + vec_e(ptr_patch_var_50 % verts % edge_idx(jv_var_57, jb_var_59, 4), jk_var_58, ptr_patch_var_50 % verts % edge_blk(jv_var_57, jb_var_59, 4)) * ptr_int % geofac_rot(jv_var_57, 4, jb_var_59) + vec_e(ptr_patch_var_50 % verts % edge_idx(jv_var_57, jb_var_59, 5), jk_var_58, ptr_patch_var_50 % verts % edge_blk(jv_var_57, jb_var_59, 5)) * ptr_int % geofac_rot(jv_var_57, 5, jb_var_59) + vec_e(ptr_patch_var_50 % verts % edge_idx(jv_var_57, jb_var_59, 6), jk_var_58, ptr_patch_var_50 % verts % edge_blk(jv_var_57, jb_var_59, 6)) * ptr_int % geofac_rot(jv_var_57, 6, jb_var_59)
        END DO
      END DO
    END DO
  END SUBROUTINE rot_vertex_ri
END MODULE mo_math_divrot
MODULE mo_real_timer
  IMPLICIT NONE
  CONTAINS
  SUBROUTINE timer_start(it_var_66)
    INTEGER, INTENT(IN) :: it_var_66
  END SUBROUTINE timer_start
  SUBROUTINE timer_stop(it_var_67)
    INTEGER, INTENT(IN) :: it_var_67
  END SUBROUTINE timer_stop
END MODULE mo_real_timer
MODULE mo_run_config
  IMPLICIT NONE
  LOGICAL :: lvert_nest
  INTEGER :: timers_level
  CONTAINS
END MODULE mo_run_config
MODULE mo_timer
  IMPLICIT NONE
  INTEGER :: timer_solve_nh_veltend
  INTEGER :: timer_intp
  CONTAINS
END MODULE mo_timer
MODULE mo_icon_interpolation_scalar
  IMPLICIT NONE
  CONTAINS
  SUBROUTINE cells2verts_scalar_ri(p_cell_in, ptr_patch_var_68, c_int, p_vert_out, opt_slev_var_69, opt_elev_var_70, opt_rlstart, opt_rlend_var_71, opt_acc_async_var_72)
    USE mo_model_domain, ONLY: t_patch
    USE mo_run_config, ONLY: timers_level
    USE mo_real_timer, ONLY: timer_start, timer_stop
    USE mo_timer, ONLY: timer_intp
    USE mo_loopindices, ONLY: get_indices_v
    TYPE(t_patch), TARGET, INTENT(IN) :: ptr_patch_var_68
    REAL(KIND = 8), INTENT(IN) :: p_cell_in(:, :, :)
    REAL(KIND = 8), INTENT(IN) :: c_int(:, :, :)
    INTEGER, INTENT(IN), OPTIONAL :: opt_slev_var_69
    INTEGER, INTENT(IN), OPTIONAL :: opt_elev_var_70
    INTEGER, INTENT(IN), OPTIONAL :: opt_rlstart, opt_rlend_var_71
    REAL(KIND = 8), INTENT(INOUT) :: p_vert_out(:, :, :)
    LOGICAL, INTENT(IN), OPTIONAL :: opt_acc_async_var_72
    INTEGER :: slev_var_73, elev_var_74
    INTEGER :: jv_var_75, jk_var_76, jb_var_77
    INTEGER :: rl_start_var_78, rl_end_var_79
    INTEGER :: i_startblk_var_80, i_endblk_var_81, i_startidx_var_82, i_endidx_var_83, i_nchdom
    slev_var_73 = 1
    elev_var_74 = UBOUND(p_cell_in, 2)
    rl_start_var_78 = 2
    rl_end_var_79 = -5
    i_nchdom = MAX(1, ptr_patch_var_68 % n_childdom)
    i_startblk_var_80 = ptr_patch_var_68 % verts % start_blk(2, 1)
    i_endblk_var_81 = ptr_patch_var_68 % verts % end_blk(- 5, i_nchdom)
    IF (timers_level > 10) CALL timer_start(timer_intp)
    DO jb_var_77 = i_startblk_var_80, i_endblk_var_81
      CALL get_indices_v(ptr_patch_var_68, jb_var_77, i_startblk_var_80, i_endblk_var_81, i_startidx_var_82, i_endidx_var_83, 2, -5)
      DO jk_var_76 = slev_var_73, elev_var_74
        DO jv_var_75 = i_startidx_var_82, i_endidx_var_83
          p_vert_out(jv_var_75, jk_var_76, jb_var_77) = c_int(jv_var_75, 1, jb_var_77) * p_cell_in(ptr_patch_var_68 % verts % cell_idx(jv_var_75, jb_var_77, 1), jk_var_76, ptr_patch_var_68 % verts % cell_blk(jv_var_75, jb_var_77, 1)) + c_int(jv_var_75, 2, jb_var_77) * p_cell_in(ptr_patch_var_68 % verts % cell_idx(jv_var_75, jb_var_77, 2), jk_var_76, ptr_patch_var_68 % verts % cell_blk(jv_var_75, jb_var_77, 2)) + c_int(jv_var_75, 3, jb_var_77) * p_cell_in(ptr_patch_var_68 % verts % cell_idx(jv_var_75, jb_var_77, 3), jk_var_76, ptr_patch_var_68 % verts % cell_blk(jv_var_75, jb_var_77, 3)) + c_int(jv_var_75, 4, jb_var_77) * p_cell_in(ptr_patch_var_68 % verts % cell_idx(jv_var_75, jb_var_77, 4), jk_var_76, ptr_patch_var_68 % verts % cell_blk(jv_var_75, jb_var_77, 4)) + c_int(jv_var_75, 5, jb_var_77) * p_cell_in(ptr_patch_var_68 % verts % cell_idx(jv_var_75, jb_var_77, 5), jk_var_76, ptr_patch_var_68 % verts % cell_blk(jv_var_75, jb_var_77, 5)) + c_int(jv_var_75, 6, jb_var_77) * p_cell_in(ptr_patch_var_68 % verts % cell_idx(jv_var_75, jb_var_77, 6), jk_var_76, ptr_patch_var_68 % verts % cell_blk(jv_var_75, jb_var_77, 6))
        END DO
      END DO
    END DO
    IF (timers_level > 10) CALL timer_stop(timer_intp)
  END SUBROUTINE cells2verts_scalar_ri
END MODULE mo_icon_interpolation_scalar
MODULE mo_vertical_grid
  IMPLICIT NONE
  INTEGER :: nrdmax(10)
  CONTAINS
END MODULE mo_vertical_grid
MODULE mo_velocity_advection
  IMPLICIT NONE
  CONTAINS
  SUBROUTINE velocity_tendencies(p_prog, p_patch, p_int, p_metrics, p_diag, z_w_concorr_me, z_kin_hor_e, z_vt_ie, ntnd, istep, lvn_only, dtime, dt_linintp_ubc, ldeepatmo)
    USE mo_model_domain, ONLY: t_patch
    USE mo_intp_data_strc, ONLY: t_int_state
    USE mo_nonhydro_types, ONLY: t_nh_diag, t_nh_metrics, t_nh_prog
    USE mo_parallel_config, ONLY: nproma
    USE mo_run_config, ONLY: lvert_nest, timers_level
    USE mo_real_timer, ONLY: timer_start, timer_stop
    USE mo_timer, ONLY: timer_solve_nh_veltend
    USE mo_vertical_grid, ONLY: nrdmax
    USE mo_init_vgrid, ONLY: nflatlev
    USE mo_nonhydrostatic_config, ONLY: lextra_diffu
    USE mo_icon_interpolation_scalar, ONLY: cells2verts_scalar_ri
    USE mo_math_divrot, ONLY: rot_vertex_ri
    USE mo_loopindices, ONLY: get_indices_c, get_indices_e
    TYPE(t_patch), TARGET, INTENT(IN) :: p_patch
    TYPE(t_int_state), TARGET, INTENT(IN) :: p_int
    TYPE(t_nh_prog), INTENT(INOUT) :: p_prog
    TYPE(t_nh_metrics), INTENT(INOUT) :: p_metrics
    TYPE(t_nh_diag), INTENT(INOUT) :: p_diag
    REAL(KIND = 8), DIMENSION(:, :, :), INTENT(INOUT) :: z_w_concorr_me, z_kin_hor_e, z_vt_ie
    INTEGER, INTENT(IN) :: ntnd
    INTEGER, INTENT(IN) :: istep
    LOGICAL, INTENT(IN) :: lvn_only
    REAL(KIND = 8), INTENT(IN) :: dtime
    REAL(KIND = 8), INTENT(IN) :: dt_linintp_ubc
    LOGICAL, INTENT(IN) :: ldeepatmo
    INTEGER :: jb_var_84, jk_var_85, jc, je
    INTEGER :: i_startblk_var_86, i_endblk_var_87, i_startidx_var_88, i_endidx_var_89
    INTEGER :: i_startblk_2, i_endblk_2, i_startidx_2, i_endidx_2
    INTEGER :: rl_start_var_90, rl_end_var_91, rl_start_2, rl_end_2
    REAL(KIND = 8) :: z_w_concorr_mc(nproma, p_patch % nlev)
    REAL(KIND = 8) :: z_w_con_c(nproma, p_patch % nlevp1)
    REAL(KIND = 8) :: z_w_con_c_full(nproma, p_patch % nlev, p_patch % nblks_c)
    REAL(KIND = 8) :: z_v_grad_w(nproma, p_patch % nlev, p_patch % nblks_e)
    REAL(KIND = 8) :: z_w_v(nproma, p_patch % nlevp1, p_patch % nblks_v)
    REAL(KIND = 8) :: zeta(nproma, p_patch % nlev, p_patch % nblks_v)
    REAL(KIND = 8) :: z_ekinh(nproma, p_patch % nlev, p_patch % nblks_c)
    INTEGER :: nlev_var_92, nlevp1_var_93
    LOGICAL :: l_vert_nested
    INTEGER :: jg
    REAL(KIND = 8) :: cfl_w_limit, vcfl, maxvcfl, vcflmax(p_patch % nblks_c)
    REAL(KIND = 8) :: w_con_e, scalfac_exdiff, difcoef, max_vcfl_dyn_var_94
    INTEGER :: ie, nrdmax_jg, nflatlev_jg, clip_count
    LOGICAL :: levmask(p_patch % nblks_c, p_patch % nlev), levelmask(p_patch % nlev)
    LOGICAL :: cfl_clipping(nproma, p_patch % nlevp1)
    CALL global_init_fn
    IF (timers_level > 5) CALL timer_start(timer_solve_nh_veltend)
    IF ((lvert_nest) .AND. (p_patch % nshift > 0)) THEN
      l_vert_nested = .TRUE.
    ELSE
      l_vert_nested = .FALSE.
    END IF
    jg = p_patch % id
    nrdmax_jg = nrdmax(jg)
    nflatlev_jg = nflatlev(jg)
    nlev_var_92 = p_patch % nlev
    nlevp1_var_93 = p_patch % nlevp1
    IF (lextra_diffu) THEN
      cfl_w_limit = 0.65D0 / dtime
      scalfac_exdiff = 0.05D0 / (dtime * (0.85D0 - cfl_w_limit * dtime))
    ELSE
      cfl_w_limit = 0.85D0 / dtime
      scalfac_exdiff = 0.0D0
    END IF
    IF (.NOT. lvn_only) CALL cells2verts_scalar_ri(p_prog % w, p_patch, p_int % cells_aw_verts, z_w_v, opt_rlend_var_71 = - 5, opt_acc_async_var_72 = .TRUE.)
    CALL rot_vertex_ri(p_prog % vn, p_patch, p_int, zeta, opt_rlend_var_53 = - 5, opt_acc_async_var_54 = .TRUE.)
    IF (istep == 1) THEN
      rl_start_var_90 = 5
      rl_end_var_91 = -10
      i_startblk_var_86 = p_patch % edges % start_block(5)
      i_endblk_var_87 = p_patch % edges % end_block(- 10)
      DO jb_var_84 = i_startblk_var_86, i_endblk_var_87
        CALL get_indices_e(p_patch, jb_var_84, i_startblk_var_86, i_endblk_var_87, i_startidx_var_88, i_endidx_var_89, 5, -10)
        DO jk_var_85 = 1, nlev_var_92
          DO je = i_startidx_var_88, i_endidx_var_89
            p_diag % vt(je, jk_var_85, jb_var_84) = p_int % rbf_vec_coeff_e(1, je, jb_var_84) * p_prog % vn(p_patch % edges % quad_idx(je, jb_var_84, 1), jk_var_85, p_patch % edges % quad_blk(je, jb_var_84, 1)) + p_int % rbf_vec_coeff_e(2, je, jb_var_84) * p_prog % vn(p_patch % edges % quad_idx(je, jb_var_84, 2), jk_var_85, p_patch % edges % quad_blk(je, jb_var_84, 2)) + p_int % rbf_vec_coeff_e(3, je, jb_var_84) * p_prog % vn(p_patch % edges % quad_idx(je, jb_var_84, 3), jk_var_85, p_patch % edges % quad_blk(je, jb_var_84, 3)) + p_int % rbf_vec_coeff_e(4, je, jb_var_84) * p_prog % vn(p_patch % edges % quad_idx(je, jb_var_84, 4), jk_var_85, p_patch % edges % quad_blk(je, jb_var_84, 4))
          END DO
        END DO
        DO jk_var_85 = 2, nlev_var_92
          DO je = i_startidx_var_88, i_endidx_var_89
            p_diag % vn_ie(je, jk_var_85, jb_var_84) = p_metrics % wgtfac_e(je, jk_var_85, jb_var_84) * p_prog % vn(je, jk_var_85, jb_var_84) + (1.0D0 - p_metrics % wgtfac_e(je, jk_var_85, jb_var_84)) * p_prog % vn(je, jk_var_85 - 1, jb_var_84)
            z_kin_hor_e(je, jk_var_85, jb_var_84) = 0.5D0 * (p_prog % vn(je, jk_var_85, jb_var_84) ** 2 + p_diag % vt(je, jk_var_85, jb_var_84) ** 2)
          END DO
        END DO
        IF (.NOT. lvn_only) THEN
          DO jk_var_85 = 2, nlev_var_92
            DO je = i_startidx_var_88, i_endidx_var_89
              z_vt_ie(je, jk_var_85, jb_var_84) = p_metrics % wgtfac_e(je, jk_var_85, jb_var_84) * p_diag % vt(je, jk_var_85, jb_var_84) + (1.0D0 - p_metrics % wgtfac_e(je, jk_var_85, jb_var_84)) * p_diag % vt(je, jk_var_85 - 1, jb_var_84)
            END DO
          END DO
        END IF
        DO jk_var_85 = nflatlev_jg, nlev_var_92
          DO je = i_startidx_var_88, i_endidx_var_89
            z_w_concorr_me(je, jk_var_85, jb_var_84) = p_prog % vn(je, jk_var_85, jb_var_84) * p_metrics % ddxn_z_full(je, jk_var_85, jb_var_84) + p_diag % vt(je, jk_var_85, jb_var_84) * p_metrics % ddxt_z_full(je, jk_var_85, jb_var_84)
          END DO
        END DO
        IF (.NOT. l_vert_nested) THEN
          DO je = i_startidx_var_88, i_endidx_var_89
            p_diag % vn_ie(je, 1, jb_var_84) = p_prog % vn(je, 1, jb_var_84)
            z_vt_ie(je, 1, jb_var_84) = p_diag % vt(je, 1, jb_var_84)
            z_kin_hor_e(je, 1, jb_var_84) = 0.5D0 * (p_prog % vn(je, 1, jb_var_84) ** 2 + p_diag % vt(je, 1, jb_var_84) ** 2)
            p_diag % vn_ie(je, nlevp1_var_93, jb_var_84) = p_metrics % wgtfacq_e(je, 1, jb_var_84) * p_prog % vn(je, nlev_var_92, jb_var_84) + p_metrics % wgtfacq_e(je, 2, jb_var_84) * p_prog % vn(je, nlev_var_92 - 1, jb_var_84) + p_metrics % wgtfacq_e(je, 3, jb_var_84) * p_prog % vn(je, nlev_var_92 - 2, jb_var_84)
          END DO
        ELSE
          DO je = i_startidx_var_88, i_endidx_var_89
            p_diag % vn_ie(je, 1, jb_var_84) = p_diag % vn_ie_ubc(je, 1, jb_var_84) + dt_linintp_ubc * p_diag % vn_ie_ubc(je, 2, jb_var_84)
            z_vt_ie(je, 1, jb_var_84) = p_diag % vt(je, 1, jb_var_84)
            z_kin_hor_e(je, 1, jb_var_84) = 0.5D0 * (p_prog % vn(je, 1, jb_var_84) ** 2 + p_diag % vt(je, 1, jb_var_84) ** 2)
            p_diag % vn_ie(je, nlevp1_var_93, jb_var_84) = p_metrics % wgtfacq_e(je, 1, jb_var_84) * p_prog % vn(je, nlev_var_92, jb_var_84) + p_metrics % wgtfacq_e(je, 2, jb_var_84) * p_prog % vn(je, nlev_var_92 - 1, jb_var_84) + p_metrics % wgtfacq_e(je, 3, jb_var_84) * p_prog % vn(je, nlev_var_92 - 2, jb_var_84)
          END DO
        END IF
      END DO
    END IF
    rl_start_var_90 = 7
    rl_end_var_91 = -9
    i_startblk_var_86 = p_patch % edges % start_block(7)
    i_endblk_var_87 = p_patch % edges % end_block(- 9)
    IF (.NOT. lvn_only) THEN
      DO jb_var_84 = i_startblk_var_86, i_endblk_var_87
        CALL get_indices_e(p_patch, jb_var_84, i_startblk_var_86, i_endblk_var_87, i_startidx_var_88, i_endidx_var_89, 7, -9)
        DO jk_var_85 = 1, nlev_var_92
          DO je = i_startidx_var_88, i_endidx_var_89
            z_v_grad_w(je, jk_var_85, jb_var_84) = p_diag % vn_ie(je, jk_var_85, jb_var_84) * p_patch % edges % inv_dual_edge_length(je, jb_var_84) * (p_prog % w(p_patch % edges % cell_idx(je, jb_var_84, 1), jk_var_85, p_patch % edges % cell_blk(je, jb_var_84, 1)) - p_prog % w(p_patch % edges % cell_idx(je, jb_var_84, 2), jk_var_85, p_patch % edges % cell_blk(je, jb_var_84, 2))) + z_vt_ie(je, jk_var_85, jb_var_84) * p_patch % edges % inv_primal_edge_length(je, jb_var_84) * p_patch % edges % tangent_orientation(je, jb_var_84) * (z_w_v(p_patch % edges % vertex_idx(je, jb_var_84, 1), jk_var_85, p_patch % edges % vertex_blk(je, jb_var_84, 1)) - z_w_v(p_patch % edges % vertex_idx(je, jb_var_84, 2), jk_var_85, p_patch % edges % vertex_blk(je, jb_var_84, 2)))
          END DO
        END DO
      END DO
    END IF
    IF (.NOT. lvn_only .AND. ldeepatmo) THEN
      DO jb_var_84 = i_startblk_var_86, i_endblk_var_87
        CALL get_indices_e(p_patch, jb_var_84, i_startblk_var_86, i_endblk_var_87, i_startidx_var_88, i_endidx_var_89, 7, -9)
        DO jk_var_85 = 1, nlev_var_92
          DO je = i_startidx_var_88, i_endidx_var_89
            z_v_grad_w(je, jk_var_85, jb_var_84) = z_v_grad_w(je, jk_var_85, jb_var_84) * p_metrics % deepatmo_gradh_ifc(jk_var_85) + p_diag % vn_ie(je, jk_var_85, jb_var_84) * (p_diag % vn_ie(je, jk_var_85, jb_var_84) * p_metrics % deepatmo_invr_ifc(jk_var_85) - p_patch % edges % ft_e(je, jb_var_84)) + z_vt_ie(je, jk_var_85, jb_var_84) * (z_vt_ie(je, jk_var_85, jb_var_84) * p_metrics % deepatmo_invr_ifc(jk_var_85) + p_patch % edges % fn_e(je, jb_var_84))
          END DO
        END DO
      END DO
    END IF
    rl_start_var_90 = 4
    rl_end_var_91 = -5
    i_startblk_var_86 = p_patch % cells % start_block(4)
    i_endblk_var_87 = p_patch % cells % end_block(- 5)
    rl_start_2 = 5
    rl_end_2 = -4
    i_startblk_2 = p_patch % cells % start_block(5)
    i_endblk_2 = p_patch % cells % end_block(- 4)
    DO jb_var_84 = i_startblk_var_86, i_endblk_var_87
      CALL get_indices_c(p_patch, jb_var_84, i_startblk_var_86, i_endblk_var_87, i_startidx_var_88, i_endidx_var_89, 4, -5)
      DO jk_var_85 = 1, nlev_var_92
        DO jc = i_startidx_var_88, i_endidx_var_89
          z_ekinh(jc, jk_var_85, jb_var_84) = p_int % e_bln_c_s(jc, 1, jb_var_84) * z_kin_hor_e(p_patch % cells % edge_idx(jc, jb_var_84, 1), jk_var_85, p_patch % cells % edge_blk(jc, jb_var_84, 1)) + p_int % e_bln_c_s(jc, 2, jb_var_84) * z_kin_hor_e(p_patch % cells % edge_idx(jc, jb_var_84, 2), jk_var_85, p_patch % cells % edge_blk(jc, jb_var_84, 2)) + p_int % e_bln_c_s(jc, 3, jb_var_84) * z_kin_hor_e(p_patch % cells % edge_idx(jc, jb_var_84, 3), jk_var_85, p_patch % cells % edge_blk(jc, jb_var_84, 3))
        END DO
      END DO
      IF (istep == 1) THEN
        DO jk_var_85 = nflatlev_jg, nlev_var_92
          DO jc = i_startidx_var_88, i_endidx_var_89
            z_w_concorr_mc(jc, jk_var_85) = p_int % e_bln_c_s(jc, 1, jb_var_84) * z_w_concorr_me(p_patch % cells % edge_idx(jc, jb_var_84, 1), jk_var_85, p_patch % cells % edge_blk(jc, jb_var_84, 1)) + p_int % e_bln_c_s(jc, 2, jb_var_84) * z_w_concorr_me(p_patch % cells % edge_idx(jc, jb_var_84, 2), jk_var_85, p_patch % cells % edge_blk(jc, jb_var_84, 2)) + p_int % e_bln_c_s(jc, 3, jb_var_84) * z_w_concorr_me(p_patch % cells % edge_idx(jc, jb_var_84, 3), jk_var_85, p_patch % cells % edge_blk(jc, jb_var_84, 3))
          END DO
        END DO
        DO jk_var_85 = nflatlev_jg + 1, nlev_var_92
          DO jc = i_startidx_var_88, i_endidx_var_89
            p_diag % w_concorr_c(jc, jk_var_85, jb_var_84) = p_metrics % wgtfac_c(jc, jk_var_85, jb_var_84) * z_w_concorr_mc(jc, jk_var_85) + (1.0D0 - p_metrics % wgtfac_c(jc, jk_var_85, jb_var_84)) * z_w_concorr_mc(jc, jk_var_85 - 1)
          END DO
        END DO
      END IF
      DO jk_var_85 = 1, nlev_var_92
        DO jc = i_startidx_var_88, i_endidx_var_89
          z_w_con_c(jc, jk_var_85) = p_prog % w(jc, jk_var_85, jb_var_84)
        END DO
      END DO
      DO jc = i_startidx_var_88, i_endidx_var_89
        z_w_con_c(jc, nlevp1_var_93) = 0.0D0
      END DO
      DO jk_var_85 = nlev_var_92, nflatlev_jg + 1, - 1
        DO jc = i_startidx_var_88, i_endidx_var_89
          z_w_con_c(jc, jk_var_85) = z_w_con_c(jc, jk_var_85) - p_diag % w_concorr_c(jc, jk_var_85, jb_var_84)
        END DO
      END DO
      DO jk_var_85 = MAX(3, nrdmax_jg - 2), nlev_var_92 - 3
        levmask(jb_var_84, jk_var_85) = .FALSE.
      END DO
      maxvcfl = 0
      DO jk_var_85 = MAX(3, nrdmax_jg - 2), nlev_var_92 - 3
        clip_count = 0
        DO jc = i_startidx_var_88, i_endidx_var_89
          cfl_clipping(jc, jk_var_85) = (ABS(z_w_con_c(jc, jk_var_85)) > cfl_w_limit * p_metrics % ddqz_z_half(jc, jk_var_85, jb_var_84))
          IF (cfl_clipping(jc, jk_var_85)) clip_count = clip_count + 1
        END DO
        IF (clip_count == 0) CYCLE
        DO jc = i_startidx_var_88, i_endidx_var_89
          IF (cfl_clipping(jc, jk_var_85)) THEN
            levmask(jb_var_84, jk_var_85) = .TRUE.
            vcfl = z_w_con_c(jc, jk_var_85) * dtime / p_metrics % ddqz_z_half(jc, jk_var_85, jb_var_84)
            maxvcfl = MAX(maxvcfl, ABS(vcfl))
            IF (vcfl < - 0.85D0) THEN
              z_w_con_c(jc, jk_var_85) = - 0.85D0 * p_metrics % ddqz_z_half(jc, jk_var_85, jb_var_84) / dtime
            ELSE IF (vcfl > 0.85D0) THEN
              z_w_con_c(jc, jk_var_85) = 0.85D0 * p_metrics % ddqz_z_half(jc, jk_var_85, jb_var_84) / dtime
            END IF
          END IF
        END DO
      END DO
      DO jk_var_85 = 1, nlev_var_92
        DO jc = i_startidx_var_88, i_endidx_var_89
          z_w_con_c_full(jc, jk_var_85, jb_var_84) = 0.5D0 * (z_w_con_c(jc, jk_var_85) + z_w_con_c(jc, jk_var_85 + 1))
        END DO
      END DO
      vcflmax(jb_var_84) = maxvcfl
      IF (lvn_only) CYCLE
      IF (jb_var_84 < i_startblk_2 .OR. jb_var_84 > i_endblk_2) CYCLE
      CALL get_indices_c(p_patch, jb_var_84, i_startblk_2, i_endblk_2, i_startidx_2, i_endidx_2, 5, -4)
      DO jk_var_85 = 2, nlev_var_92
        DO jc = i_startidx_2, i_endidx_2
          p_diag % ddt_w_adv_pc(jc, jk_var_85, jb_var_84, ntnd) = - z_w_con_c(jc, jk_var_85) * (p_prog % w(jc, jk_var_85 - 1, jb_var_84) * p_metrics % coeff1_dwdz(jc, jk_var_85, jb_var_84) - p_prog % w(jc, jk_var_85 + 1, jb_var_84) * p_metrics % coeff2_dwdz(jc, jk_var_85, jb_var_84) + p_prog % w(jc, jk_var_85, jb_var_84) * (p_metrics % coeff2_dwdz(jc, jk_var_85, jb_var_84) - p_metrics % coeff1_dwdz(jc, jk_var_85, jb_var_84)))
        END DO
      END DO
      DO jk_var_85 = 2, nlev_var_92
        DO jc = i_startidx_2, i_endidx_2
          p_diag % ddt_w_adv_pc(jc, jk_var_85, jb_var_84, ntnd) = p_diag % ddt_w_adv_pc(jc, jk_var_85, jb_var_84, ntnd) + p_int % e_bln_c_s(jc, 1, jb_var_84) * z_v_grad_w(p_patch % cells % edge_idx(jc, jb_var_84, 1), jk_var_85, p_patch % cells % edge_blk(jc, jb_var_84, 1)) + p_int % e_bln_c_s(jc, 2, jb_var_84) * z_v_grad_w(p_patch % cells % edge_idx(jc, jb_var_84, 2), jk_var_85, p_patch % cells % edge_blk(jc, jb_var_84, 2)) + p_int % e_bln_c_s(jc, 3, jb_var_84) * z_v_grad_w(p_patch % cells % edge_idx(jc, jb_var_84, 3), jk_var_85, p_patch % cells % edge_blk(jc, jb_var_84, 3))
        END DO
      END DO
      IF (lextra_diffu) THEN
        DO jk_var_85 = MAX(3, nrdmax_jg - 2), nlev_var_92 - 3
          IF (levmask(jb_var_84, jk_var_85)) THEN
            DO jc = i_startidx_2, i_endidx_2
              IF (cfl_clipping(jc, jk_var_85) .AND. p_patch % cells % decomp_info % owner_mask(jc, jb_var_84)) THEN
                difcoef = scalfac_exdiff * MIN(0.85D0 - cfl_w_limit * dtime, ABS(z_w_con_c(jc, jk_var_85)) * dtime / p_metrics % ddqz_z_half(jc, jk_var_85, jb_var_84) - cfl_w_limit * dtime)
                p_diag % ddt_w_adv_pc(jc, jk_var_85, jb_var_84, ntnd) = p_diag % ddt_w_adv_pc(jc, jk_var_85, jb_var_84, ntnd) + difcoef * p_patch % cells % area(jc, jb_var_84) * (p_prog % w(jc, jk_var_85, jb_var_84) * p_int % geofac_n2s(jc, 1, jb_var_84) + p_prog % w(p_patch % cells % neighbor_idx(jc, jb_var_84, 1), jk_var_85, p_patch % cells % neighbor_blk(jc, jb_var_84, 1)) * p_int % geofac_n2s(jc, 2, jb_var_84) + p_prog % w(p_patch % cells % neighbor_idx(jc, jb_var_84, 2), jk_var_85, p_patch % cells % neighbor_blk(jc, jb_var_84, 2)) * p_int % geofac_n2s(jc, 3, jb_var_84) + p_prog % w(p_patch % cells % neighbor_idx(jc, jb_var_84, 3), jk_var_85, p_patch % cells % neighbor_blk(jc, jb_var_84, 3)) * p_int % geofac_n2s(jc, 4, jb_var_84))
              END IF
            END DO
          END IF
        END DO
      END IF
    END DO
    DO jk_var_85 = MAX(3, nrdmax_jg - 2), nlev_var_92 - 3
      levelmask(jk_var_85) = ANY(levmask(i_startblk_var_86 : i_endblk_var_87, jk_var_85))
    END DO
    rl_start_var_90 = 10
    rl_end_var_91 = -8
    i_startblk_var_86 = p_patch % edges % start_block(10)
    i_endblk_var_87 = p_patch % edges % end_block(- 8)
    DO jb_var_84 = i_startblk_var_86, i_endblk_var_87
      CALL get_indices_e(p_patch, jb_var_84, i_startblk_var_86, i_endblk_var_87, i_startidx_var_88, i_endidx_var_89, 10, -8)
      IF (.NOT. ldeepatmo) THEN
        DO jk_var_85 = 1, nlev_var_92
          DO je = i_startidx_var_88, i_endidx_var_89
            p_diag % ddt_vn_apc_pc(je, jk_var_85, jb_var_84, ntnd) = - (z_kin_hor_e(je, jk_var_85, jb_var_84) * (p_metrics % coeff_gradekin(je, 1, jb_var_84) - p_metrics % coeff_gradekin(je, 2, jb_var_84)) + p_metrics % coeff_gradekin(je, 2, jb_var_84) * z_ekinh(p_patch % edges % cell_idx(je, jb_var_84, 2), jk_var_85, p_patch % edges % cell_blk(je, jb_var_84, 2)) - p_metrics % coeff_gradekin(je, 1, jb_var_84) * z_ekinh(p_patch % edges % cell_idx(je, jb_var_84, 1), jk_var_85, p_patch % edges % cell_blk(je, jb_var_84, 1)) + p_diag % vt(je, jk_var_85, jb_var_84) * (p_patch % edges % f_e(je, jb_var_84) + 0.5D0 * (zeta(p_patch % edges % vertex_idx(je, jb_var_84, 1), jk_var_85, p_patch % edges % vertex_blk(je, jb_var_84, 1)) + zeta(p_patch % edges % vertex_idx(je, jb_var_84, 2), jk_var_85, p_patch % edges % vertex_blk(je, jb_var_84, 2)))) + (p_int % c_lin_e(je, 1, jb_var_84) * z_w_con_c_full(p_patch % edges % cell_idx(je, jb_var_84, 1), jk_var_85, p_patch % edges % cell_blk(je, jb_var_84, 1)) + p_int % c_lin_e(je, 2, jb_var_84) * z_w_con_c_full(p_patch % edges % cell_idx(je, jb_var_84, 2), jk_var_85, p_patch % edges % cell_blk(je, jb_var_84, 2))) * (p_diag % vn_ie(je, jk_var_85, jb_var_84) - p_diag % vn_ie(je, jk_var_85 + 1, jb_var_84)) / p_metrics % ddqz_z_full_e(je, jk_var_85, jb_var_84))
          END DO
        END DO
        IF (p_diag % ddt_vn_adv_is_associated .OR. p_diag % ddt_vn_cor_is_associated) THEN
          DO jk_var_85 = 1, nlev_var_92
            DO je = i_startidx_var_88, i_endidx_var_89
              p_diag % ddt_vn_cor_pc(je, jk_var_85, jb_var_84, ntnd) = - p_diag % vt(je, jk_var_85, jb_var_84) * p_patch % edges % f_e(je, jb_var_84)
            END DO
          END DO
        END IF
      ELSE
        DO jk_var_85 = 1, nlev_var_92
          DO je = i_startidx_var_88, i_endidx_var_89
            p_diag % ddt_vn_apc_pc(je, jk_var_85, jb_var_84, ntnd) = - ((z_kin_hor_e(je, jk_var_85, jb_var_84) * (p_metrics % coeff_gradekin(je, 1, jb_var_84) - p_metrics % coeff_gradekin(je, 2, jb_var_84)) + p_metrics % coeff_gradekin(je, 2, jb_var_84) * z_ekinh(p_patch % edges % cell_idx(je, jb_var_84, 2), jk_var_85, p_patch % edges % cell_blk(je, jb_var_84, 2)) - p_metrics % coeff_gradekin(je, 1, jb_var_84) * z_ekinh(p_patch % edges % cell_idx(je, jb_var_84, 1), jk_var_85, p_patch % edges % cell_blk(je, jb_var_84, 1))) * p_metrics % deepatmo_gradh_mc(jk_var_85) + p_diag % vt(je, jk_var_85, jb_var_84) * (p_patch % edges % f_e(je, jb_var_84) + 0.5D0 * (zeta(p_patch % edges % vertex_idx(je, jb_var_84, 1), jk_var_85, p_patch % edges % vertex_blk(je, jb_var_84, 1)) + zeta(p_patch % edges % vertex_idx(je, jb_var_84, 2), jk_var_85, p_patch % edges % vertex_blk(je, jb_var_84, 2))) * p_metrics % deepatmo_gradh_mc(jk_var_85)) + (p_int % c_lin_e(je, 1, jb_var_84) * z_w_con_c_full(p_patch % edges % cell_idx(je, jb_var_84, 1), jk_var_85, p_patch % edges % cell_blk(je, jb_var_84, 1)) + p_int % c_lin_e(je, 2, jb_var_84) * z_w_con_c_full(p_patch % edges % cell_idx(je, jb_var_84, 2), jk_var_85, p_patch % edges % cell_blk(je, jb_var_84, 2))) * ((p_diag % vn_ie(je, jk_var_85, jb_var_84) - p_diag % vn_ie(je, jk_var_85 + 1, jb_var_84)) / p_metrics % ddqz_z_full_e(je, jk_var_85, jb_var_84) + p_prog % vn(je, jk_var_85, jb_var_84) * p_metrics % deepatmo_invr_mc(jk_var_85) - p_patch % edges % ft_e(je, jb_var_84)))
          END DO
        END DO
        IF (p_diag % ddt_vn_adv_is_associated .OR. p_diag % ddt_vn_cor_is_associated) THEN
          DO jk_var_85 = 1, nlev_var_92
            DO je = i_startidx_var_88, i_endidx_var_89
              p_diag % ddt_vn_cor_pc(je, jk_var_85, jb_var_84, ntnd) = - (+ p_diag % vt(je, jk_var_85, jb_var_84) * (p_patch % edges % f_e(je, jb_var_84)) + (p_int % c_lin_e(je, 1, jb_var_84) * z_w_con_c_full(p_patch % edges % cell_idx(je, jb_var_84, 1), jk_var_85, p_patch % edges % cell_blk(je, jb_var_84, 1)) + p_int % c_lin_e(je, 2, jb_var_84) * z_w_con_c_full(p_patch % edges % cell_idx(je, jb_var_84, 2), jk_var_85, p_patch % edges % cell_blk(je, jb_var_84, 2))) * (- p_patch % edges % ft_e(je, jb_var_84)))
            END DO
          END DO
        END IF
      END IF
      IF (lextra_diffu) THEN
        ie = 0
        DO jk_var_85 = MAX(3, nrdmax_jg - 2), nlev_var_92 - 4
          IF (levelmask(jk_var_85) .OR. levelmask(jk_var_85 + 1)) THEN
            DO je = i_startidx_var_88, i_endidx_var_89
              w_con_e = p_int % c_lin_e(je, 1, jb_var_84) * z_w_con_c_full(p_patch % edges % cell_idx(je, jb_var_84, 1), jk_var_85, p_patch % edges % cell_blk(je, jb_var_84, 1)) + p_int % c_lin_e(je, 2, jb_var_84) * z_w_con_c_full(p_patch % edges % cell_idx(je, jb_var_84, 2), jk_var_85, p_patch % edges % cell_blk(je, jb_var_84, 2))
              IF (ABS(w_con_e) > cfl_w_limit * p_metrics % ddqz_z_full_e(je, jk_var_85, jb_var_84)) THEN
                difcoef = scalfac_exdiff * MIN(0.85D0 - cfl_w_limit * dtime, ABS(w_con_e) * dtime / p_metrics % ddqz_z_full_e(je, jk_var_85, jb_var_84) - cfl_w_limit * dtime)
                p_diag % ddt_vn_apc_pc(je, jk_var_85, jb_var_84, ntnd) = p_diag % ddt_vn_apc_pc(je, jk_var_85, jb_var_84, ntnd) + difcoef * p_patch % edges % area_edge(je, jb_var_84) * (p_int % geofac_grdiv(je, 1, jb_var_84) * p_prog % vn(je, jk_var_85, jb_var_84) + p_int % geofac_grdiv(je, 2, jb_var_84) * p_prog % vn(p_patch % edges % quad_idx(je, jb_var_84, 1), jk_var_85, p_patch % edges % quad_blk(je, jb_var_84, 1)) + p_int % geofac_grdiv(je, 3, jb_var_84) * p_prog % vn(p_patch % edges % quad_idx(je, jb_var_84, 2), jk_var_85, p_patch % edges % quad_blk(je, jb_var_84, 2)) + p_int % geofac_grdiv(je, 4, jb_var_84) * p_prog % vn(p_patch % edges % quad_idx(je, jb_var_84, 3), jk_var_85, p_patch % edges % quad_blk(je, jb_var_84, 3)) + p_int % geofac_grdiv(je, 5, jb_var_84) * p_prog % vn(p_patch % edges % quad_idx(je, jb_var_84, 4), jk_var_85, p_patch % edges % quad_blk(je, jb_var_84, 4)) + p_patch % edges % tangent_orientation(je, jb_var_84) * p_patch % edges % inv_primal_edge_length(je, jb_var_84) * (zeta(p_patch % edges % vertex_idx(je, jb_var_84, 2), jk_var_85, p_patch % edges % vertex_blk(je, jb_var_84, 2)) - zeta(p_patch % edges % vertex_idx(je, jb_var_84, 1), jk_var_85, p_patch % edges % vertex_blk(je, jb_var_84, 1))))
              END IF
            END DO
          END IF
        END DO
      END IF
    END DO
    i_startblk_var_86 = p_patch % cells % start_block(4)
    i_endblk_var_87 = p_patch % cells % end_block(- 4)
    max_vcfl_dyn_var_94 = MAX(p_diag % max_vcfl_dyn, MAXVAL(vcflmax(i_startblk_var_86 : i_endblk_var_87)))
    p_diag % max_vcfl_dyn = max_vcfl_dyn_var_94
    IF (timers_level > 5) CALL timer_stop(timer_solve_nh_veltend)
  END SUBROUTINE velocity_tendencies
END MODULE mo_velocity_advection
SUBROUTINE global_init_fn
  USE mo_parallel_config, ONLY: nproma
  IMPLICIT NONE
  nproma = 1
END SUBROUTINE global_init_fn