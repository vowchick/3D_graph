#include "grid.h"

grid::grid()
{

}
grid::grid (polygon *p_, int n_)
{
  p = p_;
  n = n_;
  fill_js (p, n);
  fill_us();
}
void
grid::fill_us ()
{
    u.BbC = ultimate_scalar_counter (J.BbC, 1, 0, 0, 1, 0, 0);
    u.AaB = ultimate_scalar_counter (J.AaB, 1, 0, 0, 1, 0, 0);
    u.Bab = ultimate_scalar_counter (J.Bab, 1, 0, 0, 1, 0, 0);
    u.Cbc = ultimate_scalar_counter (J.Cbc, 1, 0, 0, 1, 0, 0);
    u.CcD = ultimate_scalar_counter (J.CcD, 1, 0, 0, 1, 0, 0);
    u.Dcd = ultimate_scalar_counter (J.Dcd, 1, 0, 0, 1, 0, 0);
    u.DdA = ultimate_scalar_counter (J.DdA, 1, 0, 0, 1, 0, 0);
    u.Ada = ultimate_scalar_counter (J.Ada, 1, 0, 0, 1, 0, 0);
}
double
grid::get_f_value_by_ijtr (std::function<double (double, double)> f, int i, int j, int trapeze, int n)
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
      return;
      case 1:
        A = p->B;
        B = p->C;
        C = p->c;
        D = p->b;
      return;
      case 2:
        A = p->C;
        B = p->D;
        C = p->d;
        D = p->c;
      return;
      case 3:
        A = p->D;
        B = p->A;
        C = p->a;
        D = p->d;
      return;
    }
  abort ();
}
void
grid::fill_js (polygon *p, int n)
{
    J.AaB = triangle_to_right_triangle_jacob(
                p->A.x, p->A.y,
                p->a.x, p->a.y,
                p->B.x, p->B.y, n
                );
    J.Bab = triangle_to_right_triangle_jacob(
                p->B.x, p->B.y,
                p->a.x, p->a.y,
                p->b.x, p->b.y, n
                );
    J.BbC = triangle_to_right_triangle_jacob(
                p->b.x, p->b.y,
                p->c.x, p->c.y,
                p->B.x, p->B.y, n
                );
    J.Cbc = triangle_to_right_triangle_jacob(
                p->C.x, p->C.y,
                p->b.x, p->b.y,
                p->c.x, p->c.y, n
                );
    J.CcD = triangle_to_right_triangle_jacob(
                p->C.x, p->C.y,
                p->c.x, p->c.y,
                p->D.x, p->D.y, n
                );
    J.Dcd = triangle_to_right_triangle_jacob(
                p->D.x, p->D.y,
                p->c.x, p->c.y,
                p->d.x, p->d.y, n
                );
    J.DdA = triangle_to_right_triangle_jacob(
                p->D.x, p->D.y,
                p->d.x, p->d.y,
                p->A.x, p->A.y, n
                );
    J.Ada = triangle_to_right_triangle_jacob(
                p->A.x, p->A.y,
                p->a.x, p->a.y,
                p->d.x, p->d.y, n
                );
}
#if (0)
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
#endif
