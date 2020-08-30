program function_test
end program function_test

subroutine function_level_OpenMP(n, y)
   integer :: n
   real :: y(n)

   real, allocatable :: x(:)
   real x1
   real :: x2 = 0.0
   real, save :: x3
   real, save, allocatable :: z

   if (thread_id .eq. 0) allocate(x(100))

!  lots of code

   if (thread_id .eq. 0) deallocate(x)
end subroutine function_level_OpenMP

