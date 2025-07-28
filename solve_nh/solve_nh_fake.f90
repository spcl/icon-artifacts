MODULE fake_mo_fortran_tools
  IMPLICIT NONE
  CONTAINS
  SUBROUTINE acc_wait_if_requested(acc_async_queue, opt_acc_async)
    INTEGER, INTENT(IN) :: acc_async_queue
    LOGICAL, INTENT(IN), OPTIONAL :: opt_acc_async
  END SUBROUTINE acc_wait_if_requested
  SUBROUTINE init_contiguous_dp(var, n, v, lacc, opt_acc_async)
    INTEGER, INTENT(IN) :: n
    REAL(KIND = 8), INTENT(OUT) :: var(n)
    REAL(KIND = 8), INTENT(IN) :: v
    LOGICAL, INTENT(IN), OPTIONAL :: lacc
    LOGICAL, INTENT(IN), OPTIONAL :: opt_acc_async
    INTEGER :: i
    LOGICAL :: lzacc
    CALL set_acc_host_or_device(lzacc, .TRUE.)
    DO i = 1, n
      var(i) = 0.0D0
    END DO
    CALL acc_wait_if_requested(1, .TRUE.)
  END SUBROUTINE init_contiguous_dp
  SUBROUTINE init_zero_contiguous_dp(var, n, lacc, opt_acc_async)
    INTEGER, INTENT(IN) :: n
    REAL(KIND = 8), INTENT(OUT) :: var(n)
    LOGICAL, INTENT(IN), OPTIONAL :: lacc
    LOGICAL, INTENT(IN), OPTIONAL :: opt_acc_async
    CALL init_contiguous_dp(var, n, 0.0D0, .TRUE., .TRUE.)
  END SUBROUTINE init_zero_contiguous_dp
  PURE SUBROUTINE set_acc_host_or_device(lzacc, lacc)
    LOGICAL, INTENT(OUT) :: lzacc
    LOGICAL, INTENT(IN), OPTIONAL :: lacc
    lzacc = .FALSE.
  END SUBROUTINE set_acc_host_or_device
END MODULE fake_mo_fortran_tools
MODULE fake_mo_lib_loopindices
  IMPLICIT NONE
  CONTAINS
  SUBROUTINE get_indices_c_lib(i_startidx_in, i_endidx_in, nproma, i_blk, i_startblk, i_endblk, i_startidx_out, i_endidx_out)
    INTEGER, INTENT(IN) :: i_startidx_in
    INTEGER, INTENT(IN) :: i_endidx_in
    INTEGER, INTENT(IN) :: nproma
    INTEGER, INTENT(IN) :: i_blk
    INTEGER, INTENT(IN) :: i_startblk
    INTEGER, INTENT(IN) :: i_endblk
    INTEGER, INTENT(OUT) :: i_startidx_out, i_endidx_out
    IF (i_blk == i_startblk) THEN
      i_startidx_out = MAX(1, i_startidx_in)
      i_endidx_out = nproma
      IF (i_blk == i_endblk) i_endidx_out = i_endidx_in
    ELSE IF (i_blk == i_endblk) THEN
      i_startidx_out = 1
      i_endidx_out = i_endidx_in
    ELSE
      i_startidx_out = 1
      i_endidx_out = nproma
    END IF
  END SUBROUTINE get_indices_c_lib
  SUBROUTINE get_indices_e_lib(i_startidx_in, i_endidx_in, nproma, i_blk, i_startblk, i_endblk, i_startidx_out, i_endidx_out)
    INTEGER, INTENT(IN) :: i_startidx_in
    INTEGER, INTENT(IN) :: i_endidx_in
    INTEGER, INTENT(IN) :: nproma
    INTEGER, INTENT(IN) :: i_blk
    INTEGER, INTENT(IN) :: i_startblk
    INTEGER, INTENT(IN) :: i_endblk
    INTEGER, INTENT(OUT) :: i_startidx_out, i_endidx_out
    i_startidx_out = MERGE(1, MAX(1, i_startidx_in), i_blk /= i_startblk)
    i_endidx_out = MERGE(nproma, i_endidx_in, i_blk /= i_endblk)
  END SUBROUTINE get_indices_e_lib
  SUBROUTINE get_indices_v_lib(i_startidx_in, i_endidx_in, nproma, i_blk, i_startblk, i_endblk, i_startidx_out, i_endidx_out)
    INTEGER, INTENT(IN) :: i_startidx_in
    INTEGER, INTENT(IN) :: i_endidx_in
    INTEGER, INTENT(IN) :: nproma
    INTEGER, INTENT(IN) :: i_blk
    INTEGER, INTENT(IN) :: i_startblk
    INTEGER, INTENT(IN) :: i_endblk
    INTEGER, INTENT(OUT) :: i_startidx_out, i_endidx_out
    IF (i_blk == i_startblk) THEN
      i_startidx_out = i_startidx_in
      i_endidx_out = nproma
      IF (i_blk == i_endblk) i_endidx_out = i_endidx_in
    ELSE IF (i_blk == i_endblk) THEN
      i_startidx_out = 1
      i_endidx_out = i_endidx_in
    ELSE
      i_startidx_out = 1
      i_endidx_out = nproma
    END IF
  END SUBROUTINE get_indices_v_lib
END MODULE fake_mo_lib_loopindices
MODULE fake_mo_lib_interpolation_scalar
  IMPLICIT NONE
  CONTAINS
  SUBROUTINE cells2verts_scalar_dp_lib(p_cell_in, vert_cell_idx, vert_cell_blk, c_int, p_vert_out, i_startblk, i_endblk, i_startidx_in, i_endidx_in, slev, elev, nproma, lacc, acc_async)
    USE fake_mo_fortran_tools, ONLY: set_acc_host_or_device
    USE fake_mo_lib_loopindices, ONLY: get_indices_v_lib
    REAL(KIND = 8), INTENT(IN) :: p_cell_in(:, :, :)
    INTEGER, TARGET, INTENT(IN) :: vert_cell_idx(:, :, :)
    INTEGER, TARGET, INTENT(IN) :: vert_cell_blk(:, :, :)
    REAL(KIND = 8), INTENT(IN) :: c_int(:, :, :)
    REAL(KIND = 8), INTENT(INOUT) :: p_vert_out(:, :, :)
    INTEGER, INTENT(IN) :: i_startblk
    INTEGER, INTENT(IN) :: i_endblk
    INTEGER, INTENT(IN) :: i_startidx_in
    INTEGER, INTENT(IN) :: i_endidx_in
    INTEGER, INTENT(IN) :: slev
    INTEGER, INTENT(IN) :: elev
    INTEGER, INTENT(IN) :: nproma
    LOGICAL, INTENT(IN), OPTIONAL :: lacc
    LOGICAL, INTENT(IN), OPTIONAL :: acc_async
    INTEGER :: jv, jk, jb
    INTEGER :: i_startidx, i_endidx
    LOGICAL :: lzacc
    CALL set_acc_host_or_device(lzacc, lacc)
    DO jb = i_startblk, i_endblk
      CALL get_indices_v_lib(i_startidx_in, i_endidx_in, nproma, jb, i_startblk, i_endblk, i_startidx, i_endidx)
      DO jk = 1, elev
        DO jv = i_startidx, i_endidx
          p_vert_out(jv, jk, jb) = c_int(jv, 1, jb) * p_cell_in(vert_cell_idx(jv, jb, 1), jk, vert_cell_blk(jv, jb, 1)) + c_int(jv, 2, jb) * p_cell_in(vert_cell_idx(jv, jb, 2), jk, vert_cell_blk(jv, jb, 2)) + c_int(jv, 3, jb) * p_cell_in(vert_cell_idx(jv, jb, 3), jk, vert_cell_blk(jv, jb, 3)) + c_int(jv, 4, jb) * p_cell_in(vert_cell_idx(jv, jb, 4), jk, vert_cell_blk(jv, jb, 4)) + c_int(jv, 5, jb) * p_cell_in(vert_cell_idx(jv, jb, 5), jk, vert_cell_blk(jv, jb, 5)) + c_int(jv, 6, jb) * p_cell_in(vert_cell_idx(jv, jb, 6), jk, vert_cell_blk(jv, jb, 6))
        END DO
      END DO
    END DO
    IF (.NOT. acc_async) THEN
    END IF
  END SUBROUTINE cells2verts_scalar_dp_lib
  SUBROUTINE cells2verts_scalar_ri_lib(p_cell_in, vert_cell_idx, vert_cell_blk, c_int, p_vert_out, i_startblk, i_endblk, i_startidx_in, i_endidx_in, slev, elev, nproma, lacc, acc_async)
    USE fake_mo_fortran_tools, ONLY: set_acc_host_or_device
    USE fake_mo_lib_loopindices, ONLY: get_indices_v_lib
    REAL(KIND = 8), INTENT(IN) :: p_cell_in(:, :, :)
    INTEGER, TARGET, INTENT(IN) :: vert_cell_idx(:, :, :)
    INTEGER, TARGET, INTENT(IN) :: vert_cell_blk(:, :, :)
    REAL(KIND = 8), INTENT(IN) :: c_int(:, :, :)
    REAL(KIND = 8), INTENT(INOUT) :: p_vert_out(:, :, :)
    INTEGER, INTENT(IN) :: i_startblk
    INTEGER, INTENT(IN) :: i_endblk
    INTEGER, INTENT(IN) :: i_startidx_in
    INTEGER, INTENT(IN) :: i_endidx_in
    INTEGER, INTENT(IN) :: slev
    INTEGER, INTENT(IN) :: elev
    INTEGER, INTENT(IN) :: nproma
    LOGICAL, INTENT(IN), OPTIONAL :: lacc
    LOGICAL, INTENT(IN), OPTIONAL :: acc_async
    INTEGER :: jv, jk, jb
    INTEGER :: i_startidx, i_endidx
    LOGICAL :: lzacc
    CALL set_acc_host_or_device(lzacc, lacc)
    DO jb = i_startblk, i_endblk
      CALL get_indices_v_lib(i_startidx_in, i_endidx_in, nproma, jb, i_startblk, i_endblk, i_startidx, i_endidx)
      DO jk = 1, elev
        DO jv = i_startidx, i_endidx
          p_vert_out(jv, jk, jb) = c_int(jv, 1, jb) * p_cell_in(vert_cell_idx(jv, jb, 1), jk, vert_cell_blk(jv, jb, 1)) + c_int(jv, 2, jb) * p_cell_in(vert_cell_idx(jv, jb, 2), jk, vert_cell_blk(jv, jb, 2)) + c_int(jv, 3, jb) * p_cell_in(vert_cell_idx(jv, jb, 3), jk, vert_cell_blk(jv, jb, 3)) + c_int(jv, 4, jb) * p_cell_in(vert_cell_idx(jv, jb, 4), jk, vert_cell_blk(jv, jb, 4)) + c_int(jv, 5, jb) * p_cell_in(vert_cell_idx(jv, jb, 5), jk, vert_cell_blk(jv, jb, 5)) + c_int(jv, 6, jb) * p_cell_in(vert_cell_idx(jv, jb, 6), jk, vert_cell_blk(jv, jb, 6))
        END DO
      END DO
    END DO
  END SUBROUTINE cells2verts_scalar_ri_lib
END MODULE fake_mo_lib_interpolation_scalar
MODULE fake_mo_mpi
  IMPLICIT NONE
  CONTAINS
  LOGICAL FUNCTION my_process_is_mpi_all_seq()
    my_process_is_mpi_all_seq = .TRUE.
  END FUNCTION my_process_is_mpi_all_seq
END MODULE fake_mo_mpi
MODULE fake_mo_parallel_config
  IMPLICIT NONE
  CONTAINS
  FUNCTION cpu_min_nproma(nproma, min_nproma) RESULT(new_nproma)
    INTEGER, INTENT(IN) :: nproma, min_nproma
    INTEGER :: new_nproma
    new_nproma = MIN(nproma, 256)
  END FUNCTION cpu_min_nproma
END MODULE fake_mo_parallel_config
MODULE fake_mo_real_timer
  IMPLICIT NONE
  CONTAINS
  SUBROUTINE timer_start(it)
    INTEGER, INTENT(IN) :: it
  END SUBROUTINE timer_start
  SUBROUTINE timer_stop(it)
    INTEGER, INTENT(IN) :: it
  END SUBROUTINE timer_stop
END MODULE fake_mo_real_timer
MODULE mo_decomposition_tools
  IMPLICIT NONE
  TYPE :: t_grid_domain_decomp_info
    LOGICAL, ALLOCATABLE :: owner_mask(:, :)
  END TYPE
  CONTAINS
END MODULE mo_decomposition_tools
MODULE mo_dynamics_config
  IMPLICIT NONE
  LOGICAL :: ldeepatmo
  CONTAINS
END MODULE mo_dynamics_config
MODULE mo_grid_config
  IMPLICIT NONE
  LOGICAL :: l_limited_area
  CONTAINS
END MODULE mo_grid_config
MODULE mo_gridref_config
  IMPLICIT NONE
  INTEGER :: grf_intmethod_e
  CONTAINS
END MODULE mo_gridref_config
MODULE mo_init_vgrid
  IMPLICIT NONE
  INTEGER :: nflatlev(10)
  CONTAINS
END MODULE mo_init_vgrid
MODULE mo_initicon_config
  IMPLICIT NONE
  LOGICAL :: is_iau_active = .FALSE.
  REAL(KIND = 8) :: iau_wgt_dyn = 0.0D0
  CONTAINS
END MODULE mo_initicon_config
MODULE mo_intp_data_strc
  IMPLICIT NONE
  TYPE :: t_int_state
    REAL(KIND = 8), ALLOCATABLE :: c_lin_e(:, :, :)
    REAL(KIND = 8), ALLOCATABLE :: e_bln_c_s(:, :, :)
    REAL(KIND = 8), ALLOCATABLE :: e_flx_avg(:, :, :)
    REAL(KIND = 8), ALLOCATABLE :: cells_aw_verts(:, :, :)
    REAL(KIND = 8), ALLOCATABLE :: rbf_vec_coeff_e(:, :, :)
    REAL(KIND = 8), ALLOCATABLE :: geofac_div(:, :, :)
    REAL(KIND = 8), ALLOCATABLE :: geofac_grdiv(:, :, :)
    REAL(KIND = 8), ALLOCATABLE :: geofac_rot(:, :, :)
    REAL(KIND = 8), ALLOCATABLE :: geofac_n2s(:, :, :)
    REAL(KIND = 8), ALLOCATABLE :: geofac_grg(:, :, :, :)
    REAL(KIND = 8), ALLOCATABLE :: pos_on_tplane_e(:, :, :, :)
    REAL(KIND = 8), ALLOCATABLE :: nudgecoeff_e(:, :)
  END TYPE t_int_state
END MODULE mo_intp_data_strc
MODULE mo_model_domain
  USE mo_decomposition_tools, ONLY: t_grid_domain_decomp_info
  IMPLICIT NONE
  TYPE :: t_tangent_vectors
    REAL(KIND = 8) :: v1
    REAL(KIND = 8) :: v2
  END TYPE t_tangent_vectors
  TYPE :: t_grid_cells
    INTEGER, ALLOCATABLE :: neighbor_idx(:, :, :)
    INTEGER, ALLOCATABLE :: neighbor_blk(:, :, :)
    INTEGER, ALLOCATABLE :: edge_idx(:, :, :)
    INTEGER, ALLOCATABLE :: edge_blk(:, :, :)
    REAL(KIND = 8), POINTER :: area(:, :)
    INTEGER, ALLOCATABLE :: start_index(:)
    INTEGER, ALLOCATABLE :: end_index(:)
    INTEGER, ALLOCATABLE :: start_blk(:, :)
    INTEGER, ALLOCATABLE :: start_block(:)
    INTEGER, ALLOCATABLE :: end_blk(:, :)
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
    TYPE(t_tangent_vectors), ALLOCATABLE :: primal_normal_cell(:, :, :)
    TYPE(t_tangent_vectors), ALLOCATABLE :: dual_normal_cell(:, :, :)
    REAL(KIND = 8), ALLOCATABLE :: inv_primal_edge_length(:, :)
    REAL(KIND = 8), ALLOCATABLE :: inv_dual_edge_length(:, :)
    REAL(KIND = 8), ALLOCATABLE :: area_edge(:, :)
    REAL(KIND = 8), ALLOCATABLE :: f_e(:, :)
    REAL(KIND = 8), ALLOCATABLE :: fn_e(:, :)
    REAL(KIND = 8), ALLOCATABLE :: ft_e(:, :)
    INTEGER, ALLOCATABLE :: refin_ctrl(:, :)
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
    INTEGER, ALLOCATABLE :: start_block(:)
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
MODULE mo_mpi
  IMPLICIT NONE
  LOGICAL, PUBLIC :: i_am_accel_node = .FALSE.
  CONTAINS
END MODULE mo_mpi
MODULE mo_nonhydro_types
  IMPLICIT NONE
  TYPE :: t_nh_prog
    REAL(KIND = 8), POINTER, CONTIGUOUS :: w(:, :, :), vn(:, :, :), rho(:, :, :), exner(:, :, :), theta_v(:, :, :)
  END TYPE t_nh_prog
  TYPE :: t_nh_diag
    REAL(KIND = 8), POINTER, CONTIGUOUS :: exner_pr(:, :, :), mass_fl_e(:, :, :), rho_ic(:, :, :), theta_v_ic(:, :, :), grf_tend_vn(:, :, :), grf_tend_w(:, :, :), grf_tend_rho(:, :, :), grf_tend_mflx(:, :, :), grf_bdy_mflx(:, :, :), grf_tend_thv(:, :, :), vn_ie_int(:, :, :), vn_ie_ubc(:, :, :), w_int(:, :, :), w_ubc(:, :, :), theta_v_ic_int(:, :, :), theta_v_ic_ubc(:, :, :), rho_ic_int(:, :, :), rho_ic_ubc(:, :, :), mflx_ic_int(:, :, :), mflx_ic_ubc(:, :, :)
    REAL(KIND = 8), POINTER, CONTIGUOUS :: vn_incr(:, :, :), exner_incr(:, :, :), rho_incr(:, :, :), vt(:, :, :), ddt_exner_phy(:, :, :), ddt_vn_phy(:, :, :), exner_dyn_incr(:, :, :), vn_ie(:, :, :), w_concorr_c(:, :, :), mass_fl_e_sv(:, :, :), ddt_vn_apc_pc(:, :, :, :), ddt_vn_cor_pc(:, :, :, :), ddt_w_adv_pc(:, :, :, :)
    REAL(KIND = 8), POINTER, CONTIGUOUS :: ddt_vn_dyn(:, :, :), ddt_vn_dmp(:, :, :), ddt_vn_adv(:, :, :), ddt_vn_cor(:, :, :), ddt_vn_pgr(:, :, :), ddt_vn_phd(:, :, :), ddt_vn_iau(:, :, :), ddt_vn_ray(:, :, :), ddt_vn_grf(:, :, :)
    LOGICAL :: ddt_vn_dyn_is_associated = .FALSE., ddt_vn_dmp_is_associated = .FALSE., ddt_vn_adv_is_associated = .FALSE., ddt_vn_cor_is_associated = .FALSE., ddt_vn_pgr_is_associated = .FALSE., ddt_vn_phd_is_associated = .FALSE., ddt_vn_iau_is_associated = .FALSE., ddt_vn_ray_is_associated = .FALSE., ddt_vn_grf_is_associated = .FALSE.
    REAL(KIND = 8) :: max_vcfl_dyn = 0.0D0
  END TYPE t_nh_diag
  TYPE :: t_nh_ref
    REAL(KIND = 8), POINTER :: vn_ref(:, :, :), w_ref(:, :, :)
  END TYPE t_nh_ref
  TYPE :: t_nh_metrics
    REAL(KIND = 8), POINTER, CONTIGUOUS :: rayleigh_w(:), rayleigh_vn(:), scalfac_dd3d(:), hmask_dd3d(:, :), vwind_expl_wgt(:, :), vwind_impl_wgt(:, :)
    REAL(KIND = 8), POINTER, CONTIGUOUS :: ddxn_z_full(:, :, :), ddxt_z_full(:, :, :), ddqz_z_full_e(:, :, :), ddqz_z_half(:, :, :), inv_ddqz_z_full(:, :, :), wgtfac_c(:, :, :), wgtfac_e(:, :, :), wgtfacq_c(:, :, :), wgtfacq_e(:, :, :), wgtfacq1_c(:, :, :), coeff_gradekin(:, :, :), coeff1_dwdz(:, :, :), coeff2_dwdz(:, :, :), zdiff_gradp(:, :, :, :), coeff_gradp(:, :, :, :), exner_exfac(:, :, :), theta_ref_mc(:, :, :), theta_ref_me(:, :, :), theta_ref_ic(:, :, :), exner_ref_mc(:, :, :), rho_ref_mc(:, :, :), rho_ref_me(:, :, :), d_exner_dz_ref_ic(:, :, :), d2dexdz2_fac1_mc(:, :, :), d2dexdz2_fac2_mc(:, :, :), pg_exdist(:)
    INTEGER, POINTER, CONTIGUOUS :: vertidx_gradp(:, :, :, :), pg_edgeidx(:), pg_edgeblk(:), pg_vertidx(:), bdy_mflx_e_idx(:), bdy_mflx_e_blk(:)
    REAL(KIND = 8), POINTER, CONTIGUOUS :: deepatmo_gradh_mc(:), deepatmo_divh_mc(:), deepatmo_invr_mc(:), deepatmo_divzu_mc(:), deepatmo_divzl_mc(:), deepatmo_gradh_ifc(:), deepatmo_invr_ifc(:)
    INTEGER :: pg_listdim
    INTEGER :: bdy_mflx_e_dim
  END TYPE t_nh_metrics
  TYPE :: t_nh_state
    TYPE(t_nh_diag) :: diag
    TYPE(t_nh_ref) :: ref
    TYPE(t_nh_metrics) :: metrics
  END TYPE t_nh_state
END MODULE mo_nonhydro_types
MODULE mo_nonhydrostatic_config
  IMPLICIT NONE
  INTEGER :: itime_scheme
  INTEGER :: ndyn_substeps_var(10)
  LOGICAL :: lextra_diffu
  REAL(KIND = 8) :: divdamp_fac
  REAL(KIND = 8) :: divdamp_fac_o2
  INTEGER :: divdamp_order
  INTEGER :: divdamp_type
  INTEGER :: rayleigh_type
  INTEGER :: iadv_rhotheta
  INTEGER :: igradp_method
  INTEGER :: kstart_dd3d(10)
  INTEGER :: kstart_moist(10)
  CONTAINS
END MODULE mo_nonhydrostatic_config
MODULE mo_parallel_config
  IMPLICIT NONE
  INTEGER :: nproma = 0
  CONTAINS
END MODULE mo_parallel_config
MODULE fake_mo_loopindices
  IMPLICIT NONE
  CONTAINS
  SUBROUTINE get_indices_c(p_patch, i_blk, i_startblk, i_endblk, i_startidx, i_endidx, irl_start, opt_rl_end)
    USE mo_model_domain, ONLY: t_patch
    USE fake_mo_lib_loopindices, ONLY: get_indices_c_lib
    USE mo_parallel_config, ONLY: nproma
    TYPE(t_patch), INTENT(IN) :: p_patch
    INTEGER, INTENT(IN) :: i_blk
    INTEGER, INTENT(IN) :: i_startblk
    INTEGER, INTENT(IN) :: i_endblk
    INTEGER, INTENT(IN) :: irl_start
    INTEGER, OPTIONAL, INTENT(IN) :: opt_rl_end
    INTEGER, INTENT(OUT) :: i_startidx, i_endidx
    INTEGER :: irl_end, i_startidx_in, i_endidx_in
    i_startidx_in = p_patch % cells % start_index(irl_start)
    irl_end = opt_rl_end
    i_endidx_in = p_patch % cells % end_index(irl_end)
    CALL get_indices_c_lib(i_startidx_in, i_endidx_in, nproma, i_blk, i_startblk, i_endblk, i_startidx, i_endidx)
  END SUBROUTINE get_indices_c
  SUBROUTINE get_indices_e(p_patch, i_blk, i_startblk, i_endblk, i_startidx, i_endidx, irl_start, opt_rl_end)
    USE mo_model_domain, ONLY: t_patch
    USE fake_mo_lib_loopindices, ONLY: get_indices_e_lib
    USE mo_parallel_config, ONLY: nproma
    TYPE(t_patch), INTENT(IN) :: p_patch
    INTEGER, INTENT(IN) :: i_blk
    INTEGER, INTENT(IN) :: i_startblk
    INTEGER, INTENT(IN) :: i_endblk
    INTEGER, INTENT(IN) :: irl_start
    INTEGER, OPTIONAL, INTENT(IN) :: opt_rl_end
    INTEGER, INTENT(OUT) :: i_startidx, i_endidx
    INTEGER :: irl_end, i_startidx_in, i_endidx_in
    i_startidx_in = p_patch % edges % start_index(irl_start)
    irl_end = opt_rl_end
    i_endidx_in = p_patch % edges % end_index(irl_end)
    CALL get_indices_e_lib(i_startidx_in, i_endidx_in, nproma, i_blk, i_startblk, i_endblk, i_startidx, i_endidx)
  END SUBROUTINE get_indices_e
  SUBROUTINE get_indices_v(p_patch, i_blk, i_startblk, i_endblk, i_startidx, i_endidx, irl_start, opt_rl_end)
    USE mo_model_domain, ONLY: t_patch
    USE fake_mo_lib_loopindices, ONLY: get_indices_v_lib
    USE mo_parallel_config, ONLY: nproma
    TYPE(t_patch), INTENT(IN) :: p_patch
    INTEGER, INTENT(IN) :: i_blk
    INTEGER, INTENT(IN) :: i_startblk
    INTEGER, INTENT(IN) :: i_endblk
    INTEGER, INTENT(IN) :: irl_start
    INTEGER, OPTIONAL, INTENT(IN) :: opt_rl_end
    INTEGER, INTENT(OUT) :: i_startidx, i_endidx
    INTEGER :: irl_end, i_startidx_in, i_endidx_in
    i_startidx_in = p_patch % verts % start_index(2)
    irl_end = (- 5)
    i_endidx_in = p_patch % verts % end_index(- 5)
    CALL get_indices_v_lib(i_startidx_in, i_endidx_in, nproma, i_blk, i_startblk, i_endblk, i_startidx, i_endidx)
  END SUBROUTINE get_indices_v
END MODULE fake_mo_loopindices
MODULE fake_mo_math_divrot
  IMPLICIT NONE
  CONTAINS
  SUBROUTINE rot_vertex_ri(vec_e, ptr_patch, ptr_int, rot_vec, opt_slev, opt_elev, opt_rlend, opt_acc_async)
    USE mo_model_domain, ONLY: t_patch
    USE mo_intp_data_strc, ONLY: t_int_state
    USE fake_mo_loopindices, ONLY: get_indices_v
    TYPE(t_patch), TARGET, INTENT(IN) :: ptr_patch
    TYPE(t_int_state), INTENT(IN) :: ptr_int
    REAL(KIND = 8), INTENT(IN) :: vec_e(:, :, :)
    INTEGER, INTENT(IN), OPTIONAL :: opt_slev
    INTEGER, INTENT(IN), OPTIONAL :: opt_elev
    INTEGER, INTENT(IN), OPTIONAL :: opt_rlend
    LOGICAL, INTENT(IN), OPTIONAL :: opt_acc_async
    REAL(KIND = 8), INTENT(INOUT) :: rot_vec(:, :, :)
    INTEGER :: slev, elev
    INTEGER :: jv, jk, jb
    INTEGER :: rl_start, rl_end
    INTEGER :: i_startblk, i_endblk, i_startidx, i_endidx
    slev = 1
    elev = UBOUND(vec_e, 2)
    rl_start = 2
    rl_end = (- 5)
    i_startblk = ptr_patch % verts % start_block(2)
    i_endblk = ptr_patch % verts % end_block(- 5)
    DO jb = i_startblk, i_endblk
      CALL get_indices_v(ptr_patch, jb, i_startblk, i_endblk, i_startidx, i_endidx, 2, - 5)
      DO jk = slev, elev
        DO jv = i_startidx, i_endidx
          rot_vec(jv, jk, jb) = vec_e(ptr_patch % verts % edge_idx(jv, jb, 1), jk, ptr_patch % verts % edge_blk(jv, jb, 1)) * ptr_int % geofac_rot(jv, 1, jb) + vec_e(ptr_patch % verts % edge_idx(jv, jb, 2), jk, ptr_patch % verts % edge_blk(jv, jb, 2)) * ptr_int % geofac_rot(jv, 2, jb) + vec_e(ptr_patch % verts % edge_idx(jv, jb, 3), jk, ptr_patch % verts % edge_blk(jv, jb, 3)) * ptr_int % geofac_rot(jv, 3, jb) + vec_e(ptr_patch % verts % edge_idx(jv, jb, 4), jk, ptr_patch % verts % edge_blk(jv, jb, 4)) * ptr_int % geofac_rot(jv, 4, jb) + vec_e(ptr_patch % verts % edge_idx(jv, jb, 5), jk, ptr_patch % verts % edge_blk(jv, jb, 5)) * ptr_int % geofac_rot(jv, 5, jb) + vec_e(ptr_patch % verts % edge_idx(jv, jb, 6), jk, ptr_patch % verts % edge_blk(jv, jb, 6)) * ptr_int % geofac_rot(jv, 6, jb)
        END DO
      END DO
    END DO
  END SUBROUTINE rot_vertex_ri
END MODULE fake_mo_math_divrot
MODULE fake_mo_math_gradients
  IMPLICIT NONE
  CONTAINS
  SUBROUTINE grad_green_gauss_cell_dycore(p_ccpr, ptr_patch, ptr_int, p_grad, opt_slev, opt_elev, opt_rlstart, opt_rlend, opt_acc_async)
    USE mo_model_domain, ONLY: t_patch
    USE mo_intp_data_strc, ONLY: t_int_state
    USE fake_mo_loopindices, ONLY: get_indices_c
    TYPE(t_patch), TARGET, INTENT(IN) :: ptr_patch
    TYPE(t_int_state), TARGET, INTENT(IN) :: ptr_int
    REAL(KIND = 8), INTENT(IN) :: p_ccpr(:, :, :, :)
    INTEGER, INTENT(IN), OPTIONAL :: opt_slev
    INTEGER, INTENT(IN), OPTIONAL :: opt_elev
    INTEGER, INTENT(IN), OPTIONAL :: opt_rlstart, opt_rlend
    LOGICAL, INTENT(IN), OPTIONAL :: opt_acc_async
    REAL(KIND = 8), INTENT(INOUT) :: p_grad(:, :, :, :)
    INTEGER :: slev, elev
    INTEGER :: jc, jk, jb
    INTEGER :: rl_start, rl_end
    INTEGER :: i_startblk, i_endblk, i_startidx, i_endidx, i_nchdom
    slev = 1
    elev = UBOUND(p_ccpr, 3)
    rl_start = 3
    rl_end = (- 5)
    i_nchdom = MAX(1, ptr_patch % n_childdom)
    i_startblk = ptr_patch % cells % start_blk(3, 1)
    i_endblk = ptr_patch % cells % end_blk(- 5, i_nchdom)
    DO jb = i_startblk, i_endblk
      CALL get_indices_c(ptr_patch, jb, i_startblk, i_endblk, i_startidx, i_endidx, 3, - 5)
      DO jk = slev, elev
        DO jc = i_startidx, i_endidx
          p_grad(1, jc, jk, jb) = ptr_int % geofac_grg(jc, 1, jb, 1) * p_ccpr(1, jc, jk, jb) + ptr_int % geofac_grg(jc, 2, jb, 1) * p_ccpr(1, ptr_patch % cells % neighbor_idx(jc, jb, 1), jk, ptr_patch % cells % neighbor_blk(jc, jb, 1)) + ptr_int % geofac_grg(jc, 3, jb, 1) * p_ccpr(1, ptr_patch % cells % neighbor_idx(jc, jb, 2), jk, ptr_patch % cells % neighbor_blk(jc, jb, 2)) + ptr_int % geofac_grg(jc, 4, jb, 1) * p_ccpr(1, ptr_patch % cells % neighbor_idx(jc, jb, 3), jk, ptr_patch % cells % neighbor_blk(jc, jb, 3))
          p_grad(2, jc, jk, jb) = ptr_int % geofac_grg(jc, 1, jb, 2) * p_ccpr(1, jc, jk, jb) + ptr_int % geofac_grg(jc, 2, jb, 2) * p_ccpr(1, ptr_patch % cells % neighbor_idx(jc, jb, 1), jk, ptr_patch % cells % neighbor_blk(jc, jb, 1)) + ptr_int % geofac_grg(jc, 3, jb, 2) * p_ccpr(1, ptr_patch % cells % neighbor_idx(jc, jb, 2), jk, ptr_patch % cells % neighbor_blk(jc, jb, 2)) + ptr_int % geofac_grg(jc, 4, jb, 2) * p_ccpr(1, ptr_patch % cells % neighbor_idx(jc, jb, 3), jk, ptr_patch % cells % neighbor_blk(jc, jb, 3))
          p_grad(3, jc, jk, jb) = ptr_int % geofac_grg(jc, 1, jb, 1) * p_ccpr(2, jc, jk, jb) + ptr_int % geofac_grg(jc, 2, jb, 1) * p_ccpr(2, ptr_patch % cells % neighbor_idx(jc, jb, 1), jk, ptr_patch % cells % neighbor_blk(jc, jb, 1)) + ptr_int % geofac_grg(jc, 3, jb, 1) * p_ccpr(2, ptr_patch % cells % neighbor_idx(jc, jb, 2), jk, ptr_patch % cells % neighbor_blk(jc, jb, 2)) + ptr_int % geofac_grg(jc, 4, jb, 1) * p_ccpr(2, ptr_patch % cells % neighbor_idx(jc, jb, 3), jk, ptr_patch % cells % neighbor_blk(jc, jb, 3))
          p_grad(4, jc, jk, jb) = ptr_int % geofac_grg(jc, 1, jb, 2) * p_ccpr(2, jc, jk, jb) + ptr_int % geofac_grg(jc, 2, jb, 2) * p_ccpr(2, ptr_patch % cells % neighbor_idx(jc, jb, 1), jk, ptr_patch % cells % neighbor_blk(jc, jb, 1)) + ptr_int % geofac_grg(jc, 3, jb, 2) * p_ccpr(2, ptr_patch % cells % neighbor_idx(jc, jb, 2), jk, ptr_patch % cells % neighbor_blk(jc, jb, 2)) + ptr_int % geofac_grg(jc, 4, jb, 2) * p_ccpr(2, ptr_patch % cells % neighbor_idx(jc, jb, 3), jk, ptr_patch % cells % neighbor_blk(jc, jb, 3))
        END DO
      END DO
    END DO
  END SUBROUTINE grad_green_gauss_cell_dycore
END MODULE fake_mo_math_gradients
MODULE mo_prepadv_types
  IMPLICIT NONE
  TYPE :: t_prepare_adv
    REAL(KIND = 8), POINTER, CONTIGUOUS :: mass_flx_me(:, :, :), mass_flx_ic(:, :, :), vol_flx_ic(:, :, :), vn_traj(:, :, :)
  END TYPE t_prepare_adv
END MODULE mo_prepadv_types
MODULE mo_run_config
  IMPLICIT NONE
  LOGICAL :: lvert_nest
  INTEGER :: timers_level
  CONTAINS
END MODULE mo_run_config
MODULE mo_timer
  IMPLICIT NONE
  INTEGER :: timer_solve_nh_veltend, timer_solve_nh_cellcomp, timer_solve_nh_edgecomp, timer_solve_nh_vnupd, timer_solve_nh_vimpl
  INTEGER :: timer_intp
  CONTAINS
END MODULE mo_timer
MODULE fake_mo_icon_interpolation_scalar
  IMPLICIT NONE
  CONTAINS
  SUBROUTINE cells2verts_scalar_dp(p_cell_in, ptr_patch, c_int, p_vert_out, opt_slev, opt_elev, opt_rlstart, opt_rlend, opt_acc_async)
    USE mo_model_domain, ONLY: t_patch
    USE mo_run_config, ONLY: timers_level
    USE fake_mo_real_timer, ONLY: timer_start, timer_stop
    USE mo_timer, ONLY: timer_intp
    USE fake_mo_lib_interpolation_scalar, ONLY: cells2verts_scalar_dp_lib_deconiface_4 => cells2verts_scalar_dp_lib
    USE mo_parallel_config, ONLY: nproma
    USE mo_mpi, ONLY: i_am_accel_node
    TYPE(t_patch), TARGET, INTENT(IN) :: ptr_patch
    REAL(KIND = 8), INTENT(IN) :: p_cell_in(:, :, :)
    REAL(KIND = 8), INTENT(IN) :: c_int(:, :, :)
    INTEGER, INTENT(IN), OPTIONAL :: opt_slev
    INTEGER, INTENT(IN), OPTIONAL :: opt_elev
    INTEGER, INTENT(IN), OPTIONAL :: opt_rlstart, opt_rlend
    LOGICAL, INTENT(IN), OPTIONAL :: opt_acc_async
    REAL(KIND = 8), INTENT(INOUT) :: p_vert_out(:, :, :)
    INTEGER :: slev, elev
    INTEGER :: rl_start, rl_end
    INTEGER :: i_startblk, i_endblk, i_startidx_in, i_endidx_in
    slev = 1
    elev = UBOUND(p_cell_in, 2)
    rl_start = 2
    rl_end = (- 5)
    i_startblk = ptr_patch % verts % start_block(2)
    i_endblk = ptr_patch % verts % end_block(- 5)
    i_startidx_in = ptr_patch % verts % start_index(2)
    i_endidx_in = ptr_patch % verts % end_index(- 5)
    IF (timers_level > 10) CALL timer_start(timer_intp)
    CALL cells2verts_scalar_dp_lib_deconiface_4(p_cell_in, ptr_patch % verts % cell_idx, ptr_patch % verts % cell_blk, c_int, p_vert_out, i_startblk, i_endblk, i_startidx_in, i_endidx_in, 1, elev, nproma, lacc = i_am_accel_node, acc_async = opt_acc_async)
    IF (timers_level > 10) CALL timer_stop(timer_intp)
  END SUBROUTINE cells2verts_scalar_dp
  SUBROUTINE cells2verts_scalar_ri(p_cell_in, ptr_patch, c_int, p_vert_out, opt_slev, opt_elev, opt_rlstart, opt_rlend, opt_acc_async)
    USE mo_model_domain, ONLY: t_patch
    USE mo_run_config, ONLY: timers_level
    USE fake_mo_real_timer, ONLY: timer_start, timer_stop
    USE mo_timer, ONLY: timer_intp
    USE fake_mo_lib_interpolation_scalar, ONLY: cells2verts_scalar_ri_lib
    USE mo_parallel_config, ONLY: nproma
    USE mo_mpi, ONLY: i_am_accel_node
    TYPE(t_patch), TARGET, INTENT(IN) :: ptr_patch
    REAL(KIND = 8), INTENT(IN) :: p_cell_in(:, :, :)
    REAL(KIND = 8), INTENT(IN) :: c_int(:, :, :)
    INTEGER, INTENT(IN), OPTIONAL :: opt_slev
    INTEGER, INTENT(IN), OPTIONAL :: opt_elev
    INTEGER, INTENT(IN), OPTIONAL :: opt_rlstart, opt_rlend
    REAL(KIND = 8), INTENT(INOUT) :: p_vert_out(:, :, :)
    LOGICAL, INTENT(IN), OPTIONAL :: opt_acc_async
    INTEGER :: slev, elev
    INTEGER :: rl_start, rl_end
    INTEGER :: i_startblk, i_endblk, i_startidx_in, i_endidx_in
    slev = 1
    elev = UBOUND(p_cell_in, 2)
    rl_start = 2
    rl_end = (- 5)
    i_startblk = ptr_patch % verts % start_block(2)
    i_endblk = ptr_patch % verts % end_block(- 5)
    i_startidx_in = ptr_patch % verts % start_index(2)
    i_endidx_in = ptr_patch % verts % end_index(- 5)
    IF (timers_level > 10) CALL timer_start(timer_intp)
    CALL cells2verts_scalar_ri_lib(p_cell_in, ptr_patch % verts % cell_idx, ptr_patch % verts % cell_blk, c_int, p_vert_out, i_startblk, i_endblk, i_startidx_in, i_endidx_in, 1, elev, nproma, lacc = i_am_accel_node, acc_async = .TRUE.)
    IF (timers_level > 10) CALL timer_stop(timer_intp)
  END SUBROUTINE cells2verts_scalar_ri
END MODULE fake_mo_icon_interpolation_scalar
MODULE mo_vertical_grid
  IMPLICIT NONE
  INTEGER :: nrdmax(10), nflat_gradp(10)
  CONTAINS
END MODULE mo_vertical_grid
MODULE fake_mo_velocity_advection
  IMPLICIT NONE
  CONTAINS
  SUBROUTINE velocity_tendencies(p_prog, p_patch, p_int, p_metrics, p_diag, z_w_concorr_me, z_kin_hor_e, z_vt_ie, ntnd, istep, lvn_only, dtime, dt_linintp_ubc, ldeepatmo)
    USE mo_model_domain, ONLY: t_patch
    USE mo_intp_data_strc, ONLY: t_int_state
    USE mo_nonhydro_types, ONLY: t_nh_diag, t_nh_metrics, t_nh_prog
    USE mo_parallel_config, ONLY: nproma
    USE mo_run_config, ONLY: lvert_nest, timers_level
    USE fake_mo_real_timer, ONLY: timer_start, timer_stop
    USE mo_timer, ONLY: timer_solve_nh_veltend
    USE mo_vertical_grid, ONLY: nrdmax
    USE mo_init_vgrid, ONLY: nflatlev
    USE mo_nonhydrostatic_config, ONLY: lextra_diffu
    USE fake_mo_icon_interpolation_scalar, ONLY: cells2verts_scalar_ri
    USE fake_mo_math_divrot, ONLY: rot_vertex_ri
    USE fake_mo_loopindices, ONLY: get_indices_c, get_indices_e
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
    INTEGER :: jb, jk, jc, je
    INTEGER :: i_startblk, i_endblk, i_startidx, i_endidx
    INTEGER :: i_startblk_2, i_endblk_2, i_startidx_2, i_endidx_2
    INTEGER :: rl_start, rl_end, rl_start_2, rl_end_2
    REAL(KIND = 8) :: z_w_concorr_mc(nproma, p_patch % nlev)
    REAL(KIND = 8) :: z_w_con_c(nproma, p_patch % nlevp1)
    REAL(KIND = 8) :: z_w_con_c_full(nproma, p_patch % nlev, p_patch % nblks_c)
    REAL(KIND = 8) :: z_v_grad_w(nproma, p_patch % nlev, p_patch % nblks_e)
    REAL(KIND = 8) :: z_w_v(nproma, p_patch % nlevp1, p_patch % nblks_v)
    REAL(KIND = 8) :: zeta(nproma, p_patch % nlev, p_patch % nblks_v)
    REAL(KIND = 8) :: z_ekinh(nproma, p_patch % nlev, p_patch % nblks_c)
    INTEGER :: nlev, nlevp1
    LOGICAL :: l_vert_nested
    INTEGER :: jg
    REAL(KIND = 8) :: cfl_w_limit, vcfl, maxvcfl, vcflmax(p_patch % nblks_c)
    REAL(KIND = 8) :: w_con_e, scalfac_exdiff, difcoef, max_vcfl_dyn
    INTEGER :: ie, nrdmax_jg, nflatlev_jg, clip_count
    LOGICAL :: levmask(p_patch % nblks_c, p_patch % nlev), levelmask(p_patch % nlev)
    LOGICAL :: cfl_clipping(nproma, p_patch % nlevp1)
    IF (timers_level > 5) CALL timer_start(timer_solve_nh_veltend)
    IF ((lvert_nest) .AND. (p_patch % nshift > 0)) THEN
      l_vert_nested = .TRUE.
    ELSE
      l_vert_nested = .FALSE.
    END IF
    jg = p_patch % id
    nrdmax_jg = nrdmax(jg)
    nflatlev_jg = nflatlev(jg)
    nlev = p_patch % nlev
    nlevp1 = p_patch % nlevp1
    IF (lextra_diffu) THEN
      cfl_w_limit = 0.65D0 / dtime
      scalfac_exdiff = 0.05D0 / (dtime * (0.85D0 - cfl_w_limit * dtime))
    ELSE
      cfl_w_limit = 0.85D0 / dtime
      scalfac_exdiff = 0.0D0
    END IF
    IF (.NOT. lvn_only) CALL cells2verts_scalar_ri(p_prog % w, p_patch, p_int % cells_aw_verts, z_w_v, opt_rlend = - 5, opt_acc_async = .TRUE.)
    CALL rot_vertex_ri(p_prog % vn, p_patch, p_int, zeta, opt_rlend = - 5, opt_acc_async = .TRUE.)
    IF (istep == 1) THEN
      rl_start = 5
      rl_end = (- 10)
      i_startblk = p_patch % edges % start_block(5)
      i_endblk = p_patch % edges % end_block(- 10)
      DO jb = i_startblk, i_endblk
        CALL get_indices_e(p_patch, jb, i_startblk, i_endblk, i_startidx, i_endidx, 5, - 10)
        DO jk = 1, nlev
          DO je = i_startidx, i_endidx
            p_diag % vt(je, jk, jb) = p_int % rbf_vec_coeff_e(1, je, jb) * p_prog % vn(p_patch % edges % quad_idx(je, jb, 1), jk, p_patch % edges % quad_blk(je, jb, 1)) + p_int % rbf_vec_coeff_e(2, je, jb) * p_prog % vn(p_patch % edges % quad_idx(je, jb, 2), jk, p_patch % edges % quad_blk(je, jb, 2)) + p_int % rbf_vec_coeff_e(3, je, jb) * p_prog % vn(p_patch % edges % quad_idx(je, jb, 3), jk, p_patch % edges % quad_blk(je, jb, 3)) + p_int % rbf_vec_coeff_e(4, je, jb) * p_prog % vn(p_patch % edges % quad_idx(je, jb, 4), jk, p_patch % edges % quad_blk(je, jb, 4))
          END DO
        END DO
        DO jk = 2, nlev
          DO je = i_startidx, i_endidx
            p_diag % vn_ie(je, jk, jb) = p_metrics % wgtfac_e(je, jk, jb) * p_prog % vn(je, jk, jb) + (1.0D0 - p_metrics % wgtfac_e(je, jk, jb)) * p_prog % vn(je, jk - 1, jb)
            z_kin_hor_e(je, jk, jb) = 0.5D0 * (p_prog % vn(je, jk, jb) ** 2 + p_diag % vt(je, jk, jb) ** 2)
          END DO
        END DO
        IF (.NOT. lvn_only) THEN
          DO jk = 2, nlev
            DO je = i_startidx, i_endidx
              z_vt_ie(je, jk, jb) = p_metrics % wgtfac_e(je, jk, jb) * p_diag % vt(je, jk, jb) + (1.0D0 - p_metrics % wgtfac_e(je, jk, jb)) * p_diag % vt(je, jk - 1, jb)
            END DO
          END DO
        END IF
        DO jk = nflatlev_jg, nlev
          DO je = i_startidx, i_endidx
            z_w_concorr_me(je, jk, jb) = p_prog % vn(je, jk, jb) * p_metrics % ddxn_z_full(je, jk, jb) + p_diag % vt(je, jk, jb) * p_metrics % ddxt_z_full(je, jk, jb)
          END DO
        END DO
        IF (.NOT. l_vert_nested) THEN
          DO je = i_startidx, i_endidx
            p_diag % vn_ie(je, 1, jb) = p_prog % vn(je, 1, jb)
            z_vt_ie(je, 1, jb) = p_diag % vt(je, 1, jb)
            z_kin_hor_e(je, 1, jb) = 0.5D0 * (p_prog % vn(je, 1, jb) ** 2 + p_diag % vt(je, 1, jb) ** 2)
            p_diag % vn_ie(je, nlevp1, jb) = p_metrics % wgtfacq_e(je, 1, jb) * p_prog % vn(je, nlev, jb) + p_metrics % wgtfacq_e(je, 2, jb) * p_prog % vn(je, nlev - 1, jb) + p_metrics % wgtfacq_e(je, 3, jb) * p_prog % vn(je, nlev - 2, jb)
          END DO
        ELSE
          DO je = i_startidx, i_endidx
            p_diag % vn_ie(je, 1, jb) = p_diag % vn_ie_ubc(je, 1, jb) + dt_linintp_ubc * p_diag % vn_ie_ubc(je, 2, jb)
            z_vt_ie(je, 1, jb) = p_diag % vt(je, 1, jb)
            z_kin_hor_e(je, 1, jb) = 0.5D0 * (p_prog % vn(je, 1, jb) ** 2 + p_diag % vt(je, 1, jb) ** 2)
            p_diag % vn_ie(je, nlevp1, jb) = p_metrics % wgtfacq_e(je, 1, jb) * p_prog % vn(je, nlev, jb) + p_metrics % wgtfacq_e(je, 2, jb) * p_prog % vn(je, nlev - 1, jb) + p_metrics % wgtfacq_e(je, 3, jb) * p_prog % vn(je, nlev - 2, jb)
          END DO
        END IF
      END DO
    END IF
    rl_start = 7
    rl_end = (- 9)
    i_startblk = p_patch % edges % start_block(7)
    i_endblk = p_patch % edges % end_block(- 9)
    IF (.NOT. lvn_only) THEN
      DO jb = i_startblk, i_endblk
        CALL get_indices_e(p_patch, jb, i_startblk, i_endblk, i_startidx, i_endidx, 7, - 9)
        DO jk = 1, nlev
          DO je = i_startidx, i_endidx
            z_v_grad_w(je, jk, jb) = p_diag % vn_ie(je, jk, jb) * p_patch % edges % inv_dual_edge_length(je, jb) * (p_prog % w(p_patch % edges % cell_idx(je, jb, 1), jk, p_patch % edges % cell_blk(je, jb, 1)) - p_prog % w(p_patch % edges % cell_idx(je, jb, 2), jk, p_patch % edges % cell_blk(je, jb, 2))) + z_vt_ie(je, jk, jb) * p_patch % edges % inv_primal_edge_length(je, jb) * p_patch % edges % tangent_orientation(je, jb) * (z_w_v(p_patch % edges % vertex_idx(je, jb, 1), jk, p_patch % edges % vertex_blk(je, jb, 1)) - z_w_v(p_patch % edges % vertex_idx(je, jb, 2), jk, p_patch % edges % vertex_blk(je, jb, 2)))
          END DO
        END DO
      END DO
    END IF
    IF (.NOT. lvn_only .AND. ldeepatmo) THEN
      DO jb = i_startblk, i_endblk
        CALL get_indices_e(p_patch, jb, i_startblk, i_endblk, i_startidx, i_endidx, 7, - 9)
        DO jk = 1, nlev
          DO je = i_startidx, i_endidx
            z_v_grad_w(je, jk, jb) = z_v_grad_w(je, jk, jb) * p_metrics % deepatmo_gradh_ifc(jk) + p_diag % vn_ie(je, jk, jb) * (p_diag % vn_ie(je, jk, jb) * p_metrics % deepatmo_invr_ifc(jk) - p_patch % edges % ft_e(je, jb)) + z_vt_ie(je, jk, jb) * (z_vt_ie(je, jk, jb) * p_metrics % deepatmo_invr_ifc(jk) + p_patch % edges % fn_e(je, jb))
          END DO
        END DO
      END DO
    END IF
    rl_start = 4
    rl_end = (- 5)
    i_startblk = p_patch % cells % start_block(4)
    i_endblk = p_patch % cells % end_block(- 5)
    rl_start_2 = 5
    rl_end_2 = (- 4)
    i_startblk_2 = p_patch % cells % start_block(5)
    i_endblk_2 = p_patch % cells % end_block(- 4)
    DO jb = i_startblk, i_endblk
      CALL get_indices_c(p_patch, jb, i_startblk, i_endblk, i_startidx, i_endidx, 4, - 5)
      DO jk = 1, nlev
        DO jc = i_startidx, i_endidx
          z_ekinh(jc, jk, jb) = p_int % e_bln_c_s(jc, 1, jb) * z_kin_hor_e(p_patch % cells % edge_idx(jc, jb, 1), jk, p_patch % cells % edge_blk(jc, jb, 1)) + p_int % e_bln_c_s(jc, 2, jb) * z_kin_hor_e(p_patch % cells % edge_idx(jc, jb, 2), jk, p_patch % cells % edge_blk(jc, jb, 2)) + p_int % e_bln_c_s(jc, 3, jb) * z_kin_hor_e(p_patch % cells % edge_idx(jc, jb, 3), jk, p_patch % cells % edge_blk(jc, jb, 3))
        END DO
      END DO
      IF (istep == 1) THEN
        DO jk = nflatlev_jg, nlev
          DO jc = i_startidx, i_endidx
            z_w_concorr_mc(jc, jk) = p_int % e_bln_c_s(jc, 1, jb) * z_w_concorr_me(p_patch % cells % edge_idx(jc, jb, 1), jk, p_patch % cells % edge_blk(jc, jb, 1)) + p_int % e_bln_c_s(jc, 2, jb) * z_w_concorr_me(p_patch % cells % edge_idx(jc, jb, 2), jk, p_patch % cells % edge_blk(jc, jb, 2)) + p_int % e_bln_c_s(jc, 3, jb) * z_w_concorr_me(p_patch % cells % edge_idx(jc, jb, 3), jk, p_patch % cells % edge_blk(jc, jb, 3))
          END DO
        END DO
        DO jk = nflatlev_jg + 1, nlev
          DO jc = i_startidx, i_endidx
            p_diag % w_concorr_c(jc, jk, jb) = p_metrics % wgtfac_c(jc, jk, jb) * z_w_concorr_mc(jc, jk) + (1.0D0 - p_metrics % wgtfac_c(jc, jk, jb)) * z_w_concorr_mc(jc, jk - 1)
          END DO
        END DO
      END IF
      DO jk = 1, nlev
        DO jc = i_startidx, i_endidx
          z_w_con_c(jc, jk) = p_prog % w(jc, jk, jb)
        END DO
      END DO
      DO jc = i_startidx, i_endidx
        z_w_con_c(jc, nlevp1) = 0.0D0
      END DO
      DO jk = nlev, nflatlev_jg + 1, - 1
        DO jc = i_startidx, i_endidx
          z_w_con_c(jc, jk) = z_w_con_c(jc, jk) - p_diag % w_concorr_c(jc, jk, jb)
        END DO
      END DO
      DO jk = MAX(3, nrdmax_jg - 2), nlev - 3
        levmask(jb, jk) = .FALSE.
      END DO
      maxvcfl = 0
      DO jk = MAX(3, nrdmax_jg - 2), nlev - 3
        clip_count = 0
        DO jc = i_startidx, i_endidx
          cfl_clipping(jc, jk) = (ABS(z_w_con_c(jc, jk)) > cfl_w_limit * p_metrics % ddqz_z_half(jc, jk, jb))
          IF (cfl_clipping(jc, jk)) clip_count = clip_count + 1
        END DO
        IF (clip_count == 0) CYCLE
        DO jc = i_startidx, i_endidx
          IF (cfl_clipping(jc, jk)) THEN
            levmask(jb, jk) = .TRUE.
            vcfl = z_w_con_c(jc, jk) * dtime / p_metrics % ddqz_z_half(jc, jk, jb)
            maxvcfl = MAX(maxvcfl, ABS(vcfl))
            IF (vcfl < - 0.85D0) THEN
              z_w_con_c(jc, jk) = - 0.85D0 * p_metrics % ddqz_z_half(jc, jk, jb) / dtime
            ELSE IF (vcfl > 0.85D0) THEN
              z_w_con_c(jc, jk) = 0.85D0 * p_metrics % ddqz_z_half(jc, jk, jb) / dtime
            END IF
          END IF
        END DO
      END DO
      DO jk = 1, nlev
        DO jc = i_startidx, i_endidx
          z_w_con_c_full(jc, jk, jb) = 0.5D0 * (z_w_con_c(jc, jk) + z_w_con_c(jc, jk + 1))
        END DO
      END DO
      vcflmax(jb) = maxvcfl
      IF (lvn_only) CYCLE
      IF (jb < i_startblk_2 .OR. jb > i_endblk_2) CYCLE
      CALL get_indices_c(p_patch, jb, i_startblk_2, i_endblk_2, i_startidx_2, i_endidx_2, 5, - 4)
      DO jk = 2, nlev
        DO jc = i_startidx_2, i_endidx_2
          p_diag % ddt_w_adv_pc(jc, jk, jb, ntnd) = - z_w_con_c(jc, jk) * (p_prog % w(jc, jk - 1, jb) * p_metrics % coeff1_dwdz(jc, jk, jb) - p_prog % w(jc, jk + 1, jb) * p_metrics % coeff2_dwdz(jc, jk, jb) + p_prog % w(jc, jk, jb) * (p_metrics % coeff2_dwdz(jc, jk, jb) - p_metrics % coeff1_dwdz(jc, jk, jb)))
        END DO
      END DO
      DO jk = 2, nlev
        DO jc = i_startidx_2, i_endidx_2
          p_diag % ddt_w_adv_pc(jc, jk, jb, ntnd) = p_diag % ddt_w_adv_pc(jc, jk, jb, ntnd) + p_int % e_bln_c_s(jc, 1, jb) * z_v_grad_w(p_patch % cells % edge_idx(jc, jb, 1), jk, p_patch % cells % edge_blk(jc, jb, 1)) + p_int % e_bln_c_s(jc, 2, jb) * z_v_grad_w(p_patch % cells % edge_idx(jc, jb, 2), jk, p_patch % cells % edge_blk(jc, jb, 2)) + p_int % e_bln_c_s(jc, 3, jb) * z_v_grad_w(p_patch % cells % edge_idx(jc, jb, 3), jk, p_patch % cells % edge_blk(jc, jb, 3))
        END DO
      END DO
      IF (lextra_diffu) THEN
        DO jk = MAX(3, nrdmax_jg - 2), nlev - 3
          IF (levmask(jb, jk)) THEN
            DO jc = i_startidx_2, i_endidx_2
              IF (cfl_clipping(jc, jk) .AND. p_patch % cells % decomp_info % owner_mask(jc, jb)) THEN
                difcoef = scalfac_exdiff * MIN(0.85D0 - cfl_w_limit * dtime, ABS(z_w_con_c(jc, jk)) * dtime / p_metrics % ddqz_z_half(jc, jk, jb) - cfl_w_limit * dtime)
                p_diag % ddt_w_adv_pc(jc, jk, jb, ntnd) = p_diag % ddt_w_adv_pc(jc, jk, jb, ntnd) + difcoef * p_patch % cells % area(jc, jb) * (p_prog % w(jc, jk, jb) * p_int % geofac_n2s(jc, 1, jb) + p_prog % w(p_patch % cells % neighbor_idx(jc, jb, 1), jk, p_patch % cells % neighbor_blk(jc, jb, 1)) * p_int % geofac_n2s(jc, 2, jb) + p_prog % w(p_patch % cells % neighbor_idx(jc, jb, 2), jk, p_patch % cells % neighbor_blk(jc, jb, 2)) * p_int % geofac_n2s(jc, 3, jb) + p_prog % w(p_patch % cells % neighbor_idx(jc, jb, 3), jk, p_patch % cells % neighbor_blk(jc, jb, 3)) * p_int % geofac_n2s(jc, 4, jb))
              END IF
            END DO
          END IF
        END DO
      END IF
    END DO
    DO jk = MAX(3, nrdmax_jg - 2), nlev - 3
      levelmask(jk) = ANY(levmask(i_startblk : i_endblk, jk))
    END DO
    rl_start = 10
    rl_end = (- 8)
    i_startblk = p_patch % edges % start_block(10)
    i_endblk = p_patch % edges % end_block(- 8)
    DO jb = i_startblk, i_endblk
      CALL get_indices_e(p_patch, jb, i_startblk, i_endblk, i_startidx, i_endidx, 10, - 8)
      IF (.NOT. ldeepatmo) THEN
        DO jk = 1, nlev
          DO je = i_startidx, i_endidx
            p_diag % ddt_vn_apc_pc(je, jk, jb, ntnd) = - (z_kin_hor_e(je, jk, jb) * (p_metrics % coeff_gradekin(je, 1, jb) - p_metrics % coeff_gradekin(je, 2, jb)) + p_metrics % coeff_gradekin(je, 2, jb) * z_ekinh(p_patch % edges % cell_idx(je, jb, 2), jk, p_patch % edges % cell_blk(je, jb, 2)) - p_metrics % coeff_gradekin(je, 1, jb) * z_ekinh(p_patch % edges % cell_idx(je, jb, 1), jk, p_patch % edges % cell_blk(je, jb, 1)) + p_diag % vt(je, jk, jb) * (p_patch % edges % f_e(je, jb) + 0.5D0 * (zeta(p_patch % edges % vertex_idx(je, jb, 1), jk, p_patch % edges % vertex_blk(je, jb, 1)) + zeta(p_patch % edges % vertex_idx(je, jb, 2), jk, p_patch % edges % vertex_blk(je, jb, 2)))) + (p_int % c_lin_e(je, 1, jb) * z_w_con_c_full(p_patch % edges % cell_idx(je, jb, 1), jk, p_patch % edges % cell_blk(je, jb, 1)) + p_int % c_lin_e(je, 2, jb) * z_w_con_c_full(p_patch % edges % cell_idx(je, jb, 2), jk, p_patch % edges % cell_blk(je, jb, 2))) * (p_diag % vn_ie(je, jk, jb) - p_diag % vn_ie(je, jk + 1, jb)) / p_metrics % ddqz_z_full_e(je, jk, jb))
          END DO
        END DO
        IF (p_diag % ddt_vn_adv_is_associated .OR. p_diag % ddt_vn_cor_is_associated) THEN
          DO jk = 1, nlev
            DO je = i_startidx, i_endidx
              p_diag % ddt_vn_cor_pc(je, jk, jb, ntnd) = - p_diag % vt(je, jk, jb) * p_patch % edges % f_e(je, jb)
            END DO
          END DO
        END IF
      ELSE
        DO jk = 1, nlev
          DO je = i_startidx, i_endidx
            p_diag % ddt_vn_apc_pc(je, jk, jb, ntnd) = - ((z_kin_hor_e(je, jk, jb) * (p_metrics % coeff_gradekin(je, 1, jb) - p_metrics % coeff_gradekin(je, 2, jb)) + p_metrics % coeff_gradekin(je, 2, jb) * z_ekinh(p_patch % edges % cell_idx(je, jb, 2), jk, p_patch % edges % cell_blk(je, jb, 2)) - p_metrics % coeff_gradekin(je, 1, jb) * z_ekinh(p_patch % edges % cell_idx(je, jb, 1), jk, p_patch % edges % cell_blk(je, jb, 1))) * p_metrics % deepatmo_gradh_mc(jk) + p_diag % vt(je, jk, jb) * (p_patch % edges % f_e(je, jb) + 0.5D0 * (zeta(p_patch % edges % vertex_idx(je, jb, 1), jk, p_patch % edges % vertex_blk(je, jb, 1)) + zeta(p_patch % edges % vertex_idx(je, jb, 2), jk, p_patch % edges % vertex_blk(je, jb, 2))) * p_metrics % deepatmo_gradh_mc(jk)) + (p_int % c_lin_e(je, 1, jb) * z_w_con_c_full(p_patch % edges % cell_idx(je, jb, 1), jk, p_patch % edges % cell_blk(je, jb, 1)) + p_int % c_lin_e(je, 2, jb) * z_w_con_c_full(p_patch % edges % cell_idx(je, jb, 2), jk, p_patch % edges % cell_blk(je, jb, 2))) * ((p_diag % vn_ie(je, jk, jb) - p_diag % vn_ie(je, jk + 1, jb)) / p_metrics % ddqz_z_full_e(je, jk, jb) + p_prog % vn(je, jk, jb) * p_metrics % deepatmo_invr_mc(jk) - p_patch % edges % ft_e(je, jb)))
          END DO
        END DO
        IF (p_diag % ddt_vn_adv_is_associated .OR. p_diag % ddt_vn_cor_is_associated) THEN
          DO jk = 1, nlev
            DO je = i_startidx, i_endidx
              p_diag % ddt_vn_cor_pc(je, jk, jb, ntnd) = - (+ p_diag % vt(je, jk, jb) * (p_patch % edges % f_e(je, jb)) + (p_int % c_lin_e(je, 1, jb) * z_w_con_c_full(p_patch % edges % cell_idx(je, jb, 1), jk, p_patch % edges % cell_blk(je, jb, 1)) + p_int % c_lin_e(je, 2, jb) * z_w_con_c_full(p_patch % edges % cell_idx(je, jb, 2), jk, p_patch % edges % cell_blk(je, jb, 2))) * (- p_patch % edges % ft_e(je, jb)))
            END DO
          END DO
        END IF
      END IF
      IF (lextra_diffu) THEN
        ie = 0
        DO jk = MAX(3, nrdmax_jg - 2), nlev - 4
          IF (levelmask(jk) .OR. levelmask(jk + 1)) THEN
            DO je = i_startidx, i_endidx
              w_con_e = p_int % c_lin_e(je, 1, jb) * z_w_con_c_full(p_patch % edges % cell_idx(je, jb, 1), jk, p_patch % edges % cell_blk(je, jb, 1)) + p_int % c_lin_e(je, 2, jb) * z_w_con_c_full(p_patch % edges % cell_idx(je, jb, 2), jk, p_patch % edges % cell_blk(je, jb, 2))
              IF (ABS(w_con_e) > cfl_w_limit * p_metrics % ddqz_z_full_e(je, jk, jb)) THEN
                difcoef = scalfac_exdiff * MIN(0.85D0 - cfl_w_limit * dtime, ABS(w_con_e) * dtime / p_metrics % ddqz_z_full_e(je, jk, jb) - cfl_w_limit * dtime)
                p_diag % ddt_vn_apc_pc(je, jk, jb, ntnd) = p_diag % ddt_vn_apc_pc(je, jk, jb, ntnd) + difcoef * p_patch % edges % area_edge(je, jb) * (p_int % geofac_grdiv(je, 1, jb) * p_prog % vn(je, jk, jb) + p_int % geofac_grdiv(je, 2, jb) * p_prog % vn(p_patch % edges % quad_idx(je, jb, 1), jk, p_patch % edges % quad_blk(je, jb, 1)) + p_int % geofac_grdiv(je, 3, jb) * p_prog % vn(p_patch % edges % quad_idx(je, jb, 2), jk, p_patch % edges % quad_blk(je, jb, 2)) + p_int % geofac_grdiv(je, 4, jb) * p_prog % vn(p_patch % edges % quad_idx(je, jb, 3), jk, p_patch % edges % quad_blk(je, jb, 3)) + p_int % geofac_grdiv(je, 5, jb) * p_prog % vn(p_patch % edges % quad_idx(je, jb, 4), jk, p_patch % edges % quad_blk(je, jb, 4)) + p_patch % edges % tangent_orientation(je, jb) * p_patch % edges % inv_primal_edge_length(je, jb) * (zeta(p_patch % edges % vertex_idx(je, jb, 2), jk, p_patch % edges % vertex_blk(je, jb, 2)) - zeta(p_patch % edges % vertex_idx(je, jb, 1), jk, p_patch % edges % vertex_blk(je, jb, 1))))
              END IF
            END DO
          END IF
        END DO
      END IF
    END DO
    i_startblk = p_patch % cells % start_block(4)
    i_endblk = p_patch % cells % end_block(- 4)
    max_vcfl_dyn = MAX(p_diag % max_vcfl_dyn, MAXVAL(vcflmax(i_startblk : i_endblk)))
    p_diag % max_vcfl_dyn = max_vcfl_dyn
    IF (timers_level > 5) CALL timer_stop(timer_solve_nh_veltend)
  END SUBROUTINE velocity_tendencies
END MODULE fake_mo_velocity_advection
MODULE fake_mo_solve_nonhydro
  IMPLICIT NONE
  CONTAINS
  SUBROUTINE solve_nh_predictor_pre(p_nh, p_nh_prog_nnow, p_nh_prog_nnew, p_patch, p_int, prep_adv, nnow, nnew, l_init, l_recompute, lsave_mflx, lprep_adv, lclean_mflx, idyn_timestep, jstep, dtime, lacc, jb, jk, jc, je, jks, jg, nlev, nlevp1, i_startblk, i_endblk, i_startidx, i_endidx, ishift, rl_start, rl_end, istep, ntl1, ntl2, nvar, nshift, nshift_total, z_theta_v_fl_e, z_theta_v_e, z_rho_e, z_theta_v_v, z_rho_v, z_th_ddz_exner_c, z_dexner_dz_c, z_vt_ie, z_kin_hor_e, z_exner_ex_pr, z_gradh_exner, z_rth_pr, z_grad_rth, z_w_concorr_me, z_graddiv_vn, z_w_expl, z_vn_avg, z_mflx_top, z_contr_w_fl_l, z_rho_expl, z_exner_expl, z_theta_tavg_m1, z_theta_tavg, z_rho_tavg_m1, z_rho_tavg, z_alpha, z_beta, z_q, z_graddiv2_vn, z_theta_v_pr_ic, z_exner_ic, z_w_concorr_mc, z_flxdiv_mass, z_flxdiv_theta, z_hydro_corr, z_a, z_b, z_c, z_g, z_gamma, z_w_backtraj, z_theta_v_pr_mc_m1, z_theta_v_pr_mc, z_theta1, z_theta2, wgt_nnow_vel, wgt_nnew_vel, dt_shift, wgt_nnow_rth, wgt_nnew_rth, dthalf, r_nsubsteps, r_dtimensubsteps, scal_divdamp_o2, alin, dz32, df32, dz42, df42, bqdr, aqdr, zf, dzlin, dzqdr, dt_linintp_ubc, dt_linintp_ubc_nnow, dt_linintp_ubc_nnew, z_raylfac, z_ntdistv_bary_1, distv_bary_1, z_ntdistv_bary_2, distv_bary_2, scal_divdamp, bdy_divdamp, enh_divdamp_fac, z_dwdz_dd, z_ddt_vn_dyn, z_ddt_vn_apc, z_ddt_vn_cor, z_ddt_vn_pgr, z_ddt_vn_ray, z_d_vn_dmp, z_d_vn_iau, nproma_gradp, nblks_gradp, npromz_gradp, nlen_gradp, jk_start, lvn_only, lvn_pos, l_vert_nested, l_child_vertnest)
    USE mo_nonhydro_types, ONLY: t_nh_prog, t_nh_state
    USE mo_intp_data_strc, ONLY: t_int_state
    USE mo_model_domain, ONLY: t_patch
    USE mo_prepadv_types, ONLY: t_prepare_adv
    USE mo_parallel_config, ONLY: nproma
    USE mo_vertical_grid, ONLY: nflat_gradp, nrdmax
    USE mo_nonhydrostatic_config, ONLY: iadv_rhotheta, igradp_method, itime_scheme, kstart_dd3d, rayleigh_type
    USE fake_mo_velocity_advection, ONLY: velocity_tendencies
    USE mo_dynamics_config, ONLY: ldeepatmo
    USE fake_mo_parallel_config, ONLY: cpu_min_nproma
    USE mo_run_config, ONLY: timers_level
    USE fake_mo_real_timer, ONLY: timer_start, timer_stop
    USE mo_timer, ONLY: timer_solve_nh_cellcomp, timer_solve_nh_vnupd
    USE mo_grid_config, ONLY: l_limited_area
    USE fake_mo_fortran_tools, ONLY: init_zero_contiguous_dp
    USE fake_mo_loopindices, ONLY: get_indices_c, get_indices_e
    USE mo_init_vgrid, ONLY: nflatlev
    USE fake_mo_icon_interpolation_scalar, ONLY: cells2verts_scalar_dp_deconiface_8 => cells2verts_scalar_dp, cells2verts_scalar_dp_deconiface_9 => cells2verts_scalar_dp
    USE fake_mo_math_gradients, ONLY: grad_green_gauss_cell_dycore_deconiface_10 => grad_green_gauss_cell_dycore
    USE mo_initicon_config, ONLY: iau_wgt_dyn, is_iau_active
    USE mo_gridref_config, ONLY: grf_intmethod_e
    TYPE(t_nh_state), TARGET, INTENT(INOUT) :: p_nh
    TYPE(t_int_state), TARGET, INTENT(IN) :: p_int
    TYPE(t_patch), TARGET, INTENT(INOUT) :: p_patch
    TYPE(t_prepare_adv), TARGET, INTENT(INOUT) :: prep_adv
    TYPE(t_nh_prog), TARGET, INTENT(INOUT) :: p_nh_prog_nnow, p_nh_prog_nnew
    LOGICAL, INTENT(IN) :: l_init
    LOGICAL, INTENT(IN) :: l_recompute
    LOGICAL, INTENT(IN) :: lsave_mflx
    LOGICAL, INTENT(IN) :: lprep_adv
    LOGICAL, INTENT(IN) :: lclean_mflx
    INTEGER, INTENT(IN) :: idyn_timestep
    INTEGER, INTENT(IN) :: jstep
    INTEGER, INTENT(IN) :: nnow, nnew
    REAL(KIND = 8), INTENT(IN) :: dtime
    LOGICAL, INTENT(IN), OPTIONAL :: lacc
    INTEGER, INTENT(INOUT) :: jb, jk, jc, je, jks, jg
    INTEGER, INTENT(INOUT) :: nlev, nlevp1
    INTEGER, INTENT(INOUT) :: i_startblk, i_endblk, i_startidx, i_endidx, ishift
    INTEGER, INTENT(INOUT) :: rl_start, rl_end, istep, ntl1, ntl2, nvar, nshift, nshift_total
    INTEGER :: ic, ie, ilc0, ibc0, ikp1, ikp2
    REAL(KIND = 8), INTENT(INOUT) :: z_theta_v_fl_e(nproma, p_patch % nlev, p_patch % nblks_e), z_theta_v_e(nproma, p_patch % nlev, p_patch % nblks_e), z_rho_e(nproma, p_patch % nlev, p_patch % nblks_e), z_theta_v_v(nproma, p_patch % nlev, p_patch % nblks_v), z_rho_v(nproma, p_patch % nlev, p_patch % nblks_v)
    REAL(KIND = 8), INTENT(INOUT) :: z_th_ddz_exner_c(nproma, p_patch % nlev, p_patch % nblks_c), z_dexner_dz_c(2, nproma, p_patch % nlev, p_patch % nblks_c), z_vt_ie(nproma, p_patch % nlev, p_patch % nblks_e), z_kin_hor_e(nproma, p_patch % nlev, p_patch % nblks_e), z_exner_ex_pr(nproma, p_patch % nlevp1, p_patch % nblks_c), z_gradh_exner(nproma, p_patch % nlev, p_patch % nblks_e), z_rth_pr(2, nproma, p_patch % nlev, p_patch % nblks_c), z_grad_rth(4, nproma, p_patch % nlev, p_patch % nblks_c), z_w_concorr_me(nproma, p_patch % nlev, p_patch % nblks_e)
    REAL(KIND = 8), INTENT(INOUT) :: z_graddiv_vn(nproma, p_patch % nlev, p_patch % nblks_e)
    REAL(KIND = 8), INTENT(INOUT) :: z_w_expl(nproma, p_patch % nlevp1), z_vn_avg(nproma, p_patch % nlev), z_mflx_top(nproma, p_patch % nblks_c), z_contr_w_fl_l(nproma, p_patch % nlevp1), z_rho_expl(nproma, p_patch % nlev), z_exner_expl(nproma, p_patch % nlev)
    REAL(KIND = 8), INTENT(INOUT) :: z_theta_tavg_m1, z_theta_tavg, z_rho_tavg_m1, z_rho_tavg
    REAL(KIND = 8), INTENT(INOUT) :: z_alpha(nproma, p_patch % nlevp1), z_beta(nproma, p_patch % nlev), z_q(nproma, p_patch % nlev), z_graddiv2_vn(nproma, p_patch % nlev), z_theta_v_pr_ic(nproma, p_patch % nlevp1), z_exner_ic(nproma, p_patch % nlevp1), z_w_concorr_mc(nproma, p_patch % nlev), z_flxdiv_mass(nproma, p_patch % nlev), z_flxdiv_theta(nproma, p_patch % nlev), z_hydro_corr(nproma, p_patch % nblks_e)
    REAL(KIND = 8), INTENT(INOUT) :: z_a, z_b, z_c, z_g, z_gamma, z_w_backtraj, z_theta_v_pr_mc_m1, z_theta_v_pr_mc
    REAL(KIND = 8), INTENT(INOUT) :: z_theta1, z_theta2, wgt_nnow_vel, wgt_nnew_vel, dt_shift, wgt_nnow_rth, wgt_nnew_rth, dthalf, r_nsubsteps, r_dtimensubsteps, scal_divdamp_o2, alin, dz32, df32, dz42, df42, bqdr, aqdr, zf, dzlin, dzqdr
    REAL(KIND = 8), INTENT(INOUT) :: dt_linintp_ubc, dt_linintp_ubc_nnow, dt_linintp_ubc_nnew
    REAL(KIND = 8), INTENT(INOUT) :: z_raylfac(nrdmax(p_patch % id))
    REAL(KIND = 8), INTENT(INOUT) :: z_ntdistv_bary_1, distv_bary_1, z_ntdistv_bary_2, distv_bary_2
    REAL(KIND = 8), INTENT(INOUT), DIMENSION(p_patch % nlev) :: scal_divdamp, bdy_divdamp, enh_divdamp_fac
    REAL(KIND = 8), INTENT(INOUT) :: z_dwdz_dd(nproma, kstart_dd3d(p_patch % id) : p_patch % nlev, p_patch % nblks_c)
    REAL(KIND = 8), INTENT(INOUT) :: z_ddt_vn_dyn, z_ddt_vn_apc, z_ddt_vn_cor, z_ddt_vn_pgr, z_ddt_vn_ray, z_d_vn_dmp, z_d_vn_iau
    INTEGER, INTENT(INOUT) :: nproma_gradp, nblks_gradp, npromz_gradp, nlen_gradp, jk_start
    LOGICAL, INTENT(INOUT) :: lvn_only, lvn_pos
    LOGICAL, INTENT(INOUT) :: l_vert_nested, l_child_vertnest
    istep = 1
    IF (itime_scheme >= 6 .OR. l_init .OR. l_recompute) THEN
      IF (itime_scheme < 6 .AND. .NOT. l_init) THEN
        lvn_only = .TRUE.
      ELSE
        lvn_only = .FALSE.
      END IF
      CALL velocity_tendencies(p_nh_prog_nnow, p_patch, p_int, p_nh % metrics, p_nh % diag, z_w_concorr_me, z_kin_hor_e, z_vt_ie, ntl1, 1, lvn_only, dtime, dt_linintp_ubc_nnow, ldeepatmo)
    END IF
    nvar = nnow
    IF (.TRUE. .AND. (igradp_method == 3 .OR. igradp_method == 5)) THEN
      nproma_gradp = cpu_min_nproma(nproma, 256)
      nblks_gradp = INT(p_nh % metrics % pg_listdim / nproma_gradp)
      npromz_gradp = MOD(p_nh % metrics % pg_listdim, nproma_gradp)
      IF (npromz_gradp > 0) THEN
        nblks_gradp = nblks_gradp + 1
      ELSE
        npromz_gradp = nproma_gradp
      END IF
    END IF
    IF (timers_level > 5) CALL timer_start(timer_solve_nh_cellcomp)
    rl_start = 3
    rl_end = (- 5)
    i_startblk = p_patch % cells % start_block(3)
    i_endblk = p_patch % cells % end_block((- 5))
    IF (.TRUE. .AND. (jg > 1 .OR. l_limited_area)) THEN
      CALL init_zero_contiguous_dp(z_rth_pr(1, 1, 1, 1), 2 * nproma * nlev * i_startblk, opt_acc_async = .TRUE., lacc = .TRUE.)
    END IF
    DO jb = i_startblk, i_endblk
      CALL get_indices_c(p_patch, jb, i_startblk, i_endblk, i_startidx, i_endidx, 3, (- 5))
      DO jk = 1, nlev
        DO jc = i_startidx, i_endidx
          z_exner_ex_pr(jc, jk, jb) = (1.0D0 + p_nh % metrics % exner_exfac(jc, jk, jb)) * (p_nh_prog_nnow % exner(jc, jk, jb) - p_nh % metrics % exner_ref_mc(jc, jk, jb)) - p_nh % metrics % exner_exfac(jc, jk, jb) * p_nh % diag % exner_pr(jc, jk, jb)
          p_nh % diag % exner_pr(jc, jk, jb) = p_nh_prog_nnow % exner(jc, jk, jb) - p_nh % metrics % exner_ref_mc(jc, jk, jb)
        END DO
      END DO
      z_exner_ex_pr(:, nlevp1, jb) = 0.0D0
      IF (igradp_method <= 3) THEN
        DO jc = i_startidx, i_endidx
          z_exner_ic(jc, nlevp1) = p_nh % metrics % wgtfacq_c(jc, 1, jb) * z_exner_ex_pr(jc, nlev, jb) + p_nh % metrics % wgtfacq_c(jc, 2, jb) * z_exner_ex_pr(jc, nlev - 1, jb) + p_nh % metrics % wgtfacq_c(jc, 3, jb) * z_exner_ex_pr(jc, nlev - 2, jb)
        END DO
        DO jk = nlev, MAX(2, nflatlev(jg)), - 1
          DO jc = i_startidx, i_endidx
            z_exner_ic(jc, jk) = p_nh % metrics % wgtfac_c(jc, jk, jb) * z_exner_ex_pr(jc, jk, jb) + (1.0D0 - p_nh % metrics % wgtfac_c(jc, jk, jb)) * z_exner_ex_pr(jc, jk - 1, jb)
          END DO
        END DO
        DO jk = nlev, MAX(2, nflatlev(jg)), - 1
          DO jc = i_startidx, i_endidx
            z_dexner_dz_c(1, jc, jk, jb) = (z_exner_ic(jc, jk) - z_exner_ic(jc, jk + 1)) * p_nh % metrics % inv_ddqz_z_full(jc, jk, jb)
          END DO
        END DO
        IF (nflatlev(jg) == 1) THEN
          DO jc = i_startidx, i_endidx
            z_exner_ic(jc, 1) = p_nh % metrics % wgtfacq1_c(jc, 1, jb) * z_exner_ex_pr(jc, 1, jb) + p_nh % metrics % wgtfacq1_c(jc, 2, jb) * z_exner_ex_pr(jc, 2, jb) + p_nh % metrics % wgtfacq1_c(jc, 3, jb) * z_exner_ex_pr(jc, 3, jb)
            z_dexner_dz_c(1, jc, 1, jb) = (z_exner_ic(jc, 1) - z_exner_ic(jc, 2)) * p_nh % metrics % inv_ddqz_z_full(jc, 1, jb)
          END DO
        END IF
      END IF
      DO jc = i_startidx, i_endidx
        z_rth_pr(1, jc, 1, jb) = p_nh_prog_nnow % rho(jc, 1, jb) - p_nh % metrics % rho_ref_mc(jc, 1, jb)
        z_rth_pr(2, jc, 1, jb) = p_nh_prog_nnow % theta_v(jc, 1, jb) - p_nh % metrics % theta_ref_mc(jc, 1, jb)
      END DO
      DO jk = 2, nlev
        DO jc = i_startidx, i_endidx
          p_nh % diag % rho_ic(jc, jk, jb) = p_nh % metrics % wgtfac_c(jc, jk, jb) * p_nh_prog_nnow % rho(jc, jk, jb) + (1.0D0 - p_nh % metrics % wgtfac_c(jc, jk, jb)) * p_nh_prog_nnow % rho(jc, jk - 1, jb)
          z_rth_pr(1, jc, jk, jb) = p_nh_prog_nnow % rho(jc, jk, jb) - p_nh % metrics % rho_ref_mc(jc, jk, jb)
          z_rth_pr(2, jc, jk, jb) = p_nh_prog_nnow % theta_v(jc, jk, jb) - p_nh % metrics % theta_ref_mc(jc, jk, jb)
        END DO
      END DO
      DO jk = 2, nlev
        DO jc = i_startidx, i_endidx
          z_theta_v_pr_ic(jc, jk) = p_nh % metrics % wgtfac_c(jc, jk, jb) * z_rth_pr(2, jc, jk, jb) + (1.0D0 - p_nh % metrics % wgtfac_c(jc, jk, jb)) * z_rth_pr(2, jc, jk - 1, jb)
          p_nh % diag % theta_v_ic(jc, jk, jb) = p_nh % metrics % wgtfac_c(jc, jk, jb) * p_nh_prog_nnow % theta_v(jc, jk, jb) + (1.0D0 - p_nh % metrics % wgtfac_c(jc, jk, jb)) * p_nh_prog_nnow % theta_v(jc, jk - 1, jb)
          z_th_ddz_exner_c(jc, jk, jb) = p_nh % metrics % vwind_expl_wgt(jc, jb) * p_nh % diag % theta_v_ic(jc, jk, jb) * (p_nh % diag % exner_pr(jc, jk - 1, jb) - p_nh % diag % exner_pr(jc, jk, jb)) / p_nh % metrics % ddqz_z_half(jc, jk, jb) + z_theta_v_pr_ic(jc, jk) * p_nh % metrics % d_exner_dz_ref_ic(jc, jk, jb)
        END DO
      END DO
      DO jc = i_startidx, i_endidx
        z_theta_v_pr_ic(jc, 1) = 0.0D0
        z_theta_v_pr_ic(jc, nlevp1) = p_nh % metrics % wgtfacq_c(jc, 1, jb) * z_rth_pr(2, jc, nlev, jb) + p_nh % metrics % wgtfacq_c(jc, 2, jb) * z_rth_pr(2, jc, nlev - 1, jb) + p_nh % metrics % wgtfacq_c(jc, 3, jb) * z_rth_pr(2, jc, nlev - 2, jb)
        p_nh % diag % theta_v_ic(jc, nlevp1, jb) = p_nh % metrics % theta_ref_ic(jc, nlevp1, jb) + z_theta_v_pr_ic(jc, nlevp1)
      END DO
      IF (igradp_method <= 3) THEN
        DO jk = nflat_gradp(jg), nlev
          DO jc = i_startidx, i_endidx
            z_dexner_dz_c(2, jc, jk, jb) = - 0.5D0 * ((z_theta_v_pr_ic(jc, jk) - z_theta_v_pr_ic(jc, jk + 1)) * p_nh % metrics % d2dexdz2_fac1_mc(jc, jk, jb) + z_rth_pr(2, jc, jk, jb) * p_nh % metrics % d2dexdz2_fac2_mc(jc, jk, jb))
          END DO
        END DO
      END IF
    END DO
    rl_start = (- 6)
    rl_end = (- 6)
    i_startblk = p_patch % cells % start_block(- 6)
    i_endblk = p_patch % cells % end_block(- 6)
    DO jb = i_startblk, i_endblk
      CALL get_indices_c(p_patch, jb, i_startblk, i_endblk, i_startidx, i_endidx, - 6, - 6)
      DO jk = 1, nlev
        DO jc = i_startidx, i_endidx
          z_rth_pr(1, jc, jk, jb) = p_nh_prog_nnow % rho(jc, jk, jb) - p_nh % metrics % rho_ref_mc(jc, jk, jb)
          z_rth_pr(2, jc, jk, jb) = p_nh_prog_nnow % theta_v(jc, jk, jb) - p_nh % metrics % theta_ref_mc(jc, jk, jb)
        END DO
      END DO
    END DO
    IF (timers_level > 5) THEN
      CALL timer_stop(timer_solve_nh_cellcomp)
      CALL timer_start(timer_solve_nh_vnupd)
    END IF
    IF (iadv_rhotheta == 1) THEN
      CALL cells2verts_scalar_dp_deconiface_8(p_nh_prog_nnow % rho, p_patch, p_int % cells_aw_verts, z_rho_v, opt_rlend = - 5)
      CALL cells2verts_scalar_dp_deconiface_9(p_nh_prog_nnow % theta_v, p_patch, p_int % cells_aw_verts, z_theta_v_v, opt_rlend = - 5)
    ELSE IF (iadv_rhotheta == 2) THEN
      CALL grad_green_gauss_cell_dycore_deconiface_10(z_rth_pr, p_patch, p_int, z_grad_rth, opt_rlstart = 3, opt_rlend = - 5, opt_acc_async = .TRUE.)
    END IF
    i_startblk = p_patch % edges % start_block(- 10)
    i_endblk = p_patch % edges % end_block(- 10)
    IF (i_endblk >= i_startblk) THEN
      CALL init_zero_contiguous_dp(z_rho_e(1, 1, i_startblk), nproma * nlev * (i_endblk - i_startblk + 1), opt_acc_async = .TRUE., lacc = .TRUE.)
      CALL init_zero_contiguous_dp(z_theta_v_e(1, 1, i_startblk), nproma * nlev * (i_endblk - i_startblk + 1), opt_acc_async = .TRUE., lacc = .TRUE.)
    END IF
    rl_start = 7
    rl_end = (- 9)
    i_startblk = p_patch % edges % start_block(7)
    i_endblk = p_patch % edges % end_block(- 9)
    IF (jg > 1 .OR. l_limited_area) THEN
      CALL init_zero_contiguous_dp(z_rho_e(1, 1, 1), nproma * nlev * i_startblk, opt_acc_async = .TRUE., lacc = .TRUE.)
      CALL init_zero_contiguous_dp(z_theta_v_e(1, 1, 1), nproma * nlev * i_startblk, opt_acc_async = .TRUE., lacc = .TRUE.)
    END IF
    DO jb = i_startblk, i_endblk
      CALL get_indices_e(p_patch, jb, i_startblk, i_endblk, i_startidx, i_endidx, 7, - 9)
      IF (iadv_rhotheta == 2) THEN
        DO jk = 1, nlev
          DO je = i_startidx, i_endidx
            lvn_pos = p_nh_prog_nnow % vn(je, jk, jb) >= 0.0D0
            ilc0 = MERGE(p_patch % edges % cell_idx(je, jb, 1), p_patch % edges % cell_idx(je, jb, 2), lvn_pos)
            ibc0 = MERGE(p_patch % edges % cell_blk(je, jb, 1), p_patch % edges % cell_blk(je, jb, 2), lvn_pos)
            z_ntdistv_bary_1 = - (p_nh_prog_nnow % vn(je, jk, jb) * dthalf + MERGE(p_int % pos_on_tplane_e(je, 1, 1, jb), p_int % pos_on_tplane_e(je, 2, 1, jb), lvn_pos)) * p_nh % metrics % deepatmo_gradh_mc(jk)
            z_ntdistv_bary_2 = - (p_nh % diag % vt(je, jk, jb) * dthalf + MERGE(p_int % pos_on_tplane_e(je, 1, 2, jb), p_int % pos_on_tplane_e(je, 2, 2, jb), lvn_pos)) * p_nh % metrics % deepatmo_gradh_mc(jk)
            distv_bary_1 = z_ntdistv_bary_1 * MERGE(p_patch % edges % primal_normal_cell(je, jb, 1) % v1, p_patch % edges % primal_normal_cell(je, jb, 2) % v1, lvn_pos) + z_ntdistv_bary_2 * MERGE(p_patch % edges % dual_normal_cell(je, jb, 1) % v1, p_patch % edges % dual_normal_cell(je, jb, 2) % v1, lvn_pos)
            distv_bary_2 = z_ntdistv_bary_1 * MERGE(p_patch % edges % primal_normal_cell(je, jb, 1) % v2, p_patch % edges % primal_normal_cell(je, jb, 2) % v2, lvn_pos) + z_ntdistv_bary_2 * MERGE(p_patch % edges % dual_normal_cell(je, jb, 1) % v2, p_patch % edges % dual_normal_cell(je, jb, 2) % v2, lvn_pos)
            z_rho_e(je, jk, jb) = REAL(p_nh % metrics % rho_ref_me(je, jk, jb), 8) + z_rth_pr(1, ilc0, jk, ibc0) + distv_bary_1 * z_grad_rth(1, ilc0, jk, ibc0) + distv_bary_2 * z_grad_rth(2, ilc0, jk, ibc0)
            z_theta_v_e(je, jk, jb) = REAL(p_nh % metrics % theta_ref_me(je, jk, jb), 8) + z_rth_pr(2, ilc0, jk, ibc0) + distv_bary_1 * z_grad_rth(3, ilc0, jk, ibc0) + distv_bary_2 * z_grad_rth(4, ilc0, jk, ibc0)
          END DO
        END DO
      ELSE
        DO jk = 1, nlev
          DO je = i_startidx, i_endidx
            z_rho_e(je, jk, jb) = p_int % c_lin_e(je, 1, jb) * p_nh_prog_nnow % rho(p_patch % edges % cell_idx(je, jb, 1), jk, p_patch % edges % cell_blk(je, jb, 1)) + p_int % c_lin_e(je, 2, jb) * p_nh_prog_nnow % rho(p_patch % edges % cell_idx(je, jb, 2), jk, p_patch % edges % cell_blk(je, jb, 2)) - dtime * (p_nh_prog_nnow % vn(je, jk, jb) * p_patch % edges % inv_dual_edge_length(je, jb) * (p_nh_prog_nnow % rho(p_patch % edges % cell_idx(je, jb, 2), jk, p_patch % edges % cell_blk(je, jb, 2)) - p_nh_prog_nnow % rho(p_patch % edges % cell_idx(je, jb, 1), jk, p_patch % edges % cell_blk(je, jb, 1))) + p_nh % diag % vt(je, jk, jb) * p_patch % edges % inv_primal_edge_length(je, jb) * p_patch % edges % tangent_orientation(je, jb) * (z_rho_v(p_patch % edges % vertex_idx(je, jb, 2), jk, p_patch % edges % vertex_blk(je, jb, 2)) - z_rho_v(p_patch % edges % vertex_idx(je, jb, 1), jk, p_patch % edges % vertex_blk(je, jb, 1))))
            z_theta_v_e(je, jk, jb) = p_int % c_lin_e(je, 1, jb) * p_nh_prog_nnow % theta_v(p_patch % edges % cell_idx(je, jb, 1), jk, p_patch % edges % cell_blk(je, jb, 1)) + p_int % c_lin_e(je, 2, jb) * p_nh_prog_nnow % theta_v(p_patch % edges % cell_idx(je, jb, 2), jk, p_patch % edges % cell_blk(je, jb, 2)) - dtime * (p_nh_prog_nnow % vn(je, jk, jb) * p_patch % edges % inv_dual_edge_length(je, jb) * (p_nh_prog_nnow % theta_v(p_patch % edges % cell_idx(je, jb, 2), jk, p_patch % edges % cell_blk(je, jb, 2)) - p_nh_prog_nnow % theta_v(p_patch % edges % cell_idx(je, jb, 1), jk, p_patch % edges % cell_blk(je, jb, 1))) + p_nh % diag % vt(je, jk, jb) * p_patch % edges % inv_primal_edge_length(je, jb) * p_patch % edges % tangent_orientation(je, jb) * (z_theta_v_v(p_patch % edges % vertex_idx(je, jb, 2), jk, p_patch % edges % vertex_blk(je, jb, 2)) - z_theta_v_v(p_patch % edges % vertex_idx(je, jb, 1), jk, p_patch % edges % vertex_blk(je, jb, 1))))
          END DO
        END DO
      END IF
    END DO
    rl_start = 10
    rl_end = (- 8)
    i_startblk = p_patch % edges % start_block(10)
    i_endblk = p_patch % edges % end_block((- 8))
    DO jb = i_startblk, i_endblk
      CALL get_indices_e(p_patch, jb, i_startblk, i_endblk, i_startidx, i_endidx, 10, (- 8))
      IF (idyn_timestep == 1 .AND. l_child_vertnest) THEN
        DO je = i_startidx, i_endidx
          p_nh % diag % vn_ie_int(je, 1, jb) = p_nh % diag % vn_ie(je, nshift, jb)
        END DO
      END IF
      DO jk = 1, nflatlev(jg) - 1
        DO je = i_startidx, i_endidx
          z_gradh_exner(je, jk, jb) = p_patch % edges % inv_dual_edge_length(je, jb) * p_nh % metrics % deepatmo_gradh_mc(jk) * (z_exner_ex_pr(p_patch % edges % cell_idx(je, jb, 2), jk, p_patch % edges % cell_blk(je, jb, 2)) - z_exner_ex_pr(p_patch % edges % cell_idx(je, jb, 1), jk, p_patch % edges % cell_blk(je, jb, 1)))
        END DO
      END DO
      IF (igradp_method <= 3) THEN
        DO jk = nflatlev(jg), nflat_gradp(jg)
          DO je = i_startidx, i_endidx
            z_gradh_exner(je, jk, jb) = p_patch % edges % inv_dual_edge_length(je, jb) * p_nh % metrics % deepatmo_gradh_mc(jk) * (z_exner_ex_pr(p_patch % edges % cell_idx(je, jb, 2), jk, p_patch % edges % cell_blk(je, jb, 2)) - z_exner_ex_pr(p_patch % edges % cell_idx(je, jb, 1), jk, p_patch % edges % cell_blk(je, jb, 1))) - p_nh % metrics % ddxn_z_full(je, jk, jb) * (p_int % c_lin_e(je, 1, jb) * z_dexner_dz_c(1, p_patch % edges % cell_idx(je, jb, 1), jk, p_patch % edges % cell_blk(je, jb, 1)) + p_int % c_lin_e(je, 2, jb) * z_dexner_dz_c(1, p_patch % edges % cell_idx(je, jb, 2), jk, p_patch % edges % cell_blk(je, jb, 2)))
          END DO
        END DO
        DO jk = nflat_gradp(jg) + 1, nlev
          DO je = i_startidx, i_endidx
            z_gradh_exner(je, jk, jb) = p_patch % edges % inv_dual_edge_length(je, jb) * p_nh % metrics % deepatmo_gradh_mc(jk) * (z_exner_ex_pr(p_patch % edges % cell_idx(je, jb, 2), p_nh % metrics % vertidx_gradp(2, je, jk, jb), p_patch % edges % cell_blk(je, jb, 2)) + p_nh % metrics % zdiff_gradp(2, je, jk, jb) * (z_dexner_dz_c(1, p_patch % edges % cell_idx(je, jb, 2), p_nh % metrics % vertidx_gradp(2, je, jk, jb), p_patch % edges % cell_blk(je, jb, 2)) + p_nh % metrics % zdiff_gradp(2, je, jk, jb) * z_dexner_dz_c(2, p_patch % edges % cell_idx(je, jb, 2), p_nh % metrics % vertidx_gradp(2, je, jk, jb), p_patch % edges % cell_blk(je, jb, 2))) - (z_exner_ex_pr(p_patch % edges % cell_idx(je, jb, 1), p_nh % metrics % vertidx_gradp(1, je, jk, jb), p_patch % edges % cell_blk(je, jb, 1)) + p_nh % metrics % zdiff_gradp(1, je, jk, jb) * (z_dexner_dz_c(1, p_patch % edges % cell_idx(je, jb, 1), p_nh % metrics % vertidx_gradp(1, je, jk, jb), p_patch % edges % cell_blk(je, jb, 1)) + p_nh % metrics % zdiff_gradp(1, je, jk, jb) * z_dexner_dz_c(2, p_patch % edges % cell_idx(je, jb, 1), p_nh % metrics % vertidx_gradp(1, je, jk, jb), p_patch % edges % cell_blk(je, jb, 1)))))
          END DO
        END DO
      ELSE IF (igradp_method == 4 .OR. igradp_method == 5) THEN
        DO jk = nflatlev(jg), nlev
          DO je = i_startidx, i_endidx
            z_gradh_exner(je, jk, jb) = p_patch % edges % inv_dual_edge_length(je, jb) * p_nh % metrics % deepatmo_gradh_mc(jk) * (z_exner_ex_pr(p_patch % edges % cell_idx(je, jb, 2), p_nh % metrics % vertidx_gradp(2, je, jk, jb) - 1, p_patch % edges % cell_blk(je, jb, 2)) * p_nh % metrics % coeff_gradp(5, je, jk, jb) + z_exner_ex_pr(p_patch % edges % cell_idx(je, jb, 2), p_nh % metrics % vertidx_gradp(2, je, jk, jb), p_patch % edges % cell_blk(je, jb, 2)) * p_nh % metrics % coeff_gradp(6, je, jk, jb) + z_exner_ex_pr(p_patch % edges % cell_idx(je, jb, 2), p_nh % metrics % vertidx_gradp(2, je, jk, jb) + 1, p_patch % edges % cell_blk(je, jb, 2)) * p_nh % metrics % coeff_gradp(7, je, jk, jb) + z_exner_ex_pr(p_patch % edges % cell_idx(je, jb, 2), p_nh % metrics % vertidx_gradp(2, je, jk, jb) + 2, p_patch % edges % cell_blk(je, jb, 2)) * p_nh % metrics % coeff_gradp(8, je, jk, jb) - (z_exner_ex_pr(p_patch % edges % cell_idx(je, jb, 1), p_nh % metrics % vertidx_gradp(1, je, jk, jb) - 1, p_patch % edges % cell_blk(je, jb, 1)) * p_nh % metrics % coeff_gradp(1, je, jk, jb) + z_exner_ex_pr(p_patch % edges % cell_idx(je, jb, 1), p_nh % metrics % vertidx_gradp(1, je, jk, jb), p_patch % edges % cell_blk(je, jb, 1)) * p_nh % metrics % coeff_gradp(2, je, jk, jb) + z_exner_ex_pr(p_patch % edges % cell_idx(je, jb, 1), p_nh % metrics % vertidx_gradp(1, je, jk, jb) + 1, p_patch % edges % cell_blk(je, jb, 1)) * p_nh % metrics % coeff_gradp(3, je, jk, jb) + z_exner_ex_pr(p_patch % edges % cell_idx(je, jb, 1), p_nh % metrics % vertidx_gradp(1, je, jk, jb) + 2, p_patch % edges % cell_blk(je, jb, 1)) * p_nh % metrics % coeff_gradp(4, je, jk, jb)))
          END DO
        END DO
      END IF
      IF (igradp_method == 3) THEN
        DO je = i_startidx, i_endidx
          z_theta1 = p_nh_prog_nnow % theta_v(p_patch % edges % cell_idx(je, jb, 1), p_nh % metrics % vertidx_gradp(1, je, nlev, jb), p_patch % edges % cell_blk(je, jb, 1)) + p_nh % metrics % zdiff_gradp(1, je, nlev, jb) * (p_nh % diag % theta_v_ic(p_patch % edges % cell_idx(je, jb, 1), p_nh % metrics % vertidx_gradp(1, je, nlev, jb), p_patch % edges % cell_blk(je, jb, 1)) - p_nh % diag % theta_v_ic(p_patch % edges % cell_idx(je, jb, 1), p_nh % metrics % vertidx_gradp(1, je, nlev, jb) + 1, p_patch % edges % cell_blk(je, jb, 1))) * p_nh % metrics % inv_ddqz_z_full(p_patch % edges % cell_idx(je, jb, 1), p_nh % metrics % vertidx_gradp(1, je, nlev, jb), p_patch % edges % cell_blk(je, jb, 1))
          z_theta2 = p_nh_prog_nnow % theta_v(p_patch % edges % cell_idx(je, jb, 2), p_nh % metrics % vertidx_gradp(2, je, nlev, jb), p_patch % edges % cell_blk(je, jb, 2)) + p_nh % metrics % zdiff_gradp(2, je, nlev, jb) * (p_nh % diag % theta_v_ic(p_patch % edges % cell_idx(je, jb, 2), p_nh % metrics % vertidx_gradp(2, je, nlev, jb), p_patch % edges % cell_blk(je, jb, 2)) - p_nh % diag % theta_v_ic(p_patch % edges % cell_idx(je, jb, 2), p_nh % metrics % vertidx_gradp(2, je, nlev, jb) + 1, p_patch % edges % cell_blk(je, jb, 2))) * p_nh % metrics % inv_ddqz_z_full(p_patch % edges % cell_idx(je, jb, 2), p_nh % metrics % vertidx_gradp(2, je, nlev, jb), p_patch % edges % cell_blk(je, jb, 2))
          z_hydro_corr(je, jb) = 0.00976135730211817D0 * p_patch % edges % inv_dual_edge_length(je, jb) * (z_theta2 - z_theta1) * 4.0D0 / (z_theta1 + z_theta2) ** 2
        END DO
      ELSE IF (igradp_method == 5) THEN
        DO je = i_startidx, i_endidx
          ikp1 = MIN(nlev, p_nh % metrics % vertidx_gradp(1, je, nlev, jb) + 2)
          ikp2 = MIN(nlev, p_nh % metrics % vertidx_gradp(2, je, nlev, jb) + 2)
          z_theta1 = p_nh_prog_nnow % theta_v(p_patch % edges % cell_idx(je, jb, 1), p_nh % metrics % vertidx_gradp(1, je, nlev, jb) - 1, p_patch % edges % cell_blk(je, jb, 1)) * p_nh % metrics % coeff_gradp(1, je, nlev, jb) + p_nh_prog_nnow % theta_v(p_patch % edges % cell_idx(je, jb, 1), p_nh % metrics % vertidx_gradp(1, je, nlev, jb), p_patch % edges % cell_blk(je, jb, 1)) * p_nh % metrics % coeff_gradp(2, je, nlev, jb) + p_nh_prog_nnow % theta_v(p_patch % edges % cell_idx(je, jb, 1), p_nh % metrics % vertidx_gradp(1, je, nlev, jb) + 1, p_patch % edges % cell_blk(je, jb, 1)) * p_nh % metrics % coeff_gradp(3, je, nlev, jb) + p_nh_prog_nnow % theta_v(p_patch % edges % cell_idx(je, jb, 1), ikp1, p_patch % edges % cell_blk(je, jb, 1)) * p_nh % metrics % coeff_gradp(4, je, nlev, jb)
          z_theta2 = p_nh_prog_nnow % theta_v(p_patch % edges % cell_idx(je, jb, 2), p_nh % metrics % vertidx_gradp(2, je, nlev, jb) - 1, p_patch % edges % cell_blk(je, jb, 2)) * p_nh % metrics % coeff_gradp(5, je, nlev, jb) + p_nh_prog_nnow % theta_v(p_patch % edges % cell_idx(je, jb, 2), p_nh % metrics % vertidx_gradp(2, je, nlev, jb), p_patch % edges % cell_blk(je, jb, 2)) * p_nh % metrics % coeff_gradp(6, je, nlev, jb) + p_nh_prog_nnow % theta_v(p_patch % edges % cell_idx(je, jb, 2), p_nh % metrics % vertidx_gradp(2, je, nlev, jb) + 1, p_patch % edges % cell_blk(je, jb, 2)) * p_nh % metrics % coeff_gradp(7, je, nlev, jb) + p_nh_prog_nnow % theta_v(p_patch % edges % cell_idx(je, jb, 2), ikp2, p_patch % edges % cell_blk(je, jb, 2)) * p_nh % metrics % coeff_gradp(8, je, nlev, jb)
          z_hydro_corr(je, jb) = 0.00976135730211817D0 * p_patch % edges % inv_dual_edge_length(je, jb) * (z_theta2 - z_theta1) * 4.0D0 / (z_theta1 + z_theta2) ** 2
        END DO
      END IF
    END DO
    IF (.TRUE. .AND. (igradp_method == 3 .OR. igradp_method == 5)) THEN
      DO jb = 1, nblks_gradp
        IF (jb == nblks_gradp) THEN
          nlen_gradp = npromz_gradp
        ELSE
          nlen_gradp = nproma_gradp
        END IF
        ishift = (jb - 1) * nproma_gradp
        DO je = 1, nlen_gradp
          ie = ishift + je
          z_gradh_exner(p_nh % metrics % pg_edgeidx(ie), p_nh % metrics % pg_vertidx(ie), p_nh % metrics % pg_edgeblk(ie)) = z_gradh_exner(p_nh % metrics % pg_edgeidx(ie), p_nh % metrics % pg_vertidx(ie), p_nh % metrics % pg_edgeblk(ie)) + p_nh % metrics % pg_exdist(ie) * z_hydro_corr(p_nh % metrics % pg_edgeidx(ie), p_nh % metrics % pg_edgeblk(ie))
        END DO
      END DO
    END IF
    DO jb = i_startblk, i_endblk
      CALL get_indices_e(p_patch, jb, i_startblk, i_endblk, i_startidx, i_endidx, 10, (- 8))
      DO jk = 1, nlev
        DO je = i_startidx, i_endidx
          p_nh_prog_nnew % vn(je, jk, jb) = p_nh_prog_nnow % vn(je, jk, jb) + dtime * (p_nh % diag % ddt_vn_apc_pc(je, jk, jb, ntl1) - 1004.64D0 * z_theta_v_e(je, jk, jb) * z_gradh_exner(je, jk, jb) + p_nh % diag % ddt_vn_phy(je, jk, jb))
        END DO
      END DO
      IF (is_iau_active) THEN
        DO jk = 1, nlev
          DO je = i_startidx, i_endidx
            z_d_vn_iau = iau_wgt_dyn * p_nh % diag % vn_incr(je, jk, jb)
            p_nh_prog_nnew % vn(je, jk, jb) = p_nh_prog_nnew % vn(je, jk, jb) + z_d_vn_iau
          END DO
        END DO
      END IF
      IF (rayleigh_type == 1) THEN
        DO jk = 1, nrdmax(jg)
          DO je = i_startidx, i_endidx
            z_ddt_vn_ray = - p_nh % metrics % rayleigh_vn(jk) * (p_nh_prog_nnew % vn(je, jk, jb) - p_nh % ref % vn_ref(je, jk, jb))
            p_nh_prog_nnew % vn(je, jk, jb) = p_nh_prog_nnew % vn(je, jk, jb) + z_ddt_vn_ray * dtime
          END DO
        END DO
      END IF
    END DO
    IF (.TRUE. .AND. (l_limited_area .OR. jg > 1)) THEN
      rl_start = 1
      rl_end = 9
      i_startblk = p_patch % edges % start_block(1)
      i_endblk = p_patch % edges % end_block(9)
      DO jb = i_startblk, i_endblk
        CALL get_indices_e(p_patch, jb, i_startblk, i_endblk, i_startidx, i_endidx, 1, 9)
        DO jk = 1, nlev
          DO je = i_startidx, i_endidx
            p_nh_prog_nnew % vn(je, jk, jb) = p_nh_prog_nnow % vn(je, jk, jb) + p_nh % diag % grf_tend_vn(je, jk, jb) * dtime
            IF (p_nh % diag % ddt_vn_grf_is_associated) THEN
              p_nh % diag % ddt_vn_grf(je, jk, jb) = p_nh % diag % ddt_vn_grf(je, jk, jb) + p_nh % diag % grf_tend_vn(je, jk, jb) * r_nsubsteps
            END IF
            IF (p_nh % diag % ddt_vn_dyn_is_associated) THEN
              p_nh % diag % ddt_vn_dyn(je, jk, jb) = p_nh % diag % ddt_vn_dyn(je, jk, jb) + p_nh % diag % grf_tend_vn(je, jk, jb) * r_nsubsteps
            END IF
          END DO
        END DO
      END DO
    END IF
    IF (jg > 1 .AND. grf_intmethod_e == 6 .AND. jstep == 0 .AND. .TRUE.) THEN
      DO ic = 1, p_nh % metrics % bdy_mflx_e_dim
        je = p_nh % metrics % bdy_mflx_e_idx(ic)
        jb = p_nh % metrics % bdy_mflx_e_blk(ic)
        DO jk = 1, nlev
          p_nh % diag % grf_bdy_mflx(jk, ic, 2) = p_nh % diag % grf_tend_mflx(je, jk, jb)
          p_nh % diag % grf_bdy_mflx(jk, ic, 1) = prep_adv % mass_flx_me(je, jk, jb) - dt_shift * p_nh % diag % grf_bdy_mflx(jk, ic, 2)
        END DO
      END DO
    END IF
  END SUBROUTINE solve_nh_predictor_pre
  SUBROUTINE solve_nh_predictor_post(p_nh, p_nh_prog_nnow, p_nh_prog_nnew, p_patch, p_int, prep_adv, nnow, nnew, l_init, l_recompute, lsave_mflx, lprep_adv, lclean_mflx, idyn_timestep, jstep, dtime, lacc, jb, jk, jc, je, jks, jg, nlev, nlevp1, i_startblk, i_endblk, i_startidx, i_endidx, ishift, rl_start, rl_end, istep, ntl1, ntl2, nvar, nshift, nshift_total, z_theta_v_fl_e, z_theta_v_e, z_rho_e, z_theta_v_v, z_rho_v, z_th_ddz_exner_c, z_dexner_dz_c, z_vt_ie, z_kin_hor_e, z_exner_ex_pr, z_gradh_exner, z_rth_pr, z_grad_rth, z_w_concorr_me, z_graddiv_vn, z_w_expl, z_vn_avg, z_mflx_top, z_contr_w_fl_l, z_rho_expl, z_exner_expl, z_theta_tavg_m1, z_theta_tavg, z_rho_tavg_m1, z_rho_tavg, z_alpha, z_beta, z_q, z_graddiv2_vn, z_theta_v_pr_ic, z_exner_ic, z_w_concorr_mc, z_flxdiv_mass, z_flxdiv_theta, z_hydro_corr, z_a, z_b, z_c, z_g, z_gamma, z_w_backtraj, z_theta_v_pr_mc_m1, z_theta_v_pr_mc, z_theta1, z_theta2, wgt_nnow_vel, wgt_nnew_vel, dt_shift, wgt_nnow_rth, wgt_nnew_rth, dthalf, r_nsubsteps, r_dtimensubsteps, scal_divdamp_o2, alin, dz32, df32, dz42, df42, bqdr, aqdr, zf, dzlin, dzqdr, dt_linintp_ubc, dt_linintp_ubc_nnow, dt_linintp_ubc_nnew, z_raylfac, z_ntdistv_bary_1, distv_bary_1, z_ntdistv_bary_2, distv_bary_2, scal_divdamp, bdy_divdamp, enh_divdamp_fac, z_dwdz_dd, z_ddt_vn_dyn, z_ddt_vn_apc, z_ddt_vn_cor, z_ddt_vn_pgr, z_ddt_vn_ray, z_d_vn_dmp, z_d_vn_iau, nproma_gradp, nblks_gradp, npromz_gradp, nlen_gradp, jk_start, lvn_only, lvn_pos, l_vert_nested, l_child_vertnest)
    USE mo_nonhydro_types, ONLY: t_nh_prog, t_nh_state
    USE mo_intp_data_strc, ONLY: t_int_state
    USE mo_model_domain, ONLY: t_patch
    USE mo_prepadv_types, ONLY: t_prepare_adv
    USE mo_parallel_config, ONLY: nproma
    USE mo_vertical_grid, ONLY: nrdmax
    USE mo_nonhydrostatic_config, ONLY: divdamp_type, kstart_dd3d, kstart_moist, ndyn_substeps_var, rayleigh_type
    USE fake_mo_loopindices, ONLY: get_indices_c, get_indices_e
    USE mo_init_vgrid, ONLY: nflatlev
    USE mo_gridref_config, ONLY: grf_intmethod_e
    USE mo_run_config, ONLY: timers_level
    USE fake_mo_real_timer, ONLY: timer_start, timer_stop
    USE mo_timer, ONLY: timer_solve_nh_edgecomp, timer_solve_nh_vimpl
    USE mo_initicon_config, ONLY: iau_wgt_dyn, is_iau_active
    USE mo_grid_config, ONLY: l_limited_area
    USE fake_mo_mpi, ONLY: my_process_is_mpi_all_seq
    TYPE(t_nh_state), TARGET, INTENT(INOUT) :: p_nh
    TYPE(t_int_state), TARGET, INTENT(IN) :: p_int
    TYPE(t_patch), TARGET, INTENT(INOUT) :: p_patch
    TYPE(t_prepare_adv), TARGET, INTENT(INOUT) :: prep_adv
    TYPE(t_nh_prog), TARGET, INTENT(INOUT) :: p_nh_prog_nnow, p_nh_prog_nnew
    LOGICAL, INTENT(IN) :: l_init
    LOGICAL, INTENT(IN) :: l_recompute
    LOGICAL, INTENT(IN) :: lsave_mflx
    LOGICAL, INTENT(IN) :: lprep_adv
    LOGICAL, INTENT(IN) :: lclean_mflx
    INTEGER, INTENT(IN) :: idyn_timestep
    INTEGER, INTENT(IN) :: jstep
    INTEGER, INTENT(IN) :: nnow, nnew
    REAL(KIND = 8), INTENT(IN) :: dtime
    LOGICAL, INTENT(IN), OPTIONAL :: lacc
    INTEGER, INTENT(INOUT) :: jb, jk, jc, je, jks, jg
    INTEGER, INTENT(INOUT) :: nlev, nlevp1
    INTEGER, INTENT(INOUT) :: i_startblk, i_endblk, i_startidx, i_endidx, ishift
    INTEGER, INTENT(INOUT) :: rl_start, rl_end, istep, ntl1, ntl2, nvar, nshift, nshift_total
    INTEGER :: ic
    REAL(KIND = 8), INTENT(INOUT) :: z_theta_v_fl_e(nproma, p_patch % nlev, p_patch % nblks_e), z_theta_v_e(nproma, p_patch % nlev, p_patch % nblks_e), z_rho_e(nproma, p_patch % nlev, p_patch % nblks_e), z_theta_v_v(nproma, p_patch % nlev, p_patch % nblks_v), z_rho_v(nproma, p_patch % nlev, p_patch % nblks_v)
    REAL(KIND = 8), INTENT(INOUT) :: z_th_ddz_exner_c(nproma, p_patch % nlev, p_patch % nblks_c), z_dexner_dz_c(2, nproma, p_patch % nlev, p_patch % nblks_c), z_vt_ie(nproma, p_patch % nlev, p_patch % nblks_e), z_kin_hor_e(nproma, p_patch % nlev, p_patch % nblks_e), z_exner_ex_pr(nproma, p_patch % nlevp1, p_patch % nblks_c), z_gradh_exner(nproma, p_patch % nlev, p_patch % nblks_e), z_rth_pr(2, nproma, p_patch % nlev, p_patch % nblks_c), z_grad_rth(4, nproma, p_patch % nlev, p_patch % nblks_c), z_w_concorr_me(nproma, p_patch % nlev, p_patch % nblks_e)
    REAL(KIND = 8), INTENT(INOUT) :: z_graddiv_vn(nproma, p_patch % nlev, p_patch % nblks_e)
    REAL(KIND = 8), INTENT(INOUT) :: z_w_expl(nproma, p_patch % nlevp1), z_vn_avg(nproma, p_patch % nlev), z_mflx_top(nproma, p_patch % nblks_c), z_contr_w_fl_l(nproma, p_patch % nlevp1), z_rho_expl(nproma, p_patch % nlev), z_exner_expl(nproma, p_patch % nlev)
    REAL(KIND = 8), INTENT(INOUT) :: z_theta_tavg_m1, z_theta_tavg, z_rho_tavg_m1, z_rho_tavg
    REAL(KIND = 8), INTENT(INOUT) :: z_alpha(nproma, p_patch % nlevp1), z_beta(nproma, p_patch % nlev), z_q(nproma, p_patch % nlev), z_graddiv2_vn(nproma, p_patch % nlev), z_theta_v_pr_ic(nproma, p_patch % nlevp1), z_exner_ic(nproma, p_patch % nlevp1), z_w_concorr_mc(nproma, p_patch % nlev), z_flxdiv_mass(nproma, p_patch % nlev), z_flxdiv_theta(nproma, p_patch % nlev), z_hydro_corr(nproma, p_patch % nblks_e)
    REAL(KIND = 8), INTENT(INOUT) :: z_a, z_b, z_c, z_g, z_gamma, z_w_backtraj, z_theta_v_pr_mc_m1, z_theta_v_pr_mc
    REAL(KIND = 8) :: z_w_concorr_mc_m0, z_w_concorr_mc_m1, z_w_concorr_mc_m2
    REAL(KIND = 8), INTENT(INOUT) :: z_theta1, z_theta2, wgt_nnow_vel, wgt_nnew_vel, dt_shift, wgt_nnow_rth, wgt_nnew_rth, dthalf, r_nsubsteps, r_dtimensubsteps, scal_divdamp_o2, alin, dz32, df32, dz42, df42, bqdr, aqdr, zf, dzlin, dzqdr
    REAL(KIND = 8), INTENT(INOUT) :: dt_linintp_ubc, dt_linintp_ubc_nnow, dt_linintp_ubc_nnew
    REAL(KIND = 8), INTENT(INOUT) :: z_raylfac(nrdmax(p_patch % id))
    REAL(KIND = 8), INTENT(INOUT) :: z_ntdistv_bary_1, distv_bary_1, z_ntdistv_bary_2, distv_bary_2
    REAL(KIND = 8), INTENT(INOUT), DIMENSION(p_patch % nlev) :: scal_divdamp, bdy_divdamp, enh_divdamp_fac
    REAL(KIND = 8), INTENT(INOUT) :: z_dwdz_dd(nproma, kstart_dd3d(p_patch % id) : p_patch % nlev, p_patch % nblks_c)
    REAL(KIND = 8), INTENT(INOUT) :: z_ddt_vn_dyn, z_ddt_vn_apc, z_ddt_vn_cor, z_ddt_vn_pgr, z_ddt_vn_ray, z_d_vn_dmp, z_d_vn_iau
    INTEGER, INTENT(INOUT) :: nproma_gradp, nblks_gradp, npromz_gradp, nlen_gradp, jk_start
    LOGICAL, INTENT(INOUT) :: lvn_only, lvn_pos
    LOGICAL, INTENT(INOUT) :: l_vert_nested, l_child_vertnest
    istep = 1
    rl_start = 5
    rl_end = (- 10)
    i_startblk = p_patch % edges % start_block(5)
    i_endblk = p_patch % edges % end_block((- 10))
    DO jb = i_startblk, i_endblk
      CALL get_indices_e(p_patch, jb, i_startblk, i_endblk, i_startidx, i_endidx, 5, (- 10))
      DO jk = 1, nlev
        DO je = i_startidx, i_endidx
          z_vn_avg(je, jk) = p_int % e_flx_avg(je, 1, jb) * p_nh_prog_nnew % vn(je, jk, jb) + p_int % e_flx_avg(je, 2, jb) * p_nh_prog_nnew % vn(p_patch % edges % quad_idx(je, jb, 1), jk, p_patch % edges % quad_blk(je, jb, 1)) + p_int % e_flx_avg(je, 3, jb) * p_nh_prog_nnew % vn(p_patch % edges % quad_idx(je, jb, 2), jk, p_patch % edges % quad_blk(je, jb, 2)) + p_int % e_flx_avg(je, 4, jb) * p_nh_prog_nnew % vn(p_patch % edges % quad_idx(je, jb, 3), jk, p_patch % edges % quad_blk(je, jb, 3)) + p_int % e_flx_avg(je, 5, jb) * p_nh_prog_nnew % vn(p_patch % edges % quad_idx(je, jb, 4), jk, p_patch % edges % quad_blk(je, jb, 4))
          z_graddiv_vn(je, jk, jb) = p_int % geofac_grdiv(je, 1, jb) * p_nh_prog_nnew % vn(je, jk, jb) + p_int % geofac_grdiv(je, 2, jb) * p_nh_prog_nnew % vn(p_patch % edges % quad_idx(je, jb, 1), jk, p_patch % edges % quad_blk(je, jb, 1)) + p_int % geofac_grdiv(je, 3, jb) * p_nh_prog_nnew % vn(p_patch % edges % quad_idx(je, jb, 2), jk, p_patch % edges % quad_blk(je, jb, 2)) + p_int % geofac_grdiv(je, 4, jb) * p_nh_prog_nnew % vn(p_patch % edges % quad_idx(je, jb, 3), jk, p_patch % edges % quad_blk(je, jb, 3)) + p_int % geofac_grdiv(je, 5, jb) * p_nh_prog_nnew % vn(p_patch % edges % quad_idx(je, jb, 4), jk, p_patch % edges % quad_blk(je, jb, 4))
          p_nh % diag % vt(je, jk, jb) = p_int % rbf_vec_coeff_e(1, je, jb) * p_nh_prog_nnew % vn(p_patch % edges % quad_idx(je, jb, 1), jk, p_patch % edges % quad_blk(je, jb, 1)) + p_int % rbf_vec_coeff_e(2, je, jb) * p_nh_prog_nnew % vn(p_patch % edges % quad_idx(je, jb, 2), jk, p_patch % edges % quad_blk(je, jb, 2)) + p_int % rbf_vec_coeff_e(3, je, jb) * p_nh_prog_nnew % vn(p_patch % edges % quad_idx(je, jb, 3), jk, p_patch % edges % quad_blk(je, jb, 3)) + p_int % rbf_vec_coeff_e(4, je, jb) * p_nh_prog_nnew % vn(p_patch % edges % quad_idx(je, jb, 4), jk, p_patch % edges % quad_blk(je, jb, 4))
        END DO
      END DO
      DO jk = 1, nlev
        DO je = i_startidx, i_endidx
          p_nh % diag % mass_fl_e(je, jk, jb) = z_rho_e(je, jk, jb) * z_vn_avg(je, jk) * p_nh % metrics % ddqz_z_full_e(je, jk, jb)
          z_theta_v_fl_e(je, jk, jb) = p_nh % diag % mass_fl_e(je, jk, jb) * z_theta_v_e(je, jk, jb)
        END DO
      END DO
      DO jk = nflatlev(jg), nlev
        DO je = i_startidx, i_endidx
          z_w_concorr_me(je, jk, jb) = p_nh_prog_nnew % vn(je, jk, jb) * p_nh % metrics % ddxn_z_full(je, jk, jb) + p_nh % diag % vt(je, jk, jb) * p_nh % metrics % ddxt_z_full(je, jk, jb)
        END DO
      END DO
      DO jk = 2, nlev
        DO je = i_startidx, i_endidx
          p_nh % diag % vn_ie(je, jk, jb) = p_nh % metrics % wgtfac_e(je, jk, jb) * p_nh_prog_nnew % vn(je, jk, jb) + (1.0D0 - p_nh % metrics % wgtfac_e(je, jk, jb)) * p_nh_prog_nnew % vn(je, jk - 1, jb)
          z_vt_ie(je, jk, jb) = p_nh % metrics % wgtfac_e(je, jk, jb) * p_nh % diag % vt(je, jk, jb) + (1.0D0 - p_nh % metrics % wgtfac_e(je, jk, jb)) * p_nh % diag % vt(je, jk - 1, jb)
          z_kin_hor_e(je, jk, jb) = 0.5D0 * (p_nh_prog_nnew % vn(je, jk, jb) ** 2 + p_nh % diag % vt(je, jk, jb) ** 2)
        END DO
      END DO
      IF (.NOT. l_vert_nested) THEN
        DO je = i_startidx, i_endidx
          p_nh % diag % vn_ie(je, 1, jb) = p_nh_prog_nnew % vn(je, 1, jb)
          z_vt_ie(je, 1, jb) = p_nh % diag % vt(je, 1, jb)
          z_kin_hor_e(je, 1, jb) = 0.5D0 * (p_nh_prog_nnew % vn(je, 1, jb) ** 2 + p_nh % diag % vt(je, 1, jb) ** 2)
          p_nh % diag % vn_ie(je, nlevp1, jb) = p_nh % metrics % wgtfacq_e(je, 1, jb) * p_nh_prog_nnew % vn(je, nlev, jb) + p_nh % metrics % wgtfacq_e(je, 2, jb) * p_nh_prog_nnew % vn(je, nlev - 1, jb) + p_nh % metrics % wgtfacq_e(je, 3, jb) * p_nh_prog_nnew % vn(je, nlev - 2, jb)
        END DO
      ELSE
        DO je = i_startidx, i_endidx
          p_nh % diag % vn_ie(je, 1, jb) = p_nh % diag % vn_ie_ubc(je, 1, jb) + dt_linintp_ubc_nnew * p_nh % diag % vn_ie_ubc(je, 2, jb)
          z_vt_ie(je, 1, jb) = p_nh % diag % vt(je, 1, jb)
          z_kin_hor_e(je, 1, jb) = 0.5D0 * (p_nh_prog_nnew % vn(je, 1, jb) ** 2 + p_nh % diag % vt(je, 1, jb) ** 2)
          p_nh % diag % vn_ie(je, nlevp1, jb) = p_nh % metrics % wgtfacq_e(je, 1, jb) * p_nh_prog_nnew % vn(je, nlev, jb) + p_nh % metrics % wgtfacq_e(je, 2, jb) * p_nh_prog_nnew % vn(je, nlev - 1, jb) + p_nh % metrics % wgtfacq_e(je, 3, jb) * p_nh_prog_nnew % vn(je, nlev - 2, jb)
        END DO
      END IF
    END DO
    IF (jg > 1 .AND. grf_intmethod_e == 6) THEN
      DO ic = 1, p_nh % metrics % bdy_mflx_e_dim
        je = p_nh % metrics % bdy_mflx_e_idx(ic)
        jb = p_nh % metrics % bdy_mflx_e_blk(ic)
        DO jk = 1, nlev
          p_nh % diag % mass_fl_e(je, jk, jb) = p_nh % diag % grf_bdy_mflx(jk, ic, 1) + REAL(jstep, 8) * dtime * p_nh % diag % grf_bdy_mflx(jk, ic, 2)
          z_theta_v_fl_e(je, jk, jb) = p_nh % diag % mass_fl_e(je, jk, jb) * z_theta_v_e(je, jk, jb)
        END DO
      END DO
    END IF
    rl_start = 3
    rl_end = (- 5)
    i_startblk = p_patch % cells % start_block(3)
    i_endblk = p_patch % cells % end_block(- 5)
    DO jb = i_startblk, i_endblk
      CALL get_indices_c(p_patch, jb, i_startblk, i_endblk, i_startidx, i_endidx, 3, (- 5))
      DO jk = nflatlev(jg) + 1, nlev
        DO jc = i_startidx, i_endidx
          z_w_concorr_mc_m1 = p_int % e_bln_c_s(jc, 1, jb) * z_w_concorr_me(p_patch % cells % edge_idx(jc, jb, 1), jk - 1, p_patch % cells % edge_blk(jc, jb, 1)) + p_int % e_bln_c_s(jc, 2, jb) * z_w_concorr_me(p_patch % cells % edge_idx(jc, jb, 2), jk - 1, p_patch % cells % edge_blk(jc, jb, 2)) + p_int % e_bln_c_s(jc, 3, jb) * z_w_concorr_me(p_patch % cells % edge_idx(jc, jb, 3), jk - 1, p_patch % cells % edge_blk(jc, jb, 3))
          z_w_concorr_mc_m0 = p_int % e_bln_c_s(jc, 1, jb) * z_w_concorr_me(p_patch % cells % edge_idx(jc, jb, 1), jk, p_patch % cells % edge_blk(jc, jb, 1)) + p_int % e_bln_c_s(jc, 2, jb) * z_w_concorr_me(p_patch % cells % edge_idx(jc, jb, 2), jk, p_patch % cells % edge_blk(jc, jb, 2)) + p_int % e_bln_c_s(jc, 3, jb) * z_w_concorr_me(p_patch % cells % edge_idx(jc, jb, 3), jk, p_patch % cells % edge_blk(jc, jb, 3))
          p_nh % diag % w_concorr_c(jc, jk, jb) = p_nh % metrics % wgtfac_c(jc, jk, jb) * z_w_concorr_mc_m0 + (1.0D0 - p_nh % metrics % wgtfac_c(jc, jk, jb)) * z_w_concorr_mc_m1
        END DO
      END DO
      DO jc = i_startidx, i_endidx
        z_w_concorr_mc_m2 = p_int % e_bln_c_s(jc, 1, jb) * z_w_concorr_me(p_patch % cells % edge_idx(jc, jb, 1), nlev - 2, p_patch % cells % edge_blk(jc, jb, 1)) + p_int % e_bln_c_s(jc, 2, jb) * z_w_concorr_me(p_patch % cells % edge_idx(jc, jb, 2), nlev - 2, p_patch % cells % edge_blk(jc, jb, 2)) + p_int % e_bln_c_s(jc, 3, jb) * z_w_concorr_me(p_patch % cells % edge_idx(jc, jb, 3), nlev - 2, p_patch % cells % edge_blk(jc, jb, 3))
        z_w_concorr_mc_m1 = p_int % e_bln_c_s(jc, 1, jb) * z_w_concorr_me(p_patch % cells % edge_idx(jc, jb, 1), nlev - 1, p_patch % cells % edge_blk(jc, jb, 1)) + p_int % e_bln_c_s(jc, 2, jb) * z_w_concorr_me(p_patch % cells % edge_idx(jc, jb, 2), nlev - 1, p_patch % cells % edge_blk(jc, jb, 2)) + p_int % e_bln_c_s(jc, 3, jb) * z_w_concorr_me(p_patch % cells % edge_idx(jc, jb, 3), nlev - 1, p_patch % cells % edge_blk(jc, jb, 3))
        z_w_concorr_mc_m0 = p_int % e_bln_c_s(jc, 1, jb) * z_w_concorr_me(p_patch % cells % edge_idx(jc, jb, 1), nlev, p_patch % cells % edge_blk(jc, jb, 1)) + p_int % e_bln_c_s(jc, 2, jb) * z_w_concorr_me(p_patch % cells % edge_idx(jc, jb, 2), nlev, p_patch % cells % edge_blk(jc, jb, 2)) + p_int % e_bln_c_s(jc, 3, jb) * z_w_concorr_me(p_patch % cells % edge_idx(jc, jb, 3), nlev, p_patch % cells % edge_blk(jc, jb, 3))
        p_nh % diag % w_concorr_c(jc, nlevp1, jb) = p_nh % metrics % wgtfacq_c(jc, 1, jb) * z_w_concorr_mc_m0 + p_nh % metrics % wgtfacq_c(jc, 2, jb) * z_w_concorr_mc_m1 + p_nh % metrics % wgtfacq_c(jc, 3, jb) * z_w_concorr_mc_m2
      END DO
    END DO
    IF (timers_level > 5) THEN
      CALL timer_stop(timer_solve_nh_edgecomp)
      CALL timer_start(timer_solve_nh_vimpl)
    END IF
    rl_start = 5
    rl_end = (- 4)
    i_startblk = p_patch % cells % start_block(5)
    i_endblk = p_patch % cells % end_block((- 4))
    IF (l_vert_nested) THEN
      jk_start = 2
    ELSE
      jk_start = 1
    END IF
    DO jb = i_startblk, i_endblk
      CALL get_indices_c(p_patch, jb, i_startblk, i_endblk, i_startidx, i_endidx, 5, (- 4))
      DO jk = 1, nlev
        DO jc = i_startidx, i_endidx
          z_flxdiv_mass(jc, jk) = p_nh % metrics % deepatmo_divh_mc(jk) * (p_nh % diag % mass_fl_e(p_patch % cells % edge_idx(jc, jb, 1), jk, p_patch % cells % edge_blk(jc, jb, 1)) * p_int % geofac_div(jc, 1, jb) + p_nh % diag % mass_fl_e(p_patch % cells % edge_idx(jc, jb, 2), jk, p_patch % cells % edge_blk(jc, jb, 2)) * p_int % geofac_div(jc, 2, jb) + p_nh % diag % mass_fl_e(p_patch % cells % edge_idx(jc, jb, 3), jk, p_patch % cells % edge_blk(jc, jb, 3)) * p_int % geofac_div(jc, 3, jb))
          z_flxdiv_theta(jc, jk) = p_nh % metrics % deepatmo_divh_mc(jk) * (z_theta_v_fl_e(p_patch % cells % edge_idx(jc, jb, 1), jk, p_patch % cells % edge_blk(jc, jb, 1)) * p_int % geofac_div(jc, 1, jb) + z_theta_v_fl_e(p_patch % cells % edge_idx(jc, jb, 2), jk, p_patch % cells % edge_blk(jc, jb, 2)) * p_int % geofac_div(jc, 2, jb) + z_theta_v_fl_e(p_patch % cells % edge_idx(jc, jb, 3), jk, p_patch % cells % edge_blk(jc, jb, 3)) * p_int % geofac_div(jc, 3, jb))
        END DO
      END DO
      IF (l_vert_nested .AND. .TRUE.) THEN
        DO jc = i_startidx, i_endidx
          p_nh % diag % theta_v_ic(jc, 1, jb) = p_nh % diag % theta_v_ic_ubc(jc, jb, 1) + dt_linintp_ubc * p_nh % diag % theta_v_ic_ubc(jc, jb, 2)
          p_nh % diag % rho_ic(jc, 1, jb) = p_nh % diag % rho_ic_ubc(jc, jb, 1) + dt_linintp_ubc * p_nh % diag % rho_ic_ubc(jc, jb, 2)
          z_mflx_top(jc, jb) = p_nh % diag % mflx_ic_ubc(jc, jb, 1) + dt_linintp_ubc * p_nh % diag % mflx_ic_ubc(jc, jb, 2)
        END DO
      END IF
      DO jk = 2, nlev
        DO jc = i_startidx, i_endidx
          z_w_expl(jc, jk) = p_nh_prog_nnow % w(jc, jk, jb) + dtime * (p_nh % diag % ddt_w_adv_pc(jc, jk, jb, ntl1) - 1004.64D0 * z_th_ddz_exner_c(jc, jk, jb))
          z_contr_w_fl_l(jc, jk) = p_nh % diag % rho_ic(jc, jk, jb) * (p_nh % metrics % vwind_expl_wgt(jc, jb) * p_nh_prog_nnow % w(jc, jk, jb) - p_nh % diag % w_concorr_c(jc, jk, jb))
        END DO
      END DO
      DO jk = 1, nlev
        DO jc = i_startidx, i_endidx
          z_beta(jc, jk) = dtime * 287.04D0 * p_nh_prog_nnow % exner(jc, jk, jb) / (717.5999999999999D0 * p_nh_prog_nnow % rho(jc, jk, jb) * p_nh_prog_nnow % theta_v(jc, jk, jb)) * p_nh % metrics % inv_ddqz_z_full(jc, jk, jb)
          z_alpha(jc, jk) = p_nh % metrics % vwind_impl_wgt(jc, jb) * p_nh % diag % theta_v_ic(jc, jk, jb) * p_nh % diag % rho_ic(jc, jk, jb)
        END DO
      END DO
      DO jc = i_startidx, i_endidx
        z_alpha(jc, nlevp1) = 0.0D0
        z_q(jc, 1) = 0.0D0
      END DO
      IF (.NOT. l_vert_nested) THEN
        DO jc = i_startidx, i_endidx
          p_nh_prog_nnew % w(jc, 1, jb) = 0.0D0
          z_contr_w_fl_l(jc, 1) = 0.0D0
        END DO
      ELSE
        DO jc = i_startidx, i_endidx
          p_nh_prog_nnew % w(jc, 1, jb) = p_nh % diag % w_ubc(jc, jb, 1) + dt_linintp_ubc_nnew * p_nh % diag % w_ubc(jc, jb, 2)
          z_contr_w_fl_l(jc, 1) = z_mflx_top(jc, jb) * p_nh % metrics % vwind_expl_wgt(jc, jb)
        END DO
      END IF
      DO jc = i_startidx, i_endidx
        p_nh_prog_nnew % w(jc, nlevp1, jb) = p_nh % diag % w_concorr_c(jc, nlevp1, jb)
        z_contr_w_fl_l(jc, nlevp1) = 0.0D0
      END DO
      DO jc = i_startidx, i_endidx
        z_rho_expl(jc, 1) = p_nh_prog_nnow % rho(jc, 1, jb) - dtime * p_nh % metrics % inv_ddqz_z_full(jc, 1, jb) * (z_flxdiv_mass(jc, 1) + z_contr_w_fl_l(jc, 1) * p_nh % metrics % deepatmo_divzu_mc(1) - z_contr_w_fl_l(jc, 2) * p_nh % metrics % deepatmo_divzl_mc(1))
        z_exner_expl(jc, 1) = p_nh % diag % exner_pr(jc, 1, jb) - z_beta(jc, 1) * (z_flxdiv_theta(jc, 1) + p_nh % diag % theta_v_ic(jc, 1, jb) * z_contr_w_fl_l(jc, 1) * p_nh % metrics % deepatmo_divzu_mc(1) - p_nh % diag % theta_v_ic(jc, 2, jb) * z_contr_w_fl_l(jc, 2) * p_nh % metrics % deepatmo_divzl_mc(1)) + dtime * p_nh % diag % ddt_exner_phy(jc, 1, jb)
      END DO
      DO jk = 2, nlev
        DO jc = i_startidx, i_endidx
          z_rho_expl(jc, jk) = p_nh_prog_nnow % rho(jc, jk, jb) - dtime * p_nh % metrics % inv_ddqz_z_full(jc, jk, jb) * (z_flxdiv_mass(jc, jk) + z_contr_w_fl_l(jc, jk) * p_nh % metrics % deepatmo_divzu_mc(jk) - z_contr_w_fl_l(jc, jk + 1) * p_nh % metrics % deepatmo_divzl_mc(jk))
          z_exner_expl(jc, jk) = p_nh % diag % exner_pr(jc, jk, jb) - z_beta(jc, jk) * (z_flxdiv_theta(jc, jk) + p_nh % diag % theta_v_ic(jc, jk, jb) * z_contr_w_fl_l(jc, jk) * p_nh % metrics % deepatmo_divzu_mc(jk) - p_nh % diag % theta_v_ic(jc, jk + 1, jb) * z_contr_w_fl_l(jc, jk + 1) * p_nh % metrics % deepatmo_divzl_mc(jk)) + dtime * p_nh % diag % ddt_exner_phy(jc, jk, jb)
        END DO
      END DO
      IF (is_iau_active) THEN
        DO jk = 1, nlev
          DO jc = i_startidx, i_endidx
            z_rho_expl(jc, jk) = z_rho_expl(jc, jk) + iau_wgt_dyn * p_nh % diag % rho_incr(jc, jk, jb)
            z_exner_expl(jc, jk) = z_exner_expl(jc, jk) + iau_wgt_dyn * p_nh % diag % exner_incr(jc, jk, jb)
          END DO
        END DO
      END IF
      DO jk = 2, nlev
        DO jc = i_startidx, i_endidx
          z_gamma = dtime * 1004.64D0 * p_nh % metrics % vwind_impl_wgt(jc, jb) * p_nh % diag % theta_v_ic(jc, jk, jb) / p_nh % metrics % ddqz_z_half(jc, jk, jb)
          z_a = - z_gamma * z_beta(jc, jk - 1) * z_alpha(jc, jk - 1) * p_nh % metrics % deepatmo_divzu_mc(jk - 1)
          z_c = - z_gamma * z_beta(jc, jk) * z_alpha(jc, jk + 1) * p_nh % metrics % deepatmo_divzl_mc(jk)
          z_b = 1.0D0 + z_gamma * z_alpha(jc, jk) * (z_beta(jc, jk - 1) * p_nh % metrics % deepatmo_divzl_mc(jk - 1) + z_beta(jc, jk) * p_nh % metrics % deepatmo_divzu_mc(jk))
          z_g = 1.0D0 / (z_b + z_a * z_q(jc, jk - 1))
          z_q(jc, jk) = - z_c * z_g
          p_nh_prog_nnew % w(jc, jk, jb) = z_w_expl(jc, jk) - z_gamma * (z_exner_expl(jc, jk - 1) - z_exner_expl(jc, jk))
          p_nh_prog_nnew % w(jc, jk, jb) = (p_nh_prog_nnew % w(jc, jk, jb) - z_a * p_nh_prog_nnew % w(jc, jk - 1, jb)) * z_g
        END DO
      END DO
      DO jk = nlev - 1, 2, - 1
        DO jc = i_startidx, i_endidx
          p_nh_prog_nnew % w(jc, jk, jb) = p_nh_prog_nnew % w(jc, jk, jb) + p_nh_prog_nnew % w(jc, jk + 1, jb) * z_q(jc, jk)
        END DO
      END DO
      IF (rayleigh_type == 2) THEN
        DO jk = 2, nrdmax(jg)
          DO jc = i_startidx, i_endidx
            p_nh_prog_nnew % w(jc, jk, jb) = z_raylfac(jk) * p_nh_prog_nnew % w(jc, jk, jb) + (1.0D0 - z_raylfac(jk)) * p_nh_prog_nnew % w(jc, 1, jb)
          END DO
        END DO
      ELSE IF (rayleigh_type == 1) THEN
        DO jk = 2, nrdmax(jg)
          DO jc = i_startidx, i_endidx
            p_nh_prog_nnew % w(jc, jk, jb) = p_nh_prog_nnew % w(jc, jk, jb) - dtime * p_nh % metrics % rayleigh_w(jk) * (p_nh_prog_nnew % w(jc, jk, jb) - p_nh % ref % w_ref(jc, jk, jb))
          END DO
        END DO
      END IF
      DO jk = jk_start, nlev
        DO jc = i_startidx, i_endidx
          p_nh_prog_nnew % rho(jc, jk, jb) = z_rho_expl(jc, jk) - p_nh % metrics % vwind_impl_wgt(jc, jb) * dtime * p_nh % metrics % inv_ddqz_z_full(jc, jk, jb) * (p_nh % diag % rho_ic(jc, jk, jb) * p_nh_prog_nnew % w(jc, jk, jb) * p_nh % metrics % deepatmo_divzu_mc(jk) - p_nh % diag % rho_ic(jc, jk + 1, jb) * p_nh_prog_nnew % w(jc, jk + 1, jb) * p_nh % metrics % deepatmo_divzl_mc(jk))
          p_nh_prog_nnew % exner(jc, jk, jb) = z_exner_expl(jc, jk) + p_nh % metrics % exner_ref_mc(jc, jk, jb) - z_beta(jc, jk) * (z_alpha(jc, jk) * p_nh_prog_nnew % w(jc, jk, jb) * p_nh % metrics % deepatmo_divzu_mc(jk) - z_alpha(jc, jk + 1) * p_nh_prog_nnew % w(jc, jk + 1, jb) * p_nh % metrics % deepatmo_divzl_mc(jk))
          p_nh_prog_nnew % theta_v(jc, jk, jb) = p_nh_prog_nnow % rho(jc, jk, jb) * p_nh_prog_nnow % theta_v(jc, jk, jb) * ((p_nh_prog_nnew % exner(jc, jk, jb) / p_nh_prog_nnow % exner(jc, jk, jb) - 1.0D0) * 2.4999999999999996D0 + 1.0D0) / p_nh_prog_nnew % rho(jc, jk, jb)
        END DO
      END DO
      IF (l_vert_nested) THEN
        DO jc = i_startidx, i_endidx
          p_nh_prog_nnew % rho(jc, 1, jb) = z_rho_expl(jc, 1) - p_nh % metrics % vwind_impl_wgt(jc, jb) * dtime * p_nh % metrics % inv_ddqz_z_full(jc, 1, jb) * (z_mflx_top(jc, jb) * p_nh % metrics % deepatmo_divzu_mc(1) - p_nh % diag % rho_ic(jc, 2, jb) * p_nh_prog_nnew % w(jc, 2, jb) * p_nh % metrics % deepatmo_divzl_mc(1))
          p_nh_prog_nnew % exner(jc, 1, jb) = z_exner_expl(jc, 1) + p_nh % metrics % exner_ref_mc(jc, 1, jb) - z_beta(jc, 1) * (p_nh % metrics % vwind_impl_wgt(jc, jb) * p_nh % diag % theta_v_ic(jc, 1, jb) * z_mflx_top(jc, jb) * p_nh % metrics % deepatmo_divzu_mc(1) - z_alpha(jc, 2) * p_nh_prog_nnew % w(jc, 2, jb) * p_nh % metrics % deepatmo_divzl_mc(1))
          p_nh_prog_nnew % theta_v(jc, 1, jb) = p_nh_prog_nnow % rho(jc, 1, jb) * p_nh_prog_nnow % theta_v(jc, 1, jb) * ((p_nh_prog_nnew % exner(jc, 1, jb) / p_nh_prog_nnow % exner(jc, 1, jb) - 1.0D0) * 2.4999999999999996D0 + 1.0D0) / p_nh_prog_nnew % rho(jc, 1, jb)
        END DO
      END IF
      IF (.TRUE. .AND. divdamp_type >= 3) THEN
        DO jk = kstart_dd3d(jg), nlev
          DO jc = i_startidx, i_endidx
            z_dwdz_dd(jc, jk, jb) = p_nh % metrics % inv_ddqz_z_full(jc, jk, jb) * ((p_nh_prog_nnew % w(jc, jk, jb) - p_nh_prog_nnew % w(jc, jk + 1, jb)) - (p_nh % diag % w_concorr_c(jc, jk, jb) - p_nh % diag % w_concorr_c(jc, jk + 1, jb)))
          END DO
        END DO
      END IF
      IF (.TRUE. .AND. idyn_timestep == 1) THEN
        DO jk = kstart_moist(jg), nlev
          DO jc = i_startidx, i_endidx
            p_nh % diag % exner_dyn_incr(jc, jk, jb) = p_nh_prog_nnow % exner(jc, jk, jb)
          END DO
        END DO
      ELSE IF (.FALSE.) THEN
        DO jk = kstart_moist(jg), nlev
          DO jc = i_startidx, i_endidx
            p_nh % diag % exner_dyn_incr(jc, jk, jb) = p_nh_prog_nnew % exner(jc, jk, jb) - (p_nh % diag % exner_dyn_incr(jc, jk, jb) + ndyn_substeps_var(jg) * dtime * p_nh % diag % ddt_exner_phy(jc, jk, jb))
          END DO
        END DO
      END IF
    END DO
    IF (l_limited_area .OR. jg > 1) THEN
      rl_start = 1
      rl_end = 4
      i_startblk = p_patch % cells % start_block(1)
      i_endblk = p_patch % cells % end_block(4)
      DO jb = i_startblk, i_endblk
        CALL get_indices_c(p_patch, jb, i_startblk, i_endblk, i_startidx, i_endidx, 1, 4)
        IF (.TRUE. .AND. my_process_is_mpi_all_seq()) THEN
          DO jk = 1, nlev
            DO jc = i_startidx, i_endidx
              p_nh_prog_nnew % rho(jc, jk, jb) = p_nh_prog_nnow % rho(jc, jk, jb) + dtime * p_nh % diag % grf_tend_rho(jc, jk, jb)
              p_nh_prog_nnew % theta_v(jc, jk, jb) = p_nh_prog_nnow % theta_v(jc, jk, jb) + dtime * p_nh % diag % grf_tend_thv(jc, jk, jb)
              p_nh_prog_nnew % exner(jc, jk, jb) = EXP(0.4000000000000001D0 * LOG(0.0028704000000000004D0 * p_nh_prog_nnew % rho(jc, jk, jb) * p_nh_prog_nnew % theta_v(jc, jk, jb)))
              p_nh_prog_nnew % w(jc, jk, jb) = p_nh_prog_nnow % w(jc, jk, jb) + dtime * p_nh % diag % grf_tend_w(jc, jk, jb)
            END DO
          END DO
          DO jc = i_startidx, i_endidx
            p_nh_prog_nnew % w(jc, nlevp1, jb) = p_nh_prog_nnow % w(jc, nlevp1, jb) + dtime * p_nh % diag % grf_tend_w(jc, nlevp1, jb)
          END DO
        ELSE IF (.TRUE.) THEN
          DO jk = 1, nlev
            DO jc = i_startidx, i_endidx
              p_nh_prog_nnew % rho(jc, jk, jb) = p_nh_prog_nnow % rho(jc, jk, jb) + dtime * p_nh % diag % grf_tend_rho(jc, jk, jb)
              p_nh_prog_nnew % exner(jc, jk, jb) = p_nh_prog_nnow % theta_v(jc, jk, jb) + dtime * p_nh % diag % grf_tend_thv(jc, jk, jb)
              p_nh_prog_nnew % w(jc, jk, jb) = p_nh_prog_nnow % w(jc, jk, jb) + dtime * p_nh % diag % grf_tend_w(jc, jk, jb)
            END DO
          END DO
          DO jc = i_startidx, i_endidx
            p_nh_prog_nnew % w(jc, nlevp1, jb) = p_nh_prog_nnow % w(jc, nlevp1, jb) + dtime * p_nh % diag % grf_tend_w(jc, nlevp1, jb)
          END DO
        END IF
        IF (.TRUE. .AND. divdamp_type >= 3) THEN
          DO jk = kstart_dd3d(jg), nlev
            DO jc = i_startidx, i_endidx
              z_dwdz_dd(jc, jk, jb) = p_nh % metrics % inv_ddqz_z_full(jc, jk, jb) * ((p_nh_prog_nnew % w(jc, jk, jb) - p_nh_prog_nnew % w(jc, jk + 1, jb)) - (p_nh % diag % w_concorr_c(jc, jk, jb) - p_nh % diag % w_concorr_c(jc, jk + 1, jb)))
            END DO
          END DO
        END IF
      END DO
    END IF
  END SUBROUTINE solve_nh_predictor_post
  SUBROUTINE solve_nh_corrector_pre(p_nh, p_nh_prog_nnow, p_nh_prog_nnew, p_patch, p_int, prep_adv, nnow, nnew, l_init, l_recompute, lsave_mflx, lprep_adv, lclean_mflx, idyn_timestep, jstep, dtime, lacc, jb, jk, jc, je, jks, jg, nlev, nlevp1, i_startblk, i_endblk, i_startidx, i_endidx, ishift, rl_start, rl_end, istep, ntl1, ntl2, nvar, nshift, nshift_total, z_theta_v_fl_e, z_theta_v_e, z_rho_e, z_theta_v_v, z_rho_v, z_th_ddz_exner_c, z_dexner_dz_c, z_vt_ie, z_kin_hor_e, z_exner_ex_pr, z_gradh_exner, z_rth_pr, z_grad_rth, z_w_concorr_me, z_graddiv_vn, z_w_expl, z_vn_avg, z_mflx_top, z_contr_w_fl_l, z_rho_expl, z_exner_expl, z_theta_tavg_m1, z_theta_tavg, z_rho_tavg_m1, z_rho_tavg, z_alpha, z_beta, z_q, z_graddiv2_vn, z_theta_v_pr_ic, z_exner_ic, z_w_concorr_mc, z_flxdiv_mass, z_flxdiv_theta, z_hydro_corr, z_a, z_b, z_c, z_g, z_gamma, z_w_backtraj, z_theta_v_pr_mc_m1, z_theta_v_pr_mc, z_theta1, z_theta2, wgt_nnow_vel, wgt_nnew_vel, dt_shift, wgt_nnow_rth, wgt_nnew_rth, dthalf, r_nsubsteps, r_dtimensubsteps, scal_divdamp_o2, alin, dz32, df32, dz42, df42, bqdr, aqdr, zf, dzlin, dzqdr, dt_linintp_ubc, dt_linintp_ubc_nnow, dt_linintp_ubc_nnew, z_raylfac, z_ntdistv_bary_1, distv_bary_1, z_ntdistv_bary_2, distv_bary_2, scal_divdamp, bdy_divdamp, enh_divdamp_fac, z_dwdz_dd, z_ddt_vn_dyn, z_ddt_vn_apc, z_ddt_vn_cor, z_ddt_vn_pgr, z_ddt_vn_ray, z_d_vn_dmp, z_d_vn_iau, nproma_gradp, nblks_gradp, npromz_gradp, nlen_gradp, jk_start, lvn_only, lvn_pos, l_vert_nested, l_child_vertnest)
    USE mo_nonhydro_types, ONLY: t_nh_prog, t_nh_state
    USE mo_intp_data_strc, ONLY: t_int_state
    USE mo_model_domain, ONLY: t_patch
    USE mo_prepadv_types, ONLY: t_prepare_adv
    USE mo_parallel_config, ONLY: nproma
    USE mo_vertical_grid, ONLY: nrdmax
    USE mo_nonhydrostatic_config, ONLY: divdamp_fac, divdamp_fac_o2, divdamp_order, divdamp_type, itime_scheme, kstart_dd3d, rayleigh_type
    USE fake_mo_velocity_advection, ONLY: velocity_tendencies
    USE mo_dynamics_config, ONLY: ldeepatmo
    USE mo_run_config, ONLY: timers_level
    USE fake_mo_real_timer, ONLY: timer_start, timer_stop
    USE mo_timer, ONLY: timer_solve_nh_cellcomp, timer_solve_nh_vnupd
    USE fake_mo_loopindices, ONLY: get_indices_c, get_indices_e
    USE mo_grid_config, ONLY: l_limited_area
    USE mo_initicon_config, ONLY: iau_wgt_dyn, is_iau_active
    TYPE(t_nh_state), TARGET, INTENT(INOUT) :: p_nh
    TYPE(t_int_state), TARGET, INTENT(IN) :: p_int
    TYPE(t_patch), TARGET, INTENT(INOUT) :: p_patch
    TYPE(t_prepare_adv), TARGET, INTENT(INOUT) :: prep_adv
    TYPE(t_nh_prog), TARGET, INTENT(INOUT) :: p_nh_prog_nnow, p_nh_prog_nnew
    LOGICAL, INTENT(IN) :: l_init
    LOGICAL, INTENT(IN) :: l_recompute
    LOGICAL, INTENT(IN) :: lsave_mflx
    LOGICAL, INTENT(IN) :: lprep_adv
    LOGICAL, INTENT(IN) :: lclean_mflx
    INTEGER, INTENT(IN) :: idyn_timestep
    INTEGER, INTENT(IN) :: jstep
    INTEGER, INTENT(IN) :: nnow, nnew
    REAL(KIND = 8), INTENT(IN) :: dtime
    LOGICAL, INTENT(IN), OPTIONAL :: lacc
    INTEGER, INTENT(INOUT) :: jb, jk, jc, je, jks, jg
    INTEGER, INTENT(INOUT) :: nlev, nlevp1
    INTEGER, INTENT(INOUT) :: i_startblk, i_endblk, i_startidx, i_endidx, ishift
    INTEGER, INTENT(INOUT) :: rl_start, rl_end, istep, ntl1, ntl2, nvar, nshift, nshift_total
    REAL(KIND = 8), INTENT(INOUT) :: z_theta_v_fl_e(nproma, p_patch % nlev, p_patch % nblks_e), z_theta_v_e(nproma, p_patch % nlev, p_patch % nblks_e), z_rho_e(nproma, p_patch % nlev, p_patch % nblks_e), z_theta_v_v(nproma, p_patch % nlev, p_patch % nblks_v), z_rho_v(nproma, p_patch % nlev, p_patch % nblks_v)
    REAL(KIND = 8), INTENT(INOUT) :: z_th_ddz_exner_c(nproma, p_patch % nlev, p_patch % nblks_c), z_dexner_dz_c(2, nproma, p_patch % nlev, p_patch % nblks_c), z_vt_ie(nproma, p_patch % nlev, p_patch % nblks_e), z_kin_hor_e(nproma, p_patch % nlev, p_patch % nblks_e), z_exner_ex_pr(nproma, p_patch % nlevp1, p_patch % nblks_c), z_gradh_exner(nproma, p_patch % nlev, p_patch % nblks_e), z_rth_pr(2, nproma, p_patch % nlev, p_patch % nblks_c), z_grad_rth(4, nproma, p_patch % nlev, p_patch % nblks_c), z_w_concorr_me(nproma, p_patch % nlev, p_patch % nblks_e)
    REAL(KIND = 8), INTENT(INOUT) :: z_graddiv_vn(nproma, p_patch % nlev, p_patch % nblks_e)
    REAL(KIND = 8), INTENT(INOUT) :: z_w_expl(nproma, p_patch % nlevp1), z_vn_avg(nproma, p_patch % nlev), z_mflx_top(nproma, p_patch % nblks_c), z_contr_w_fl_l(nproma, p_patch % nlevp1), z_rho_expl(nproma, p_patch % nlev), z_exner_expl(nproma, p_patch % nlev)
    REAL(KIND = 8), INTENT(INOUT) :: z_theta_tavg_m1, z_theta_tavg, z_rho_tavg_m1, z_rho_tavg
    REAL(KIND = 8), INTENT(INOUT) :: z_alpha(nproma, p_patch % nlevp1), z_beta(nproma, p_patch % nlev), z_q(nproma, p_patch % nlev), z_graddiv2_vn(nproma, p_patch % nlev), z_theta_v_pr_ic(nproma, p_patch % nlevp1), z_exner_ic(nproma, p_patch % nlevp1), z_w_concorr_mc(nproma, p_patch % nlev), z_flxdiv_mass(nproma, p_patch % nlev), z_flxdiv_theta(nproma, p_patch % nlev), z_hydro_corr(nproma, p_patch % nblks_e)
    REAL(KIND = 8), INTENT(INOUT) :: z_a, z_b, z_c, z_g, z_gamma, z_w_backtraj, z_theta_v_pr_mc_m1, z_theta_v_pr_mc
    REAL(KIND = 8), INTENT(INOUT) :: z_theta1, z_theta2, wgt_nnow_vel, wgt_nnew_vel, dt_shift, wgt_nnow_rth, wgt_nnew_rth, dthalf, r_nsubsteps, r_dtimensubsteps, scal_divdamp_o2, alin, dz32, df32, dz42, df42, bqdr, aqdr, zf, dzlin, dzqdr
    REAL(KIND = 8), INTENT(INOUT) :: dt_linintp_ubc, dt_linintp_ubc_nnow, dt_linintp_ubc_nnew
    REAL(KIND = 8), INTENT(INOUT) :: z_raylfac(nrdmax(p_patch % id))
    REAL(KIND = 8), INTENT(INOUT) :: z_ntdistv_bary_1, distv_bary_1, z_ntdistv_bary_2, distv_bary_2
    REAL(KIND = 8), INTENT(INOUT), DIMENSION(p_patch % nlev) :: scal_divdamp, bdy_divdamp, enh_divdamp_fac
    REAL(KIND = 8), INTENT(INOUT) :: z_dwdz_dd(nproma, kstart_dd3d(p_patch % id) : p_patch % nlev, p_patch % nblks_c)
    REAL(KIND = 8), INTENT(INOUT) :: z_ddt_vn_dyn, z_ddt_vn_apc, z_ddt_vn_cor, z_ddt_vn_pgr, z_ddt_vn_ray, z_d_vn_dmp, z_d_vn_iau
    INTEGER, INTENT(INOUT) :: nproma_gradp, nblks_gradp, npromz_gradp, nlen_gradp, jk_start
    LOGICAL, INTENT(INOUT) :: lvn_only, lvn_pos
    LOGICAL, INTENT(INOUT) :: l_vert_nested, l_child_vertnest
    istep = 2
    lvn_only = .FALSE.
    CALL velocity_tendencies(p_nh_prog_nnew, p_patch, p_int, p_nh % metrics, p_nh % diag, z_w_concorr_me, z_kin_hor_e, z_vt_ie, ntl2, 2, .FALSE., dtime, dt_linintp_ubc_nnew, ldeepatmo)
    nvar = nnew
    IF (timers_level > 5) CALL timer_start(timer_solve_nh_cellcomp)
    rl_start = 3
    rl_end = (- 4)
    i_startblk = p_patch % cells % start_block(3)
    i_endblk = p_patch % cells % end_block((- 4))
    DO jb = i_startblk, i_endblk
      CALL get_indices_c(p_patch, jb, i_startblk, i_endblk, i_startidx, i_endidx, 3, (- 4))
      DO jk = 2, nlev
        DO jc = i_startidx, i_endidx
          z_w_backtraj = - (p_nh_prog_nnew % w(jc, jk, jb) - p_nh % diag % w_concorr_c(jc, jk, jb)) * dtime * 0.5D0 / p_nh % metrics % ddqz_z_half(jc, jk, jb)
          z_rho_tavg_m1 = wgt_nnow_rth * p_nh_prog_nnow % rho(jc, jk - 1, jb) + wgt_nnew_rth * p_nh_prog_nnew % rho(jc, jk - 1, jb)
          z_theta_tavg_m1 = wgt_nnow_rth * p_nh_prog_nnow % theta_v(jc, jk - 1, jb) + wgt_nnew_rth * p_nh_prog_nnew % theta_v(jc, jk - 1, jb)
          z_rho_tavg = wgt_nnow_rth * p_nh_prog_nnow % rho(jc, jk, jb) + wgt_nnew_rth * p_nh_prog_nnew % rho(jc, jk, jb)
          z_theta_tavg = wgt_nnow_rth * p_nh_prog_nnow % theta_v(jc, jk, jb) + wgt_nnew_rth * p_nh_prog_nnew % theta_v(jc, jk, jb)
          p_nh % diag % rho_ic(jc, jk, jb) = p_nh % metrics % wgtfac_c(jc, jk, jb) * z_rho_tavg + (1.0D0 - p_nh % metrics % wgtfac_c(jc, jk, jb)) * z_rho_tavg_m1 + z_w_backtraj * (z_rho_tavg_m1 - z_rho_tavg)
          z_theta_v_pr_mc_m1 = z_theta_tavg_m1 - p_nh % metrics % theta_ref_mc(jc, jk - 1, jb)
          z_theta_v_pr_mc = z_theta_tavg - p_nh % metrics % theta_ref_mc(jc, jk, jb)
          z_theta_v_pr_ic(jc, jk) = p_nh % metrics % wgtfac_c(jc, jk, jb) * z_theta_v_pr_mc + (1.0D0 - p_nh % metrics % wgtfac_c(jc, jk, jb)) * z_theta_v_pr_mc_m1
          p_nh % diag % theta_v_ic(jc, jk, jb) = p_nh % metrics % wgtfac_c(jc, jk, jb) * z_theta_tavg + (1.0D0 - p_nh % metrics % wgtfac_c(jc, jk, jb)) * z_theta_tavg_m1 + z_w_backtraj * (z_theta_tavg_m1 - z_theta_tavg)
          z_th_ddz_exner_c(jc, jk, jb) = p_nh % metrics % vwind_expl_wgt(jc, jb) * p_nh % diag % theta_v_ic(jc, jk, jb) * (p_nh % diag % exner_pr(jc, jk - 1, jb) - p_nh % diag % exner_pr(jc, jk, jb)) / p_nh % metrics % ddqz_z_half(jc, jk, jb) + z_theta_v_pr_ic(jc, jk) * p_nh % metrics % d_exner_dz_ref_ic(jc, jk, jb)
        END DO
      END DO
    END DO
    IF (timers_level > 5) THEN
      CALL timer_stop(timer_solve_nh_cellcomp)
      CALL timer_start(timer_solve_nh_vnupd)
    END IF
    IF (.TRUE. .AND. divdamp_type >= 3) THEN
      rl_start = 7
      rl_end = (- 10)
      i_startblk = p_patch % edges % start_block(7)
      i_endblk = p_patch % edges % end_block(- 10)
      DO jb = i_startblk, i_endblk
        CALL get_indices_e(p_patch, jb, i_startblk, i_endblk, i_startidx, i_endidx, 7, - 10)
        DO jk = kstart_dd3d(jg), nlev
          DO je = i_startidx, i_endidx
            z_graddiv_vn(je, jk, jb) = z_graddiv_vn(je, jk, jb) + p_nh % metrics % hmask_dd3d(je, jb) * p_nh % metrics % scalfac_dd3d(jk) * p_patch % edges % inv_dual_edge_length(je, jb) * (z_dwdz_dd(p_patch % edges % cell_idx(je, jb, 2), jk, p_patch % edges % cell_blk(je, jb, 2)) - z_dwdz_dd(p_patch % edges % cell_idx(je, jb, 1), jk, p_patch % edges % cell_blk(je, jb, 1)))
          END DO
        END DO
      END DO
    END IF
    rl_start = 10
    rl_end = (- 8)
    i_startblk = p_patch % edges % start_block(10)
    i_endblk = p_patch % edges % end_block((- 8))
    DO jb = i_startblk, i_endblk
      CALL get_indices_e(p_patch, jb, i_startblk, i_endblk, i_startidx, i_endidx, 10, (- 8))
      IF ((itime_scheme >= 4) .AND. .TRUE.) THEN
        DO jk = 1, nlev
          DO je = i_startidx, i_endidx
            z_ddt_vn_apc = p_nh % diag % ddt_vn_apc_pc(je, jk, jb, ntl1) * wgt_nnow_vel + p_nh % diag % ddt_vn_apc_pc(je, jk, jb, ntl2) * wgt_nnew_vel
            z_ddt_vn_pgr = - 1004.64D0 * z_theta_v_e(je, jk, jb) * z_gradh_exner(je, jk, jb)
            z_ddt_vn_dyn = z_ddt_vn_apc + z_ddt_vn_pgr + p_nh % diag % ddt_vn_phy(je, jk, jb)
            p_nh_prog_nnew % vn(je, jk, jb) = p_nh_prog_nnow % vn(je, jk, jb) + dtime * z_ddt_vn_dyn
            IF (p_nh % diag % ddt_vn_adv_is_associated .OR. p_nh % diag % ddt_vn_cor_is_associated) THEN
              z_ddt_vn_cor = p_nh % diag % ddt_vn_cor_pc(je, jk, jb, ntl1) * wgt_nnow_vel + p_nh % diag % ddt_vn_cor_pc(je, jk, jb, ntl2) * wgt_nnew_vel
              IF (p_nh % diag % ddt_vn_adv_is_associated) THEN
                p_nh % diag % ddt_vn_adv(je, jk, jb) = p_nh % diag % ddt_vn_adv(je, jk, jb) + r_nsubsteps * (z_ddt_vn_apc - z_ddt_vn_cor)
              END IF
              IF (p_nh % diag % ddt_vn_cor_is_associated) THEN
                p_nh % diag % ddt_vn_cor(je, jk, jb) = p_nh % diag % ddt_vn_cor(je, jk, jb) + r_nsubsteps * z_ddt_vn_cor
              END IF
            END IF
            IF (p_nh % diag % ddt_vn_pgr_is_associated) THEN
              p_nh % diag % ddt_vn_pgr(je, jk, jb) = p_nh % diag % ddt_vn_pgr(je, jk, jb) + r_nsubsteps * z_ddt_vn_pgr
            END IF
            IF (p_nh % diag % ddt_vn_phd_is_associated) THEN
              p_nh % diag % ddt_vn_phd(je, jk, jb) = p_nh % diag % ddt_vn_phd(je, jk, jb) + r_nsubsteps * p_nh % diag % ddt_vn_phy(je, jk, jb)
            END IF
            IF (p_nh % diag % ddt_vn_dyn_is_associated) THEN
              p_nh % diag % ddt_vn_dyn(je, jk, jb) = p_nh % diag % ddt_vn_dyn(je, jk, jb) + r_nsubsteps * z_ddt_vn_dyn
            END IF
          END DO
        END DO
      ELSE
        DO jk = 1, nlev
          DO je = i_startidx, i_endidx
            p_nh_prog_nnew % vn(je, jk, jb) = p_nh_prog_nnow % vn(je, jk, jb) + dtime * (p_nh % diag % ddt_vn_apc_pc(je, jk, jb, ntl1) - 1004.64D0 * z_theta_v_e(je, jk, jb) * z_gradh_exner(je, jk, jb) + p_nh % diag % ddt_vn_phy(je, jk, jb))
          END DO
        END DO
      END IF
      IF (divdamp_order == 4 .OR. divdamp_order == 24) THEN
        DO jk = 1, nlev
          DO je = i_startidx, i_endidx
            z_graddiv2_vn(je, jk) = p_int % geofac_grdiv(je, 1, jb) * z_graddiv_vn(je, jk, jb) + p_int % geofac_grdiv(je, 2, jb) * z_graddiv_vn(p_patch % edges % quad_idx(je, jb, 1), jk, p_patch % edges % quad_blk(je, jb, 1)) + p_int % geofac_grdiv(je, 3, jb) * z_graddiv_vn(p_patch % edges % quad_idx(je, jb, 2), jk, p_patch % edges % quad_blk(je, jb, 2)) + p_int % geofac_grdiv(je, 4, jb) * z_graddiv_vn(p_patch % edges % quad_idx(je, jb, 3), jk, p_patch % edges % quad_blk(je, jb, 3)) + p_int % geofac_grdiv(je, 5, jb) * z_graddiv_vn(p_patch % edges % quad_idx(je, jb, 4), jk, p_patch % edges % quad_blk(je, jb, 4))
          END DO
        END DO
      END IF
      IF (divdamp_order == 2 .OR. (divdamp_order == 24 .AND. scal_divdamp_o2 > 1D-06)) THEN
        DO jk = 1, nlev
          DO je = i_startidx, i_endidx
            z_d_vn_dmp = scal_divdamp_o2 * z_graddiv_vn(je, jk, jb)
            p_nh_prog_nnew % vn(je, jk, jb) = p_nh_prog_nnew % vn(je, jk, jb) + z_d_vn_dmp
            IF (p_nh % diag % ddt_vn_dmp_is_associated) THEN
              p_nh % diag % ddt_vn_dmp(je, jk, jb) = p_nh % diag % ddt_vn_dmp(je, jk, jb) + z_d_vn_dmp * r_dtimensubsteps
            END IF
            IF (p_nh % diag % ddt_vn_dyn_is_associated) THEN
              p_nh % diag % ddt_vn_dyn(je, jk, jb) = p_nh % diag % ddt_vn_dyn(je, jk, jb) + z_d_vn_dmp * r_dtimensubsteps
            END IF
          END DO
        END DO
      END IF
      IF (divdamp_order == 4 .OR. (divdamp_order == 24 .AND. divdamp_fac_o2 <= 4.0D0 * divdamp_fac)) THEN
        IF (l_limited_area .OR. jg > 1) THEN
          DO jk = 1, nlev
            DO je = i_startidx, i_endidx
              z_d_vn_dmp = (scal_divdamp(jk) + bdy_divdamp(jk) * p_int % nudgecoeff_e(je, jb)) * z_graddiv2_vn(je, jk)
              p_nh_prog_nnew % vn(je, jk, jb) = p_nh_prog_nnew % vn(je, jk, jb) + z_d_vn_dmp
              IF (p_nh % diag % ddt_vn_dmp_is_associated) THEN
                p_nh % diag % ddt_vn_dmp(je, jk, jb) = p_nh % diag % ddt_vn_dmp(je, jk, jb) + z_d_vn_dmp * r_dtimensubsteps
              END IF
              IF (p_nh % diag % ddt_vn_dyn_is_associated) THEN
                p_nh % diag % ddt_vn_dyn(je, jk, jb) = p_nh % diag % ddt_vn_dyn(je, jk, jb) + z_d_vn_dmp * r_dtimensubsteps
              END IF
            END DO
          END DO
        ELSE
          DO jk = 1, nlev
            DO je = i_startidx, i_endidx
              z_d_vn_dmp = scal_divdamp(jk) * z_graddiv2_vn(je, jk)
              p_nh_prog_nnew % vn(je, jk, jb) = p_nh_prog_nnew % vn(je, jk, jb) + z_d_vn_dmp
              IF (p_nh % diag % ddt_vn_dmp_is_associated) THEN
                p_nh % diag % ddt_vn_dmp(je, jk, jb) = p_nh % diag % ddt_vn_dmp(je, jk, jb) + z_d_vn_dmp * r_dtimensubsteps
              END IF
              IF (p_nh % diag % ddt_vn_dyn_is_associated) THEN
                p_nh % diag % ddt_vn_dyn(je, jk, jb) = p_nh % diag % ddt_vn_dyn(je, jk, jb) + z_d_vn_dmp * r_dtimensubsteps
              END IF
            END DO
          END DO
        END IF
      END IF
      IF (is_iau_active) THEN
        DO jk = 1, nlev
          DO je = i_startidx, i_endidx
            z_d_vn_iau = iau_wgt_dyn * p_nh % diag % vn_incr(je, jk, jb)
            p_nh_prog_nnew % vn(je, jk, jb) = p_nh_prog_nnew % vn(je, jk, jb) + z_d_vn_iau
            IF (p_nh % diag % ddt_vn_iau_is_associated) THEN
              p_nh % diag % ddt_vn_iau(je, jk, jb) = p_nh % diag % ddt_vn_iau(je, jk, jb) + z_d_vn_iau * r_dtimensubsteps
            END IF
            IF (p_nh % diag % ddt_vn_dyn_is_associated) THEN
              p_nh % diag % ddt_vn_dyn(je, jk, jb) = p_nh % diag % ddt_vn_dyn(je, jk, jb) + z_d_vn_iau * r_dtimensubsteps
            END IF
          END DO
        END DO
      END IF
      IF (rayleigh_type == 1) THEN
        DO jk = 1, nrdmax(jg)
          DO je = i_startidx, i_endidx
            z_ddt_vn_ray = - p_nh % metrics % rayleigh_vn(jk) * (p_nh_prog_nnew % vn(je, jk, jb) - p_nh % ref % vn_ref(je, jk, jb))
            p_nh_prog_nnew % vn(je, jk, jb) = p_nh_prog_nnew % vn(je, jk, jb) + z_ddt_vn_ray * dtime
            IF (p_nh % diag % ddt_vn_ray_is_associated) THEN
              p_nh % diag % ddt_vn_ray(je, jk, jb) = p_nh % diag % ddt_vn_ray(je, jk, jb) + z_ddt_vn_ray * r_nsubsteps
            END IF
            IF (p_nh % diag % ddt_vn_dyn_is_associated) THEN
              p_nh % diag % ddt_vn_dyn(je, jk, jb) = p_nh % diag % ddt_vn_dyn(je, jk, jb) + z_ddt_vn_ray * r_nsubsteps
            END IF
          END DO
        END DO
      END IF
    END DO
  END SUBROUTINE solve_nh_corrector_pre
  SUBROUTINE solve_nh_corrector_post(p_nh, p_nh_prog_nnow, p_nh_prog_nnew, p_patch, p_int, prep_adv, nnow, nnew, l_init, l_recompute, lsave_mflx, lprep_adv, lclean_mflx, idyn_timestep, jstep, dtime, lacc, jb, jk, jc, je, jks, jg, nlev, nlevp1, i_startblk, i_endblk, i_startidx, i_endidx, ishift, rl_start, rl_end, istep, ntl1, ntl2, nvar, nshift, nshift_total, z_theta_v_fl_e, z_theta_v_e, z_rho_e, z_theta_v_v, z_rho_v, z_th_ddz_exner_c, z_dexner_dz_c, z_vt_ie, z_kin_hor_e, z_exner_ex_pr, z_gradh_exner, z_rth_pr, z_grad_rth, z_w_concorr_me, z_graddiv_vn, z_w_expl, z_vn_avg, z_mflx_top, z_contr_w_fl_l, z_rho_expl, z_exner_expl, z_theta_tavg_m1, z_theta_tavg, z_rho_tavg_m1, z_rho_tavg, z_alpha, z_beta, z_q, z_graddiv2_vn, z_theta_v_pr_ic, z_exner_ic, z_w_concorr_mc, z_flxdiv_mass, z_flxdiv_theta, z_hydro_corr, z_a, z_b, z_c, z_g, z_gamma, z_w_backtraj, z_theta_v_pr_mc_m1, z_theta_v_pr_mc, z_theta1, z_theta2, wgt_nnow_vel, wgt_nnew_vel, dt_shift, wgt_nnow_rth, wgt_nnew_rth, dthalf, r_nsubsteps, r_dtimensubsteps, scal_divdamp_o2, alin, dz32, df32, dz42, df42, bqdr, aqdr, zf, dzlin, dzqdr, dt_linintp_ubc, dt_linintp_ubc_nnow, dt_linintp_ubc_nnew, z_raylfac, z_ntdistv_bary_1, distv_bary_1, z_ntdistv_bary_2, distv_bary_2, scal_divdamp, bdy_divdamp, enh_divdamp_fac, z_dwdz_dd, z_ddt_vn_dyn, z_ddt_vn_apc, z_ddt_vn_cor, z_ddt_vn_pgr, z_ddt_vn_ray, z_d_vn_dmp, z_d_vn_iau, nproma_gradp, nblks_gradp, npromz_gradp, nlen_gradp, jk_start, lvn_only, lvn_pos, l_vert_nested, l_child_vertnest)
    USE mo_nonhydro_types, ONLY: t_nh_prog, t_nh_state
    USE mo_intp_data_strc, ONLY: t_int_state
    USE mo_model_domain, ONLY: t_patch
    USE mo_prepadv_types, ONLY: t_prepare_adv
    USE mo_parallel_config, ONLY: nproma
    USE mo_vertical_grid, ONLY: nrdmax
    USE mo_nonhydrostatic_config, ONLY: itime_scheme, kstart_dd3d, kstart_moist, ndyn_substeps_var, rayleigh_type
    USE fake_mo_loopindices, ONLY: get_indices_c, get_indices_e
    USE mo_init_vgrid, ONLY: nflatlev
    USE mo_gridref_config, ONLY: grf_intmethod_e
    USE mo_run_config, ONLY: timers_level
    USE fake_mo_real_timer, ONLY: timer_start, timer_stop
    USE mo_timer, ONLY: timer_solve_nh_edgecomp, timer_solve_nh_vimpl
    USE mo_initicon_config, ONLY: iau_wgt_dyn, is_iau_active
    USE mo_grid_config, ONLY: l_limited_area
    TYPE(t_nh_state), TARGET, INTENT(INOUT) :: p_nh
    TYPE(t_int_state), TARGET, INTENT(IN) :: p_int
    TYPE(t_patch), TARGET, INTENT(INOUT) :: p_patch
    TYPE(t_prepare_adv), TARGET, INTENT(INOUT) :: prep_adv
    TYPE(t_nh_prog), TARGET, INTENT(INOUT) :: p_nh_prog_nnow, p_nh_prog_nnew
    LOGICAL, INTENT(IN) :: l_init
    LOGICAL, INTENT(IN) :: l_recompute
    LOGICAL, INTENT(IN) :: lsave_mflx
    LOGICAL, INTENT(IN) :: lprep_adv
    LOGICAL, INTENT(IN) :: lclean_mflx
    INTEGER, INTENT(IN) :: idyn_timestep
    INTEGER, INTENT(IN) :: jstep
    INTEGER, INTENT(IN) :: nnow, nnew
    REAL(KIND = 8), INTENT(IN) :: dtime
    LOGICAL, INTENT(IN), OPTIONAL :: lacc
    INTEGER, INTENT(INOUT) :: jb, jk, jc, je, jks, jg
    INTEGER, INTENT(INOUT) :: nlev, nlevp1
    INTEGER, INTENT(INOUT) :: i_startblk, i_endblk, i_startidx, i_endidx, ishift
    INTEGER, INTENT(INOUT) :: rl_start, rl_end, istep, ntl1, ntl2, nvar, nshift, nshift_total
    INTEGER :: ic
    REAL(KIND = 8), INTENT(INOUT) :: z_theta_v_fl_e(nproma, p_patch % nlev, p_patch % nblks_e), z_theta_v_e(nproma, p_patch % nlev, p_patch % nblks_e), z_rho_e(nproma, p_patch % nlev, p_patch % nblks_e), z_theta_v_v(nproma, p_patch % nlev, p_patch % nblks_v), z_rho_v(nproma, p_patch % nlev, p_patch % nblks_v)
    REAL(KIND = 8), INTENT(INOUT) :: z_th_ddz_exner_c(nproma, p_patch % nlev, p_patch % nblks_c), z_dexner_dz_c(2, nproma, p_patch % nlev, p_patch % nblks_c), z_vt_ie(nproma, p_patch % nlev, p_patch % nblks_e), z_kin_hor_e(nproma, p_patch % nlev, p_patch % nblks_e), z_exner_ex_pr(nproma, p_patch % nlevp1, p_patch % nblks_c), z_gradh_exner(nproma, p_patch % nlev, p_patch % nblks_e), z_rth_pr(2, nproma, p_patch % nlev, p_patch % nblks_c), z_grad_rth(4, nproma, p_patch % nlev, p_patch % nblks_c), z_w_concorr_me(nproma, p_patch % nlev, p_patch % nblks_e)
    REAL(KIND = 8), INTENT(INOUT) :: z_graddiv_vn(nproma, p_patch % nlev, p_patch % nblks_e)
    REAL(KIND = 8), INTENT(INOUT) :: z_w_expl(nproma, p_patch % nlevp1), z_vn_avg(nproma, p_patch % nlev), z_mflx_top(nproma, p_patch % nblks_c), z_contr_w_fl_l(nproma, p_patch % nlevp1), z_rho_expl(nproma, p_patch % nlev), z_exner_expl(nproma, p_patch % nlev)
    REAL(KIND = 8), INTENT(INOUT) :: z_theta_tavg_m1, z_theta_tavg, z_rho_tavg_m1, z_rho_tavg
    REAL(KIND = 8), INTENT(INOUT) :: z_alpha(nproma, p_patch % nlevp1), z_beta(nproma, p_patch % nlev), z_q(nproma, p_patch % nlev), z_graddiv2_vn(nproma, p_patch % nlev), z_theta_v_pr_ic(nproma, p_patch % nlevp1), z_exner_ic(nproma, p_patch % nlevp1), z_w_concorr_mc(nproma, p_patch % nlev), z_flxdiv_mass(nproma, p_patch % nlev), z_flxdiv_theta(nproma, p_patch % nlev), z_hydro_corr(nproma, p_patch % nblks_e)
    REAL(KIND = 8), INTENT(INOUT) :: z_a, z_b, z_c, z_g, z_gamma, z_w_backtraj, z_theta_v_pr_mc_m1, z_theta_v_pr_mc
    REAL(KIND = 8) :: z_w_concorr_mc_m0, z_w_concorr_mc_m1, z_w_concorr_mc_m2
    REAL(KIND = 8), INTENT(INOUT) :: z_theta1, z_theta2, wgt_nnow_vel, wgt_nnew_vel, dt_shift, wgt_nnow_rth, wgt_nnew_rth, dthalf, r_nsubsteps, r_dtimensubsteps, scal_divdamp_o2, alin, dz32, df32, dz42, df42, bqdr, aqdr, zf, dzlin, dzqdr
    REAL(KIND = 8), INTENT(INOUT) :: dt_linintp_ubc, dt_linintp_ubc_nnow, dt_linintp_ubc_nnew
    REAL(KIND = 8), INTENT(INOUT) :: z_raylfac(nrdmax(p_patch % id))
    REAL(KIND = 8), INTENT(INOUT) :: z_ntdistv_bary_1, distv_bary_1, z_ntdistv_bary_2, distv_bary_2
    REAL(KIND = 8), INTENT(INOUT), DIMENSION(p_patch % nlev) :: scal_divdamp, bdy_divdamp, enh_divdamp_fac
    REAL(KIND = 8), INTENT(INOUT) :: z_dwdz_dd(nproma, kstart_dd3d(p_patch % id) : p_patch % nlev, p_patch % nblks_c)
    REAL(KIND = 8), INTENT(INOUT) :: z_ddt_vn_dyn, z_ddt_vn_apc, z_ddt_vn_cor, z_ddt_vn_pgr, z_ddt_vn_ray, z_d_vn_dmp, z_d_vn_iau
    INTEGER, INTENT(INOUT) :: nproma_gradp, nblks_gradp, npromz_gradp, nlen_gradp, jk_start
    LOGICAL, INTENT(INOUT) :: lvn_only, lvn_pos
    LOGICAL, INTENT(INOUT) :: l_vert_nested, l_child_vertnest
    istep = 2
    rl_start = 5
    rl_end = (- 10)
    i_startblk = p_patch % edges % start_block(5)
    i_endblk = p_patch % edges % end_block((- 10))
    DO jb = i_startblk, i_endblk
      CALL get_indices_e(p_patch, jb, i_startblk, i_endblk, i_startidx, i_endidx, 5, (- 10))
      IF (itime_scheme >= 5) THEN
        DO jk = 1, nlev
          DO je = i_startidx, i_endidx
            z_vn_avg(je, jk) = p_int % e_flx_avg(je, 1, jb) * p_nh_prog_nnew % vn(je, jk, jb) + p_int % e_flx_avg(je, 2, jb) * p_nh_prog_nnew % vn(p_patch % edges % quad_idx(je, jb, 1), jk, p_patch % edges % quad_blk(je, jb, 1)) + p_int % e_flx_avg(je, 3, jb) * p_nh_prog_nnew % vn(p_patch % edges % quad_idx(je, jb, 2), jk, p_patch % edges % quad_blk(je, jb, 2)) + p_int % e_flx_avg(je, 4, jb) * p_nh_prog_nnew % vn(p_patch % edges % quad_idx(je, jb, 3), jk, p_patch % edges % quad_blk(je, jb, 3)) + p_int % e_flx_avg(je, 5, jb) * p_nh_prog_nnew % vn(p_patch % edges % quad_idx(je, jb, 4), jk, p_patch % edges % quad_blk(je, jb, 4))
            p_nh % diag % vt(je, jk, jb) = p_int % rbf_vec_coeff_e(1, je, jb) * p_nh_prog_nnew % vn(p_patch % edges % quad_idx(je, jb, 1), jk, p_patch % edges % quad_blk(je, jb, 1)) + p_int % rbf_vec_coeff_e(2, je, jb) * p_nh_prog_nnew % vn(p_patch % edges % quad_idx(je, jb, 2), jk, p_patch % edges % quad_blk(je, jb, 2)) + p_int % rbf_vec_coeff_e(3, je, jb) * p_nh_prog_nnew % vn(p_patch % edges % quad_idx(je, jb, 3), jk, p_patch % edges % quad_blk(je, jb, 3)) + p_int % rbf_vec_coeff_e(4, je, jb) * p_nh_prog_nnew % vn(p_patch % edges % quad_idx(je, jb, 4), jk, p_patch % edges % quad_blk(je, jb, 4))
          END DO
        END DO
      ELSE
        DO jk = 1, nlev
          DO je = i_startidx, i_endidx
            z_vn_avg(je, jk) = p_int % e_flx_avg(je, 1, jb) * p_nh_prog_nnew % vn(je, jk, jb) + p_int % e_flx_avg(je, 2, jb) * p_nh_prog_nnew % vn(p_patch % edges % quad_idx(je, jb, 1), jk, p_patch % edges % quad_blk(je, jb, 1)) + p_int % e_flx_avg(je, 3, jb) * p_nh_prog_nnew % vn(p_patch % edges % quad_idx(je, jb, 2), jk, p_patch % edges % quad_blk(je, jb, 2)) + p_int % e_flx_avg(je, 4, jb) * p_nh_prog_nnew % vn(p_patch % edges % quad_idx(je, jb, 3), jk, p_patch % edges % quad_blk(je, jb, 3)) + p_int % e_flx_avg(je, 5, jb) * p_nh_prog_nnew % vn(p_patch % edges % quad_idx(je, jb, 4), jk, p_patch % edges % quad_blk(je, jb, 4))
          END DO
        END DO
      END IF
      DO jk = 1, nlev
        DO je = i_startidx, i_endidx
          p_nh % diag % mass_fl_e(je, jk, jb) = z_rho_e(je, jk, jb) * z_vn_avg(je, jk) * p_nh % metrics % ddqz_z_full_e(je, jk, jb)
          z_theta_v_fl_e(je, jk, jb) = p_nh % diag % mass_fl_e(je, jk, jb) * z_theta_v_e(je, jk, jb)
        END DO
      END DO
      IF (lsave_mflx .AND. .TRUE.) THEN
        DO jk = 1, nlev
          DO je = i_startidx, i_endidx
            IF (p_patch % edges % refin_ctrl(je, jb) <= - 4 .AND. p_patch % edges % refin_ctrl(je, jb) >= - 6) THEN
              p_nh % diag % mass_fl_e_sv(je, jk, jb) = p_nh % diag % mass_fl_e(je, jk, jb)
            END IF
          END DO
        END DO
      END IF
      IF (lprep_adv .AND. .TRUE.) THEN
        IF (lclean_mflx) THEN
          DO jk = 1, nlev
            DO je = i_startidx, i_endidx
              prep_adv % vn_traj(je, jk, jb) = 0.0D0
              prep_adv % mass_flx_me(je, jk, jb) = 0.0D0
            END DO
          END DO
        END IF
        DO jk = 1, nlev
          DO je = i_startidx, i_endidx
            prep_adv % vn_traj(je, jk, jb) = prep_adv % vn_traj(je, jk, jb) + r_nsubsteps * z_vn_avg(je, jk)
            prep_adv % mass_flx_me(je, jk, jb) = prep_adv % mass_flx_me(je, jk, jb) + r_nsubsteps * p_nh % diag % mass_fl_e(je, jk, jb)
          END DO
        END DO
      END IF
      IF (.FALSE. .OR. itime_scheme >= 5) THEN
        DO jk = nflatlev(jg), nlev
          DO je = i_startidx, i_endidx
            z_w_concorr_me(je, jk, jb) = p_nh_prog_nnew % vn(je, jk, jb) * p_nh % metrics % ddxn_z_full(je, jk, jb) + p_nh % diag % vt(je, jk, jb) * p_nh % metrics % ddxt_z_full(je, jk, jb)
          END DO
        END DO
      END IF
    END DO
    IF (jg > 1 .AND. grf_intmethod_e == 6) THEN
      DO ic = 1, p_nh % metrics % bdy_mflx_e_dim
        je = p_nh % metrics % bdy_mflx_e_idx(ic)
        jb = p_nh % metrics % bdy_mflx_e_blk(ic)
        IF (lprep_adv .AND. .TRUE.) THEN
          DO jk = 1, nlev
            prep_adv % mass_flx_me(je, jk, jb) = prep_adv % mass_flx_me(je, jk, jb) - r_nsubsteps * p_nh % diag % mass_fl_e(je, jk, jb)
            prep_adv % vn_traj(je, jk, jb) = prep_adv % vn_traj(je, jk, jb) - r_nsubsteps * p_nh % diag % mass_fl_e(je, jk, jb) / (z_rho_e(je, jk, jb) * p_nh % metrics % ddqz_z_full_e(je, jk, jb))
          END DO
        END IF
        DO jk = 1, nlev
          p_nh % diag % mass_fl_e(je, jk, jb) = p_nh % diag % grf_bdy_mflx(jk, ic, 1) + REAL(jstep, 8) * dtime * p_nh % diag % grf_bdy_mflx(jk, ic, 2)
          z_theta_v_fl_e(je, jk, jb) = p_nh % diag % mass_fl_e(je, jk, jb) * z_theta_v_e(je, jk, jb)
        END DO
        IF (lprep_adv .AND. .TRUE.) THEN
          DO jk = 1, nlev
            prep_adv % mass_flx_me(je, jk, jb) = prep_adv % mass_flx_me(je, jk, jb) + r_nsubsteps * p_nh % diag % mass_fl_e(je, jk, jb)
            prep_adv % vn_traj(je, jk, jb) = prep_adv % vn_traj(je, jk, jb) + r_nsubsteps * p_nh % diag % mass_fl_e(je, jk, jb) / (z_rho_e(je, jk, jb) * p_nh % metrics % ddqz_z_full_e(je, jk, jb))
          END DO
        END IF
      END DO
    END IF
    IF (.FALSE. .OR. itime_scheme >= 5) THEN
      rl_start = 3
      rl_end = (- 5)
      i_startblk = p_patch % cells % start_block(3)
      i_endblk = p_patch % cells % end_block(- 5)
      DO jb = i_startblk, i_endblk
        CALL get_indices_c(p_patch, jb, i_startblk, i_endblk, i_startidx, i_endidx, 3, (- 5))
        DO jk = nflatlev(jg) + 1, nlev
          DO jc = i_startidx, i_endidx
            z_w_concorr_mc_m1 = p_int % e_bln_c_s(jc, 1, jb) * z_w_concorr_me(p_patch % cells % edge_idx(jc, jb, 1), jk - 1, p_patch % cells % edge_blk(jc, jb, 1)) + p_int % e_bln_c_s(jc, 2, jb) * z_w_concorr_me(p_patch % cells % edge_idx(jc, jb, 2), jk - 1, p_patch % cells % edge_blk(jc, jb, 2)) + p_int % e_bln_c_s(jc, 3, jb) * z_w_concorr_me(p_patch % cells % edge_idx(jc, jb, 3), jk - 1, p_patch % cells % edge_blk(jc, jb, 3))
            z_w_concorr_mc_m0 = p_int % e_bln_c_s(jc, 1, jb) * z_w_concorr_me(p_patch % cells % edge_idx(jc, jb, 1), jk, p_patch % cells % edge_blk(jc, jb, 1)) + p_int % e_bln_c_s(jc, 2, jb) * z_w_concorr_me(p_patch % cells % edge_idx(jc, jb, 2), jk, p_patch % cells % edge_blk(jc, jb, 2)) + p_int % e_bln_c_s(jc, 3, jb) * z_w_concorr_me(p_patch % cells % edge_idx(jc, jb, 3), jk, p_patch % cells % edge_blk(jc, jb, 3))
            p_nh % diag % w_concorr_c(jc, jk, jb) = p_nh % metrics % wgtfac_c(jc, jk, jb) * z_w_concorr_mc_m0 + (1.0D0 - p_nh % metrics % wgtfac_c(jc, jk, jb)) * z_w_concorr_mc_m1
          END DO
        END DO
        DO jc = i_startidx, i_endidx
          z_w_concorr_mc_m2 = p_int % e_bln_c_s(jc, 1, jb) * z_w_concorr_me(p_patch % cells % edge_idx(jc, jb, 1), nlev - 2, p_patch % cells % edge_blk(jc, jb, 1)) + p_int % e_bln_c_s(jc, 2, jb) * z_w_concorr_me(p_patch % cells % edge_idx(jc, jb, 2), nlev - 2, p_patch % cells % edge_blk(jc, jb, 2)) + p_int % e_bln_c_s(jc, 3, jb) * z_w_concorr_me(p_patch % cells % edge_idx(jc, jb, 3), nlev - 2, p_patch % cells % edge_blk(jc, jb, 3))
          z_w_concorr_mc_m1 = p_int % e_bln_c_s(jc, 1, jb) * z_w_concorr_me(p_patch % cells % edge_idx(jc, jb, 1), nlev - 1, p_patch % cells % edge_blk(jc, jb, 1)) + p_int % e_bln_c_s(jc, 2, jb) * z_w_concorr_me(p_patch % cells % edge_idx(jc, jb, 2), nlev - 1, p_patch % cells % edge_blk(jc, jb, 2)) + p_int % e_bln_c_s(jc, 3, jb) * z_w_concorr_me(p_patch % cells % edge_idx(jc, jb, 3), nlev - 1, p_patch % cells % edge_blk(jc, jb, 3))
          z_w_concorr_mc_m0 = p_int % e_bln_c_s(jc, 1, jb) * z_w_concorr_me(p_patch % cells % edge_idx(jc, jb, 1), nlev, p_patch % cells % edge_blk(jc, jb, 1)) + p_int % e_bln_c_s(jc, 2, jb) * z_w_concorr_me(p_patch % cells % edge_idx(jc, jb, 2), nlev, p_patch % cells % edge_blk(jc, jb, 2)) + p_int % e_bln_c_s(jc, 3, jb) * z_w_concorr_me(p_patch % cells % edge_idx(jc, jb, 3), nlev, p_patch % cells % edge_blk(jc, jb, 3))
          p_nh % diag % w_concorr_c(jc, nlevp1, jb) = p_nh % metrics % wgtfacq_c(jc, 1, jb) * z_w_concorr_mc_m0 + p_nh % metrics % wgtfacq_c(jc, 2, jb) * z_w_concorr_mc_m1 + p_nh % metrics % wgtfacq_c(jc, 3, jb) * z_w_concorr_mc_m2
        END DO
      END DO
    END IF
    IF (timers_level > 5) THEN
      CALL timer_stop(timer_solve_nh_edgecomp)
      CALL timer_start(timer_solve_nh_vimpl)
    END IF
    rl_start = 5
    rl_end = (- 4)
    i_startblk = p_patch % cells % start_block(5)
    i_endblk = p_patch % cells % end_block((- 4))
    IF (l_vert_nested) THEN
      jk_start = 2
    ELSE
      jk_start = 1
    END IF
    DO jb = i_startblk, i_endblk
      CALL get_indices_c(p_patch, jb, i_startblk, i_endblk, i_startidx, i_endidx, 5, (- 4))
      DO jk = 1, nlev
        DO jc = i_startidx, i_endidx
          z_flxdiv_mass(jc, jk) = p_nh % metrics % deepatmo_divh_mc(jk) * (p_nh % diag % mass_fl_e(p_patch % cells % edge_idx(jc, jb, 1), jk, p_patch % cells % edge_blk(jc, jb, 1)) * p_int % geofac_div(jc, 1, jb) + p_nh % diag % mass_fl_e(p_patch % cells % edge_idx(jc, jb, 2), jk, p_patch % cells % edge_blk(jc, jb, 2)) * p_int % geofac_div(jc, 2, jb) + p_nh % diag % mass_fl_e(p_patch % cells % edge_idx(jc, jb, 3), jk, p_patch % cells % edge_blk(jc, jb, 3)) * p_int % geofac_div(jc, 3, jb))
          z_flxdiv_theta(jc, jk) = p_nh % metrics % deepatmo_divh_mc(jk) * (z_theta_v_fl_e(p_patch % cells % edge_idx(jc, jb, 1), jk, p_patch % cells % edge_blk(jc, jb, 1)) * p_int % geofac_div(jc, 1, jb) + z_theta_v_fl_e(p_patch % cells % edge_idx(jc, jb, 2), jk, p_patch % cells % edge_blk(jc, jb, 2)) * p_int % geofac_div(jc, 2, jb) + z_theta_v_fl_e(p_patch % cells % edge_idx(jc, jb, 3), jk, p_patch % cells % edge_blk(jc, jb, 3)) * p_int % geofac_div(jc, 3, jb))
        END DO
      END DO
      IF (.TRUE. .AND. (itime_scheme >= 4)) THEN
        DO jk = 2, nlev
          DO jc = i_startidx, i_endidx
            z_w_expl(jc, jk) = p_nh_prog_nnow % w(jc, jk, jb) + dtime * (wgt_nnow_vel * p_nh % diag % ddt_w_adv_pc(jc, jk, jb, ntl1) + wgt_nnew_vel * p_nh % diag % ddt_w_adv_pc(jc, jk, jb, ntl2) - 1004.64D0 * z_th_ddz_exner_c(jc, jk, jb))
            z_contr_w_fl_l(jc, jk) = p_nh % diag % rho_ic(jc, jk, jb) * (p_nh % metrics % vwind_expl_wgt(jc, jb) * p_nh_prog_nnow % w(jc, jk, jb) - p_nh % diag % w_concorr_c(jc, jk, jb))
          END DO
        END DO
      ELSE
        DO jk = 2, nlev
          DO jc = i_startidx, i_endidx
            z_w_expl(jc, jk) = p_nh_prog_nnow % w(jc, jk, jb) + dtime * (p_nh % diag % ddt_w_adv_pc(jc, jk, jb, ntl1) - 1004.64D0 * z_th_ddz_exner_c(jc, jk, jb))
            z_contr_w_fl_l(jc, jk) = p_nh % diag % rho_ic(jc, jk, jb) * (p_nh % metrics % vwind_expl_wgt(jc, jb) * p_nh_prog_nnow % w(jc, jk, jb) - p_nh % diag % w_concorr_c(jc, jk, jb))
          END DO
        END DO
      END IF
      DO jk = 1, nlev
        DO jc = i_startidx, i_endidx
          z_beta(jc, jk) = dtime * 287.04D0 * p_nh_prog_nnow % exner(jc, jk, jb) / (717.5999999999999D0 * p_nh_prog_nnow % rho(jc, jk, jb) * p_nh_prog_nnow % theta_v(jc, jk, jb)) * p_nh % metrics % inv_ddqz_z_full(jc, jk, jb)
          z_alpha(jc, jk) = p_nh % metrics % vwind_impl_wgt(jc, jb) * p_nh % diag % theta_v_ic(jc, jk, jb) * p_nh % diag % rho_ic(jc, jk, jb)
        END DO
      END DO
      DO jc = i_startidx, i_endidx
        z_alpha(jc, nlevp1) = 0.0D0
        z_q(jc, 1) = 0.0D0
      END DO
      IF (.NOT. l_vert_nested) THEN
        DO jc = i_startidx, i_endidx
          p_nh_prog_nnew % w(jc, 1, jb) = 0.0D0
          z_contr_w_fl_l(jc, 1) = 0.0D0
        END DO
      ELSE
        DO jc = i_startidx, i_endidx
          p_nh_prog_nnew % w(jc, 1, jb) = p_nh % diag % w_ubc(jc, jb, 1) + dt_linintp_ubc_nnew * p_nh % diag % w_ubc(jc, jb, 2)
          z_contr_w_fl_l(jc, 1) = z_mflx_top(jc, jb) * p_nh % metrics % vwind_expl_wgt(jc, jb)
        END DO
      END IF
      DO jc = i_startidx, i_endidx
        p_nh_prog_nnew % w(jc, nlevp1, jb) = p_nh % diag % w_concorr_c(jc, nlevp1, jb)
        z_contr_w_fl_l(jc, nlevp1) = 0.0D0
      END DO
      DO jc = i_startidx, i_endidx
        z_rho_expl(jc, 1) = p_nh_prog_nnow % rho(jc, 1, jb) - dtime * p_nh % metrics % inv_ddqz_z_full(jc, 1, jb) * (z_flxdiv_mass(jc, 1) + z_contr_w_fl_l(jc, 1) * p_nh % metrics % deepatmo_divzu_mc(1) - z_contr_w_fl_l(jc, 2) * p_nh % metrics % deepatmo_divzl_mc(1))
        z_exner_expl(jc, 1) = p_nh % diag % exner_pr(jc, 1, jb) - z_beta(jc, 1) * (z_flxdiv_theta(jc, 1) + p_nh % diag % theta_v_ic(jc, 1, jb) * z_contr_w_fl_l(jc, 1) * p_nh % metrics % deepatmo_divzu_mc(1) - p_nh % diag % theta_v_ic(jc, 2, jb) * z_contr_w_fl_l(jc, 2) * p_nh % metrics % deepatmo_divzl_mc(1)) + dtime * p_nh % diag % ddt_exner_phy(jc, 1, jb)
      END DO
      DO jk = 2, nlev
        DO jc = i_startidx, i_endidx
          z_rho_expl(jc, jk) = p_nh_prog_nnow % rho(jc, jk, jb) - dtime * p_nh % metrics % inv_ddqz_z_full(jc, jk, jb) * (z_flxdiv_mass(jc, jk) + z_contr_w_fl_l(jc, jk) * p_nh % metrics % deepatmo_divzu_mc(jk) - z_contr_w_fl_l(jc, jk + 1) * p_nh % metrics % deepatmo_divzl_mc(jk))
          z_exner_expl(jc, jk) = p_nh % diag % exner_pr(jc, jk, jb) - z_beta(jc, jk) * (z_flxdiv_theta(jc, jk) + p_nh % diag % theta_v_ic(jc, jk, jb) * z_contr_w_fl_l(jc, jk) * p_nh % metrics % deepatmo_divzu_mc(jk) - p_nh % diag % theta_v_ic(jc, jk + 1, jb) * z_contr_w_fl_l(jc, jk + 1) * p_nh % metrics % deepatmo_divzl_mc(jk)) + dtime * p_nh % diag % ddt_exner_phy(jc, jk, jb)
        END DO
      END DO
      IF (is_iau_active) THEN
        DO jk = 1, nlev
          DO jc = i_startidx, i_endidx
            z_rho_expl(jc, jk) = z_rho_expl(jc, jk) + iau_wgt_dyn * p_nh % diag % rho_incr(jc, jk, jb)
            z_exner_expl(jc, jk) = z_exner_expl(jc, jk) + iau_wgt_dyn * p_nh % diag % exner_incr(jc, jk, jb)
          END DO
        END DO
      END IF
      DO jk = 2, nlev
        DO jc = i_startidx, i_endidx
          z_gamma = dtime * 1004.64D0 * p_nh % metrics % vwind_impl_wgt(jc, jb) * p_nh % diag % theta_v_ic(jc, jk, jb) / p_nh % metrics % ddqz_z_half(jc, jk, jb)
          z_a = - z_gamma * z_beta(jc, jk - 1) * z_alpha(jc, jk - 1) * p_nh % metrics % deepatmo_divzu_mc(jk - 1)
          z_c = - z_gamma * z_beta(jc, jk) * z_alpha(jc, jk + 1) * p_nh % metrics % deepatmo_divzl_mc(jk)
          z_b = 1.0D0 + z_gamma * z_alpha(jc, jk) * (z_beta(jc, jk - 1) * p_nh % metrics % deepatmo_divzl_mc(jk - 1) + z_beta(jc, jk) * p_nh % metrics % deepatmo_divzu_mc(jk))
          z_g = 1.0D0 / (z_b + z_a * z_q(jc, jk - 1))
          z_q(jc, jk) = - z_c * z_g
          p_nh_prog_nnew % w(jc, jk, jb) = z_w_expl(jc, jk) - z_gamma * (z_exner_expl(jc, jk - 1) - z_exner_expl(jc, jk))
          p_nh_prog_nnew % w(jc, jk, jb) = (p_nh_prog_nnew % w(jc, jk, jb) - z_a * p_nh_prog_nnew % w(jc, jk - 1, jb)) * z_g
        END DO
      END DO
      DO jk = nlev - 1, 2, - 1
        DO jc = i_startidx, i_endidx
          p_nh_prog_nnew % w(jc, jk, jb) = p_nh_prog_nnew % w(jc, jk, jb) + p_nh_prog_nnew % w(jc, jk + 1, jb) * z_q(jc, jk)
        END DO
      END DO
      IF (rayleigh_type == 2) THEN
        DO jk = 2, nrdmax(jg)
          DO jc = i_startidx, i_endidx
            p_nh_prog_nnew % w(jc, jk, jb) = z_raylfac(jk) * p_nh_prog_nnew % w(jc, jk, jb) + (1.0D0 - z_raylfac(jk)) * p_nh_prog_nnew % w(jc, 1, jb)
          END DO
        END DO
      ELSE IF (rayleigh_type == 1) THEN
        DO jk = 2, nrdmax(jg)
          DO jc = i_startidx, i_endidx
            p_nh_prog_nnew % w(jc, jk, jb) = p_nh_prog_nnew % w(jc, jk, jb) - dtime * p_nh % metrics % rayleigh_w(jk) * (p_nh_prog_nnew % w(jc, jk, jb) - p_nh % ref % w_ref(jc, jk, jb))
          END DO
        END DO
      END IF
      DO jk = jk_start, nlev
        DO jc = i_startidx, i_endidx
          p_nh_prog_nnew % rho(jc, jk, jb) = z_rho_expl(jc, jk) - p_nh % metrics % vwind_impl_wgt(jc, jb) * dtime * p_nh % metrics % inv_ddqz_z_full(jc, jk, jb) * (p_nh % diag % rho_ic(jc, jk, jb) * p_nh_prog_nnew % w(jc, jk, jb) * p_nh % metrics % deepatmo_divzu_mc(jk) - p_nh % diag % rho_ic(jc, jk + 1, jb) * p_nh_prog_nnew % w(jc, jk + 1, jb) * p_nh % metrics % deepatmo_divzl_mc(jk))
          p_nh_prog_nnew % exner(jc, jk, jb) = z_exner_expl(jc, jk) + p_nh % metrics % exner_ref_mc(jc, jk, jb) - z_beta(jc, jk) * (z_alpha(jc, jk) * p_nh_prog_nnew % w(jc, jk, jb) * p_nh % metrics % deepatmo_divzu_mc(jk) - z_alpha(jc, jk + 1) * p_nh_prog_nnew % w(jc, jk + 1, jb) * p_nh % metrics % deepatmo_divzl_mc(jk))
          p_nh_prog_nnew % theta_v(jc, jk, jb) = p_nh_prog_nnow % rho(jc, jk, jb) * p_nh_prog_nnow % theta_v(jc, jk, jb) * ((p_nh_prog_nnew % exner(jc, jk, jb) / p_nh_prog_nnow % exner(jc, jk, jb) - 1.0D0) * 2.4999999999999996D0 + 1.0D0) / p_nh_prog_nnew % rho(jc, jk, jb)
        END DO
      END DO
      IF (l_vert_nested) THEN
        DO jc = i_startidx, i_endidx
          p_nh_prog_nnew % rho(jc, 1, jb) = z_rho_expl(jc, 1) - p_nh % metrics % vwind_impl_wgt(jc, jb) * dtime * p_nh % metrics % inv_ddqz_z_full(jc, 1, jb) * (z_mflx_top(jc, jb) * p_nh % metrics % deepatmo_divzu_mc(1) - p_nh % diag % rho_ic(jc, 2, jb) * p_nh_prog_nnew % w(jc, 2, jb) * p_nh % metrics % deepatmo_divzl_mc(1))
          p_nh_prog_nnew % exner(jc, 1, jb) = z_exner_expl(jc, 1) + p_nh % metrics % exner_ref_mc(jc, 1, jb) - z_beta(jc, 1) * (p_nh % metrics % vwind_impl_wgt(jc, jb) * p_nh % diag % theta_v_ic(jc, 1, jb) * z_mflx_top(jc, jb) * p_nh % metrics % deepatmo_divzu_mc(1) - z_alpha(jc, 2) * p_nh_prog_nnew % w(jc, 2, jb) * p_nh % metrics % deepatmo_divzl_mc(1))
          p_nh_prog_nnew % theta_v(jc, 1, jb) = p_nh_prog_nnow % rho(jc, 1, jb) * p_nh_prog_nnow % theta_v(jc, 1, jb) * ((p_nh_prog_nnew % exner(jc, 1, jb) / p_nh_prog_nnow % exner(jc, 1, jb) - 1.0D0) * 2.4999999999999996D0 + 1.0D0) / p_nh_prog_nnew % rho(jc, 1, jb)
        END DO
      END IF
      IF (lprep_adv .AND. .TRUE.) THEN
        IF (lclean_mflx) THEN
          DO jk = 1, nlev
            DO jc = i_startidx, i_endidx
              prep_adv % mass_flx_ic(jc, jk, jb) = 0.0D0
              prep_adv % vol_flx_ic(jc, jk, jb) = 0.0D0
            END DO
          END DO
        END IF
        DO jk = 2, nlev
          DO jc = i_startidx, i_endidx
            z_a = r_nsubsteps * (z_contr_w_fl_l(jc, jk) + p_nh % diag % rho_ic(jc, jk, jb) * p_nh % metrics % vwind_impl_wgt(jc, jb) * p_nh_prog_nnew % w(jc, jk, jb))
            prep_adv % mass_flx_ic(jc, jk, jb) = prep_adv % mass_flx_ic(jc, jk, jb) + z_a
            prep_adv % vol_flx_ic(jc, jk, jb) = prep_adv % vol_flx_ic(jc, jk, jb) + z_a / p_nh % diag % rho_ic(jc, jk, jb)
          END DO
        END DO
        IF (l_vert_nested) THEN
          DO jc = i_startidx, i_endidx
            prep_adv % mass_flx_ic(jc, 1, jb) = prep_adv % mass_flx_ic(jc, 1, jb) + r_nsubsteps * z_mflx_top(jc, jb)
            prep_adv % vol_flx_ic(jc, 1, jb) = prep_adv % vol_flx_ic(jc, 1, jb) + r_nsubsteps * z_mflx_top(jc, jb) / p_nh % diag % rho_ic(jc, 1, jb)
          END DO
        END IF
      END IF
      IF (.TRUE. .AND. idyn_timestep == ndyn_substeps_var(jg)) THEN
        DO jk = kstart_moist(jg), nlev
          DO jc = i_startidx, i_endidx
            p_nh % diag % exner_dyn_incr(jc, jk, jb) = p_nh_prog_nnew % exner(jc, jk, jb) - (p_nh % diag % exner_dyn_incr(jc, jk, jb) + ndyn_substeps_var(jg) * dtime * p_nh % diag % ddt_exner_phy(jc, jk, jb))
          END DO
        END DO
      END IF
      IF (.TRUE. .AND. l_child_vertnest) THEN
        DO jc = i_startidx, i_endidx
          p_nh % diag % w_int(jc, jb, idyn_timestep) = 0.5D0 * (p_nh_prog_nnow % w(jc, nshift, jb) + p_nh_prog_nnew % w(jc, nshift, jb))
          p_nh % diag % theta_v_ic_int(jc, jb, idyn_timestep) = p_nh % diag % theta_v_ic(jc, nshift, jb)
          p_nh % diag % rho_ic_int(jc, jb, idyn_timestep) = p_nh % diag % rho_ic(jc, nshift, jb)
          p_nh % diag % mflx_ic_int(jc, jb, idyn_timestep) = p_nh % diag % rho_ic(jc, nshift, jb) * (p_nh % metrics % vwind_expl_wgt(jc, jb) * p_nh_prog_nnow % w(jc, nshift, jb) + p_nh % metrics % vwind_impl_wgt(jc, jb) * p_nh_prog_nnew % w(jc, nshift, jb))
        END DO
      END IF
    END DO
    IF (l_limited_area .OR. jg > 1) THEN
      rl_start = 1
      rl_end = 4
      i_startblk = p_patch % cells % start_block(1)
      i_endblk = p_patch % cells % end_block(4)
      DO jb = i_startblk, i_endblk
        CALL get_indices_c(p_patch, jb, i_startblk, i_endblk, i_startidx, i_endidx, 1, 4)
        IF (lprep_adv .AND. .TRUE.) THEN
          IF (lclean_mflx) THEN
            prep_adv % mass_flx_ic(i_startidx : i_endidx, :, jb) = 0.0D0
          END IF
          DO jk = 2, nlev
            DO jc = i_startidx, i_endidx
              prep_adv % mass_flx_ic(jc, jk, jb) = prep_adv % mass_flx_ic(jc, jk, jb) + r_nsubsteps * p_nh % diag % rho_ic(jc, jk, jb) * (p_nh % metrics % vwind_expl_wgt(jc, jb) * p_nh_prog_nnow % w(jc, jk, jb) + p_nh % metrics % vwind_impl_wgt(jc, jb) * p_nh_prog_nnew % w(jc, jk, jb) - p_nh % diag % w_concorr_c(jc, jk, jb))
            END DO
          END DO
          IF (l_vert_nested) THEN
            DO jc = i_startidx, i_endidx
              prep_adv % mass_flx_ic(jc, 1, jb) = prep_adv % mass_flx_ic(jc, 1, jb) + r_nsubsteps * (p_nh % diag % mflx_ic_ubc(jc, jb, 1) + dt_linintp_ubc * p_nh % diag % mflx_ic_ubc(jc, jb, 2))
            END DO
          END IF
        END IF
      END DO
    END IF
  END SUBROUTINE solve_nh_corrector_post
END MODULE fake_mo_solve_nonhydro