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
  fill_u2s ();
  find_width ();
  find_height ();
}

void
grid::find_width ()
{
  double first  = fabs (p->A.x - p->B.x),
         second = fabs (p->A.x - p->C.x),
         third  = fabs (p->A.x - p->D.x),
         fourth = fabs (p->B.x - p->C.x),
         fivth  = fabs (p->B.x - p->D.x),
         sixth  = fabs (p->C.x - p->D.x);

  double max = std::max (first, second);
  max = std::max (max, third);
  max = std::max (max, fourth);
  max = std::max (max, fivth);
  max = std::max (max, sixth);

  width = max;
}

void
grid::find_height ()
{
  double first  = fabs (p->A.y - p->B.y),
         second = fabs (p->A.y - p->C.y),
         third  = fabs (p->A.y - p->D.y),
         fourth = fabs (p->B.y - p->C.y),
         fivth  = fabs (p->B.y - p->D.y),
         sixth  = fabs (p->C.y - p->D.y);

  double max = std::max (first, second);
  max = std::max (max, third);
  max = std::max (max, fourth);
  max = std::max (max, fivth);
  max = std::max (max, sixth);

  height = max;
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
void
grid::fill_u2s ()
{
    u.BbC2 = ultimate_scalar_counter (J.BbC, 1, 0, 0, 0, 0, 1);
    u.AaB2 = ultimate_scalar_counter (J.AaB, 1, 0, 0, 0, 0, 1);
    u.Bab2 = ultimate_scalar_counter (J.Bab, 1, 0, 0, 0, 0, 1);
    u.Cbc2 = ultimate_scalar_counter (J.Cbc, 1, 0, 0, 0, 0, 1);
    u.CcD2 = ultimate_scalar_counter (J.CcD, 1, 0, 0, 0, 0, 1);
    u.Dcd2 = ultimate_scalar_counter (J.Dcd, 1, 0, 0, 0, 0, 1);
    u.DdA2 = ultimate_scalar_counter (J.DdA, 1, 0, 0, 0, 0, 1);
    u.Ada2 = ultimate_scalar_counter (J.Ada, 1, 0, 0, 0, 0, 1);
}
double
grid::get_value (std::vector <double> &f, double x, double y, int trapeze_num, int odd)
{
  //needs to be finished
  point A, B, C, D;
  point xy (x, y);
  fill_points (A, B, C, D, trapeze_num);
  int i = 0, j = 0;
  if (odd)
    {
      point c = C, d = D;
      point moveDC (C.x - D.x, C.y - D.y),
            moveDB (B.x - D.x, B.y - D.y),
            moveCB (B.x - C.x, B.y - C.y);
      point d_ = d;
      d_.x += moveCB.x / n;
      d_.y += moveCB.y / n;
      i = find_index (d, d, moveDC, moveDB, xy, d_);

      d = D;
      j = n - 1 - find_index (d, c, moveDB, moveCB, xy, c);
    }
  else
    {
      point a = A, b = B, d = D;
      point moveAB (B.x - A.x, B.y - A.y),
            moveDB (B.x - D.x, B.y - D.y);
      i = find_index (a, d, moveAB, moveDB, xy, d);

      b = B;
      d = D;
      point moveDA (A.x - D.x, A.y - D.y);
      point d_ (C);
      j = n - 1 - find_index (d, d, moveDA, moveDB, xy, d_);

    }
  if (i >= n - 1 || j > n - 1)
     abort ();

  triangle one, two;
  Trapeze trap (A, B, C, D);
  fill_triangles (one, two, i, j, trapeze_num, trap);
  triangle tri = which_triangle (xy, one, two);

  return interpolate (f, tri, xy);
}

void
grid::fill_triangles (triangle &one, triangle &two, int i, int j, int trapeze_num, Trapeze &tr)
{
  //needs to be thouroughly checked. but probably works
  one.a.second = two.a.second = get_k (i, j, trapeze_num, n);

  int n = this->n - 1;
  point moveW, moveSW, moveS;
  if (i + j <= n)
    {
      point moveAB (tr.B.x - tr.A.x, tr.B.y - tr.A.y),
            moveAD (tr.D.x - tr.A.x, tr.D.y - tr.A.y);

      one.a.first.x = tr.A.x + i * moveAB.x / n;
      one.a.first.y = tr.A.y + i * moveAB.y / n;

      one.a.first.x += j * moveAD.x / n;
      one.a.first.y += j * moveAD.y / n;

      moveW.x = moveAB.x;
      moveW.y = moveAB.y;

      moveSW.x = tr.B.x - tr.D.x;
      moveSW.y = tr.B.y - tr.D.y;

      moveS.x = -moveAD.x;
      moveS.y = -moveAD.y;
}
  else
    {
      point moveCB (tr.B.x - tr.C.x, tr.B.y - tr.C.y),
            moveDC (tr.C.x - tr.D.x, tr.C.y - tr.D.y);

      one.a.first.x = tr.D.x + i * moveDC.x / n;
      one.a.first.y = tr.D.y + i * moveDC.y / n;

      one.a.first.x += (n - 1 - j) * moveCB.x / n;
      one.a.first.y += (n - 1 - j) * moveCB.y / n;

      moveW.x = moveDC.x;
      moveW.y = moveDC.y;

      moveSW.x = tr.B.x - tr.D.x;
      moveSW.y = tr.B.y - tr.D.y;

      moveS.x = moveCB.x;
      moveS.y = moveCB.y;
    }
  two.a.first.x = one.a.first.x;
  two.a.first.y = one.a.first.y;

  if (j == 0)
    {
      one.filled = true;
      two.filled = false;

      one.singular = true;

      one.b.first.x = one.a.first.x + moveW.x / n;
      one.b.first.y = one.a.first.y + moveW.y / n;

      one.c.first.x = one.b.first.x;
      one.c.first.y = one.b.first.y;

      if (i < n - 2)
        one.b.second = one.c.second = get_k (i + 1, 0, trapeze_num, n);
      else
        {
          int next_trapeze = (trapeze_num + 1) % 4;
          one.b.second = one.c.second = get_k (0, 0, next_trapeze, n);
        }
      return;
    }
  else
    {
      one.filled = two.filled = true;

      one.b.first.x = one.a.first.x + moveW.x / n;
      one.b.first.y = one.a.first.y + moveW.y / n;

      one.c.first.x = one.a.first.x + moveSW.x / n;
      one.c.first.y = one.a.first.y + moveSW.y / n;

      two.b.first.x = one.a.first.x + moveSW.x / n;
      two.b.first.y = one.a.first.y + moveSW.y / n;

      two.c.first.x = one.a.first.x + moveS.x / n;
      two.c.first.y = one.a.first.y + moveS.y / n;

      if (i < n - 2)
        {
          one.b.second = get_k (i + 1, j, trapeze_num, n);
          one.c.second  = two.b.second = get_k (i + 1, j - 1, trapeze_num, n);
        }
      else
        {
          int next_trapeze = (trapeze_num + 1) % 4;
          one.b.second = get_k (0, j, next_trapeze, n);
          one.c.second = two.b.second = get_k (0, j - 1, next_trapeze, n);
        }
      two.c.second = get_k (i, j - 1, trapeze_num, n);
      return;
    }
  abort ();
}

triangle
grid::which_triangle (point xy, triangle one, triangle two)
{
  //probably works, isn't that hard
  if (!one.filled && two.filled)
    return two;
  if (!two.filled && one.filled)
    return one;

  if (!two.filled && ! one.filled)
    abort ();

  if (is_in_triangle (xy, one.a.first, one.b.first, one.c.first))
    return one;

  if (is_in_triangle (xy, two.a.first, two.b.first, two.c.first))
    return two;

  abort ();
  return one;
}

double
grid::interpolate (std::vector<double> &f, triangle tri, point xy)
{

  if (tri.singular)
    {
      double len_axy, len_ab;
      len_axy = sqrt ((xy.x - tri.a.first.x) * (xy.x - tri.a.first.x) +
                      (xy.y - tri.a.first.x) * (xy.y - tri.a.first.y));
      len_ab = sqrt ((tri.b.first.x - tri.a.first.x) * (tri.b.first.x - tri.a.first.x) +
                     (tri.b.first.y - tri.a.first.y) * (tri.b.first.y - tri.a.first.y));
      return f[tri.a.second] + len_axy / len_ab * (f[tri.b.second] - f[tri.a.second]);
    }

  double a1 = tri.a.first.x, a2 = tri.a.first.y,
         b1 = tri.b.first.x, b2 = tri.b.first.y,
         c1 = tri.c.first.x, c2 = tri.c.first.y;

  double fa = f[tri.a.second], fb = f[tri.b.second], fc = f[tri.c.second];

  double div = a1 * b2 + a2 * c1 + b1 * c2 - b2 * c1 - a1 * c2 - a2 * b1;

  double a = 0., b = 0., c = 0.;

  a = fa * b2 + a2 * fc + fb * c2 - fc * b2 - fa * c2 - fb * a2;
  a /= div;

  b = a1 * fb + fa * c1 + fc * b1 - fb * c1 - fa * b1 - fc * a1;
  b /= div;

  c = a1 * b2 * fc + a2 * c1 * fb + b1 * c2 * fa - c1 * b2 * fa - a1 * c2 * fb - a2 * b1 * fc;
  c /= div;


  return a * xy.x + b * xy.y + c;
}

int
grid::find_index (point a, point b, point moveac, point movebc, point xy, point second_point_for_line)
{
  double start = which_side (xy, a, second_point_for_line);
  point e, f;
  int i = 0, n = this->n - 1;
   if (fabs (start) > 1e-16)
     {
       e.x = a.x + moveac.x / n;
       e.y = a.y + moveac.y / n;
       f.x = b.x + movebc.x / n;
       f.y = b.y + movebc.y / n;
       i = 1;
       double cont = which_side (xy, e, f);
       while (cont * start > 1e-16)
         {
           i++;
           e.x = a.x + i * moveac.x / n;
           e.y = a.y + i * moveac.y / n;
           f.x = b.x + i * movebc.x / n;
           f.y = b.y + i * movebc.y / n;
           cont = which_side (xy, e, f);
         }
       i--;
     }
   return i;
}

double
grid::get_f_value_by_ijtr (std::function<double (double, double)> f, int i, int j, int trapeze, int n)
{

  int n_ = n - 1;

  point A, B, C, D;
  point desired;

  fill_points (A, B, C, D, trapeze);

  if (i + j <= n)
    {
      desired.x = A.x + i * (B.x - A.x) / n_;
      desired.y = A.y + i * (B.y - A.y) / n_;

      desired.x += (j * (D.x - A.x) / n_);
      desired.y += (j * (D.y - A.y) / n_);
    }
  else
    {
      point moveDC (C.x - D.x, C.y - D.y),
            moveCB (B.x - C.x, B.y - C.y);

      desired.x = D.x + i * moveDC.x / n_ + (n - 1 - j) * moveCB.x / n_;
      desired.y = D.y + i * moveDC.x / n_ + (n - 1 - j) * moveCB.y / n_;
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
                p->C.x, p->C.y,
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
