module util
   implicit none

   ! set up real variable precision as double precision
   integer, parameter  :: dp=selected_real_kind(15,300)

contains

   ! read the contents of filename. currently, the size must be known
   function read_file(filename) result(masses)
      implicit none

      ! parameters
      character(len = *), intent(in)              :: filename
      !integer, intent(in)                         :: n_lines
      integer                                     :: i, ierr
      real(kind=dp), dimension(100)                 :: masses

      ! open and read filename
      open(10, file=filename, status='old', iostat=ierr)
      if (ierr/=0) stop "Error opening input file"
      do i=1,100
         read(10,*) masses(i)
      end do

   end function read_file

   recursive function fuel_for_mass(mass) result(fuel)
      implicit none

      ! parameters
      integer, intent(in) :: mass
      integer             :: fuel

      ! calculate fuel required for module
      fuel = int(mass/3.0_dp) - 2

      ! recursively calculate fuel required for fuel
      if ( (int(fuel/3.0_dp) - 2) .gt. 0) then
         fuel = fuel + fuel_for_mass(fuel)
      end if

   end function fuel_for_mass

end module util

program counter_upper
   use util
   implicit none

   ! parameters
   integer, dimension(100)  :: masses
   integer                :: i, sum

   sum = 0
   ! read input
   masses = read_file('input')

   ! work out fuel
   do i=1,100
      sum = sum + fuel_for_mass(masses(i))
   end do

   print *, "Total fuel required: ",sum

end program counter_upper
