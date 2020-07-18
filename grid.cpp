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

  point A, B, C, D;
  point desired;

  fill_points (A, B, C, D, trapeze);

  if (i + j <= n)
    {
      desired.x = A.x + i * (B.x - A.x) / n;
      desired.y = A.y + i * (B.y - A.y) / n;

      desired.x += (j * (D.x - A.x) / n);
      desired.y += (j * (D.y - A.y) / n);
    }
  else
    {
      desired.x = D.x + i * (B.x - D.x) / n;
      desired.y = D.y + i * (B.y - D.y) / n;

      desired.x += (j + i - n) * (C.x - D.x) / n;
      desired.y += (j + i - n) * (C.y - D.y) / n;
    }


  return f (desired.x, desired.y);
}
void
grid::fill_points (point &A, point &B, point &C, point &D, int trapeze)
{
  switch (trapeze)
    {
      case 0:
        A = p->A;
        B = p->B;
        C = p->b;
        D = p->a;
      break;
      case 1:
        A = p->B;
        B = p->C;
        C = p->c;
        D = p->b;
      break;
      case 2:
        A = p->C;
        B = p->D;
        C = p->d;
        D = p->c;
      break;
      case 3:
        A = p->D;
        B = p->A;
        C = p->a;
        D = p->d;
      break;
    }
  abort ();
}
