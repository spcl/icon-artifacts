MODULE corrector_post
  IMPLICIT NONE
  INTERFACE serialize
    MODULE PROCEDURE :: W_string
    MODULE PROCEDURE W_t_int_state, W_t_grid_cells, W_t_grid_edges, W_t_patch, W_t_nh_prog, W_t_nh_diag, W_t_nh_ref, W_t_nh_metrics, W_t_nh_state, W_t_prepare_adv, W_logical_R_1, W_integer__1_R_1, W_integer__2_R_1, W_integer__4_R_1, W_integer__8_R_1, W_real__4_R_1, W_real__8_R_1, W_logical_R_2, W_integer__1_R_2, W_integer__2_R_2, W_integer__4_R_2, W_integer__8_R_2, W_real__4_R_2, W_real__8_R_2, W_logical_R_3, W_integer__1_R_3, W_integer__2_R_3, W_integer__4_R_3, W_integer__8_R_3, W_real__4_R_3, W_real__8_R_3, W_logical_R_4, W_integer__1_R_4, W_integer__2_R_4, W_integer__4_R_4, W_integer__8_R_4, W_real__4_R_4, W_real__8_R_4, W_dt_t_nh_prog_R_1, W_logical, W_integer1, W_integer2, W_integer4, W_integer8, W_real4, W_real8
  END INTERFACE serialize
  INTEGER :: generation = 0
  CONTAINS
  SUBROUTINE tic
    generation = generation + 1
  END SUBROUTINE tic
  FUNCTION cat(prefix, asis) RESULT(path)
    CHARACTER(LEN = *), INTENT(IN) :: prefix
    CHARACTER(LEN = :), ALLOCATABLE :: path
    CHARACTER(LEN = 50) :: gen
    LOGICAL, INTENT(IN) :: asis
    IF (asis) THEN
      path = prefix
    ELSE
      WRITE(gen, '(g0)') generation
      path = prefix // '.' // TRIM(gen) // ".data"
    END IF
  END FUNCTION cat
  FUNCTION at(prefix, asis) RESULT(io)
    CHARACTER(LEN = *), INTENT(IN) :: prefix
    INTEGER :: io
    LOGICAL, OPTIONAL, INTENT(IN) :: asis
    LOGICAL :: asis_local
    asis_local = .FALSE.
    IF (PRESENT(asis)) asis_local = asis
    OPEN(NEWUNIT = io, FILE = cat(prefix, asis_local), STATUS = "replace", ACTION = "write")
  END FUNCTION at
  SUBROUTINE W_string(io, x, cleanup, nline)
    INTEGER :: io
    CHARACTER(LEN = *), INTENT(IN) :: x
    INTEGER :: i, xend
    LOGICAL, OPTIONAL, INTENT(IN) :: cleanup, nline
    LOGICAL :: cleanup_local, nline_local
    cleanup_local = .TRUE.
    nline_local = .TRUE.
    IF (PRESENT(cleanup)) cleanup_local = cleanup
    IF (PRESENT(nline)) nline_local = nline
    xend = LEN(x)
    DO i = 1, LEN(x)
      IF (x(i : i) == CHAR(0)) THEN
        xend = i - 1
        EXIT
      END IF
    END DO
    WRITE(io, '(A)', ADVANCE = 'no') TRIM(x(1 : xend))
    IF (nline_local) WRITE(io, '(g0)', ADVANCE = 'no') NEW_LINE('A')
    IF (cleanup_local) CLOSE(UNIT = io)
  END SUBROUTINE W_string
  SUBROUTINE W_t_int_state(io, x, cleanup, nline)
    USE mo_intp_data_strc, ONLY: t_int_state
    INTEGER :: io
    TYPE(t_int_state), TARGET, INTENT(IN) :: x
    LOGICAL, OPTIONAL, INTENT(IN) :: cleanup, nline
    INTEGER :: kmeta, kmeta_0, kmeta_1, kmeta_2, kmeta_3, kmeta_4, kmeta_5, kmeta_6, kmeta_7, kmeta_8, kmeta_9
    LOGICAL :: cleanup_local, nline_local
    cleanup_local = .TRUE.
    nline_local = .TRUE.
    IF (PRESENT(cleanup)) cleanup_local = cleanup
    IF (PRESENT(nline)) nline_local = nline
    CALL serialize(io, '# e_bln_c_s', cleanup = .FALSE.)
    CALL serialize(io, '# alloc', cleanup = .FALSE.)
    CALL serialize(io, ALLOCATED(x % e_bln_c_s), cleanup = .FALSE.)
    IF (ALLOCATED(x % e_bln_c_s)) THEN
      CALL serialize(io, "# rank", cleanup = .FALSE.)
      CALL serialize(io, 3, cleanup = .FALSE.)
      CALL serialize(io, "# size", cleanup = .FALSE.)
      DO kmeta = 1, 3
        CALL serialize(io, SIZE(x % e_bln_c_s, kmeta), cleanup = .FALSE.)
      END DO
      CALL serialize(io, "# lbound", cleanup = .FALSE.)
      DO kmeta = 1, 3
        CALL serialize(io, LBOUND(x % e_bln_c_s, kmeta), cleanup = .FALSE.)
      END DO
      CALL serialize(io, x % e_bln_c_s, cleanup = .FALSE., nline = .TRUE., meta = .FALSE.)
    END IF
    CALL serialize(io, '# e_flx_avg', cleanup = .FALSE.)
    CALL serialize(io, '# alloc', cleanup = .FALSE.)
    CALL serialize(io, ALLOCATED(x % e_flx_avg), cleanup = .FALSE.)
    IF (ALLOCATED(x % e_flx_avg)) THEN
      CALL serialize(io, "# rank", cleanup = .FALSE.)
      CALL serialize(io, 3, cleanup = .FALSE.)
      CALL serialize(io, "# size", cleanup = .FALSE.)
      DO kmeta = 1, 3
        CALL serialize(io, SIZE(x % e_flx_avg, kmeta), cleanup = .FALSE.)
      END DO
      CALL serialize(io, "# lbound", cleanup = .FALSE.)
      DO kmeta = 1, 3
        CALL serialize(io, LBOUND(x % e_flx_avg, kmeta), cleanup = .FALSE.)
      END DO
      CALL serialize(io, x % e_flx_avg, cleanup = .FALSE., nline = .TRUE., meta = .FALSE.)
    END IF
    CALL serialize(io, '# rbf_vec_coeff_e', cleanup = .FALSE.)
    CALL serialize(io, '# alloc', cleanup = .FALSE.)
    CALL serialize(io, ALLOCATED(x % rbf_vec_coeff_e), cleanup = .FALSE.)
    IF (ALLOCATED(x % rbf_vec_coeff_e)) THEN
      CALL serialize(io, "# rank", cleanup = .FALSE.)
      CALL serialize(io, 3, cleanup = .FALSE.)
      CALL serialize(io, "# size", cleanup = .FALSE.)
      DO kmeta = 1, 3
        CALL serialize(io, SIZE(x % rbf_vec_coeff_e, kmeta), cleanup = .FALSE.)
      END DO
      CALL serialize(io, "# lbound", cleanup = .FALSE.)
      DO kmeta = 1, 3
        CALL serialize(io, LBOUND(x % rbf_vec_coeff_e, kmeta), cleanup = .FALSE.)
      END DO
      CALL serialize(io, x % rbf_vec_coeff_e, cleanup = .FALSE., nline = .TRUE., meta = .FALSE.)
    END IF
    CALL serialize(io, '# geofac_div', cleanup = .FALSE.)
    CALL serialize(io, '# alloc', cleanup = .FALSE.)
    CALL serialize(io, ALLOCATED(x % geofac_div), cleanup = .FALSE.)
    IF (ALLOCATED(x % geofac_div)) THEN
      CALL serialize(io, "# rank", cleanup = .FALSE.)
      CALL serialize(io, 3, cleanup = .FALSE.)
      CALL serialize(io, "# size", cleanup = .FALSE.)
      DO kmeta = 1, 3
        CALL serialize(io, SIZE(x % geofac_div, kmeta), cleanup = .FALSE.)
      END DO
      CALL serialize(io, "# lbound", cleanup = .FALSE.)
      DO kmeta = 1, 3
        CALL serialize(io, LBOUND(x % geofac_div, kmeta), cleanup = .FALSE.)
      END DO
      CALL serialize(io, x % geofac_div, cleanup = .FALSE., nline = .TRUE., meta = .FALSE.)
    END IF
    IF (nline_local) WRITE(io, '(g0)', ADVANCE = 'no') NEW_LINE('A')
    IF (cleanup_local) CLOSE(UNIT = io)
  END SUBROUTINE W_t_int_state
  SUBROUTINE W_t_grid_cells(io, x, cleanup, nline)
    USE mo_model_domain, ONLY: t_grid_cells
    INTEGER :: io
    TYPE(t_grid_cells), TARGET, INTENT(IN) :: x
    LOGICAL, OPTIONAL, INTENT(IN) :: cleanup, nline
    INTEGER :: kmeta, kmeta_0, kmeta_1, kmeta_2, kmeta_3, kmeta_4, kmeta_5, kmeta_6, kmeta_7, kmeta_8, kmeta_9
    LOGICAL :: cleanup_local, nline_local
    cleanup_local = .TRUE.
    nline_local = .TRUE.
    IF (PRESENT(cleanup)) cleanup_local = cleanup
    IF (PRESENT(nline)) nline_local = nline
    CALL serialize(io, '# edge_idx', cleanup = .FALSE.)
    CALL serialize(io, '# alloc', cleanup = .FALSE.)
    CALL serialize(io, ALLOCATED(x % edge_idx), cleanup = .FALSE.)
    IF (ALLOCATED(x % edge_idx)) THEN
      CALL serialize(io, "# rank", cleanup = .FALSE.)
      CALL serialize(io, 3, cleanup = .FALSE.)
      CALL serialize(io, "# size", cleanup = .FALSE.)
      DO kmeta = 1, 3
        CALL serialize(io, SIZE(x % edge_idx, kmeta), cleanup = .FALSE.)
      END DO
      CALL serialize(io, "# lbound", cleanup = .FALSE.)
      DO kmeta = 1, 3
        CALL serialize(io, LBOUND(x % edge_idx, kmeta), cleanup = .FALSE.)
      END DO
      CALL serialize(io, x % edge_idx, cleanup = .FALSE., nline = .TRUE., meta = .FALSE.)
    END IF
    CALL serialize(io, '# edge_blk', cleanup = .FALSE.)
    CALL serialize(io, '# alloc', cleanup = .FALSE.)
    CALL serialize(io, ALLOCATED(x % edge_blk), cleanup = .FALSE.)
    IF (ALLOCATED(x % edge_blk)) THEN
      CALL serialize(io, "# rank", cleanup = .FALSE.)
      CALL serialize(io, 3, cleanup = .FALSE.)
      CALL serialize(io, "# size", cleanup = .FALSE.)
      DO kmeta = 1, 3
        CALL serialize(io, SIZE(x % edge_blk, kmeta), cleanup = .FALSE.)
      END DO
      CALL serialize(io, "# lbound", cleanup = .FALSE.)
      DO kmeta = 1, 3
        CALL serialize(io, LBOUND(x % edge_blk, kmeta), cleanup = .FALSE.)
      END DO
      CALL serialize(io, x % edge_blk, cleanup = .FALSE., nline = .TRUE., meta = .FALSE.)
    END IF
    CALL serialize(io, '# start_index', cleanup = .FALSE.)
    CALL serialize(io, '# alloc', cleanup = .FALSE.)
    CALL serialize(io, ALLOCATED(x % start_index), cleanup = .FALSE.)
    IF (ALLOCATED(x % start_index)) THEN
      CALL serialize(io, "# rank", cleanup = .FALSE.)
      CALL serialize(io, 1, cleanup = .FALSE.)
      CALL serialize(io, "# size", cleanup = .FALSE.)
      DO kmeta = 1, 1
        CALL serialize(io, SIZE(x % start_index, kmeta), cleanup = .FALSE.)
      END DO
      CALL serialize(io, "# lbound", cleanup = .FALSE.)
      DO kmeta = 1, 1
        CALL serialize(io, LBOUND(x % start_index, kmeta), cleanup = .FALSE.)
      END DO
      CALL serialize(io, x % start_index, cleanup = .FALSE., nline = .TRUE., meta = .FALSE.)
    END IF
    CALL serialize(io, '# end_index', cleanup = .FALSE.)
    CALL serialize(io, '# alloc', cleanup = .FALSE.)
    CALL serialize(io, ALLOCATED(x % end_index), cleanup = .FALSE.)
    IF (ALLOCATED(x % end_index)) THEN
      CALL serialize(io, "# rank", cleanup = .FALSE.)
      CALL serialize(io, 1, cleanup = .FALSE.)
      CALL serialize(io, "# size", cleanup = .FALSE.)
      DO kmeta = 1, 1
        CALL serialize(io, SIZE(x % end_index, kmeta), cleanup = .FALSE.)
      END DO
      CALL serialize(io, "# lbound", cleanup = .FALSE.)
      DO kmeta = 1, 1
        CALL serialize(io, LBOUND(x % end_index, kmeta), cleanup = .FALSE.)
      END DO
      CALL serialize(io, x % end_index, cleanup = .FALSE., nline = .TRUE., meta = .FALSE.)
    END IF
    CALL serialize(io, '# start_block', cleanup = .FALSE.)
    CALL serialize(io, '# alloc', cleanup = .FALSE.)
    CALL serialize(io, ALLOCATED(x % start_block), cleanup = .FALSE.)
    IF (ALLOCATED(x % start_block)) THEN
      CALL serialize(io, "# rank", cleanup = .FALSE.)
      CALL serialize(io, 1, cleanup = .FALSE.)
      CALL serialize(io, "# size", cleanup = .FALSE.)
      DO kmeta = 1, 1
        CALL serialize(io, SIZE(x % start_block, kmeta), cleanup = .FALSE.)
      END DO
      CALL serialize(io, "# lbound", cleanup = .FALSE.)
      DO kmeta = 1, 1
        CALL serialize(io, LBOUND(x % start_block, kmeta), cleanup = .FALSE.)
      END DO
      CALL serialize(io, x % start_block, cleanup = .FALSE., nline = .TRUE., meta = .FALSE.)
    END IF
    CALL serialize(io, '# end_block', cleanup = .FALSE.)
    CALL serialize(io, '# alloc', cleanup = .FALSE.)
    CALL serialize(io, ALLOCATED(x % end_block), cleanup = .FALSE.)
    IF (ALLOCATED(x % end_block)) THEN
      CALL serialize(io, "# rank", cleanup = .FALSE.)
      CALL serialize(io, 1, cleanup = .FALSE.)
      CALL serialize(io, "# size", cleanup = .FALSE.)
      DO kmeta = 1, 1
        CALL serialize(io, SIZE(x % end_block, kmeta), cleanup = .FALSE.)
      END DO
      CALL serialize(io, "# lbound", cleanup = .FALSE.)
      DO kmeta = 1, 1
        CALL serialize(io, LBOUND(x % end_block, kmeta), cleanup = .FALSE.)
      END DO
      CALL serialize(io, x % end_block, cleanup = .FALSE., nline = .TRUE., meta = .FALSE.)
    END IF
    IF (nline_local) WRITE(io, '(g0)', ADVANCE = 'no') NEW_LINE('A')
    IF (cleanup_local) CLOSE(UNIT = io)
  END SUBROUTINE W_t_grid_cells
  SUBROUTINE W_t_grid_edges(io, x, cleanup, nline)
    USE mo_model_domain, ONLY: t_grid_edges
    INTEGER :: io
    TYPE(t_grid_edges), TARGET, INTENT(IN) :: x
    LOGICAL, OPTIONAL, INTENT(IN) :: cleanup, nline
    INTEGER :: kmeta, kmeta_0, kmeta_1, kmeta_2, kmeta_3, kmeta_4, kmeta_5, kmeta_6, kmeta_7, kmeta_8, kmeta_9
    LOGICAL :: cleanup_local, nline_local
    cleanup_local = .TRUE.
    nline_local = .TRUE.
    IF (PRESENT(cleanup)) cleanup_local = cleanup
    IF (PRESENT(nline)) nline_local = nline
    CALL serialize(io, '# quad_idx', cleanup = .FALSE.)
    CALL serialize(io, '# alloc', cleanup = .FALSE.)
    CALL serialize(io, ALLOCATED(x % quad_idx), cleanup = .FALSE.)
    IF (ALLOCATED(x % quad_idx)) THEN
      CALL serialize(io, "# rank", cleanup = .FALSE.)
      CALL serialize(io, 3, cleanup = .FALSE.)
      CALL serialize(io, "# size", cleanup = .FALSE.)
      DO kmeta = 1, 3
        CALL serialize(io, SIZE(x % quad_idx, kmeta), cleanup = .FALSE.)
      END DO
      CALL serialize(io, "# lbound", cleanup = .FALSE.)
      DO kmeta = 1, 3
        CALL serialize(io, LBOUND(x % quad_idx, kmeta), cleanup = .FALSE.)
      END DO
      CALL serialize(io, x % quad_idx, cleanup = .FALSE., nline = .TRUE., meta = .FALSE.)
    END IF
    CALL serialize(io, '# quad_blk', cleanup = .FALSE.)
    CALL serialize(io, '# alloc', cleanup = .FALSE.)
    CALL serialize(io, ALLOCATED(x % quad_blk), cleanup = .FALSE.)
    IF (ALLOCATED(x % quad_blk)) THEN
      CALL serialize(io, "# rank", cleanup = .FALSE.)
      CALL serialize(io, 3, cleanup = .FALSE.)
      CALL serialize(io, "# size", cleanup = .FALSE.)
      DO kmeta = 1, 3
        CALL serialize(io, SIZE(x % quad_blk, kmeta), cleanup = .FALSE.)
      END DO
      CALL serialize(io, "# lbound", cleanup = .FALSE.)
      DO kmeta = 1, 3
        CALL serialize(io, LBOUND(x % quad_blk, kmeta), cleanup = .FALSE.)
      END DO
      CALL serialize(io, x % quad_blk, cleanup = .FALSE., nline = .TRUE., meta = .FALSE.)
    END IF
    CALL serialize(io, '# refin_ctrl', cleanup = .FALSE.)
    CALL serialize(io, '# alloc', cleanup = .FALSE.)
    CALL serialize(io, ALLOCATED(x % refin_ctrl), cleanup = .FALSE.)
    IF (ALLOCATED(x % refin_ctrl)) THEN
      CALL serialize(io, "# rank", cleanup = .FALSE.)
      CALL serialize(io, 2, cleanup = .FALSE.)
      CALL serialize(io, "# size", cleanup = .FALSE.)
      DO kmeta = 1, 2
        CALL serialize(io, SIZE(x % refin_ctrl, kmeta), cleanup = .FALSE.)
      END DO
      CALL serialize(io, "# lbound", cleanup = .FALSE.)
      DO kmeta = 1, 2
        CALL serialize(io, LBOUND(x % refin_ctrl, kmeta), cleanup = .FALSE.)
      END DO
      CALL serialize(io, x % refin_ctrl, cleanup = .FALSE., nline = .TRUE., meta = .FALSE.)
    END IF
    CALL serialize(io, '# start_index', cleanup = .FALSE.)
    CALL serialize(io, '# alloc', cleanup = .FALSE.)
    CALL serialize(io, ALLOCATED(x % start_index), cleanup = .FALSE.)
    IF (ALLOCATED(x % start_index)) THEN
      CALL serialize(io, "# rank", cleanup = .FALSE.)
      CALL serialize(io, 1, cleanup = .FALSE.)
      CALL serialize(io, "# size", cleanup = .FALSE.)
      DO kmeta = 1, 1
        CALL serialize(io, SIZE(x % start_index, kmeta), cleanup = .FALSE.)
      END DO
      CALL serialize(io, "# lbound", cleanup = .FALSE.)
      DO kmeta = 1, 1
        CALL serialize(io, LBOUND(x % start_index, kmeta), cleanup = .FALSE.)
      END DO
      CALL serialize(io, x % start_index, cleanup = .FALSE., nline = .TRUE., meta = .FALSE.)
    END IF
    CALL serialize(io, '# end_index', cleanup = .FALSE.)
    CALL serialize(io, '# alloc', cleanup = .FALSE.)
    CALL serialize(io, ALLOCATED(x % end_index), cleanup = .FALSE.)
    IF (ALLOCATED(x % end_index)) THEN
      CALL serialize(io, "# rank", cleanup = .FALSE.)
      CALL serialize(io, 1, cleanup = .FALSE.)
      CALL serialize(io, "# size", cleanup = .FALSE.)
      DO kmeta = 1, 1
        CALL serialize(io, SIZE(x % end_index, kmeta), cleanup = .FALSE.)
      END DO
      CALL serialize(io, "# lbound", cleanup = .FALSE.)
      DO kmeta = 1, 1
        CALL serialize(io, LBOUND(x % end_index, kmeta), cleanup = .FALSE.)
      END DO
      CALL serialize(io, x % end_index, cleanup = .FALSE., nline = .TRUE., meta = .FALSE.)
    END IF
    CALL serialize(io, '# start_block', cleanup = .FALSE.)
    CALL serialize(io, '# alloc', cleanup = .FALSE.)
    CALL serialize(io, ALLOCATED(x % start_block), cleanup = .FALSE.)
    IF (ALLOCATED(x % start_block)) THEN
      CALL serialize(io, "# rank", cleanup = .FALSE.)
      CALL serialize(io, 1, cleanup = .FALSE.)
      CALL serialize(io, "# size", cleanup = .FALSE.)
      DO kmeta = 1, 1
        CALL serialize(io, SIZE(x % start_block, kmeta), cleanup = .FALSE.)
      END DO
      CALL serialize(io, "# lbound", cleanup = .FALSE.)
      DO kmeta = 1, 1
        CALL serialize(io, LBOUND(x % start_block, kmeta), cleanup = .FALSE.)
      END DO
      CALL serialize(io, x % start_block, cleanup = .FALSE., nline = .TRUE., meta = .FALSE.)
    END IF
    CALL serialize(io, '# end_block', cleanup = .FALSE.)
    CALL serialize(io, '# alloc', cleanup = .FALSE.)
    CALL serialize(io, ALLOCATED(x % end_block), cleanup = .FALSE.)
    IF (ALLOCATED(x % end_block)) THEN
      CALL serialize(io, "# rank", cleanup = .FALSE.)
      CALL serialize(io, 1, cleanup = .FALSE.)
      CALL serialize(io, "# size", cleanup = .FALSE.)
      DO kmeta = 1, 1
        CALL serialize(io, SIZE(x % end_block, kmeta), cleanup = .FALSE.)
      END DO
      CALL serialize(io, "# lbound", cleanup = .FALSE.)
      DO kmeta = 1, 1
        CALL serialize(io, LBOUND(x % end_block, kmeta), cleanup = .FALSE.)
      END DO
      CALL serialize(io, x % end_block, cleanup = .FALSE., nline = .TRUE., meta = .FALSE.)
    END IF
    IF (nline_local) WRITE(io, '(g0)', ADVANCE = 'no') NEW_LINE('A')
    IF (cleanup_local) CLOSE(UNIT = io)
  END SUBROUTINE W_t_grid_edges
  SUBROUTINE W_t_patch(io, x, cleanup, nline)
    USE mo_model_domain, ONLY: t_patch
    INTEGER :: io
    TYPE(t_patch), TARGET, INTENT(IN) :: x
    LOGICAL, OPTIONAL, INTENT(IN) :: cleanup, nline
    INTEGER :: kmeta, kmeta_0, kmeta_1, kmeta_2, kmeta_3, kmeta_4, kmeta_5, kmeta_6, kmeta_7, kmeta_8, kmeta_9
    LOGICAL :: cleanup_local, nline_local
    cleanup_local = .TRUE.
    nline_local = .TRUE.
    IF (PRESENT(cleanup)) cleanup_local = cleanup
    IF (PRESENT(nline)) nline_local = nline
    CALL serialize(io, '# id', cleanup = .FALSE.)
    CALL serialize(io, x % id, cleanup = .FALSE.)
    CALL serialize(io, '# nblks_c', cleanup = .FALSE.)
    CALL serialize(io, x % nblks_c, cleanup = .FALSE.)
    CALL serialize(io, '# nblks_e', cleanup = .FALSE.)
    CALL serialize(io, x % nblks_e, cleanup = .FALSE.)
    CALL serialize(io, '# nblks_v', cleanup = .FALSE.)
    CALL serialize(io, x % nblks_v, cleanup = .FALSE.)
    CALL serialize(io, '# nlev', cleanup = .FALSE.)
    CALL serialize(io, x % nlev, cleanup = .FALSE.)
    CALL serialize(io, '# nlevp1', cleanup = .FALSE.)
    CALL serialize(io, x % nlevp1, cleanup = .FALSE.)
    CALL serialize(io, '# cells', cleanup = .FALSE.)
    CALL serialize(io, x % cells, cleanup = .FALSE.)
    CALL serialize(io, '# edges', cleanup = .FALSE.)
    CALL serialize(io, x % edges, cleanup = .FALSE.)
    IF (nline_local) WRITE(io, '(g0)', ADVANCE = 'no') NEW_LINE('A')
    IF (cleanup_local) CLOSE(UNIT = io)
  END SUBROUTINE W_t_patch
  SUBROUTINE W_t_nh_prog(io, x, cleanup, nline)
    USE mo_nonhydro_types, ONLY: t_nh_prog
    INTEGER :: io
    TYPE(t_nh_prog), TARGET, INTENT(IN) :: x
    LOGICAL, OPTIONAL, INTENT(IN) :: cleanup, nline
    INTEGER :: kmeta, kmeta_0, kmeta_1, kmeta_2, kmeta_3, kmeta_4, kmeta_5, kmeta_6, kmeta_7, kmeta_8, kmeta_9
    LOGICAL :: cleanup_local, nline_local
    cleanup_local = .TRUE.
    nline_local = .TRUE.
    IF (PRESENT(cleanup)) cleanup_local = cleanup
    IF (PRESENT(nline)) nline_local = nline
    CALL serialize(io, '# w', cleanup = .FALSE.)
    CALL serialize(io, '# assoc', cleanup = .FALSE.)
    CALL serialize(io, ASSOCIATED(x % w), cleanup = .FALSE.)
    IF (ASSOCIATED(x % w)) THEN
      kmeta = 0
      CALL serialize(io, "# missing", cleanup = .FALSE.)
      CALL serialize(io, (kmeta == 0), cleanup = .FALSE.)
      CALL serialize(io, x % w, cleanup = .FALSE.)
    END IF
    CALL serialize(io, '# vn', cleanup = .FALSE.)
    CALL serialize(io, '# assoc', cleanup = .FALSE.)
    CALL serialize(io, ASSOCIATED(x % vn), cleanup = .FALSE.)
    IF (ASSOCIATED(x % vn)) THEN
      kmeta = 0
      CALL serialize(io, "# missing", cleanup = .FALSE.)
      CALL serialize(io, (kmeta == 0), cleanup = .FALSE.)
      CALL serialize(io, x % vn, cleanup = .FALSE.)
    END IF
    CALL serialize(io, '# rho', cleanup = .FALSE.)
    CALL serialize(io, '# assoc', cleanup = .FALSE.)
    CALL serialize(io, ASSOCIATED(x % rho), cleanup = .FALSE.)
    IF (ASSOCIATED(x % rho)) THEN
      kmeta = 0
      CALL serialize(io, "# missing", cleanup = .FALSE.)
      CALL serialize(io, (kmeta == 0), cleanup = .FALSE.)
      CALL serialize(io, x % rho, cleanup = .FALSE.)
    END IF
    CALL serialize(io, '# exner', cleanup = .FALSE.)
    CALL serialize(io, '# assoc', cleanup = .FALSE.)
    CALL serialize(io, ASSOCIATED(x % exner), cleanup = .FALSE.)
    IF (ASSOCIATED(x % exner)) THEN
      kmeta = 0
      CALL serialize(io, "# missing", cleanup = .FALSE.)
      CALL serialize(io, (kmeta == 0), cleanup = .FALSE.)
      CALL serialize(io, x % exner, cleanup = .FALSE.)
    END IF
    CALL serialize(io, '# theta_v', cleanup = .FALSE.)
    CALL serialize(io, '# assoc', cleanup = .FALSE.)
    CALL serialize(io, ASSOCIATED(x % theta_v), cleanup = .FALSE.)
    IF (ASSOCIATED(x % theta_v)) THEN
      kmeta = 0
      CALL serialize(io, "# missing", cleanup = .FALSE.)
      CALL serialize(io, (kmeta == 0), cleanup = .FALSE.)
      CALL serialize(io, x % theta_v, cleanup = .FALSE.)
    END IF
    IF (nline_local) WRITE(io, '(g0)', ADVANCE = 'no') NEW_LINE('A')
    IF (cleanup_local) CLOSE(UNIT = io)
  END SUBROUTINE W_t_nh_prog
  SUBROUTINE W_t_nh_diag(io, x, cleanup, nline)
    USE mo_nonhydro_types, ONLY: t_nh_diag
    INTEGER :: io
    TYPE(t_nh_diag), TARGET, INTENT(IN) :: x
    LOGICAL, OPTIONAL, INTENT(IN) :: cleanup, nline
    INTEGER :: kmeta, kmeta_0, kmeta_1, kmeta_2, kmeta_3, kmeta_4, kmeta_5, kmeta_6, kmeta_7, kmeta_8, kmeta_9
    LOGICAL :: cleanup_local, nline_local
    cleanup_local = .TRUE.
    nline_local = .TRUE.
    IF (PRESENT(cleanup)) cleanup_local = cleanup
    IF (PRESENT(nline)) nline_local = nline
    CALL serialize(io, '# exner_pr', cleanup = .FALSE.)
    CALL serialize(io, '# assoc', cleanup = .FALSE.)
    CALL serialize(io, ASSOCIATED(x % exner_pr), cleanup = .FALSE.)
    IF (ASSOCIATED(x % exner_pr)) THEN
      kmeta = 0
      CALL serialize(io, "# missing", cleanup = .FALSE.)
      CALL serialize(io, (kmeta == 0), cleanup = .FALSE.)
      CALL serialize(io, x % exner_pr, cleanup = .FALSE.)
    END IF
    CALL serialize(io, '# mass_fl_e', cleanup = .FALSE.)
    CALL serialize(io, '# assoc', cleanup = .FALSE.)
    CALL serialize(io, ASSOCIATED(x % mass_fl_e), cleanup = .FALSE.)
    IF (ASSOCIATED(x % mass_fl_e)) THEN
      kmeta = 0
      CALL serialize(io, "# missing", cleanup = .FALSE.)
      CALL serialize(io, (kmeta == 0), cleanup = .FALSE.)
      CALL serialize(io, x % mass_fl_e, cleanup = .FALSE.)
    END IF
    CALL serialize(io, '# rho_ic', cleanup = .FALSE.)
    CALL serialize(io, '# assoc', cleanup = .FALSE.)
    CALL serialize(io, ASSOCIATED(x % rho_ic), cleanup = .FALSE.)
    IF (ASSOCIATED(x % rho_ic)) THEN
      kmeta = 0
      CALL serialize(io, "# missing", cleanup = .FALSE.)
      CALL serialize(io, (kmeta == 0), cleanup = .FALSE.)
      CALL serialize(io, x % rho_ic, cleanup = .FALSE.)
    END IF
    CALL serialize(io, '# theta_v_ic', cleanup = .FALSE.)
    CALL serialize(io, '# assoc', cleanup = .FALSE.)
    CALL serialize(io, ASSOCIATED(x % theta_v_ic), cleanup = .FALSE.)
    IF (ASSOCIATED(x % theta_v_ic)) THEN
      kmeta = 0
      CALL serialize(io, "# missing", cleanup = .FALSE.)
      CALL serialize(io, (kmeta == 0), cleanup = .FALSE.)
      CALL serialize(io, x % theta_v_ic, cleanup = .FALSE.)
    END IF
    CALL serialize(io, '# grf_bdy_mflx', cleanup = .FALSE.)
    CALL serialize(io, '# assoc', cleanup = .FALSE.)
    CALL serialize(io, ASSOCIATED(x % grf_bdy_mflx), cleanup = .FALSE.)
    IF (ASSOCIATED(x % grf_bdy_mflx)) THEN
      kmeta = 0
      CALL serialize(io, "# missing", cleanup = .FALSE.)
      CALL serialize(io, (kmeta == 0), cleanup = .FALSE.)
      CALL serialize(io, x % grf_bdy_mflx, cleanup = .FALSE.)
    END IF
    CALL serialize(io, '# w_int', cleanup = .FALSE.)
    CALL serialize(io, '# assoc', cleanup = .FALSE.)
    CALL serialize(io, ASSOCIATED(x % w_int), cleanup = .FALSE.)
    IF (ASSOCIATED(x % w_int)) THEN
      kmeta = 0
      CALL serialize(io, "# missing", cleanup = .FALSE.)
      CALL serialize(io, (kmeta == 0), cleanup = .FALSE.)
      CALL serialize(io, x % w_int, cleanup = .FALSE.)
    END IF
    CALL serialize(io, '# w_ubc', cleanup = .FALSE.)
    CALL serialize(io, '# assoc', cleanup = .FALSE.)
    CALL serialize(io, ASSOCIATED(x % w_ubc), cleanup = .FALSE.)
    IF (ASSOCIATED(x % w_ubc)) THEN
      kmeta = 0
      CALL serialize(io, "# missing", cleanup = .FALSE.)
      CALL serialize(io, (kmeta == 0), cleanup = .FALSE.)
      CALL serialize(io, x % w_ubc, cleanup = .FALSE.)
    END IF
    CALL serialize(io, '# theta_v_ic_int', cleanup = .FALSE.)
    CALL serialize(io, '# assoc', cleanup = .FALSE.)
    CALL serialize(io, ASSOCIATED(x % theta_v_ic_int), cleanup = .FALSE.)
    IF (ASSOCIATED(x % theta_v_ic_int)) THEN
      kmeta = 0
      CALL serialize(io, "# missing", cleanup = .FALSE.)
      CALL serialize(io, (kmeta == 0), cleanup = .FALSE.)
      CALL serialize(io, x % theta_v_ic_int, cleanup = .FALSE.)
    END IF
    CALL serialize(io, '# rho_ic_int', cleanup = .FALSE.)
    CALL serialize(io, '# assoc', cleanup = .FALSE.)
    CALL serialize(io, ASSOCIATED(x % rho_ic_int), cleanup = .FALSE.)
    IF (ASSOCIATED(x % rho_ic_int)) THEN
      kmeta = 0
      CALL serialize(io, "# missing", cleanup = .FALSE.)
      CALL serialize(io, (kmeta == 0), cleanup = .FALSE.)
      CALL serialize(io, x % rho_ic_int, cleanup = .FALSE.)
    END IF
    CALL serialize(io, '# mflx_ic_int', cleanup = .FALSE.)
    CALL serialize(io, '# assoc', cleanup = .FALSE.)
    CALL serialize(io, ASSOCIATED(x % mflx_ic_int), cleanup = .FALSE.)
    IF (ASSOCIATED(x % mflx_ic_int)) THEN
      kmeta = 0
      CALL serialize(io, "# missing", cleanup = .FALSE.)
      CALL serialize(io, (kmeta == 0), cleanup = .FALSE.)
      CALL serialize(io, x % mflx_ic_int, cleanup = .FALSE.)
    END IF
    CALL serialize(io, '# mflx_ic_ubc', cleanup = .FALSE.)
    CALL serialize(io, '# assoc', cleanup = .FALSE.)
    CALL serialize(io, ASSOCIATED(x % mflx_ic_ubc), cleanup = .FALSE.)
    IF (ASSOCIATED(x % mflx_ic_ubc)) THEN
      kmeta = 0
      CALL serialize(io, "# missing", cleanup = .FALSE.)
      CALL serialize(io, (kmeta == 0), cleanup = .FALSE.)
      CALL serialize(io, x % mflx_ic_ubc, cleanup = .FALSE.)
    END IF
    CALL serialize(io, '# exner_incr', cleanup = .FALSE.)
    CALL serialize(io, '# assoc', cleanup = .FALSE.)
    CALL serialize(io, ASSOCIATED(x % exner_incr), cleanup = .FALSE.)
    IF (ASSOCIATED(x % exner_incr)) THEN
      kmeta = 0
      CALL serialize(io, "# missing", cleanup = .FALSE.)
      CALL serialize(io, (kmeta == 0), cleanup = .FALSE.)
      CALL serialize(io, x % exner_incr, cleanup = .FALSE.)
    END IF
    CALL serialize(io, '# rho_incr', cleanup = .FALSE.)
    CALL serialize(io, '# assoc', cleanup = .FALSE.)
    CALL serialize(io, ASSOCIATED(x % rho_incr), cleanup = .FALSE.)
    IF (ASSOCIATED(x % rho_incr)) THEN
      kmeta = 0
      CALL serialize(io, "# missing", cleanup = .FALSE.)
      CALL serialize(io, (kmeta == 0), cleanup = .FALSE.)
      CALL serialize(io, x % rho_incr, cleanup = .FALSE.)
    END IF
    CALL serialize(io, '# vt', cleanup = .FALSE.)
    CALL serialize(io, '# assoc', cleanup = .FALSE.)
    CALL serialize(io, ASSOCIATED(x % vt), cleanup = .FALSE.)
    IF (ASSOCIATED(x % vt)) THEN
      kmeta = 0
      CALL serialize(io, "# missing", cleanup = .FALSE.)
      CALL serialize(io, (kmeta == 0), cleanup = .FALSE.)
      CALL serialize(io, x % vt, cleanup = .FALSE.)
    END IF
    CALL serialize(io, '# ddt_exner_phy', cleanup = .FALSE.)
    CALL serialize(io, '# assoc', cleanup = .FALSE.)
    CALL serialize(io, ASSOCIATED(x % ddt_exner_phy), cleanup = .FALSE.)
    IF (ASSOCIATED(x % ddt_exner_phy)) THEN
      kmeta = 0
      CALL serialize(io, "# missing", cleanup = .FALSE.)
      CALL serialize(io, (kmeta == 0), cleanup = .FALSE.)
      CALL serialize(io, x % ddt_exner_phy, cleanup = .FALSE.)
    END IF
    CALL serialize(io, '# exner_dyn_incr', cleanup = .FALSE.)
    CALL serialize(io, '# assoc', cleanup = .FALSE.)
    CALL serialize(io, ASSOCIATED(x % exner_dyn_incr), cleanup = .FALSE.)
    IF (ASSOCIATED(x % exner_dyn_incr)) THEN
      kmeta = 0
      CALL serialize(io, "# missing", cleanup = .FALSE.)
      CALL serialize(io, (kmeta == 0), cleanup = .FALSE.)
      CALL serialize(io, x % exner_dyn_incr, cleanup = .FALSE.)
    END IF
    CALL serialize(io, '# w_concorr_c', cleanup = .FALSE.)
    CALL serialize(io, '# assoc', cleanup = .FALSE.)
    CALL serialize(io, ASSOCIATED(x % w_concorr_c), cleanup = .FALSE.)
    IF (ASSOCIATED(x % w_concorr_c)) THEN
      kmeta = 0
      CALL serialize(io, "# missing", cleanup = .FALSE.)
      CALL serialize(io, (kmeta == 0), cleanup = .FALSE.)
      CALL serialize(io, x % w_concorr_c, cleanup = .FALSE.)
    END IF
    CALL serialize(io, '# mass_fl_e_sv', cleanup = .FALSE.)
    CALL serialize(io, '# assoc', cleanup = .FALSE.)
    CALL serialize(io, ASSOCIATED(x % mass_fl_e_sv), cleanup = .FALSE.)
    IF (ASSOCIATED(x % mass_fl_e_sv)) THEN
      kmeta = 0
      CALL serialize(io, "# missing", cleanup = .FALSE.)
      CALL serialize(io, (kmeta == 0), cleanup = .FALSE.)
      CALL serialize(io, x % mass_fl_e_sv, cleanup = .FALSE.)
    END IF
    CALL serialize(io, '# ddt_w_adv_pc', cleanup = .FALSE.)
    CALL serialize(io, '# assoc', cleanup = .FALSE.)
    CALL serialize(io, ASSOCIATED(x % ddt_w_adv_pc), cleanup = .FALSE.)
    IF (ASSOCIATED(x % ddt_w_adv_pc)) THEN
      kmeta = 0
      CALL serialize(io, "# missing", cleanup = .FALSE.)
      CALL serialize(io, (kmeta == 0), cleanup = .FALSE.)
      CALL serialize(io, x % ddt_w_adv_pc, cleanup = .FALSE.)
    END IF
    IF (nline_local) WRITE(io, '(g0)', ADVANCE = 'no') NEW_LINE('A')
    IF (cleanup_local) CLOSE(UNIT = io)
  END SUBROUTINE W_t_nh_diag
  SUBROUTINE W_t_nh_ref(io, x, cleanup, nline)
    USE mo_nonhydro_types, ONLY: t_nh_ref
    INTEGER :: io
    TYPE(t_nh_ref), TARGET, INTENT(IN) :: x
    LOGICAL, OPTIONAL, INTENT(IN) :: cleanup, nline
    INTEGER :: kmeta, kmeta_0, kmeta_1, kmeta_2, kmeta_3, kmeta_4, kmeta_5, kmeta_6, kmeta_7, kmeta_8, kmeta_9
    LOGICAL :: cleanup_local, nline_local
    cleanup_local = .TRUE.
    nline_local = .TRUE.
    IF (PRESENT(cleanup)) cleanup_local = cleanup
    IF (PRESENT(nline)) nline_local = nline
    CALL serialize(io, '# w_ref', cleanup = .FALSE.)
    CALL serialize(io, '# assoc', cleanup = .FALSE.)
    CALL serialize(io, ASSOCIATED(x % w_ref), cleanup = .FALSE.)
    IF (ASSOCIATED(x % w_ref)) THEN
      kmeta = 0
      CALL serialize(io, "# missing", cleanup = .FALSE.)
      CALL serialize(io, (kmeta == 0), cleanup = .FALSE.)
      CALL serialize(io, x % w_ref, cleanup = .FALSE.)
    END IF
    IF (nline_local) WRITE(io, '(g0)', ADVANCE = 'no') NEW_LINE('A')
    IF (cleanup_local) CLOSE(UNIT = io)
  END SUBROUTINE W_t_nh_ref
  SUBROUTINE W_t_nh_metrics(io, x, cleanup, nline)
    USE mo_nonhydro_types, ONLY: t_nh_metrics
    INTEGER :: io
    TYPE(t_nh_metrics), TARGET, INTENT(IN) :: x
    LOGICAL, OPTIONAL, INTENT(IN) :: cleanup, nline
    INTEGER :: kmeta, kmeta_0, kmeta_1, kmeta_2, kmeta_3, kmeta_4, kmeta_5, kmeta_6, kmeta_7, kmeta_8, kmeta_9
    LOGICAL :: cleanup_local, nline_local
    cleanup_local = .TRUE.
    nline_local = .TRUE.
    IF (PRESENT(cleanup)) cleanup_local = cleanup
    IF (PRESENT(nline)) nline_local = nline
    CALL serialize(io, '# rayleigh_w', cleanup = .FALSE.)
    CALL serialize(io, '# assoc', cleanup = .FALSE.)
    CALL serialize(io, ASSOCIATED(x % rayleigh_w), cleanup = .FALSE.)
    IF (ASSOCIATED(x % rayleigh_w)) THEN
      kmeta = 0
      CALL serialize(io, "# missing", cleanup = .FALSE.)
      CALL serialize(io, (kmeta == 0), cleanup = .FALSE.)
      CALL serialize(io, x % rayleigh_w, cleanup = .FALSE.)
    END IF
    CALL serialize(io, '# vwind_expl_wgt', cleanup = .FALSE.)
    CALL serialize(io, '# assoc', cleanup = .FALSE.)
    CALL serialize(io, ASSOCIATED(x % vwind_expl_wgt), cleanup = .FALSE.)
    IF (ASSOCIATED(x % vwind_expl_wgt)) THEN
      kmeta = 0
      CALL serialize(io, "# missing", cleanup = .FALSE.)
      CALL serialize(io, (kmeta == 0), cleanup = .FALSE.)
      CALL serialize(io, x % vwind_expl_wgt, cleanup = .FALSE.)
    END IF
    CALL serialize(io, '# vwind_impl_wgt', cleanup = .FALSE.)
    CALL serialize(io, '# assoc', cleanup = .FALSE.)
    CALL serialize(io, ASSOCIATED(x % vwind_impl_wgt), cleanup = .FALSE.)
    IF (ASSOCIATED(x % vwind_impl_wgt)) THEN
      kmeta = 0
      CALL serialize(io, "# missing", cleanup = .FALSE.)
      CALL serialize(io, (kmeta == 0), cleanup = .FALSE.)
      CALL serialize(io, x % vwind_impl_wgt, cleanup = .FALSE.)
    END IF
    CALL serialize(io, '# ddxn_z_full', cleanup = .FALSE.)
    CALL serialize(io, '# assoc', cleanup = .FALSE.)
    CALL serialize(io, ASSOCIATED(x % ddxn_z_full), cleanup = .FALSE.)
    IF (ASSOCIATED(x % ddxn_z_full)) THEN
      kmeta = 0
      CALL serialize(io, "# missing", cleanup = .FALSE.)
      CALL serialize(io, (kmeta == 0), cleanup = .FALSE.)
      CALL serialize(io, x % ddxn_z_full, cleanup = .FALSE.)
    END IF
    CALL serialize(io, '# ddxt_z_full', cleanup = .FALSE.)
    CALL serialize(io, '# assoc', cleanup = .FALSE.)
    CALL serialize(io, ASSOCIATED(x % ddxt_z_full), cleanup = .FALSE.)
    IF (ASSOCIATED(x % ddxt_z_full)) THEN
      kmeta = 0
      CALL serialize(io, "# missing", cleanup = .FALSE.)
      CALL serialize(io, (kmeta == 0), cleanup = .FALSE.)
      CALL serialize(io, x % ddxt_z_full, cleanup = .FALSE.)
    END IF
    CALL serialize(io, '# ddqz_z_full_e', cleanup = .FALSE.)
    CALL serialize(io, '# assoc', cleanup = .FALSE.)
    CALL serialize(io, ASSOCIATED(x % ddqz_z_full_e), cleanup = .FALSE.)
    IF (ASSOCIATED(x % ddqz_z_full_e)) THEN
      kmeta = 0
      CALL serialize(io, "# missing", cleanup = .FALSE.)
      CALL serialize(io, (kmeta == 0), cleanup = .FALSE.)
      CALL serialize(io, x % ddqz_z_full_e, cleanup = .FALSE.)
    END IF
    CALL serialize(io, '# ddqz_z_half', cleanup = .FALSE.)
    CALL serialize(io, '# assoc', cleanup = .FALSE.)
    CALL serialize(io, ASSOCIATED(x % ddqz_z_half), cleanup = .FALSE.)
    IF (ASSOCIATED(x % ddqz_z_half)) THEN
      kmeta = 0
      CALL serialize(io, "# missing", cleanup = .FALSE.)
      CALL serialize(io, (kmeta == 0), cleanup = .FALSE.)
      CALL serialize(io, x % ddqz_z_half, cleanup = .FALSE.)
    END IF
    CALL serialize(io, '# inv_ddqz_z_full', cleanup = .FALSE.)
    CALL serialize(io, '# assoc', cleanup = .FALSE.)
    CALL serialize(io, ASSOCIATED(x % inv_ddqz_z_full), cleanup = .FALSE.)
    IF (ASSOCIATED(x % inv_ddqz_z_full)) THEN
      kmeta = 0
      CALL serialize(io, "# missing", cleanup = .FALSE.)
      CALL serialize(io, (kmeta == 0), cleanup = .FALSE.)
      CALL serialize(io, x % inv_ddqz_z_full, cleanup = .FALSE.)
    END IF
    CALL serialize(io, '# wgtfac_c', cleanup = .FALSE.)
    CALL serialize(io, '# assoc', cleanup = .FALSE.)
    CALL serialize(io, ASSOCIATED(x % wgtfac_c), cleanup = .FALSE.)
    IF (ASSOCIATED(x % wgtfac_c)) THEN
      kmeta = 0
      CALL serialize(io, "# missing", cleanup = .FALSE.)
      CALL serialize(io, (kmeta == 0), cleanup = .FALSE.)
      CALL serialize(io, x % wgtfac_c, cleanup = .FALSE.)
    END IF
    CALL serialize(io, '# wgtfacq_c', cleanup = .FALSE.)
    CALL serialize(io, '# assoc', cleanup = .FALSE.)
    CALL serialize(io, ASSOCIATED(x % wgtfacq_c), cleanup = .FALSE.)
    IF (ASSOCIATED(x % wgtfacq_c)) THEN
      kmeta = 0
      CALL serialize(io, "# missing", cleanup = .FALSE.)
      CALL serialize(io, (kmeta == 0), cleanup = .FALSE.)
      CALL serialize(io, x % wgtfacq_c, cleanup = .FALSE.)
    END IF
    CALL serialize(io, '# exner_ref_mc', cleanup = .FALSE.)
    CALL serialize(io, '# assoc', cleanup = .FALSE.)
    CALL serialize(io, ASSOCIATED(x % exner_ref_mc), cleanup = .FALSE.)
    IF (ASSOCIATED(x % exner_ref_mc)) THEN
      kmeta = 0
      CALL serialize(io, "# missing", cleanup = .FALSE.)
      CALL serialize(io, (kmeta == 0), cleanup = .FALSE.)
      CALL serialize(io, x % exner_ref_mc, cleanup = .FALSE.)
    END IF
    CALL serialize(io, '# bdy_mflx_e_idx', cleanup = .FALSE.)
    CALL serialize(io, '# assoc', cleanup = .FALSE.)
    CALL serialize(io, ASSOCIATED(x % bdy_mflx_e_idx), cleanup = .FALSE.)
    IF (ASSOCIATED(x % bdy_mflx_e_idx)) THEN
      kmeta = 0
      CALL serialize(io, "# missing", cleanup = .FALSE.)
      CALL serialize(io, (kmeta == 0), cleanup = .FALSE.)
      CALL serialize(io, x % bdy_mflx_e_idx, cleanup = .FALSE.)
    END IF
    CALL serialize(io, '# bdy_mflx_e_blk', cleanup = .FALSE.)
    CALL serialize(io, '# assoc', cleanup = .FALSE.)
    CALL serialize(io, ASSOCIATED(x % bdy_mflx_e_blk), cleanup = .FALSE.)
    IF (ASSOCIATED(x % bdy_mflx_e_blk)) THEN
      kmeta = 0
      CALL serialize(io, "# missing", cleanup = .FALSE.)
      CALL serialize(io, (kmeta == 0), cleanup = .FALSE.)
      CALL serialize(io, x % bdy_mflx_e_blk, cleanup = .FALSE.)
    END IF
    CALL serialize(io, '# deepatmo_divh_mc', cleanup = .FALSE.)
    CALL serialize(io, '# assoc', cleanup = .FALSE.)
    CALL serialize(io, ASSOCIATED(x % deepatmo_divh_mc), cleanup = .FALSE.)
    IF (ASSOCIATED(x % deepatmo_divh_mc)) THEN
      kmeta = 0
      CALL serialize(io, "# missing", cleanup = .FALSE.)
      CALL serialize(io, (kmeta == 0), cleanup = .FALSE.)
      CALL serialize(io, x % deepatmo_divh_mc, cleanup = .FALSE.)
    END IF
    CALL serialize(io, '# deepatmo_divzu_mc', cleanup = .FALSE.)
    CALL serialize(io, '# assoc', cleanup = .FALSE.)
    CALL serialize(io, ASSOCIATED(x % deepatmo_divzu_mc), cleanup = .FALSE.)
    IF (ASSOCIATED(x % deepatmo_divzu_mc)) THEN
      kmeta = 0
      CALL serialize(io, "# missing", cleanup = .FALSE.)
      CALL serialize(io, (kmeta == 0), cleanup = .FALSE.)
      CALL serialize(io, x % deepatmo_divzu_mc, cleanup = .FALSE.)
    END IF
    CALL serialize(io, '# deepatmo_divzl_mc', cleanup = .FALSE.)
    CALL serialize(io, '# assoc', cleanup = .FALSE.)
    CALL serialize(io, ASSOCIATED(x % deepatmo_divzl_mc), cleanup = .FALSE.)
    IF (ASSOCIATED(x % deepatmo_divzl_mc)) THEN
      kmeta = 0
      CALL serialize(io, "# missing", cleanup = .FALSE.)
      CALL serialize(io, (kmeta == 0), cleanup = .FALSE.)
      CALL serialize(io, x % deepatmo_divzl_mc, cleanup = .FALSE.)
    END IF
    CALL serialize(io, '# bdy_mflx_e_dim', cleanup = .FALSE.)
    CALL serialize(io, x % bdy_mflx_e_dim, cleanup = .FALSE.)
    IF (nline_local) WRITE(io, '(g0)', ADVANCE = 'no') NEW_LINE('A')
    IF (cleanup_local) CLOSE(UNIT = io)
  END SUBROUTINE W_t_nh_metrics
  SUBROUTINE W_t_nh_state(io, x, cleanup, nline)
    USE mo_nonhydro_types, ONLY: t_nh_state
    INTEGER :: io
    TYPE(t_nh_state), TARGET, INTENT(IN) :: x
    LOGICAL, OPTIONAL, INTENT(IN) :: cleanup, nline
    INTEGER :: kmeta, kmeta_0, kmeta_1, kmeta_2, kmeta_3, kmeta_4, kmeta_5, kmeta_6, kmeta_7, kmeta_8, kmeta_9
    LOGICAL :: cleanup_local, nline_local
    cleanup_local = .TRUE.
    nline_local = .TRUE.
    IF (PRESENT(cleanup)) cleanup_local = cleanup
    IF (PRESENT(nline)) nline_local = nline
    CALL serialize(io, '# prog', cleanup = .FALSE.)
    CALL serialize(io, '# alloc', cleanup = .FALSE.)
    CALL serialize(io, ALLOCATED(x % prog), cleanup = .FALSE.)
    IF (ALLOCATED(x % prog)) THEN
      CALL serialize(io, "# rank", cleanup = .FALSE.)
      CALL serialize(io, 1, cleanup = .FALSE.)
      CALL serialize(io, "# size", cleanup = .FALSE.)
      DO kmeta = 1, 1
        CALL serialize(io, SIZE(x % prog, kmeta), cleanup = .FALSE.)
      END DO
      CALL serialize(io, "# lbound", cleanup = .FALSE.)
      DO kmeta = 1, 1
        CALL serialize(io, LBOUND(x % prog, kmeta), cleanup = .FALSE.)
      END DO
      CALL serialize(io, x % prog, cleanup = .FALSE., nline = .TRUE., meta = .FALSE.)
    END IF
    CALL serialize(io, '# diag', cleanup = .FALSE.)
    CALL serialize(io, x % diag, cleanup = .FALSE.)
    CALL serialize(io, '# ref', cleanup = .FALSE.)
    CALL serialize(io, x % ref, cleanup = .FALSE.)
    CALL serialize(io, '# metrics', cleanup = .FALSE.)
    CALL serialize(io, x % metrics, cleanup = .FALSE.)
    IF (nline_local) WRITE(io, '(g0)', ADVANCE = 'no') NEW_LINE('A')
    IF (cleanup_local) CLOSE(UNIT = io)
  END SUBROUTINE W_t_nh_state
  SUBROUTINE W_t_prepare_adv(io, x, cleanup, nline)
    USE mo_prepadv_types, ONLY: t_prepare_adv
    INTEGER :: io
    TYPE(t_prepare_adv), TARGET, INTENT(IN) :: x
    LOGICAL, OPTIONAL, INTENT(IN) :: cleanup, nline
    INTEGER :: kmeta, kmeta_0, kmeta_1, kmeta_2, kmeta_3, kmeta_4, kmeta_5, kmeta_6, kmeta_7, kmeta_8, kmeta_9
    LOGICAL :: cleanup_local, nline_local
    cleanup_local = .TRUE.
    nline_local = .TRUE.
    IF (PRESENT(cleanup)) cleanup_local = cleanup
    IF (PRESENT(nline)) nline_local = nline
    CALL serialize(io, '# mass_flx_me', cleanup = .FALSE.)
    CALL serialize(io, '# assoc', cleanup = .FALSE.)
    CALL serialize(io, ASSOCIATED(x % mass_flx_me), cleanup = .FALSE.)
    IF (ASSOCIATED(x % mass_flx_me)) THEN
      kmeta = 0
      CALL serialize(io, "# missing", cleanup = .FALSE.)
      CALL serialize(io, (kmeta == 0), cleanup = .FALSE.)
      CALL serialize(io, x % mass_flx_me, cleanup = .FALSE.)
    END IF
    CALL serialize(io, '# mass_flx_ic', cleanup = .FALSE.)
    CALL serialize(io, '# assoc', cleanup = .FALSE.)
    CALL serialize(io, ASSOCIATED(x % mass_flx_ic), cleanup = .FALSE.)
    IF (ASSOCIATED(x % mass_flx_ic)) THEN
      kmeta = 0
      CALL serialize(io, "# missing", cleanup = .FALSE.)
      CALL serialize(io, (kmeta == 0), cleanup = .FALSE.)
      CALL serialize(io, x % mass_flx_ic, cleanup = .FALSE.)
    END IF
    CALL serialize(io, '# vol_flx_ic', cleanup = .FALSE.)
    CALL serialize(io, '# assoc', cleanup = .FALSE.)
    CALL serialize(io, ASSOCIATED(x % vol_flx_ic), cleanup = .FALSE.)
    IF (ASSOCIATED(x % vol_flx_ic)) THEN
      kmeta = 0
      CALL serialize(io, "# missing", cleanup = .FALSE.)
      CALL serialize(io, (kmeta == 0), cleanup = .FALSE.)
      CALL serialize(io, x % vol_flx_ic, cleanup = .FALSE.)
    END IF
    CALL serialize(io, '# vn_traj', cleanup = .FALSE.)
    CALL serialize(io, '# assoc', cleanup = .FALSE.)
    CALL serialize(io, ASSOCIATED(x % vn_traj), cleanup = .FALSE.)
    IF (ASSOCIATED(x % vn_traj)) THEN
      kmeta = 0
      CALL serialize(io, "# missing", cleanup = .FALSE.)
      CALL serialize(io, (kmeta == 0), cleanup = .FALSE.)
      CALL serialize(io, x % vn_traj, cleanup = .FALSE.)
    END IF
    IF (nline_local) WRITE(io, '(g0)', ADVANCE = 'no') NEW_LINE('A')
    IF (cleanup_local) CLOSE(UNIT = io)
  END SUBROUTINE W_t_prepare_adv
  SUBROUTINE W_logical_R_1(io, x, cleanup, nline, meta)
    INTEGER :: io
    LOGICAL, INTENT(IN) :: x(:)
    INTEGER :: k, kmeta, k1
    LOGICAL, OPTIONAL, INTENT(IN) :: cleanup, nline, meta
    LOGICAL :: cleanup_local, nline_local, meta_local
    cleanup_local = .TRUE.
    nline_local = .TRUE.
    meta_local = .TRUE.
    IF (PRESENT(cleanup)) cleanup_local = cleanup
    IF (PRESENT(nline)) nline_local = nline
    IF (PRESENT(meta)) meta_local = meta
    IF (meta_local) THEN
      CALL serialize(io, "# rank", cleanup = .FALSE.)
      CALL serialize(io, 1, cleanup = .FALSE.)
      CALL serialize(io, "# size", cleanup = .FALSE.)
      DO kmeta = 1, 1
        CALL serialize(io, SIZE(x, kmeta), cleanup = .FALSE.)
      END DO
      CALL serialize(io, "# lbound", cleanup = .FALSE.)
      DO kmeta = 1, 1
        CALL serialize(io, LBOUND(x, kmeta), cleanup = .FALSE.)
      END DO
    END IF
    CALL serialize(io, "# entries", cleanup = .FALSE.)
    DO k1 = LBOUND(x, 1), UBOUND(x, 1)
      CALL serialize(io, x(k1), cleanup = .FALSE.)
    END DO
    IF (cleanup_local) CLOSE(UNIT = io)
  END SUBROUTINE W_logical_R_1
  SUBROUTINE W_integer__1_R_1(io, x, cleanup, nline, meta)
    INTEGER :: io
    INTEGER(KIND = 1), INTENT(IN) :: x(:)
    INTEGER :: k, kmeta, k1
    LOGICAL, OPTIONAL, INTENT(IN) :: cleanup, nline, meta
    LOGICAL :: cleanup_local, nline_local, meta_local
    cleanup_local = .TRUE.
    nline_local = .TRUE.
    meta_local = .TRUE.
    IF (PRESENT(cleanup)) cleanup_local = cleanup
    IF (PRESENT(nline)) nline_local = nline
    IF (PRESENT(meta)) meta_local = meta
    IF (meta_local) THEN
      CALL serialize(io, "# rank", cleanup = .FALSE.)
      CALL serialize(io, 1, cleanup = .FALSE.)
      CALL serialize(io, "# size", cleanup = .FALSE.)
      DO kmeta = 1, 1
        CALL serialize(io, SIZE(x, kmeta), cleanup = .FALSE.)
      END DO
      CALL serialize(io, "# lbound", cleanup = .FALSE.)
      DO kmeta = 1, 1
        CALL serialize(io, LBOUND(x, kmeta), cleanup = .FALSE.)
      END DO
    END IF
    CALL serialize(io, "# entries", cleanup = .FALSE.)
    DO k1 = LBOUND(x, 1), UBOUND(x, 1)
      CALL serialize(io, x(k1), cleanup = .FALSE.)
    END DO
    IF (cleanup_local) CLOSE(UNIT = io)
  END SUBROUTINE W_integer__1_R_1
  SUBROUTINE W_integer__2_R_1(io, x, cleanup, nline, meta)
    INTEGER :: io
    INTEGER(KIND = 2), INTENT(IN) :: x(:)
    INTEGER :: k, kmeta, k1
    LOGICAL, OPTIONAL, INTENT(IN) :: cleanup, nline, meta
    LOGICAL :: cleanup_local, nline_local, meta_local
    cleanup_local = .TRUE.
    nline_local = .TRUE.
    meta_local = .TRUE.
    IF (PRESENT(cleanup)) cleanup_local = cleanup
    IF (PRESENT(nline)) nline_local = nline
    IF (PRESENT(meta)) meta_local = meta
    IF (meta_local) THEN
      CALL serialize(io, "# rank", cleanup = .FALSE.)
      CALL serialize(io, 1, cleanup = .FALSE.)
      CALL serialize(io, "# size", cleanup = .FALSE.)
      DO kmeta = 1, 1
        CALL serialize(io, SIZE(x, kmeta), cleanup = .FALSE.)
      END DO
      CALL serialize(io, "# lbound", cleanup = .FALSE.)
      DO kmeta = 1, 1
        CALL serialize(io, LBOUND(x, kmeta), cleanup = .FALSE.)
      END DO
    END IF
    CALL serialize(io, "# entries", cleanup = .FALSE.)
    DO k1 = LBOUND(x, 1), UBOUND(x, 1)
      CALL serialize(io, x(k1), cleanup = .FALSE.)
    END DO
    IF (cleanup_local) CLOSE(UNIT = io)
  END SUBROUTINE W_integer__2_R_1
  SUBROUTINE W_integer__4_R_1(io, x, cleanup, nline, meta)
    INTEGER :: io
    INTEGER(KIND = 4), INTENT(IN) :: x(:)
    INTEGER :: k, kmeta, k1
    LOGICAL, OPTIONAL, INTENT(IN) :: cleanup, nline, meta
    LOGICAL :: cleanup_local, nline_local, meta_local
    cleanup_local = .TRUE.
    nline_local = .TRUE.
    meta_local = .TRUE.
    IF (PRESENT(cleanup)) cleanup_local = cleanup
    IF (PRESENT(nline)) nline_local = nline
    IF (PRESENT(meta)) meta_local = meta
    IF (meta_local) THEN
      CALL serialize(io, "# rank", cleanup = .FALSE.)
      CALL serialize(io, 1, cleanup = .FALSE.)
      CALL serialize(io, "# size", cleanup = .FALSE.)
      DO kmeta = 1, 1
        CALL serialize(io, SIZE(x, kmeta), cleanup = .FALSE.)
      END DO
      CALL serialize(io, "# lbound", cleanup = .FALSE.)
      DO kmeta = 1, 1
        CALL serialize(io, LBOUND(x, kmeta), cleanup = .FALSE.)
      END DO
    END IF
    CALL serialize(io, "# entries", cleanup = .FALSE.)
    DO k1 = LBOUND(x, 1), UBOUND(x, 1)
      CALL serialize(io, x(k1), cleanup = .FALSE.)
    END DO
    IF (cleanup_local) CLOSE(UNIT = io)
  END SUBROUTINE W_integer__4_R_1
  SUBROUTINE W_integer__8_R_1(io, x, cleanup, nline, meta)
    INTEGER :: io
    INTEGER(KIND = 8), INTENT(IN) :: x(:)
    INTEGER :: k, kmeta, k1
    LOGICAL, OPTIONAL, INTENT(IN) :: cleanup, nline, meta
    LOGICAL :: cleanup_local, nline_local, meta_local
    cleanup_local = .TRUE.
    nline_local = .TRUE.
    meta_local = .TRUE.
    IF (PRESENT(cleanup)) cleanup_local = cleanup
    IF (PRESENT(nline)) nline_local = nline
    IF (PRESENT(meta)) meta_local = meta
    IF (meta_local) THEN
      CALL serialize(io, "# rank", cleanup = .FALSE.)
      CALL serialize(io, 1, cleanup = .FALSE.)
      CALL serialize(io, "# size", cleanup = .FALSE.)
      DO kmeta = 1, 1
        CALL serialize(io, SIZE(x, kmeta), cleanup = .FALSE.)
      END DO
      CALL serialize(io, "# lbound", cleanup = .FALSE.)
      DO kmeta = 1, 1
        CALL serialize(io, LBOUND(x, kmeta), cleanup = .FALSE.)
      END DO
    END IF
    CALL serialize(io, "# entries", cleanup = .FALSE.)
    DO k1 = LBOUND(x, 1), UBOUND(x, 1)
      CALL serialize(io, x(k1), cleanup = .FALSE.)
    END DO
    IF (cleanup_local) CLOSE(UNIT = io)
  END SUBROUTINE W_integer__8_R_1
  SUBROUTINE W_real__4_R_1(io, x, cleanup, nline, meta)
    INTEGER :: io
    REAL(KIND = 4), INTENT(IN) :: x(:)
    INTEGER :: k, kmeta, k1
    LOGICAL, OPTIONAL, INTENT(IN) :: cleanup, nline, meta
    LOGICAL :: cleanup_local, nline_local, meta_local
    cleanup_local = .TRUE.
    nline_local = .TRUE.
    meta_local = .TRUE.
    IF (PRESENT(cleanup)) cleanup_local = cleanup
    IF (PRESENT(nline)) nline_local = nline
    IF (PRESENT(meta)) meta_local = meta
    IF (meta_local) THEN
      CALL serialize(io, "# rank", cleanup = .FALSE.)
      CALL serialize(io, 1, cleanup = .FALSE.)
      CALL serialize(io, "# size", cleanup = .FALSE.)
      DO kmeta = 1, 1
        CALL serialize(io, SIZE(x, kmeta), cleanup = .FALSE.)
      END DO
      CALL serialize(io, "# lbound", cleanup = .FALSE.)
      DO kmeta = 1, 1
        CALL serialize(io, LBOUND(x, kmeta), cleanup = .FALSE.)
      END DO
    END IF
    CALL serialize(io, "# entries", cleanup = .FALSE.)
    DO k1 = LBOUND(x, 1), UBOUND(x, 1)
      CALL serialize(io, x(k1), cleanup = .FALSE.)
    END DO
    IF (cleanup_local) CLOSE(UNIT = io)
  END SUBROUTINE W_real__4_R_1
  SUBROUTINE W_real__8_R_1(io, x, cleanup, nline, meta)
    INTEGER :: io
    REAL(KIND = 8), INTENT(IN) :: x(:)
    INTEGER :: k, kmeta, k1
    LOGICAL, OPTIONAL, INTENT(IN) :: cleanup, nline, meta
    LOGICAL :: cleanup_local, nline_local, meta_local
    cleanup_local = .TRUE.
    nline_local = .TRUE.
    meta_local = .TRUE.
    IF (PRESENT(cleanup)) cleanup_local = cleanup
    IF (PRESENT(nline)) nline_local = nline
    IF (PRESENT(meta)) meta_local = meta
    IF (meta_local) THEN
      CALL serialize(io, "# rank", cleanup = .FALSE.)
      CALL serialize(io, 1, cleanup = .FALSE.)
      CALL serialize(io, "# size", cleanup = .FALSE.)
      DO kmeta = 1, 1
        CALL serialize(io, SIZE(x, kmeta), cleanup = .FALSE.)
      END DO
      CALL serialize(io, "# lbound", cleanup = .FALSE.)
      DO kmeta = 1, 1
        CALL serialize(io, LBOUND(x, kmeta), cleanup = .FALSE.)
      END DO
    END IF
    CALL serialize(io, "# entries", cleanup = .FALSE.)
    DO k1 = LBOUND(x, 1), UBOUND(x, 1)
      CALL serialize(io, x(k1), cleanup = .FALSE.)
    END DO
    IF (cleanup_local) CLOSE(UNIT = io)
  END SUBROUTINE W_real__8_R_1
  SUBROUTINE W_logical_R_2(io, x, cleanup, nline, meta)
    INTEGER :: io
    LOGICAL, INTENT(IN) :: x(:, :)
    INTEGER :: k, kmeta, k1, k2
    LOGICAL, OPTIONAL, INTENT(IN) :: cleanup, nline, meta
    LOGICAL :: cleanup_local, nline_local, meta_local
    cleanup_local = .TRUE.
    nline_local = .TRUE.
    meta_local = .TRUE.
    IF (PRESENT(cleanup)) cleanup_local = cleanup
    IF (PRESENT(nline)) nline_local = nline
    IF (PRESENT(meta)) meta_local = meta
    IF (meta_local) THEN
      CALL serialize(io, "# rank", cleanup = .FALSE.)
      CALL serialize(io, 2, cleanup = .FALSE.)
      CALL serialize(io, "# size", cleanup = .FALSE.)
      DO kmeta = 1, 2
        CALL serialize(io, SIZE(x, kmeta), cleanup = .FALSE.)
      END DO
      CALL serialize(io, "# lbound", cleanup = .FALSE.)
      DO kmeta = 1, 2
        CALL serialize(io, LBOUND(x, kmeta), cleanup = .FALSE.)
      END DO
    END IF
    CALL serialize(io, "# entries", cleanup = .FALSE.)
    DO k2 = LBOUND(x, 2), UBOUND(x, 2)
      DO k1 = LBOUND(x, 1), UBOUND(x, 1)
        CALL serialize(io, x(k1, k2), cleanup = .FALSE.)
      END DO
    END DO
    IF (cleanup_local) CLOSE(UNIT = io)
  END SUBROUTINE W_logical_R_2
  SUBROUTINE W_integer__1_R_2(io, x, cleanup, nline, meta)
    INTEGER :: io
    INTEGER(KIND = 1), INTENT(IN) :: x(:, :)
    INTEGER :: k, kmeta, k1, k2
    LOGICAL, OPTIONAL, INTENT(IN) :: cleanup, nline, meta
    LOGICAL :: cleanup_local, nline_local, meta_local
    cleanup_local = .TRUE.
    nline_local = .TRUE.
    meta_local = .TRUE.
    IF (PRESENT(cleanup)) cleanup_local = cleanup
    IF (PRESENT(nline)) nline_local = nline
    IF (PRESENT(meta)) meta_local = meta
    IF (meta_local) THEN
      CALL serialize(io, "# rank", cleanup = .FALSE.)
      CALL serialize(io, 2, cleanup = .FALSE.)
      CALL serialize(io, "# size", cleanup = .FALSE.)
      DO kmeta = 1, 2
        CALL serialize(io, SIZE(x, kmeta), cleanup = .FALSE.)
      END DO
      CALL serialize(io, "# lbound", cleanup = .FALSE.)
      DO kmeta = 1, 2
        CALL serialize(io, LBOUND(x, kmeta), cleanup = .FALSE.)
      END DO
    END IF
    CALL serialize(io, "# entries", cleanup = .FALSE.)
    DO k2 = LBOUND(x, 2), UBOUND(x, 2)
      DO k1 = LBOUND(x, 1), UBOUND(x, 1)
        CALL serialize(io, x(k1, k2), cleanup = .FALSE.)
      END DO
    END DO
    IF (cleanup_local) CLOSE(UNIT = io)
  END SUBROUTINE W_integer__1_R_2
  SUBROUTINE W_integer__2_R_2(io, x, cleanup, nline, meta)
    INTEGER :: io
    INTEGER(KIND = 2), INTENT(IN) :: x(:, :)
    INTEGER :: k, kmeta, k1, k2
    LOGICAL, OPTIONAL, INTENT(IN) :: cleanup, nline, meta
    LOGICAL :: cleanup_local, nline_local, meta_local
    cleanup_local = .TRUE.
    nline_local = .TRUE.
    meta_local = .TRUE.
    IF (PRESENT(cleanup)) cleanup_local = cleanup
    IF (PRESENT(nline)) nline_local = nline
    IF (PRESENT(meta)) meta_local = meta
    IF (meta_local) THEN
      CALL serialize(io, "# rank", cleanup = .FALSE.)
      CALL serialize(io, 2, cleanup = .FALSE.)
      CALL serialize(io, "# size", cleanup = .FALSE.)
      DO kmeta = 1, 2
        CALL serialize(io, SIZE(x, kmeta), cleanup = .FALSE.)
      END DO
      CALL serialize(io, "# lbound", cleanup = .FALSE.)
      DO kmeta = 1, 2
        CALL serialize(io, LBOUND(x, kmeta), cleanup = .FALSE.)
      END DO
    END IF
    CALL serialize(io, "# entries", cleanup = .FALSE.)
    DO k2 = LBOUND(x, 2), UBOUND(x, 2)
      DO k1 = LBOUND(x, 1), UBOUND(x, 1)
        CALL serialize(io, x(k1, k2), cleanup = .FALSE.)
      END DO
    END DO
    IF (cleanup_local) CLOSE(UNIT = io)
  END SUBROUTINE W_integer__2_R_2
  SUBROUTINE W_integer__4_R_2(io, x, cleanup, nline, meta)
    INTEGER :: io
    INTEGER(KIND = 4), INTENT(IN) :: x(:, :)
    INTEGER :: k, kmeta, k1, k2
    LOGICAL, OPTIONAL, INTENT(IN) :: cleanup, nline, meta
    LOGICAL :: cleanup_local, nline_local, meta_local
    cleanup_local = .TRUE.
    nline_local = .TRUE.
    meta_local = .TRUE.
    IF (PRESENT(cleanup)) cleanup_local = cleanup
    IF (PRESENT(nline)) nline_local = nline
    IF (PRESENT(meta)) meta_local = meta
    IF (meta_local) THEN
      CALL serialize(io, "# rank", cleanup = .FALSE.)
      CALL serialize(io, 2, cleanup = .FALSE.)
      CALL serialize(io, "# size", cleanup = .FALSE.)
      DO kmeta = 1, 2
        CALL serialize(io, SIZE(x, kmeta), cleanup = .FALSE.)
      END DO
      CALL serialize(io, "# lbound", cleanup = .FALSE.)
      DO kmeta = 1, 2
        CALL serialize(io, LBOUND(x, kmeta), cleanup = .FALSE.)
      END DO
    END IF
    CALL serialize(io, "# entries", cleanup = .FALSE.)
    DO k2 = LBOUND(x, 2), UBOUND(x, 2)
      DO k1 = LBOUND(x, 1), UBOUND(x, 1)
        CALL serialize(io, x(k1, k2), cleanup = .FALSE.)
      END DO
    END DO
    IF (cleanup_local) CLOSE(UNIT = io)
  END SUBROUTINE W_integer__4_R_2
  SUBROUTINE W_integer__8_R_2(io, x, cleanup, nline, meta)
    INTEGER :: io
    INTEGER(KIND = 8), INTENT(IN) :: x(:, :)
    INTEGER :: k, kmeta, k1, k2
    LOGICAL, OPTIONAL, INTENT(IN) :: cleanup, nline, meta
    LOGICAL :: cleanup_local, nline_local, meta_local
    cleanup_local = .TRUE.
    nline_local = .TRUE.
    meta_local = .TRUE.
    IF (PRESENT(cleanup)) cleanup_local = cleanup
    IF (PRESENT(nline)) nline_local = nline
    IF (PRESENT(meta)) meta_local = meta
    IF (meta_local) THEN
      CALL serialize(io, "# rank", cleanup = .FALSE.)
      CALL serialize(io, 2, cleanup = .FALSE.)
      CALL serialize(io, "# size", cleanup = .FALSE.)
      DO kmeta = 1, 2
        CALL serialize(io, SIZE(x, kmeta), cleanup = .FALSE.)
      END DO
      CALL serialize(io, "# lbound", cleanup = .FALSE.)
      DO kmeta = 1, 2
        CALL serialize(io, LBOUND(x, kmeta), cleanup = .FALSE.)
      END DO
    END IF
    CALL serialize(io, "# entries", cleanup = .FALSE.)
    DO k2 = LBOUND(x, 2), UBOUND(x, 2)
      DO k1 = LBOUND(x, 1), UBOUND(x, 1)
        CALL serialize(io, x(k1, k2), cleanup = .FALSE.)
      END DO
    END DO
    IF (cleanup_local) CLOSE(UNIT = io)
  END SUBROUTINE W_integer__8_R_2
  SUBROUTINE W_real__4_R_2(io, x, cleanup, nline, meta)
    INTEGER :: io
    REAL(KIND = 4), INTENT(IN) :: x(:, :)
    INTEGER :: k, kmeta, k1, k2
    LOGICAL, OPTIONAL, INTENT(IN) :: cleanup, nline, meta
    LOGICAL :: cleanup_local, nline_local, meta_local
    cleanup_local = .TRUE.
    nline_local = .TRUE.
    meta_local = .TRUE.
    IF (PRESENT(cleanup)) cleanup_local = cleanup
    IF (PRESENT(nline)) nline_local = nline
    IF (PRESENT(meta)) meta_local = meta
    IF (meta_local) THEN
      CALL serialize(io, "# rank", cleanup = .FALSE.)
      CALL serialize(io, 2, cleanup = .FALSE.)
      CALL serialize(io, "# size", cleanup = .FALSE.)
      DO kmeta = 1, 2
        CALL serialize(io, SIZE(x, kmeta), cleanup = .FALSE.)
      END DO
      CALL serialize(io, "# lbound", cleanup = .FALSE.)
      DO kmeta = 1, 2
        CALL serialize(io, LBOUND(x, kmeta), cleanup = .FALSE.)
      END DO
    END IF
    CALL serialize(io, "# entries", cleanup = .FALSE.)
    DO k2 = LBOUND(x, 2), UBOUND(x, 2)
      DO k1 = LBOUND(x, 1), UBOUND(x, 1)
        CALL serialize(io, x(k1, k2), cleanup = .FALSE.)
      END DO
    END DO
    IF (cleanup_local) CLOSE(UNIT = io)
  END SUBROUTINE W_real__4_R_2
  SUBROUTINE W_real__8_R_2(io, x, cleanup, nline, meta)
    INTEGER :: io
    REAL(KIND = 8), INTENT(IN) :: x(:, :)
    INTEGER :: k, kmeta, k1, k2
    LOGICAL, OPTIONAL, INTENT(IN) :: cleanup, nline, meta
    LOGICAL :: cleanup_local, nline_local, meta_local
    cleanup_local = .TRUE.
    nline_local = .TRUE.
    meta_local = .TRUE.
    IF (PRESENT(cleanup)) cleanup_local = cleanup
    IF (PRESENT(nline)) nline_local = nline
    IF (PRESENT(meta)) meta_local = meta
    IF (meta_local) THEN
      CALL serialize(io, "# rank", cleanup = .FALSE.)
      CALL serialize(io, 2, cleanup = .FALSE.)
      CALL serialize(io, "# size", cleanup = .FALSE.)
      DO kmeta = 1, 2
        CALL serialize(io, SIZE(x, kmeta), cleanup = .FALSE.)
      END DO
      CALL serialize(io, "# lbound", cleanup = .FALSE.)
      DO kmeta = 1, 2
        CALL serialize(io, LBOUND(x, kmeta), cleanup = .FALSE.)
      END DO
    END IF
    CALL serialize(io, "# entries", cleanup = .FALSE.)
    DO k2 = LBOUND(x, 2), UBOUND(x, 2)
      DO k1 = LBOUND(x, 1), UBOUND(x, 1)
        CALL serialize(io, x(k1, k2), cleanup = .FALSE.)
      END DO
    END DO
    IF (cleanup_local) CLOSE(UNIT = io)
  END SUBROUTINE W_real__8_R_2
  SUBROUTINE W_logical_R_3(io, x, cleanup, nline, meta)
    INTEGER :: io
    LOGICAL, INTENT(IN) :: x(:, :, :)
    INTEGER :: k, kmeta, k1, k2, k3
    LOGICAL, OPTIONAL, INTENT(IN) :: cleanup, nline, meta
    LOGICAL :: cleanup_local, nline_local, meta_local
    cleanup_local = .TRUE.
    nline_local = .TRUE.
    meta_local = .TRUE.
    IF (PRESENT(cleanup)) cleanup_local = cleanup
    IF (PRESENT(nline)) nline_local = nline
    IF (PRESENT(meta)) meta_local = meta
    IF (meta_local) THEN
      CALL serialize(io, "# rank", cleanup = .FALSE.)
      CALL serialize(io, 3, cleanup = .FALSE.)
      CALL serialize(io, "# size", cleanup = .FALSE.)
      DO kmeta = 1, 3
        CALL serialize(io, SIZE(x, kmeta), cleanup = .FALSE.)
      END DO
      CALL serialize(io, "# lbound", cleanup = .FALSE.)
      DO kmeta = 1, 3
        CALL serialize(io, LBOUND(x, kmeta), cleanup = .FALSE.)
      END DO
    END IF
    CALL serialize(io, "# entries", cleanup = .FALSE.)
    DO k3 = LBOUND(x, 3), UBOUND(x, 3)
      DO k2 = LBOUND(x, 2), UBOUND(x, 2)
        DO k1 = LBOUND(x, 1), UBOUND(x, 1)
          CALL serialize(io, x(k1, k2, k3), cleanup = .FALSE.)
        END DO
      END DO
    END DO
    IF (cleanup_local) CLOSE(UNIT = io)
  END SUBROUTINE W_logical_R_3
  SUBROUTINE W_integer__1_R_3(io, x, cleanup, nline, meta)
    INTEGER :: io
    INTEGER(KIND = 1), INTENT(IN) :: x(:, :, :)
    INTEGER :: k, kmeta, k1, k2, k3
    LOGICAL, OPTIONAL, INTENT(IN) :: cleanup, nline, meta
    LOGICAL :: cleanup_local, nline_local, meta_local
    cleanup_local = .TRUE.
    nline_local = .TRUE.
    meta_local = .TRUE.
    IF (PRESENT(cleanup)) cleanup_local = cleanup
    IF (PRESENT(nline)) nline_local = nline
    IF (PRESENT(meta)) meta_local = meta
    IF (meta_local) THEN
      CALL serialize(io, "# rank", cleanup = .FALSE.)
      CALL serialize(io, 3, cleanup = .FALSE.)
      CALL serialize(io, "# size", cleanup = .FALSE.)
      DO kmeta = 1, 3
        CALL serialize(io, SIZE(x, kmeta), cleanup = .FALSE.)
      END DO
      CALL serialize(io, "# lbound", cleanup = .FALSE.)
      DO kmeta = 1, 3
        CALL serialize(io, LBOUND(x, kmeta), cleanup = .FALSE.)
      END DO
    END IF
    CALL serialize(io, "# entries", cleanup = .FALSE.)
    DO k3 = LBOUND(x, 3), UBOUND(x, 3)
      DO k2 = LBOUND(x, 2), UBOUND(x, 2)
        DO k1 = LBOUND(x, 1), UBOUND(x, 1)
          CALL serialize(io, x(k1, k2, k3), cleanup = .FALSE.)
        END DO
      END DO
    END DO
    IF (cleanup_local) CLOSE(UNIT = io)
  END SUBROUTINE W_integer__1_R_3
  SUBROUTINE W_integer__2_R_3(io, x, cleanup, nline, meta)
    INTEGER :: io
    INTEGER(KIND = 2), INTENT(IN) :: x(:, :, :)
    INTEGER :: k, kmeta, k1, k2, k3
    LOGICAL, OPTIONAL, INTENT(IN) :: cleanup, nline, meta
    LOGICAL :: cleanup_local, nline_local, meta_local
    cleanup_local = .TRUE.
    nline_local = .TRUE.
    meta_local = .TRUE.
    IF (PRESENT(cleanup)) cleanup_local = cleanup
    IF (PRESENT(nline)) nline_local = nline
    IF (PRESENT(meta)) meta_local = meta
    IF (meta_local) THEN
      CALL serialize(io, "# rank", cleanup = .FALSE.)
      CALL serialize(io, 3, cleanup = .FALSE.)
      CALL serialize(io, "# size", cleanup = .FALSE.)
      DO kmeta = 1, 3
        CALL serialize(io, SIZE(x, kmeta), cleanup = .FALSE.)
      END DO
      CALL serialize(io, "# lbound", cleanup = .FALSE.)
      DO kmeta = 1, 3
        CALL serialize(io, LBOUND(x, kmeta), cleanup = .FALSE.)
      END DO
    END IF
    CALL serialize(io, "# entries", cleanup = .FALSE.)
    DO k3 = LBOUND(x, 3), UBOUND(x, 3)
      DO k2 = LBOUND(x, 2), UBOUND(x, 2)
        DO k1 = LBOUND(x, 1), UBOUND(x, 1)
          CALL serialize(io, x(k1, k2, k3), cleanup = .FALSE.)
        END DO
      END DO
    END DO
    IF (cleanup_local) CLOSE(UNIT = io)
  END SUBROUTINE W_integer__2_R_3
  SUBROUTINE W_integer__4_R_3(io, x, cleanup, nline, meta)
    INTEGER :: io
    INTEGER(KIND = 4), INTENT(IN) :: x(:, :, :)
    INTEGER :: k, kmeta, k1, k2, k3
    LOGICAL, OPTIONAL, INTENT(IN) :: cleanup, nline, meta
    LOGICAL :: cleanup_local, nline_local, meta_local
    cleanup_local = .TRUE.
    nline_local = .TRUE.
    meta_local = .TRUE.
    IF (PRESENT(cleanup)) cleanup_local = cleanup
    IF (PRESENT(nline)) nline_local = nline
    IF (PRESENT(meta)) meta_local = meta
    IF (meta_local) THEN
      CALL serialize(io, "# rank", cleanup = .FALSE.)
      CALL serialize(io, 3, cleanup = .FALSE.)
      CALL serialize(io, "# size", cleanup = .FALSE.)
      DO kmeta = 1, 3
        CALL serialize(io, SIZE(x, kmeta), cleanup = .FALSE.)
      END DO
      CALL serialize(io, "# lbound", cleanup = .FALSE.)
      DO kmeta = 1, 3
        CALL serialize(io, LBOUND(x, kmeta), cleanup = .FALSE.)
      END DO
    END IF
    CALL serialize(io, "# entries", cleanup = .FALSE.)
    DO k3 = LBOUND(x, 3), UBOUND(x, 3)
      DO k2 = LBOUND(x, 2), UBOUND(x, 2)
        DO k1 = LBOUND(x, 1), UBOUND(x, 1)
          CALL serialize(io, x(k1, k2, k3), cleanup = .FALSE.)
        END DO
      END DO
    END DO
    IF (cleanup_local) CLOSE(UNIT = io)
  END SUBROUTINE W_integer__4_R_3
  SUBROUTINE W_integer__8_R_3(io, x, cleanup, nline, meta)
    INTEGER :: io
    INTEGER(KIND = 8), INTENT(IN) :: x(:, :, :)
    INTEGER :: k, kmeta, k1, k2, k3
    LOGICAL, OPTIONAL, INTENT(IN) :: cleanup, nline, meta
    LOGICAL :: cleanup_local, nline_local, meta_local
    cleanup_local = .TRUE.
    nline_local = .TRUE.
    meta_local = .TRUE.
    IF (PRESENT(cleanup)) cleanup_local = cleanup
    IF (PRESENT(nline)) nline_local = nline
    IF (PRESENT(meta)) meta_local = meta
    IF (meta_local) THEN
      CALL serialize(io, "# rank", cleanup = .FALSE.)
      CALL serialize(io, 3, cleanup = .FALSE.)
      CALL serialize(io, "# size", cleanup = .FALSE.)
      DO kmeta = 1, 3
        CALL serialize(io, SIZE(x, kmeta), cleanup = .FALSE.)
      END DO
      CALL serialize(io, "# lbound", cleanup = .FALSE.)
      DO kmeta = 1, 3
        CALL serialize(io, LBOUND(x, kmeta), cleanup = .FALSE.)
      END DO
    END IF
    CALL serialize(io, "# entries", cleanup = .FALSE.)
    DO k3 = LBOUND(x, 3), UBOUND(x, 3)
      DO k2 = LBOUND(x, 2), UBOUND(x, 2)
        DO k1 = LBOUND(x, 1), UBOUND(x, 1)
          CALL serialize(io, x(k1, k2, k3), cleanup = .FALSE.)
        END DO
      END DO
    END DO
    IF (cleanup_local) CLOSE(UNIT = io)
  END SUBROUTINE W_integer__8_R_3
  SUBROUTINE W_real__4_R_3(io, x, cleanup, nline, meta)
    INTEGER :: io
    REAL(KIND = 4), INTENT(IN) :: x(:, :, :)
    INTEGER :: k, kmeta, k1, k2, k3
    LOGICAL, OPTIONAL, INTENT(IN) :: cleanup, nline, meta
    LOGICAL :: cleanup_local, nline_local, meta_local
    cleanup_local = .TRUE.
    nline_local = .TRUE.
    meta_local = .TRUE.
    IF (PRESENT(cleanup)) cleanup_local = cleanup
    IF (PRESENT(nline)) nline_local = nline
    IF (PRESENT(meta)) meta_local = meta
    IF (meta_local) THEN
      CALL serialize(io, "# rank", cleanup = .FALSE.)
      CALL serialize(io, 3, cleanup = .FALSE.)
      CALL serialize(io, "# size", cleanup = .FALSE.)
      DO kmeta = 1, 3
        CALL serialize(io, SIZE(x, kmeta), cleanup = .FALSE.)
      END DO
      CALL serialize(io, "# lbound", cleanup = .FALSE.)
      DO kmeta = 1, 3
        CALL serialize(io, LBOUND(x, kmeta), cleanup = .FALSE.)
      END DO
    END IF
    CALL serialize(io, "# entries", cleanup = .FALSE.)
    DO k3 = LBOUND(x, 3), UBOUND(x, 3)
      DO k2 = LBOUND(x, 2), UBOUND(x, 2)
        DO k1 = LBOUND(x, 1), UBOUND(x, 1)
          CALL serialize(io, x(k1, k2, k3), cleanup = .FALSE.)
        END DO
      END DO
    END DO
    IF (cleanup_local) CLOSE(UNIT = io)
  END SUBROUTINE W_real__4_R_3
  SUBROUTINE W_real__8_R_3(io, x, cleanup, nline, meta)
    INTEGER :: io
    REAL(KIND = 8), INTENT(IN) :: x(:, :, :)
    INTEGER :: k, kmeta, k1, k2, k3
    LOGICAL, OPTIONAL, INTENT(IN) :: cleanup, nline, meta
    LOGICAL :: cleanup_local, nline_local, meta_local
    cleanup_local = .TRUE.
    nline_local = .TRUE.
    meta_local = .TRUE.
    IF (PRESENT(cleanup)) cleanup_local = cleanup
    IF (PRESENT(nline)) nline_local = nline
    IF (PRESENT(meta)) meta_local = meta
    IF (meta_local) THEN
      CALL serialize(io, "# rank", cleanup = .FALSE.)
      CALL serialize(io, 3, cleanup = .FALSE.)
      CALL serialize(io, "# size", cleanup = .FALSE.)
      DO kmeta = 1, 3
        CALL serialize(io, SIZE(x, kmeta), cleanup = .FALSE.)
      END DO
      CALL serialize(io, "# lbound", cleanup = .FALSE.)
      DO kmeta = 1, 3
        CALL serialize(io, LBOUND(x, kmeta), cleanup = .FALSE.)
      END DO
    END IF
    CALL serialize(io, "# entries", cleanup = .FALSE.)
    DO k3 = LBOUND(x, 3), UBOUND(x, 3)
      DO k2 = LBOUND(x, 2), UBOUND(x, 2)
        DO k1 = LBOUND(x, 1), UBOUND(x, 1)
          CALL serialize(io, x(k1, k2, k3), cleanup = .FALSE.)
        END DO
      END DO
    END DO
    IF (cleanup_local) CLOSE(UNIT = io)
  END SUBROUTINE W_real__8_R_3
  SUBROUTINE W_logical_R_4(io, x, cleanup, nline, meta)
    INTEGER :: io
    LOGICAL, INTENT(IN) :: x(:, :, :, :)
    INTEGER :: k, kmeta, k1, k2, k3, k4
    LOGICAL, OPTIONAL, INTENT(IN) :: cleanup, nline, meta
    LOGICAL :: cleanup_local, nline_local, meta_local
    cleanup_local = .TRUE.
    nline_local = .TRUE.
    meta_local = .TRUE.
    IF (PRESENT(cleanup)) cleanup_local = cleanup
    IF (PRESENT(nline)) nline_local = nline
    IF (PRESENT(meta)) meta_local = meta
    IF (meta_local) THEN
      CALL serialize(io, "# rank", cleanup = .FALSE.)
      CALL serialize(io, 4, cleanup = .FALSE.)
      CALL serialize(io, "# size", cleanup = .FALSE.)
      DO kmeta = 1, 4
        CALL serialize(io, SIZE(x, kmeta), cleanup = .FALSE.)
      END DO
      CALL serialize(io, "# lbound", cleanup = .FALSE.)
      DO kmeta = 1, 4
        CALL serialize(io, LBOUND(x, kmeta), cleanup = .FALSE.)
      END DO
    END IF
    CALL serialize(io, "# entries", cleanup = .FALSE.)
    DO k4 = LBOUND(x, 4), UBOUND(x, 4)
      DO k3 = LBOUND(x, 3), UBOUND(x, 3)
        DO k2 = LBOUND(x, 2), UBOUND(x, 2)
          DO k1 = LBOUND(x, 1), UBOUND(x, 1)
            CALL serialize(io, x(k1, k2, k3, k4), cleanup = .FALSE.)
          END DO
        END DO
      END DO
    END DO
    IF (cleanup_local) CLOSE(UNIT = io)
  END SUBROUTINE W_logical_R_4
  SUBROUTINE W_integer__1_R_4(io, x, cleanup, nline, meta)
    INTEGER :: io
    INTEGER(KIND = 1), INTENT(IN) :: x(:, :, :, :)
    INTEGER :: k, kmeta, k1, k2, k3, k4
    LOGICAL, OPTIONAL, INTENT(IN) :: cleanup, nline, meta
    LOGICAL :: cleanup_local, nline_local, meta_local
    cleanup_local = .TRUE.
    nline_local = .TRUE.
    meta_local = .TRUE.
    IF (PRESENT(cleanup)) cleanup_local = cleanup
    IF (PRESENT(nline)) nline_local = nline
    IF (PRESENT(meta)) meta_local = meta
    IF (meta_local) THEN
      CALL serialize(io, "# rank", cleanup = .FALSE.)
      CALL serialize(io, 4, cleanup = .FALSE.)
      CALL serialize(io, "# size", cleanup = .FALSE.)
      DO kmeta = 1, 4
        CALL serialize(io, SIZE(x, kmeta), cleanup = .FALSE.)
      END DO
      CALL serialize(io, "# lbound", cleanup = .FALSE.)
      DO kmeta = 1, 4
        CALL serialize(io, LBOUND(x, kmeta), cleanup = .FALSE.)
      END DO
    END IF
    CALL serialize(io, "# entries", cleanup = .FALSE.)
    DO k4 = LBOUND(x, 4), UBOUND(x, 4)
      DO k3 = LBOUND(x, 3), UBOUND(x, 3)
        DO k2 = LBOUND(x, 2), UBOUND(x, 2)
          DO k1 = LBOUND(x, 1), UBOUND(x, 1)
            CALL serialize(io, x(k1, k2, k3, k4), cleanup = .FALSE.)
          END DO
        END DO
      END DO
    END DO
    IF (cleanup_local) CLOSE(UNIT = io)
  END SUBROUTINE W_integer__1_R_4
  SUBROUTINE W_integer__2_R_4(io, x, cleanup, nline, meta)
    INTEGER :: io
    INTEGER(KIND = 2), INTENT(IN) :: x(:, :, :, :)
    INTEGER :: k, kmeta, k1, k2, k3, k4
    LOGICAL, OPTIONAL, INTENT(IN) :: cleanup, nline, meta
    LOGICAL :: cleanup_local, nline_local, meta_local
    cleanup_local = .TRUE.
    nline_local = .TRUE.
    meta_local = .TRUE.
    IF (PRESENT(cleanup)) cleanup_local = cleanup
    IF (PRESENT(nline)) nline_local = nline
    IF (PRESENT(meta)) meta_local = meta
    IF (meta_local) THEN
      CALL serialize(io, "# rank", cleanup = .FALSE.)
      CALL serialize(io, 4, cleanup = .FALSE.)
      CALL serialize(io, "# size", cleanup = .FALSE.)
      DO kmeta = 1, 4
        CALL serialize(io, SIZE(x, kmeta), cleanup = .FALSE.)
      END DO
      CALL serialize(io, "# lbound", cleanup = .FALSE.)
      DO kmeta = 1, 4
        CALL serialize(io, LBOUND(x, kmeta), cleanup = .FALSE.)
      END DO
    END IF
    CALL serialize(io, "# entries", cleanup = .FALSE.)
    DO k4 = LBOUND(x, 4), UBOUND(x, 4)
      DO k3 = LBOUND(x, 3), UBOUND(x, 3)
        DO k2 = LBOUND(x, 2), UBOUND(x, 2)
          DO k1 = LBOUND(x, 1), UBOUND(x, 1)
            CALL serialize(io, x(k1, k2, k3, k4), cleanup = .FALSE.)
          END DO
        END DO
      END DO
    END DO
    IF (cleanup_local) CLOSE(UNIT = io)
  END SUBROUTINE W_integer__2_R_4
  SUBROUTINE W_integer__4_R_4(io, x, cleanup, nline, meta)
    INTEGER :: io
    INTEGER(KIND = 4), INTENT(IN) :: x(:, :, :, :)
    INTEGER :: k, kmeta, k1, k2, k3, k4
    LOGICAL, OPTIONAL, INTENT(IN) :: cleanup, nline, meta
    LOGICAL :: cleanup_local, nline_local, meta_local
    cleanup_local = .TRUE.
    nline_local = .TRUE.
    meta_local = .TRUE.
    IF (PRESENT(cleanup)) cleanup_local = cleanup
    IF (PRESENT(nline)) nline_local = nline
    IF (PRESENT(meta)) meta_local = meta
    IF (meta_local) THEN
      CALL serialize(io, "# rank", cleanup = .FALSE.)
      CALL serialize(io, 4, cleanup = .FALSE.)
      CALL serialize(io, "# size", cleanup = .FALSE.)
      DO kmeta = 1, 4
        CALL serialize(io, SIZE(x, kmeta), cleanup = .FALSE.)
      END DO
      CALL serialize(io, "# lbound", cleanup = .FALSE.)
      DO kmeta = 1, 4
        CALL serialize(io, LBOUND(x, kmeta), cleanup = .FALSE.)
      END DO
    END IF
    CALL serialize(io, "# entries", cleanup = .FALSE.)
    DO k4 = LBOUND(x, 4), UBOUND(x, 4)
      DO k3 = LBOUND(x, 3), UBOUND(x, 3)
        DO k2 = LBOUND(x, 2), UBOUND(x, 2)
          DO k1 = LBOUND(x, 1), UBOUND(x, 1)
            CALL serialize(io, x(k1, k2, k3, k4), cleanup = .FALSE.)
          END DO
        END DO
      END DO
    END DO
    IF (cleanup_local) CLOSE(UNIT = io)
  END SUBROUTINE W_integer__4_R_4
  SUBROUTINE W_integer__8_R_4(io, x, cleanup, nline, meta)
    INTEGER :: io
    INTEGER(KIND = 8), INTENT(IN) :: x(:, :, :, :)
    INTEGER :: k, kmeta, k1, k2, k3, k4
    LOGICAL, OPTIONAL, INTENT(IN) :: cleanup, nline, meta
    LOGICAL :: cleanup_local, nline_local, meta_local
    cleanup_local = .TRUE.
    nline_local = .TRUE.
    meta_local = .TRUE.
    IF (PRESENT(cleanup)) cleanup_local = cleanup
    IF (PRESENT(nline)) nline_local = nline
    IF (PRESENT(meta)) meta_local = meta
    IF (meta_local) THEN
      CALL serialize(io, "# rank", cleanup = .FALSE.)
      CALL serialize(io, 4, cleanup = .FALSE.)
      CALL serialize(io, "# size", cleanup = .FALSE.)
      DO kmeta = 1, 4
        CALL serialize(io, SIZE(x, kmeta), cleanup = .FALSE.)
      END DO
      CALL serialize(io, "# lbound", cleanup = .FALSE.)
      DO kmeta = 1, 4
        CALL serialize(io, LBOUND(x, kmeta), cleanup = .FALSE.)
      END DO
    END IF
    CALL serialize(io, "# entries", cleanup = .FALSE.)
    DO k4 = LBOUND(x, 4), UBOUND(x, 4)
      DO k3 = LBOUND(x, 3), UBOUND(x, 3)
        DO k2 = LBOUND(x, 2), UBOUND(x, 2)
          DO k1 = LBOUND(x, 1), UBOUND(x, 1)
            CALL serialize(io, x(k1, k2, k3, k4), cleanup = .FALSE.)
          END DO
        END DO
      END DO
    END DO
    IF (cleanup_local) CLOSE(UNIT = io)
  END SUBROUTINE W_integer__8_R_4
  SUBROUTINE W_real__4_R_4(io, x, cleanup, nline, meta)
    INTEGER :: io
    REAL(KIND = 4), INTENT(IN) :: x(:, :, :, :)
    INTEGER :: k, kmeta, k1, k2, k3, k4
    LOGICAL, OPTIONAL, INTENT(IN) :: cleanup, nline, meta
    LOGICAL :: cleanup_local, nline_local, meta_local
    cleanup_local = .TRUE.
    nline_local = .TRUE.
    meta_local = .TRUE.
    IF (PRESENT(cleanup)) cleanup_local = cleanup
    IF (PRESENT(nline)) nline_local = nline
    IF (PRESENT(meta)) meta_local = meta
    IF (meta_local) THEN
      CALL serialize(io, "# rank", cleanup = .FALSE.)
      CALL serialize(io, 4, cleanup = .FALSE.)
      CALL serialize(io, "# size", cleanup = .FALSE.)
      DO kmeta = 1, 4
        CALL serialize(io, SIZE(x, kmeta), cleanup = .FALSE.)
      END DO
      CALL serialize(io, "# lbound", cleanup = .FALSE.)
      DO kmeta = 1, 4
        CALL serialize(io, LBOUND(x, kmeta), cleanup = .FALSE.)
      END DO
    END IF
    CALL serialize(io, "# entries", cleanup = .FALSE.)
    DO k4 = LBOUND(x, 4), UBOUND(x, 4)
      DO k3 = LBOUND(x, 3), UBOUND(x, 3)
        DO k2 = LBOUND(x, 2), UBOUND(x, 2)
          DO k1 = LBOUND(x, 1), UBOUND(x, 1)
            CALL serialize(io, x(k1, k2, k3, k4), cleanup = .FALSE.)
          END DO
        END DO
      END DO
    END DO
    IF (cleanup_local) CLOSE(UNIT = io)
  END SUBROUTINE W_real__4_R_4
  SUBROUTINE W_real__8_R_4(io, x, cleanup, nline, meta)
    INTEGER :: io
    REAL(KIND = 8), INTENT(IN) :: x(:, :, :, :)
    INTEGER :: k, kmeta, k1, k2, k3, k4
    LOGICAL, OPTIONAL, INTENT(IN) :: cleanup, nline, meta
    LOGICAL :: cleanup_local, nline_local, meta_local
    cleanup_local = .TRUE.
    nline_local = .TRUE.
    meta_local = .TRUE.
    IF (PRESENT(cleanup)) cleanup_local = cleanup
    IF (PRESENT(nline)) nline_local = nline
    IF (PRESENT(meta)) meta_local = meta
    IF (meta_local) THEN
      CALL serialize(io, "# rank", cleanup = .FALSE.)
      CALL serialize(io, 4, cleanup = .FALSE.)
      CALL serialize(io, "# size", cleanup = .FALSE.)
      DO kmeta = 1, 4
        CALL serialize(io, SIZE(x, kmeta), cleanup = .FALSE.)
      END DO
      CALL serialize(io, "# lbound", cleanup = .FALSE.)
      DO kmeta = 1, 4
        CALL serialize(io, LBOUND(x, kmeta), cleanup = .FALSE.)
      END DO
    END IF
    CALL serialize(io, "# entries", cleanup = .FALSE.)
    DO k4 = LBOUND(x, 4), UBOUND(x, 4)
      DO k3 = LBOUND(x, 3), UBOUND(x, 3)
        DO k2 = LBOUND(x, 2), UBOUND(x, 2)
          DO k1 = LBOUND(x, 1), UBOUND(x, 1)
            CALL serialize(io, x(k1, k2, k3, k4), cleanup = .FALSE.)
          END DO
        END DO
      END DO
    END DO
    IF (cleanup_local) CLOSE(UNIT = io)
  END SUBROUTINE W_real__8_R_4
  SUBROUTINE W_dt_t_nh_prog_R_1(io, x, cleanup, nline, meta)
    USE mo_nonhydro_types, ONLY: t_nh_prog
    INTEGER :: io
    TYPE(t_nh_prog), INTENT(IN) :: x(:)
    INTEGER :: k, kmeta, k1
    LOGICAL, OPTIONAL, INTENT(IN) :: cleanup, nline, meta
    LOGICAL :: cleanup_local, nline_local, meta_local
    cleanup_local = .TRUE.
    nline_local = .TRUE.
    meta_local = .TRUE.
    IF (PRESENT(cleanup)) cleanup_local = cleanup
    IF (PRESENT(nline)) nline_local = nline
    IF (PRESENT(meta)) meta_local = meta
    IF (meta_local) THEN
      CALL serialize(io, "# rank", cleanup = .FALSE.)
      CALL serialize(io, 1, cleanup = .FALSE.)
      CALL serialize(io, "# size", cleanup = .FALSE.)
      DO kmeta = 1, 1
        CALL serialize(io, SIZE(x, kmeta), cleanup = .FALSE.)
      END DO
      CALL serialize(io, "# lbound", cleanup = .FALSE.)
      DO kmeta = 1, 1
        CALL serialize(io, LBOUND(x, kmeta), cleanup = .FALSE.)
      END DO
    END IF
    CALL serialize(io, "# entries", cleanup = .FALSE.)
    DO k1 = LBOUND(x, 1), UBOUND(x, 1)
      CALL serialize(io, x(k1), cleanup = .FALSE.)
    END DO
    IF (cleanup_local) CLOSE(UNIT = io)
  END SUBROUTINE W_dt_t_nh_prog_R_1
  SUBROUTINE W_logical(io, x, cleanup, nline)
    CHARACTER(LEN = 50) :: buf
    INTEGER :: io
    LOGICAL, INTENT(IN) :: x
    INTEGER :: y
    LOGICAL, OPTIONAL, INTENT(IN) :: cleanup, nline
    LOGICAL :: cleanup_local, nline_local
    cleanup_local = .TRUE.
    nline_local = .TRUE.
    IF (PRESENT(cleanup)) cleanup_local = cleanup
    IF (PRESENT(nline)) nline_local = nline
    y = MERGE(1, 0, x)
    WRITE(io, '(g0)', ADVANCE = 'no') y
    IF (nline_local) WRITE(io, '(g0)', ADVANCE = 'no') NEW_LINE('A')
    IF (cleanup_local) CLOSE(UNIT = io)
  END SUBROUTINE W_logical
  SUBROUTINE W_integer1(io, x, cleanup, nline)
    CHARACTER(LEN = 50) :: buf
    INTEGER :: io
    INTEGER(KIND = 1), INTENT(IN) :: x
    INTEGER :: y
    LOGICAL, OPTIONAL, INTENT(IN) :: cleanup, nline
    LOGICAL :: cleanup_local, nline_local
    cleanup_local = .TRUE.
    nline_local = .TRUE.
    IF (PRESENT(cleanup)) cleanup_local = cleanup
    IF (PRESENT(nline)) nline_local = nline
    WRITE(io, '(g0)', ADVANCE = 'no') x
    IF (nline_local) WRITE(io, '(g0)', ADVANCE = 'no') NEW_LINE('A')
    IF (cleanup_local) CLOSE(UNIT = io)
  END SUBROUTINE W_integer1
  SUBROUTINE W_integer2(io, x, cleanup, nline)
    CHARACTER(LEN = 50) :: buf
    INTEGER :: io
    INTEGER(KIND = 2), INTENT(IN) :: x
    INTEGER :: y
    LOGICAL, OPTIONAL, INTENT(IN) :: cleanup, nline
    LOGICAL :: cleanup_local, nline_local
    cleanup_local = .TRUE.
    nline_local = .TRUE.
    IF (PRESENT(cleanup)) cleanup_local = cleanup
    IF (PRESENT(nline)) nline_local = nline
    WRITE(io, '(g0)', ADVANCE = 'no') x
    IF (nline_local) WRITE(io, '(g0)', ADVANCE = 'no') NEW_LINE('A')
    IF (cleanup_local) CLOSE(UNIT = io)
  END SUBROUTINE W_integer2
  SUBROUTINE W_integer4(io, x, cleanup, nline)
    CHARACTER(LEN = 50) :: buf
    INTEGER :: io
    INTEGER(KIND = 4), INTENT(IN) :: x
    INTEGER :: y
    LOGICAL, OPTIONAL, INTENT(IN) :: cleanup, nline
    LOGICAL :: cleanup_local, nline_local
    cleanup_local = .TRUE.
    nline_local = .TRUE.
    IF (PRESENT(cleanup)) cleanup_local = cleanup
    IF (PRESENT(nline)) nline_local = nline
    WRITE(io, '(g0)', ADVANCE = 'no') x
    IF (nline_local) WRITE(io, '(g0)', ADVANCE = 'no') NEW_LINE('A')
    IF (cleanup_local) CLOSE(UNIT = io)
  END SUBROUTINE W_integer4
  SUBROUTINE W_integer8(io, x, cleanup, nline)
    CHARACTER(LEN = 50) :: buf
    INTEGER :: io
    INTEGER(KIND = 8), INTENT(IN) :: x
    INTEGER :: y
    LOGICAL, OPTIONAL, INTENT(IN) :: cleanup, nline
    LOGICAL :: cleanup_local, nline_local
    cleanup_local = .TRUE.
    nline_local = .TRUE.
    IF (PRESENT(cleanup)) cleanup_local = cleanup
    IF (PRESENT(nline)) nline_local = nline
    WRITE(io, '(g0)', ADVANCE = 'no') x
    IF (nline_local) WRITE(io, '(g0)', ADVANCE = 'no') NEW_LINE('A')
    IF (cleanup_local) CLOSE(UNIT = io)
  END SUBROUTINE W_integer8
  SUBROUTINE W_real4(io, x, cleanup, nline)
    CHARACTER(LEN = 50) :: buf
    INTEGER :: io
    REAL(KIND = 4), INTENT(IN) :: x
    INTEGER :: y
    LOGICAL, OPTIONAL, INTENT(IN) :: cleanup, nline
    LOGICAL :: cleanup_local, nline_local
    cleanup_local = .TRUE.
    nline_local = .TRUE.
    IF (PRESENT(cleanup)) cleanup_local = cleanup
    IF (PRESENT(nline)) nline_local = nline
    WRITE(buf, '(e28.20)') x
    WRITE(io, '(A)', ADVANCE = 'no') TRIM(ADJUSTL(buf))
    IF (nline_local) WRITE(io, '(g0)', ADVANCE = 'no') NEW_LINE('A')
    IF (cleanup_local) CLOSE(UNIT = io)
  END SUBROUTINE W_real4
  SUBROUTINE W_real8(io, x, cleanup, nline)
    CHARACTER(LEN = 50) :: buf
    INTEGER :: io
    REAL(KIND = 8), INTENT(IN) :: x
    INTEGER :: y
    LOGICAL, OPTIONAL, INTENT(IN) :: cleanup, nline
    LOGICAL :: cleanup_local, nline_local
    cleanup_local = .TRUE.
    nline_local = .TRUE.
    IF (PRESENT(cleanup)) cleanup_local = cleanup
    IF (PRESENT(nline)) nline_local = nline
    WRITE(buf, '(e28.20)') x
    WRITE(io, '(A)', ADVANCE = 'no') TRIM(ADJUSTL(buf))
    IF (nline_local) WRITE(io, '(g0)', ADVANCE = 'no') NEW_LINE('A')
    IF (cleanup_local) CLOSE(UNIT = io)
  END SUBROUTINE W_real8
  SUBROUTINE serialize_global_data(io)
    USE mo_grid_config, ONLY: l_limited_area => l_limited_area
    USE mo_gridref_config, ONLY: grf_intmethod_e => grf_intmethod_e
    USE mo_init_vgrid, ONLY: nflatlev => nflatlev
    USE mo_initicon_config, ONLY: is_iau_active => is_iau_active
    USE mo_initicon_config, ONLY: iau_wgt_dyn => iau_wgt_dyn
    USE mo_nonhydrostatic_config, ONLY: itime_scheme => itime_scheme
    USE mo_nonhydrostatic_config, ONLY: ndyn_substeps_var => ndyn_substeps_var
    USE mo_nonhydrostatic_config, ONLY: rayleigh_type => rayleigh_type
    USE mo_nonhydrostatic_config, ONLY: kstart_dd3d => kstart_dd3d
    USE mo_nonhydrostatic_config, ONLY: kstart_moist => kstart_moist
    USE mo_parallel_config, ONLY: nproma => nproma
    USE mo_run_config, ONLY: timers_level => timers_level
    USE mo_timer, ONLY: timer_solve_nh_edgecomp => timer_solve_nh_edgecomp
    USE mo_timer, ONLY: timer_solve_nh_vimpl => timer_solve_nh_vimpl
    USE mo_vertical_grid, ONLY: nrdmax => nrdmax
    INTEGER :: io
    CALL serialize(io, "# l_limited_area", cleanup = .FALSE.)
    CALL serialize(io, l_limited_area, cleanup = .FALSE.)
    CALL serialize(io, "# grf_intmethod_e", cleanup = .FALSE.)
    CALL serialize(io, grf_intmethod_e, cleanup = .FALSE.)
    CALL serialize(io, "# nflatlev", cleanup = .FALSE.)
    CALL serialize(io, nflatlev, cleanup = .FALSE.)
    CALL serialize(io, "# is_iau_active", cleanup = .FALSE.)
    CALL serialize(io, is_iau_active, cleanup = .FALSE.)
    CALL serialize(io, "# iau_wgt_dyn", cleanup = .FALSE.)
    CALL serialize(io, iau_wgt_dyn, cleanup = .FALSE.)
    CALL serialize(io, "# itime_scheme", cleanup = .FALSE.)
    CALL serialize(io, itime_scheme, cleanup = .FALSE.)
    CALL serialize(io, "# ndyn_substeps_var", cleanup = .FALSE.)
    CALL serialize(io, ndyn_substeps_var, cleanup = .FALSE.)
    CALL serialize(io, "# rayleigh_type", cleanup = .FALSE.)
    CALL serialize(io, rayleigh_type, cleanup = .FALSE.)
    CALL serialize(io, "# kstart_dd3d", cleanup = .FALSE.)
    CALL serialize(io, kstart_dd3d, cleanup = .FALSE.)
    CALL serialize(io, "# kstart_moist", cleanup = .FALSE.)
    CALL serialize(io, kstart_moist, cleanup = .FALSE.)
    CALL serialize(io, "# nproma", cleanup = .FALSE.)
    CALL serialize(io, nproma, cleanup = .FALSE.)
    CALL serialize(io, "# timers_level", cleanup = .FALSE.)
    CALL serialize(io, timers_level, cleanup = .FALSE.)
    CALL serialize(io, "# timer_solve_nh_edgecomp", cleanup = .FALSE.)
    CALL serialize(io, timer_solve_nh_edgecomp, cleanup = .FALSE.)
    CALL serialize(io, "# timer_solve_nh_vimpl", cleanup = .FALSE.)
    CALL serialize(io, timer_solve_nh_vimpl, cleanup = .FALSE.)
    CALL serialize(io, "# nrdmax", cleanup = .FALSE.)
    CALL serialize(io, nrdmax, cleanup = .FALSE.)
    CLOSE(UNIT = io)
  END SUBROUTINE serialize_global_data
END MODULE corrector_post