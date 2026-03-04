SUBROUTINE kernel(a)
  IMPLICIT NONE
  REAL(KIND = 8), INTENT(INOUT) :: a(:, :, :)
  INTEGER :: i, j, k
  DO k = 1, SIZE(a, 3)
    DO j = 1, SIZE(a, 2)
      DO i = 1, SIZE(a, 1)
        a(i, j, k) = a(i, j, k) + 1.0D0
      END DO
    END DO
  END DO
END SUBROUTINE kernel