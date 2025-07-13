MODULE serde_base
  IMPLICIT NONE
  INTERFACE serialize
    MODULE PROCEDURE :: W_string
    MODULE PROCEDURE W_logical_R_1, W_integer__1_R_1, W_integer__2_R_1, W_integer__4_R_1, W_integer__8_R_1, W_real__4_R_1, W_real__8_R_1, W_logical_R_2, W_integer__1_R_2, W_integer__2_R_2, W_integer__4_R_2, W_integer__8_R_2, W_real__4_R_2, W_real__8_R_2, W_logical_R_3, W_integer__1_R_3, W_integer__2_R_3, W_integer__4_R_3, W_integer__8_R_3, W_real__4_R_3, W_real__8_R_3, W_logical_R_4, W_integer__1_R_4, W_integer__2_R_4, W_integer__4_R_4, W_integer__8_R_4, W_real__4_R_4, W_real__8_R_4, W_logical, W_integer1, W_integer2, W_integer4, W_integer8, W_real4, W_real8
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
    WRITE(io, *) x
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
    WRITE(io, *) x
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
    WRITE(io, *) x
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
    WRITE(io, *) x
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
    WRITE(io, '(E28.20)') x
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
    WRITE(io, '(E28.20)') x
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
    WRITE(io, *) x
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
    WRITE(io, *) x
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
    WRITE(io, *) x
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
    WRITE(io, *) x
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
    WRITE(io, '(E28.20)') x
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
    WRITE(io, '(E28.20)') x
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
    WRITE(io, *) x
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
    WRITE(io, *) x
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
    WRITE(io, *) x
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
    WRITE(io, *) x
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
    WRITE(io, '(E28.20)') x
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
    WRITE(io, '(E28.20)') x
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
    WRITE(io, *) x
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
    WRITE(io, *) x
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
    WRITE(io, *) x
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
    WRITE(io, *) x
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
    WRITE(io, '(E28.20)') x
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
    WRITE(io, '(E28.20)') x
    IF (cleanup_local) CLOSE(UNIT = io)
  END SUBROUTINE W_real__8_R_4
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
END MODULE serde_base
