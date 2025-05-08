MODULE global_mod
  TYPE :: global_data_type
    INTEGER :: nflatlev(10)
    LOGICAL, PUBLIC :: i_am_accel_node = .FALSE.
    LOGICAL :: lextra_diffu
    INTEGER :: nproma = 0
    INTEGER :: timers_level
    INTEGER :: timer_solve_nh_veltend
    INTEGER :: timer_intp
    INTEGER :: nrdmax(10)
  END TYPE global_data_type
END MODULE global_mod
MODULE mo_decomposition_tools
  IMPLICIT NONE
  TYPE :: t_grid_domain_decomp_info
    LOGICAL, ALLOCATABLE :: owner_mask(:, :)
  END TYPE
  CONTAINS
END MODULE mo_decomposition_tools
MODULE mo_fortran_tools
  IMPLICIT NONE
  CONTAINS
  PURE SUBROUTINE set_acc_host_or_device(global_data_var_1, lzacc_var_2, lacc_var_3)
    USE global_mod, ONLY: global_data_type
    TYPE(global_data_type) :: global_data_var_1
    LOGICAL, INTENT(OUT) :: lzacc_var_2
    LOGICAL, INTENT(IN), OPTIONAL :: lacc_var_3
    lzacc_var_2 = .FALSE.
  END SUBROUTINE set_acc_host_or_device
END MODULE mo_fortran_tools
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
END MODULE mo_intp_data_strc
MODULE mo_lib_loopindices
  IMPLICIT NONE
  CONTAINS
  SUBROUTINE get_indices_c_lib(global_data_var_4, i_startidx_in_var_5, i_endidx_in_var_6, nproma_var_7, i_blk_var_8, i_startblk_var_9, i_endblk_var_10, i_startidx_out_var_11, i_endidx_out_var_12)
    USE global_mod, ONLY: global_data_type
    TYPE(global_data_type) :: global_data_var_4
    INTEGER, INTENT(IN) :: i_startidx_in_var_5
    INTEGER, INTENT(IN) :: i_endidx_in_var_6
    INTEGER, INTENT(IN) :: nproma_var_7
    INTEGER, INTENT(IN) :: i_blk_var_8
    INTEGER, INTENT(IN) :: i_startblk_var_9
    INTEGER, INTENT(IN) :: i_endblk_var_10
    INTEGER, INTENT(OUT) :: i_startidx_out_var_11, i_endidx_out_var_12
    IF (i_blk_var_8 == i_startblk_var_9) THEN
      i_startidx_out_var_11 = MAX(1, i_startidx_in_var_5)
      i_endidx_out_var_12 = nproma_var_7
      IF (i_blk_var_8 == i_endblk_var_10) i_endidx_out_var_12 = i_endidx_in_var_6
    ELSE IF (i_blk_var_8 == i_endblk_var_10) THEN
      i_startidx_out_var_11 = 1
      i_endidx_out_var_12 = i_endidx_in_var_6
    ELSE
      i_startidx_out_var_11 = 1
      i_endidx_out_var_12 = nproma_var_7
    END IF
  END SUBROUTINE get_indices_c_lib
  SUBROUTINE get_indices_e_lib(global_data_var_13, i_startidx_in_var_14, i_endidx_in_var_15, nproma_var_16, i_blk_var_17, i_startblk_var_18, i_endblk_var_19, i_startidx_out_var_20, i_endidx_out_var_21)
    USE global_mod, ONLY: global_data_type
    TYPE(global_data_type) :: global_data_var_13
    INTEGER, INTENT(IN) :: i_startidx_in_var_14
    INTEGER, INTENT(IN) :: i_endidx_in_var_15
    INTEGER, INTENT(IN) :: nproma_var_16
    INTEGER, INTENT(IN) :: i_blk_var_17
    INTEGER, INTENT(IN) :: i_startblk_var_18
    INTEGER, INTENT(IN) :: i_endblk_var_19
    INTEGER, INTENT(OUT) :: i_startidx_out_var_20, i_endidx_out_var_21
    i_startidx_out_var_20 = MERGE(1, MAX(1, i_startidx_in_var_14), i_blk_var_17 /= i_startblk_var_18)
    i_endidx_out_var_21 = MERGE(nproma_var_16, i_endidx_in_var_15, i_blk_var_17 /= i_endblk_var_19)
  END SUBROUTINE get_indices_e_lib
  SUBROUTINE get_indices_v_lib(global_data_var_22, i_startidx_in_var_23, i_endidx_in_var_24, nproma_var_25, i_blk_var_26, i_startblk_var_27, i_endblk_var_28, i_startidx_out_var_29, i_endidx_out_var_30)
    USE global_mod, ONLY: global_data_type
    TYPE(global_data_type) :: global_data_var_22
    INTEGER, INTENT(IN) :: i_startidx_in_var_23
    INTEGER, INTENT(IN) :: i_endidx_in_var_24
    INTEGER, INTENT(IN) :: nproma_var_25
    INTEGER, INTENT(IN) :: i_blk_var_26
    INTEGER, INTENT(IN) :: i_startblk_var_27
    INTEGER, INTENT(IN) :: i_endblk_var_28
    INTEGER, INTENT(OUT) :: i_startidx_out_var_29, i_endidx_out_var_30
    IF (i_blk_var_26 == i_startblk_var_27) THEN
      i_startidx_out_var_29 = i_startidx_in_var_23
      i_endidx_out_var_30 = nproma_var_25
      IF (i_blk_var_26 == i_endblk_var_28) i_endidx_out_var_30 = i_endidx_in_var_24
    ELSE IF (i_blk_var_26 == i_endblk_var_28) THEN
      i_startidx_out_var_29 = 1
      i_endidx_out_var_30 = i_endidx_in_var_24
    ELSE
      i_startidx_out_var_29 = 1
      i_endidx_out_var_30 = nproma_var_25
    END IF
  END SUBROUTINE get_indices_v_lib
END MODULE mo_lib_loopindices
MODULE mo_lib_interpolation_scalar
  IMPLICIT NONE
  CONTAINS
  SUBROUTINE cells2verts_scalar_ri_lib(global_data_var_31, p_cell_in_var_32, vert_cell_idx, vert_cell_blk, c_int_var_33, p_vert_out_var_34, i_startblk_var_35, i_endblk_var_36, i_startidx_in_var_37, i_endidx_in_var_38, slev_var_39, elev_var_40, nproma_var_41, lacc_var_42, acc_async)
    USE global_mod, ONLY: global_data_type
    USE mo_fortran_tools, ONLY: set_acc_host_or_device
    USE mo_lib_loopindices, ONLY: get_indices_v_lib
    TYPE(global_data_type) :: global_data_var_31
    REAL(KIND = 8), INTENT(IN) :: p_cell_in_var_32(:, :, :)
    INTEGER, TARGET, INTENT(IN) :: vert_cell_idx(:, :, :)
    INTEGER, TARGET, INTENT(IN) :: vert_cell_blk(:, :, :)
    REAL(KIND = 8), INTENT(IN) :: c_int_var_33(:, :, :)
    REAL(KIND = 8), INTENT(INOUT) :: p_vert_out_var_34(:, :, :)
    INTEGER, INTENT(IN) :: i_startblk_var_35
    INTEGER, INTENT(IN) :: i_endblk_var_36
    INTEGER, INTENT(IN) :: i_startidx_in_var_37
    INTEGER, INTENT(IN) :: i_endidx_in_var_38
    INTEGER, INTENT(IN) :: slev_var_39
    INTEGER, INTENT(IN) :: elev_var_40
    INTEGER, INTENT(IN) :: nproma_var_41
    LOGICAL, INTENT(IN), OPTIONAL :: lacc_var_42
    LOGICAL, INTENT(IN), OPTIONAL :: acc_async
    INTEGER :: jv_var_43, jk_var_44, jb_var_45
    INTEGER :: i_startidx_var_46, i_endidx_var_47
    LOGICAL :: lzacc_var_48
    CALL set_acc_host_or_device(global_data_var_31, lzacc_var_48, lacc_var_42)
    DO jb_var_45 = i_startblk_var_35, i_endblk_var_36
      CALL get_indices_v_lib(global_data_var_31, i_startidx_in_var_37, i_endidx_in_var_38, nproma_var_41, jb_var_45, i_startblk_var_35, i_endblk_var_36, i_startidx_var_46, i_endidx_var_47)
      DO jk_var_44 = 1, elev_var_40
        DO jv_var_43 = i_startidx_var_46, i_endidx_var_47
          p_vert_out_var_34(jv_var_43, jk_var_44, jb_var_45) = c_int_var_33(jv_var_43, 1, jb_var_45) * p_cell_in_var_32(vert_cell_idx(jv_var_43, jb_var_45, 1), jk_var_44, vert_cell_blk(jv_var_43, jb_var_45, 1)) + c_int_var_33(jv_var_43, 2, jb_var_45) * p_cell_in_var_32(vert_cell_idx(jv_var_43, jb_var_45, 2), jk_var_44, vert_cell_blk(jv_var_43, jb_var_45, 2)) + c_int_var_33(jv_var_43, 3, jb_var_45) * p_cell_in_var_32(vert_cell_idx(jv_var_43, jb_var_45, 3), jk_var_44, vert_cell_blk(jv_var_43, jb_var_45, 3)) + c_int_var_33(jv_var_43, 4, jb_var_45) * p_cell_in_var_32(vert_cell_idx(jv_var_43, jb_var_45, 4), jk_var_44, vert_cell_blk(jv_var_43, jb_var_45, 4)) + c_int_var_33(jv_var_43, 5, jb_var_45) * p_cell_in_var_32(vert_cell_idx(jv_var_43, jb_var_45, 5), jk_var_44, vert_cell_blk(jv_var_43, jb_var_45, 5)) + c_int_var_33(jv_var_43, 6, jb_var_45) * p_cell_in_var_32(vert_cell_idx(jv_var_43, jb_var_45, 6), jk_var_44, vert_cell_blk(jv_var_43, jb_var_45, 6))
        END DO
      END DO
    END DO
  END SUBROUTINE cells2verts_scalar_ri_lib
END MODULE mo_lib_interpolation_scalar
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
    INTEGER, ALLOCATABLE :: start_block(:)
    INTEGER, ALLOCATABLE :: end_block(:)
  END TYPE t_grid_vertices
  TYPE :: t_patch
    INTEGER :: nblks_c
    INTEGER :: nblks_e
    INTEGER :: nblks_v
    TYPE(t_grid_cells) :: cells
    TYPE(t_grid_edges) :: edges
    TYPE(t_grid_vertices) :: verts
  END TYPE t_patch
  CONTAINS
END MODULE mo_model_domain
MODULE mo_loopindices
  IMPLICIT NONE
  CONTAINS
  SUBROUTINE get_indices_c(global_data_var_69, p_patch_var_70, i_blk_var_71, i_startblk_var_72, i_endblk_var_73, i_startidx_var_76, i_endidx_var_77, irl_start_var_74, opt_rl_end_var_75)
    USE global_mod, ONLY: global_data_type
    USE mo_model_domain, ONLY: t_patch
    USE mo_lib_loopindices, ONLY: get_indices_c_lib
    TYPE(global_data_type) :: global_data_var_69
    TYPE(t_patch), INTENT(IN) :: p_patch_var_70
    INTEGER, INTENT(IN) :: i_blk_var_71
    INTEGER, INTENT(IN) :: i_startblk_var_72
    INTEGER, INTENT(IN) :: i_endblk_var_73
    INTEGER, INTENT(IN) :: irl_start_var_74
    INTEGER, OPTIONAL, INTENT(IN) :: opt_rl_end_var_75
    INTEGER, INTENT(OUT) :: i_startidx_var_76, i_endidx_var_77
    INTEGER :: irl_end_var_78, i_startidx_in_var_79, i_endidx_in_var_80
    i_startidx_in_var_79 = p_patch_var_70 % cells % start_index(irl_start_var_74)
    irl_end_var_78 = opt_rl_end_var_75
    i_endidx_in_var_80 = p_patch_var_70 % cells % end_index(irl_end_var_78)
    CALL get_indices_c_lib(global_data_var_69, i_startidx_in_var_79, i_endidx_in_var_80, global_data_var_69 % nproma, i_blk_var_71, i_startblk_var_72, i_endblk_var_73, i_startidx_var_76, i_endidx_var_77)
  END SUBROUTINE get_indices_c
  SUBROUTINE get_indices_e(global_data_var_81, p_patch_var_82, i_blk_var_83, i_startblk_var_84, i_endblk_var_85, i_startidx_var_88, i_endidx_var_89, irl_start_var_86, opt_rl_end_var_87)
    USE global_mod, ONLY: global_data_type
    USE mo_model_domain, ONLY: t_patch
    USE mo_lib_loopindices, ONLY: get_indices_e_lib
    TYPE(global_data_type) :: global_data_var_81
    TYPE(t_patch), INTENT(IN) :: p_patch_var_82
    INTEGER, INTENT(IN) :: i_blk_var_83
    INTEGER, INTENT(IN) :: i_startblk_var_84
    INTEGER, INTENT(IN) :: i_endblk_var_85
    INTEGER, INTENT(IN) :: irl_start_var_86
    INTEGER, OPTIONAL, INTENT(IN) :: opt_rl_end_var_87
    INTEGER, INTENT(OUT) :: i_startidx_var_88, i_endidx_var_89
    INTEGER :: irl_end_var_90, i_startidx_in_var_91, i_endidx_in_var_92
    i_startidx_in_var_91 = p_patch_var_82 % edges % start_index(irl_start_var_86)
    irl_end_var_90 = opt_rl_end_var_87
    i_endidx_in_var_92 = p_patch_var_82 % edges % end_index(irl_end_var_90)
    CALL get_indices_e_lib(global_data_var_81, i_startidx_in_var_91, i_endidx_in_var_92, global_data_var_81 % nproma, i_blk_var_83, i_startblk_var_84, i_endblk_var_85, i_startidx_var_88, i_endidx_var_89)
  END SUBROUTINE get_indices_e
  SUBROUTINE get_indices_v(global_data_var_93, p_patch_var_94, i_blk_var_95, i_startblk_var_96, i_endblk_var_97, i_startidx_var_100, i_endidx_var_101, irl_start_var_98, opt_rl_end_var_99)
    USE global_mod, ONLY: global_data_type
    USE mo_model_domain, ONLY: t_patch
    USE mo_lib_loopindices, ONLY: get_indices_v_lib
    TYPE(global_data_type) :: global_data_var_93
    TYPE(t_patch), INTENT(IN) :: p_patch_var_94
    INTEGER, INTENT(IN) :: i_blk_var_95
    INTEGER, INTENT(IN) :: i_startblk_var_96
    INTEGER, INTENT(IN) :: i_endblk_var_97
    INTEGER, INTENT(IN) :: irl_start_var_98
    INTEGER, OPTIONAL, INTENT(IN) :: opt_rl_end_var_99
    INTEGER, INTENT(OUT) :: i_startidx_var_100, i_endidx_var_101
    INTEGER :: irl_end_var_102, i_startidx_in_var_103, i_endidx_in_var_104
    i_startidx_in_var_103 = p_patch_var_94 % verts % start_index(2)
    irl_end_var_102 = -5
    i_endidx_in_var_104 = p_patch_var_94 % verts % end_index(- 5)
    CALL get_indices_v_lib(global_data_var_93, i_startidx_in_var_103, i_endidx_in_var_104, global_data_var_93 % nproma, i_blk_var_95, i_startblk_var_96, i_endblk_var_97, i_startidx_var_100, i_endidx_var_101)
  END SUBROUTINE get_indices_v
END MODULE mo_loopindices
MODULE mo_math_divrot
  IMPLICIT NONE
  CONTAINS
  SUBROUTINE rot_vertex_ri(global_data_var_105, vec_e, ptr_patch_var_106, ptr_int, rot_vec, opt_slev_var_107, opt_elev_var_108, opt_rlend_var_109, opt_acc_async_var_110)
    USE global_mod, ONLY: global_data_type
    USE mo_model_domain, ONLY: t_patch
    USE mo_intp_data_strc, ONLY: t_int_state
    USE mo_loopindices, ONLY: get_indices_v
    TYPE(global_data_type) :: global_data_var_105
    TYPE(t_patch), TARGET, INTENT(IN) :: ptr_patch_var_106
    TYPE(t_int_state), INTENT(IN) :: ptr_int
    REAL(KIND = 8), INTENT(IN) :: vec_e(:, :, :)
    INTEGER, INTENT(IN), OPTIONAL :: opt_slev_var_107
    INTEGER, INTENT(IN), OPTIONAL :: opt_elev_var_108
    INTEGER, INTENT(IN), OPTIONAL :: opt_rlend_var_109
    LOGICAL, INTENT(IN), OPTIONAL :: opt_acc_async_var_110
    REAL(KIND = 8), INTENT(INOUT) :: rot_vec(:, :, :)
    INTEGER :: slev_var_111, elev_var_112
    INTEGER :: jv_var_113, jk_var_114, jb_var_115
    INTEGER :: rl_start_var_116, rl_end_var_117
    INTEGER :: i_startblk_var_118, i_endblk_var_119, i_startidx_var_120, i_endidx_var_121
    slev_var_111 = 1
    elev_var_112 = UBOUND(vec_e, 2)
    rl_start_var_116 = 2
    rl_end_var_117 = -5
    i_startblk_var_118 = ptr_patch_var_106 % verts % start_block(2)
    i_endblk_var_119 = ptr_patch_var_106 % verts % end_block(- 5)
    DO jb_var_115 = i_startblk_var_118, i_endblk_var_119
      CALL get_indices_v(global_data_var_105, ptr_patch_var_106, jb_var_115, i_startblk_var_118, i_endblk_var_119, i_startidx_var_120, i_endidx_var_121, 2, - 5)
      DO jk_var_114 = slev_var_111, elev_var_112
        DO jv_var_113 = i_startidx_var_120, i_endidx_var_121
          rot_vec(jv_var_113, jk_var_114, jb_var_115) = vec_e(ptr_patch_var_106 % verts % edge_idx(jv_var_113, jb_var_115, 1), jk_var_114, ptr_patch_var_106 % verts % edge_blk(jv_var_113, jb_var_115, 1)) * ptr_int % geofac_rot(jv_var_113, 1, jb_var_115) + vec_e(ptr_patch_var_106 % verts % edge_idx(jv_var_113, jb_var_115, 2), jk_var_114, ptr_patch_var_106 % verts % edge_blk(jv_var_113, jb_var_115, 2)) * ptr_int % geofac_rot(jv_var_113, 2, jb_var_115) + vec_e(ptr_patch_var_106 % verts % edge_idx(jv_var_113, jb_var_115, 3), jk_var_114, ptr_patch_var_106 % verts % edge_blk(jv_var_113, jb_var_115, 3)) * ptr_int % geofac_rot(jv_var_113, 3, jb_var_115) + vec_e(ptr_patch_var_106 % verts % edge_idx(jv_var_113, jb_var_115, 4), jk_var_114, ptr_patch_var_106 % verts % edge_blk(jv_var_113, jb_var_115, 4)) * ptr_int % geofac_rot(jv_var_113, 4, jb_var_115) + vec_e(ptr_patch_var_106 % verts % edge_idx(jv_var_113, jb_var_115, 5), jk_var_114, ptr_patch_var_106 % verts % edge_blk(jv_var_113, jb_var_115, 5)) * ptr_int % geofac_rot(jv_var_113, 5, jb_var_115) + vec_e(ptr_patch_var_106 % verts % edge_idx(jv_var_113, jb_var_115, 6), jk_var_114, ptr_patch_var_106 % verts % edge_blk(jv_var_113, jb_var_115, 6)) * ptr_int % geofac_rot(jv_var_113, 6, jb_var_115)
        END DO
      END DO
    END DO
  END SUBROUTINE rot_vertex_ri
END MODULE mo_math_divrot
MODULE mo_nonhydro_types
  IMPLICIT NONE
  TYPE :: t_nh_prog
    REAL(KIND = 8), POINTER, CONTIGUOUS :: w(:, :, :), vn(:, :, :)
  END TYPE t_nh_prog
  TYPE :: t_nh_diag
    REAL(KIND = 8), POINTER, CONTIGUOUS :: vt(:, :, :), vn_ie(:, :, :), w_concorr_c(:, :, :), ddt_vn_apc_pc(:, :, :, :), ddt_w_adv_pc(:, :, :, :)
    REAL(KIND = 8) :: max_vcfl_dyn = 0.0D0
  END TYPE t_nh_diag
  TYPE :: t_nh_metrics
    REAL(KIND = 8), POINTER, CONTIGUOUS :: ddxn_z_full(:, :, :), ddxt_z_full(:, :, :), ddqz_z_full_e(:, :, :), ddqz_z_half(:, :, :), wgtfac_c(:, :, :), wgtfac_e(:, :, :), wgtfacq_e(:, :, :), coeff_gradekin(:, :, :), coeff1_dwdz(:, :, :), coeff2_dwdz(:, :, :)
    REAL(KIND = 8), POINTER, CONTIGUOUS :: deepatmo_gradh_mc(:), deepatmo_invr_mc(:), deepatmo_gradh_ifc(:), deepatmo_invr_ifc(:)
  END TYPE t_nh_metrics
END MODULE mo_nonhydro_types
MODULE mo_real_timer
  IMPLICIT NONE
  CONTAINS
  SUBROUTINE timer_start(global_data_var_123, it_var_124)
    USE global_mod, ONLY: global_data_type
    TYPE(global_data_type) :: global_data_var_123
    INTEGER, INTENT(IN) :: it_var_124
  END SUBROUTINE timer_start
  SUBROUTINE timer_stop(global_data_var_125, it_var_126)
    USE global_mod, ONLY: global_data_type
    TYPE(global_data_type) :: global_data_var_125
    INTEGER, INTENT(IN) :: it_var_126
  END SUBROUTINE timer_stop
END MODULE mo_real_timer
MODULE mo_icon_interpolation_scalar
  IMPLICIT NONE
  CONTAINS
  SUBROUTINE cells2verts_scalar_ri(global_data_var_127, p_cell_in_var_129, ptr_patch_var_128, c_int_var_130, p_vert_out_var_134, opt_slev_var_131, opt_elev_var_132, opt_rlstart, opt_rlend_var_133, opt_acc_async_var_135)
    USE global_mod, ONLY: global_data_type
    USE mo_model_domain, ONLY: t_patch
    USE mo_real_timer, ONLY: timer_start, timer_stop
    USE mo_lib_interpolation_scalar, ONLY: cells2verts_scalar_ri_lib
    TYPE(global_data_type) :: global_data_var_127
    TYPE(t_patch), TARGET, INTENT(IN) :: ptr_patch_var_128
    REAL(KIND = 8), INTENT(IN) :: p_cell_in_var_129(:, :, :)
    REAL(KIND = 8), INTENT(IN) :: c_int_var_130(:, :, :)
    INTEGER, INTENT(IN), OPTIONAL :: opt_slev_var_131
    INTEGER, INTENT(IN), OPTIONAL :: opt_elev_var_132
    INTEGER, INTENT(IN), OPTIONAL :: opt_rlstart, opt_rlend_var_133
    REAL(KIND = 8), INTENT(INOUT) :: p_vert_out_var_134(:, :, :)
    LOGICAL, INTENT(IN), OPTIONAL :: opt_acc_async_var_135
    INTEGER :: slev_var_136, elev_var_137
    INTEGER :: rl_start_var_138, rl_end_var_139
    INTEGER :: i_startblk_var_140, i_endblk_var_141, i_startidx_in_var_142, i_endidx_in_var_143
    slev_var_136 = 1
    elev_var_137 = UBOUND(p_cell_in_var_129, 2)
    rl_start_var_138 = 2
    rl_end_var_139 = -5
    i_startblk_var_140 = ptr_patch_var_128 % verts % start_block(2)
    i_endblk_var_141 = ptr_patch_var_128 % verts % end_block(- 5)
    i_startidx_in_var_142 = ptr_patch_var_128 % verts % start_index(2)
    i_endidx_in_var_143 = ptr_patch_var_128 % verts % end_index(- 5)
    IF (global_data_var_127 % timers_level > 10) CALL timer_start(global_data_var_127, global_data_var_127 % timer_intp)
    CALL cells2verts_scalar_ri_lib(global_data_var_127, p_cell_in_var_129, ptr_patch_var_128 % verts % cell_idx, ptr_patch_var_128 % verts % cell_blk, c_int_var_130, p_vert_out_var_134, i_startblk_var_140, i_endblk_var_141, i_startidx_in_var_142, i_endidx_in_var_143, 1, elev_var_137, global_data_var_127 % nproma, lacc_var_42 = global_data_var_127 % i_am_accel_node, acc_async = .TRUE.)
    IF (global_data_var_127 % timers_level > 10) CALL timer_stop(global_data_var_127, global_data_var_127 % timer_intp)
  END SUBROUTINE cells2verts_scalar_ri
END MODULE mo_icon_interpolation_scalar
MODULE mo_velocity_advection
  IMPLICIT NONE
  CONTAINS
  SUBROUTINE velocity_tendencies(global_data, p_prog, p_patch, p_int, p_metrics, p_diag, z_w_concorr_me, z_kin_hor_e, z_vt_ie, ntnd, istep, lvn_only, dtime, dt_linintp_ubc, ldeepatmo)
    USE global_mod, ONLY: global_data_type
    USE mo_model_domain, ONLY: t_patch
    USE mo_intp_data_strc, ONLY: t_int_state
    USE mo_nonhydro_types, ONLY: t_nh_diag, t_nh_metrics, t_nh_prog
    USE mo_real_timer, ONLY: timer_start, timer_stop
    USE mo_icon_interpolation_scalar, ONLY: cells2verts_scalar_ri
    USE mo_math_divrot, ONLY: rot_vertex_ri
    USE mo_loopindices, ONLY: get_indices_c, get_indices_e
    TYPE(global_data_type) :: global_data
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
    INTEGER :: jb_var_144, jk_var_145, jc, je
    INTEGER :: i_startblk_var_146, i_endblk_var_147, i_startidx_var_148, i_endidx_var_149
    INTEGER :: i_startblk_2, i_endblk_2, i_startidx_2, i_endidx_2
    INTEGER :: rl_start_var_150, rl_end_var_151, rl_start_2, rl_end_2
    REAL(KIND = 8) :: z_w_concorr_mc(global_data % nproma, 90)
    REAL(KIND = 8) :: z_w_con_c(global_data % nproma, 91)
    REAL(KIND = 8) :: z_w_con_c_full(global_data % nproma, 90, p_patch % nblks_c)
    REAL(KIND = 8) :: z_v_grad_w(global_data % nproma, 90, p_patch % nblks_e)
    REAL(KIND = 8) :: z_w_v(global_data % nproma, 91, p_patch % nblks_v)
    REAL(KIND = 8) :: zeta(global_data % nproma, 90, p_patch % nblks_v)
    REAL(KIND = 8) :: z_ekinh(global_data % nproma, 90, p_patch % nblks_c)
    INTEGER :: nlev, nlevp1
    LOGICAL :: l_vert_nested
    INTEGER :: jg
    REAL(KIND = 8) :: cfl_w_limit, vcfl, maxvcfl, vcflmax(p_patch % nblks_c)
    REAL(KIND = 8) :: w_con_e, scalfac_exdiff, difcoef, max_vcfl_dyn_var_152
    INTEGER :: ie, nrdmax_jg, nflatlev_jg, clip_count
    LOGICAL :: levmask(p_patch % nblks_c, 90), levelmask(90)
    LOGICAL :: cfl_clipping(global_data % nproma, 91)
    IF (global_data % timers_level > 5) CALL timer_start(global_data, global_data % timer_solve_nh_veltend)
    l_vert_nested = .FALSE.
    jg = 1
    nrdmax_jg = global_data % nrdmax(1)
    nflatlev_jg = global_data % nflatlev(1)
    nlev = 90
    nlevp1 = 91
    IF (global_data % lextra_diffu) THEN
      cfl_w_limit = 0.65D0 / dtime
      scalfac_exdiff = 0.05D0 / (dtime * (0.85D0 - cfl_w_limit * dtime))
    ELSE
      cfl_w_limit = 0.85D0 / dtime
      scalfac_exdiff = 0.0D0
    END IF
    IF (.NOT. lvn_only) CALL cells2verts_scalar_ri(global_data, p_prog % w, p_patch, p_int % cells_aw_verts, z_w_v, opt_rlend_var_133 = - 5, opt_acc_async_var_135 = .TRUE.)
    CALL rot_vertex_ri(global_data, p_prog % vn, p_patch, p_int, zeta, opt_rlend_var_109 = - 5, opt_acc_async_var_110 = .TRUE.)
    IF (istep == 1) THEN
      rl_start_var_150 = 5
      rl_end_var_151 = -10
      i_startblk_var_146 = p_patch % edges % start_block(5)
      i_endblk_var_147 = p_patch % edges % end_block(- 10)
      DO jb_var_144 = i_startblk_var_146, i_endblk_var_147
        CALL get_indices_e(global_data, p_patch, jb_var_144, i_startblk_var_146, i_endblk_var_147, i_startidx_var_148, i_endidx_var_149, 5, - 10)
        DO jk_var_145 = 1, nlev
          DO je = i_startidx_var_148, i_endidx_var_149
            p_diag % vt(je, jk_var_145, jb_var_144) = p_int % rbf_vec_coeff_e(1, je, jb_var_144) * p_prog % vn(p_patch % edges % quad_idx(je, jb_var_144, 1), jk_var_145, p_patch % edges % quad_blk(je, jb_var_144, 1)) + p_int % rbf_vec_coeff_e(2, je, jb_var_144) * p_prog % vn(p_patch % edges % quad_idx(je, jb_var_144, 2), jk_var_145, p_patch % edges % quad_blk(je, jb_var_144, 2)) + p_int % rbf_vec_coeff_e(3, je, jb_var_144) * p_prog % vn(p_patch % edges % quad_idx(je, jb_var_144, 3), jk_var_145, p_patch % edges % quad_blk(je, jb_var_144, 3)) + p_int % rbf_vec_coeff_e(4, je, jb_var_144) * p_prog % vn(p_patch % edges % quad_idx(je, jb_var_144, 4), jk_var_145, p_patch % edges % quad_blk(je, jb_var_144, 4))
          END DO
        END DO
        DO jk_var_145 = 2, nlev
          DO je = i_startidx_var_148, i_endidx_var_149
            p_diag % vn_ie(je, jk_var_145, jb_var_144) = p_metrics % wgtfac_e(je, jk_var_145, jb_var_144) * p_prog % vn(je, jk_var_145, jb_var_144) + (1.0D0 - p_metrics % wgtfac_e(je, jk_var_145, jb_var_144)) * p_prog % vn(je, jk_var_145 - 1, jb_var_144)
            z_kin_hor_e(je, jk_var_145, jb_var_144) = 0.5D0 * (p_prog % vn(je, jk_var_145, jb_var_144) ** 2 + p_diag % vt(je, jk_var_145, jb_var_144) ** 2)
          END DO
        END DO
        IF (.NOT. lvn_only) THEN
          DO jk_var_145 = 2, nlev
            DO je = i_startidx_var_148, i_endidx_var_149
              z_vt_ie(je, jk_var_145, jb_var_144) = p_metrics % wgtfac_e(je, jk_var_145, jb_var_144) * p_diag % vt(je, jk_var_145, jb_var_144) + (1.0D0 - p_metrics % wgtfac_e(je, jk_var_145, jb_var_144)) * p_diag % vt(je, jk_var_145 - 1, jb_var_144)
            END DO
          END DO
        END IF
        DO jk_var_145 = nflatlev_jg, nlev
          DO je = i_startidx_var_148, i_endidx_var_149
            z_w_concorr_me(je, jk_var_145, jb_var_144) = p_prog % vn(je, jk_var_145, jb_var_144) * p_metrics % ddxn_z_full(je, jk_var_145, jb_var_144) + p_diag % vt(je, jk_var_145, jb_var_144) * p_metrics % ddxt_z_full(je, jk_var_145, jb_var_144)
          END DO
        END DO
        DO je = i_startidx_var_148, i_endidx_var_149
          p_diag % vn_ie(je, 1, jb_var_144) = p_prog % vn(je, 1, jb_var_144)
          z_vt_ie(je, 1, jb_var_144) = p_diag % vt(je, 1, jb_var_144)
          z_kin_hor_e(je, 1, jb_var_144) = 0.5D0 * (p_prog % vn(je, 1, jb_var_144) ** 2 + p_diag % vt(je, 1, jb_var_144) ** 2)
          p_diag % vn_ie(je, nlevp1, jb_var_144) = p_metrics % wgtfacq_e(je, 1, jb_var_144) * p_prog % vn(je, 90, jb_var_144) + p_metrics % wgtfacq_e(je, 2, jb_var_144) * p_prog % vn(je, 89, jb_var_144) + p_metrics % wgtfacq_e(je, 3, jb_var_144) * p_prog % vn(je, 88, jb_var_144)
        END DO
      END DO
    END IF
    rl_start_var_150 = 7
    rl_end_var_151 = -9
    i_startblk_var_146 = p_patch % edges % start_block(7)
    i_endblk_var_147 = p_patch % edges % end_block(- 9)
    IF (.NOT. lvn_only) THEN
      DO jb_var_144 = i_startblk_var_146, i_endblk_var_147
        CALL get_indices_e(global_data, p_patch, jb_var_144, i_startblk_var_146, i_endblk_var_147, i_startidx_var_148, i_endidx_var_149, 7, - 9)
        DO jk_var_145 = 1, nlev
          DO je = i_startidx_var_148, i_endidx_var_149
            z_v_grad_w(je, jk_var_145, jb_var_144) = p_diag % vn_ie(je, jk_var_145, jb_var_144) * p_patch % edges % inv_dual_edge_length(je, jb_var_144) * (p_prog % w(p_patch % edges % cell_idx(je, jb_var_144, 1), jk_var_145, p_patch % edges % cell_blk(je, jb_var_144, 1)) - p_prog % w(p_patch % edges % cell_idx(je, jb_var_144, 2), jk_var_145, p_patch % edges % cell_blk(je, jb_var_144, 2))) + z_vt_ie(je, jk_var_145, jb_var_144) * p_patch % edges % inv_primal_edge_length(je, jb_var_144) * p_patch % edges % tangent_orientation(je, jb_var_144) * (z_w_v(p_patch % edges % vertex_idx(je, jb_var_144, 1), jk_var_145, p_patch % edges % vertex_blk(je, jb_var_144, 1)) - z_w_v(p_patch % edges % vertex_idx(je, jb_var_144, 2), jk_var_145, p_patch % edges % vertex_blk(je, jb_var_144, 2)))
          END DO
        END DO
      END DO
    END IF
    IF (.NOT. lvn_only .AND. ldeepatmo) THEN
      DO jb_var_144 = i_startblk_var_146, i_endblk_var_147
        CALL get_indices_e(global_data, p_patch, jb_var_144, i_startblk_var_146, i_endblk_var_147, i_startidx_var_148, i_endidx_var_149, 7, - 9)
        DO jk_var_145 = 1, nlev
          DO je = i_startidx_var_148, i_endidx_var_149
            z_v_grad_w(je, jk_var_145, jb_var_144) = z_v_grad_w(je, jk_var_145, jb_var_144) * p_metrics % deepatmo_gradh_ifc(jk_var_145) + p_diag % vn_ie(je, jk_var_145, jb_var_144) * (p_diag % vn_ie(je, jk_var_145, jb_var_144) * p_metrics % deepatmo_invr_ifc(jk_var_145) - p_patch % edges % ft_e(je, jb_var_144)) + z_vt_ie(je, jk_var_145, jb_var_144) * (z_vt_ie(je, jk_var_145, jb_var_144) * p_metrics % deepatmo_invr_ifc(jk_var_145) + p_patch % edges % fn_e(je, jb_var_144))
          END DO
        END DO
      END DO
    END IF
    rl_start_var_150 = 4
    rl_end_var_151 = -5
    i_startblk_var_146 = p_patch % cells % start_block(4)
    i_endblk_var_147 = p_patch % cells % end_block(- 5)
    rl_start_2 = 5
    rl_end_2 = -4
    i_startblk_2 = p_patch % cells % start_block(5)
    i_endblk_2 = p_patch % cells % end_block(- 4)
    DO jb_var_144 = i_startblk_var_146, i_endblk_var_147
      CALL get_indices_c(global_data, p_patch, jb_var_144, i_startblk_var_146, i_endblk_var_147, i_startidx_var_148, i_endidx_var_149, 4, - 5)
      DO jk_var_145 = 1, nlev
        DO jc = i_startidx_var_148, i_endidx_var_149
          z_ekinh(jc, jk_var_145, jb_var_144) = p_int % e_bln_c_s(jc, 1, jb_var_144) * z_kin_hor_e(p_patch % cells % edge_idx(jc, jb_var_144, 1), jk_var_145, p_patch % cells % edge_blk(jc, jb_var_144, 1)) + p_int % e_bln_c_s(jc, 2, jb_var_144) * z_kin_hor_e(p_patch % cells % edge_idx(jc, jb_var_144, 2), jk_var_145, p_patch % cells % edge_blk(jc, jb_var_144, 2)) + p_int % e_bln_c_s(jc, 3, jb_var_144) * z_kin_hor_e(p_patch % cells % edge_idx(jc, jb_var_144, 3), jk_var_145, p_patch % cells % edge_blk(jc, jb_var_144, 3))
        END DO
      END DO
      IF (istep == 1) THEN
        DO jk_var_145 = nflatlev_jg, nlev
          DO jc = i_startidx_var_148, i_endidx_var_149
            z_w_concorr_mc(jc, jk_var_145) = p_int % e_bln_c_s(jc, 1, jb_var_144) * z_w_concorr_me(p_patch % cells % edge_idx(jc, jb_var_144, 1), jk_var_145, p_patch % cells % edge_blk(jc, jb_var_144, 1)) + p_int % e_bln_c_s(jc, 2, jb_var_144) * z_w_concorr_me(p_patch % cells % edge_idx(jc, jb_var_144, 2), jk_var_145, p_patch % cells % edge_blk(jc, jb_var_144, 2)) + p_int % e_bln_c_s(jc, 3, jb_var_144) * z_w_concorr_me(p_patch % cells % edge_idx(jc, jb_var_144, 3), jk_var_145, p_patch % cells % edge_blk(jc, jb_var_144, 3))
          END DO
        END DO
        DO jk_var_145 = nflatlev_jg + 1, nlev
          DO jc = i_startidx_var_148, i_endidx_var_149
            p_diag % w_concorr_c(jc, jk_var_145, jb_var_144) = p_metrics % wgtfac_c(jc, jk_var_145, jb_var_144) * z_w_concorr_mc(jc, jk_var_145) + (1.0D0 - p_metrics % wgtfac_c(jc, jk_var_145, jb_var_144)) * z_w_concorr_mc(jc, jk_var_145 - 1)
          END DO
        END DO
      END IF
      DO jk_var_145 = 1, nlev
        DO jc = i_startidx_var_148, i_endidx_var_149
          z_w_con_c(jc, jk_var_145) = p_prog % w(jc, jk_var_145, jb_var_144)
        END DO
      END DO
      DO jc = i_startidx_var_148, i_endidx_var_149
        z_w_con_c(jc, 91) = 0.0D0
      END DO
      DO jk_var_145 = nlev, nflatlev_jg + 1, - 1
        DO jc = i_startidx_var_148, i_endidx_var_149
          z_w_con_c(jc, jk_var_145) = z_w_con_c(jc, jk_var_145) - p_diag % w_concorr_c(jc, jk_var_145, jb_var_144)
        END DO
      END DO
      DO jk_var_145 = MAX(3, nrdmax_jg - 2), nlev - 3
        levmask(jb_var_144, jk_var_145) = .FALSE.
      END DO
      maxvcfl = 0
      DO jk_var_145 = MAX(3, nrdmax_jg - 2), nlev - 3
        clip_count = 0
        DO jc = i_startidx_var_148, i_endidx_var_149
          cfl_clipping(jc, jk_var_145) = (ABS(z_w_con_c(jc, jk_var_145)) > cfl_w_limit * p_metrics % ddqz_z_half(jc, jk_var_145, jb_var_144))
          IF (cfl_clipping(jc, jk_var_145)) clip_count = clip_count + 1
        END DO
        IF (clip_count == 0) CYCLE
        DO jc = i_startidx_var_148, i_endidx_var_149
          IF (cfl_clipping(jc, jk_var_145)) THEN
            levmask(jb_var_144, jk_var_145) = .TRUE.
            vcfl = z_w_con_c(jc, jk_var_145) * dtime / p_metrics % ddqz_z_half(jc, jk_var_145, jb_var_144)
            maxvcfl = MAX(maxvcfl, ABS(vcfl))
            IF (vcfl < - 0.85D0) THEN
              z_w_con_c(jc, jk_var_145) = - 0.85D0 * p_metrics % ddqz_z_half(jc, jk_var_145, jb_var_144) / dtime
            ELSE IF (vcfl > 0.85D0) THEN
              z_w_con_c(jc, jk_var_145) = 0.85D0 * p_metrics % ddqz_z_half(jc, jk_var_145, jb_var_144) / dtime
            END IF
          END IF
        END DO
      END DO
      DO jk_var_145 = 1, nlev
        DO jc = i_startidx_var_148, i_endidx_var_149
          z_w_con_c_full(jc, jk_var_145, jb_var_144) = 0.5D0 * (z_w_con_c(jc, jk_var_145) + z_w_con_c(jc, jk_var_145 + 1))
        END DO
      END DO
      vcflmax(jb_var_144) = maxvcfl
      IF (lvn_only) CYCLE
      IF (jb_var_144 < i_startblk_2 .OR. jb_var_144 > i_endblk_2) CYCLE
      CALL get_indices_c(global_data, p_patch, jb_var_144, i_startblk_2, i_endblk_2, i_startidx_2, i_endidx_2, 5, - 4)
      DO jk_var_145 = 2, nlev
        DO jc = i_startidx_2, i_endidx_2
          p_diag % ddt_w_adv_pc(jc, jk_var_145, jb_var_144, ntnd) = - z_w_con_c(jc, jk_var_145) * (p_prog % w(jc, jk_var_145 - 1, jb_var_144) * p_metrics % coeff1_dwdz(jc, jk_var_145, jb_var_144) - p_prog % w(jc, jk_var_145 + 1, jb_var_144) * p_metrics % coeff2_dwdz(jc, jk_var_145, jb_var_144) + p_prog % w(jc, jk_var_145, jb_var_144) * (p_metrics % coeff2_dwdz(jc, jk_var_145, jb_var_144) - p_metrics % coeff1_dwdz(jc, jk_var_145, jb_var_144)))
        END DO
      END DO
      DO jk_var_145 = 2, nlev
        DO jc = i_startidx_2, i_endidx_2
          p_diag % ddt_w_adv_pc(jc, jk_var_145, jb_var_144, ntnd) = p_diag % ddt_w_adv_pc(jc, jk_var_145, jb_var_144, ntnd) + p_int % e_bln_c_s(jc, 1, jb_var_144) * z_v_grad_w(p_patch % cells % edge_idx(jc, jb_var_144, 1), jk_var_145, p_patch % cells % edge_blk(jc, jb_var_144, 1)) + p_int % e_bln_c_s(jc, 2, jb_var_144) * z_v_grad_w(p_patch % cells % edge_idx(jc, jb_var_144, 2), jk_var_145, p_patch % cells % edge_blk(jc, jb_var_144, 2)) + p_int % e_bln_c_s(jc, 3, jb_var_144) * z_v_grad_w(p_patch % cells % edge_idx(jc, jb_var_144, 3), jk_var_145, p_patch % cells % edge_blk(jc, jb_var_144, 3))
        END DO
      END DO
      IF (global_data % lextra_diffu) THEN
        DO jk_var_145 = MAX(3, nrdmax_jg - 2), nlev - 3
          IF (levmask(jb_var_144, jk_var_145)) THEN
            DO jc = i_startidx_2, i_endidx_2
              IF (cfl_clipping(jc, jk_var_145) .AND. p_patch % cells % decomp_info % owner_mask(jc, jb_var_144)) THEN
                difcoef = scalfac_exdiff * MIN(0.85D0 - cfl_w_limit * dtime, ABS(z_w_con_c(jc, jk_var_145)) * dtime / p_metrics % ddqz_z_half(jc, jk_var_145, jb_var_144) - cfl_w_limit * dtime)
                p_diag % ddt_w_adv_pc(jc, jk_var_145, jb_var_144, ntnd) = p_diag % ddt_w_adv_pc(jc, jk_var_145, jb_var_144, ntnd) + difcoef * p_patch % cells % area(jc, jb_var_144) * (p_prog % w(jc, jk_var_145, jb_var_144) * p_int % geofac_n2s(jc, 1, jb_var_144) + p_prog % w(p_patch % cells % neighbor_idx(jc, jb_var_144, 1), jk_var_145, p_patch % cells % neighbor_blk(jc, jb_var_144, 1)) * p_int % geofac_n2s(jc, 2, jb_var_144) + p_prog % w(p_patch % cells % neighbor_idx(jc, jb_var_144, 2), jk_var_145, p_patch % cells % neighbor_blk(jc, jb_var_144, 2)) * p_int % geofac_n2s(jc, 3, jb_var_144) + p_prog % w(p_patch % cells % neighbor_idx(jc, jb_var_144, 3), jk_var_145, p_patch % cells % neighbor_blk(jc, jb_var_144, 3)) * p_int % geofac_n2s(jc, 4, jb_var_144))
              END IF
            END DO
          END IF
        END DO
      END IF
    END DO
    DO jk_var_145 = MAX(3, nrdmax_jg - 2), nlev - 3
      levelmask(jk_var_145) = ANY(levmask(i_startblk_var_146 : i_endblk_var_147, jk_var_145))
    END DO
    rl_start_var_150 = 10
    rl_end_var_151 = -8
    i_startblk_var_146 = p_patch % edges % start_block(10)
    i_endblk_var_147 = p_patch % edges % end_block(- 8)
    DO jb_var_144 = i_startblk_var_146, i_endblk_var_147
      CALL get_indices_e(global_data, p_patch, jb_var_144, i_startblk_var_146, i_endblk_var_147, i_startidx_var_148, i_endidx_var_149, 10, - 8)
      IF (.NOT. ldeepatmo) THEN
        DO jk_var_145 = 1, nlev
          DO je = i_startidx_var_148, i_endidx_var_149
            p_diag % ddt_vn_apc_pc(je, jk_var_145, jb_var_144, ntnd) = - (z_kin_hor_e(je, jk_var_145, jb_var_144) * (p_metrics % coeff_gradekin(je, 1, jb_var_144) - p_metrics % coeff_gradekin(je, 2, jb_var_144)) + p_metrics % coeff_gradekin(je, 2, jb_var_144) * z_ekinh(p_patch % edges % cell_idx(je, jb_var_144, 2), jk_var_145, p_patch % edges % cell_blk(je, jb_var_144, 2)) - p_metrics % coeff_gradekin(je, 1, jb_var_144) * z_ekinh(p_patch % edges % cell_idx(je, jb_var_144, 1), jk_var_145, p_patch % edges % cell_blk(je, jb_var_144, 1)) + p_diag % vt(je, jk_var_145, jb_var_144) * (p_patch % edges % f_e(je, jb_var_144) + 0.5D0 * (zeta(p_patch % edges % vertex_idx(je, jb_var_144, 1), jk_var_145, p_patch % edges % vertex_blk(je, jb_var_144, 1)) + zeta(p_patch % edges % vertex_idx(je, jb_var_144, 2), jk_var_145, p_patch % edges % vertex_blk(je, jb_var_144, 2)))) + (p_int % c_lin_e(je, 1, jb_var_144) * z_w_con_c_full(p_patch % edges % cell_idx(je, jb_var_144, 1), jk_var_145, p_patch % edges % cell_blk(je, jb_var_144, 1)) + p_int % c_lin_e(je, 2, jb_var_144) * z_w_con_c_full(p_patch % edges % cell_idx(je, jb_var_144, 2), jk_var_145, p_patch % edges % cell_blk(je, jb_var_144, 2))) * (p_diag % vn_ie(je, jk_var_145, jb_var_144) - p_diag % vn_ie(je, jk_var_145 + 1, jb_var_144)) / p_metrics % ddqz_z_full_e(je, jk_var_145, jb_var_144))
          END DO
        END DO
      ELSE
        DO jk_var_145 = 1, nlev
          DO je = i_startidx_var_148, i_endidx_var_149
            p_diag % ddt_vn_apc_pc(je, jk_var_145, jb_var_144, ntnd) = - ((z_kin_hor_e(je, jk_var_145, jb_var_144) * (p_metrics % coeff_gradekin(je, 1, jb_var_144) - p_metrics % coeff_gradekin(je, 2, jb_var_144)) + p_metrics % coeff_gradekin(je, 2, jb_var_144) * z_ekinh(p_patch % edges % cell_idx(je, jb_var_144, 2), jk_var_145, p_patch % edges % cell_blk(je, jb_var_144, 2)) - p_metrics % coeff_gradekin(je, 1, jb_var_144) * z_ekinh(p_patch % edges % cell_idx(je, jb_var_144, 1), jk_var_145, p_patch % edges % cell_blk(je, jb_var_144, 1))) * p_metrics % deepatmo_gradh_mc(jk_var_145) + p_diag % vt(je, jk_var_145, jb_var_144) * (p_patch % edges % f_e(je, jb_var_144) + 0.5D0 * (zeta(p_patch % edges % vertex_idx(je, jb_var_144, 1), jk_var_145, p_patch % edges % vertex_blk(je, jb_var_144, 1)) + zeta(p_patch % edges % vertex_idx(je, jb_var_144, 2), jk_var_145, p_patch % edges % vertex_blk(je, jb_var_144, 2))) * p_metrics % deepatmo_gradh_mc(jk_var_145)) + (p_int % c_lin_e(je, 1, jb_var_144) * z_w_con_c_full(p_patch % edges % cell_idx(je, jb_var_144, 1), jk_var_145, p_patch % edges % cell_blk(je, jb_var_144, 1)) + p_int % c_lin_e(je, 2, jb_var_144) * z_w_con_c_full(p_patch % edges % cell_idx(je, jb_var_144, 2), jk_var_145, p_patch % edges % cell_blk(je, jb_var_144, 2))) * ((p_diag % vn_ie(je, jk_var_145, jb_var_144) - p_diag % vn_ie(je, jk_var_145 + 1, jb_var_144)) / p_metrics % ddqz_z_full_e(je, jk_var_145, jb_var_144) + p_prog % vn(je, jk_var_145, jb_var_144) * p_metrics % deepatmo_invr_mc(jk_var_145) - p_patch % edges % ft_e(je, jb_var_144)))
          END DO
        END DO
      END IF
      IF (global_data % lextra_diffu) THEN
        ie = 0
        DO jk_var_145 = MAX(3, nrdmax_jg - 2), nlev - 4
          IF (levelmask(jk_var_145) .OR. levelmask(jk_var_145 + 1)) THEN
            DO je = i_startidx_var_148, i_endidx_var_149
              w_con_e = p_int % c_lin_e(je, 1, jb_var_144) * z_w_con_c_full(p_patch % edges % cell_idx(je, jb_var_144, 1), jk_var_145, p_patch % edges % cell_blk(je, jb_var_144, 1)) + p_int % c_lin_e(je, 2, jb_var_144) * z_w_con_c_full(p_patch % edges % cell_idx(je, jb_var_144, 2), jk_var_145, p_patch % edges % cell_blk(je, jb_var_144, 2))
              IF (ABS(w_con_e) > cfl_w_limit * p_metrics % ddqz_z_full_e(je, jk_var_145, jb_var_144)) THEN
                difcoef = scalfac_exdiff * MIN(0.85D0 - cfl_w_limit * dtime, ABS(w_con_e) * dtime / p_metrics % ddqz_z_full_e(je, jk_var_145, jb_var_144) - cfl_w_limit * dtime)
                p_diag % ddt_vn_apc_pc(je, jk_var_145, jb_var_144, ntnd) = p_diag % ddt_vn_apc_pc(je, jk_var_145, jb_var_144, ntnd) + difcoef * p_patch % edges % area_edge(je, jb_var_144) * (p_int % geofac_grdiv(je, 1, jb_var_144) * p_prog % vn(je, jk_var_145, jb_var_144) + p_int % geofac_grdiv(je, 2, jb_var_144) * p_prog % vn(p_patch % edges % quad_idx(je, jb_var_144, 1), jk_var_145, p_patch % edges % quad_blk(je, jb_var_144, 1)) + p_int % geofac_grdiv(je, 3, jb_var_144) * p_prog % vn(p_patch % edges % quad_idx(je, jb_var_144, 2), jk_var_145, p_patch % edges % quad_blk(je, jb_var_144, 2)) + p_int % geofac_grdiv(je, 4, jb_var_144) * p_prog % vn(p_patch % edges % quad_idx(je, jb_var_144, 3), jk_var_145, p_patch % edges % quad_blk(je, jb_var_144, 3)) + p_int % geofac_grdiv(je, 5, jb_var_144) * p_prog % vn(p_patch % edges % quad_idx(je, jb_var_144, 4), jk_var_145, p_patch % edges % quad_blk(je, jb_var_144, 4)) + p_patch % edges % tangent_orientation(je, jb_var_144) * p_patch % edges % inv_primal_edge_length(je, jb_var_144) * (zeta(p_patch % edges % vertex_idx(je, jb_var_144, 2), jk_var_145, p_patch % edges % vertex_blk(je, jb_var_144, 2)) - zeta(p_patch % edges % vertex_idx(je, jb_var_144, 1), jk_var_145, p_patch % edges % vertex_blk(je, jb_var_144, 1))))
              END IF
            END DO
          END IF
        END DO
      END IF
    END DO
    i_startblk_var_146 = p_patch % cells % start_block(4)
    i_endblk_var_147 = p_patch % cells % end_block(- 4)
    max_vcfl_dyn_var_152 = MAX(0.0D0, MAXVAL(vcflmax(i_startblk_var_146 : i_endblk_var_147)))
    p_diag % max_vcfl_dyn = max_vcfl_dyn_var_152
    IF (global_data % timers_level > 5) CALL timer_stop(global_data, global_data % timer_solve_nh_veltend)
  END SUBROUTINE velocity_tendencies
END MODULE mo_velocity_advection