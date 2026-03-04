subroutine kernel(A)
  implicit none
  real(kind=8), intent(inout) :: A(:, :, :)
  integer :: i, j, k

  do k = 1, size(A, 3)
    do j = 1, size(A, 2)
      do i = 1, size(A, 1)
        A(i, j, k) = A(i, j, k) + 1.0d0
      end do
    end do
  end do

end subroutine kernel