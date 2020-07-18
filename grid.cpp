#include "grid.h"

grid::grid()
{

}
grid::grid (polygon *p_, int n_)
{
  p = p_;
  n = n_;
  fill_us();
}
void
grid::fill_us ()
{
    Js j;
    fill_js (j, p, n);

    u.BbC = ultimate_scalar_counter (j.BbC, 1, 0, 0, 1, 0, 0);
    u.AaB = ultimate_scalar_counter (j.AaB, 1, 0, 0, 1, 0, 0);
    u.Bab = ultimate_scalar_counter (j.Bab, 1, 0, 0, 1, 0, 0);
    u.Cbc = ultimate_scalar_counter (j.Cbc, 1, 0, 0, 1, 0, 0);
    u.CcD = ultimate_scalar_counter (j.CcD, 1, 0, 0, 1, 0, 0);
    u.Dcd = ultimate_scalar_counter (j.Dcd, 1, 0, 0, 1, 0, 0);
    u.DdA = ultimate_scalar_counter (j.DdA, 1, 0, 0, 1, 0, 0);
    u.Ada = ultimate_scalar_counter (j.Ada, 1, 0, 0, 1, 0, 0);
}
double
grid::get_f_value_by_ijtr (std::function<double (double, double)> f, int i, int j, int trapeze)
{
FIX_UNUSED (f, i, j, trapeze);
    return 0;
}
