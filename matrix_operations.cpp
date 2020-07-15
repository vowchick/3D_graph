#include "matrix_operations.h"
double
triangle_to_right_triangle_jacob (
        double x1, double y1,     // ->(0, 1)
        double x2, double y2,     // -> (0, 0)
        double x3, double y3,
        int n)     // -> (1, 0)
{
    double J = (x3 - x2) * (y1 - y2) - (x1 - x2) * (y3 - y2);
    return fabs (J) / (n * n);
}
double
ultimate_scalar_counter (double J,
                         double f1, double f2, double f3,
                         double g1, double g2, double g3)
{
    double A = f1 - f3, B = f2 - f3, C = f3,
           D = g1 - g3, E = g2 - g3, F = g3;
    double integral = A * (2 * D + E + 4 * F) +
                      B * (D  + 2 * E + 4 * F) +
                      4 * C * (D + E + 3 * F);
    return integral * J / 24.;
}
void
fill_the_matrix_msr_format (double *matrix,     //pointer to the matrix
                            int n,              //number of points
                            polygon p)
{

    FIX_UNUSED (matrix);
    //Здесь n = nx + 1 - количество точек на ребре, не количество отрезков разбиения
    Js j;
    us u;
    fill_js (j, p, n);
    fill_us (j, u);
    //A->a и параллельно идем к B и от A к a
    // затем от B к a и так далее

}
int
get_k (int i, int j, int trapeze_num, int n)
{
    if (i + j < n)
      {
        return trapeze_num * (n * n - n + 1) + (2 * n - i + 1) * i / 2 + j;
      }
    else
      {
        return trapeze_num * (n * n - n + 1) + (n * (n + 1) / 2) + i * (i - 1) / 2 + (j - n + i);
      }
}
void
get_ijtrapeze (int *i, int *j, int *trapeze_num, int k, int n)
{
   *trapeze_num = k / (n * n - n + 1);
   k %= (n * n - n + 1);
   if (k < n * (n + 1) / 2)
     {
       int tmp = n, it = 0;
        while (tmp <= k)
          {
            tmp += (n - ++it);
          }
        *i = (it);
        tmp -= (n - it);
        *j = k - tmp;
     }
   else
     {
       k -= (n * (n + 1) / 2 - 1);
       int tmp = 1, it = 0;
       while (tmp <= k)
         {
           tmp += (++(it));
         }
       *i = it;
       tmp -= it;
       *j = (k - tmp + n - *i);
     }
}
int
get_num_of_diag (int k, int n)
{
  int i, j, trapeze_num;
  get_ijtrapeze (&i, &j, &trapeze_num, k, n);
  if (j > 0 && j < n - 1)
      return 6;
  else if (j == 0 || j == n - 1)
      return 4;
  abort ();
}
int
allocation_size (int n)
{
    int size = 4 * (n * n - n + 1);
    int al_size = 0;
    for (int i = 0; i < size; i++)
        al_size += get_num_of_diag (i, n);
    return size + al_size + 1;
}
int get_off_diag (int n, int k, double *a_diag, double *a,
                  int *I, us u)
{
    int i, j, trapeze_num;
    get_ijtrapeze (&i, &j, &trapeze_num, k, n);
    //расписываем случаи
    //полностью внутри
    if (j > 0 && j < n - 1 && i > 0 && i < n - 1)
      {
        double tr1, tr2;
        if (i + j < n)
          {
            tr1 = tr2 = get_u (0, trapeze_num, u);
			for (int i = 0; i < 6; i++)
			  a[i] = 2 * tr1;
          }
        else if (i + j == n)
          {
            tr1 = get_u (0, trapeze_num, u);
            tr2 = get_u (1, trapeze_num, u);
            a[0] = 2 * tr2;
            a[1] = tr1 + tr2;
            a[2] = 2 * tr1;
            a[3] = 2 * tr1;
            a[4] = tr1 + tr2;
            a[5] = 2 * tr2;
          }
        else
          {
            tr1 = tr2 = get_u (1, trapeze_num, u);
			for (int i = 0; i < 6; i++)
			  a[i] = 2 * tr2;
          }
        *a_diag  = 3 * (tr1 + tr2);

        if (i < n - 2)
          {
            I[0] = get_k (i, j + 1, trapeze_num, n);
            I[1] = get_k (i - 1, j + 1, trapeze_num, n);
            I[2] = get_k (i - 1, j, trapeze_num, n);
            I[3] = get_k (i, j - 1, trapeze_num, n);
            I[4] = get_k (i + 1, j - 1, trapeze_num, n);
            I[5] = get_k (i + 1, j, trapeze_num, n);
          }
        else
          {
            I[0] = get_k (i, j + 1, trapeze_num, n);
            I[1] = get_k (i - 1, j + 1, trapeze_num, n);
            I[2] = get_k (i - 1, j, trapeze_num, n);
            I[3] = get_k (i, j - 1, trapeze_num, n);

            int next_trapeze = (trapeze_num + 1) % 8;

            I[4] = get_k (0, j - 1, next_trapeze, n);
            I[5] = get_k (0, j, next_trapeze, n);
          }

        return 6;
      }
    //правая сторона трапеции
    else if (i == 0 && j > 0 && j < n - 1)
      {

        return 6;
      }
    //нижняя сторона трапеции
    else if (j == 0 && i > 0 && i < n - 1)
      {
        return 4;
      }
    //верхняя сторона трапеции
    else if (j == n - 1 && i > 0 && i < n - 1)
      {
        return 4;
      }
    //правый нижний угол
    else if (j == 0 && i == 0)
      {
        return 4;
      }
    //правый верхний угол
    else if (j == n - 1 && i == 0)
      {
        return 4;
      }
    abort ();
    return -1000;
}
void
carcass (int n, int *I)
{
    int len = allocation_size(n);
    int N = 4 * (n * n - n + 1);
    int nz = len - N - 1;
    int l = 0, s = 0;
    I[0] = N + 1;
    for (int k = 1; k <= N; k++)
      {
        l = get_num_of_diag(k - 1, n);
        I[k] = I[k - 1] + l;
        s += l;
      }
    assert (s == nz);
    assert (I[N] == len);
    printf ("Here!: %d %d\n", s, nz);
    printf ("%d %d\n", I[N], len);
}
void
fill_js (Js &J, polygon p, int n)
{
    J.AaB = triangle_to_right_triangle_jacob(
                p.A.x, p.A.y,
                p.a.x, p.a.y,
                p.B.x, p.B.y, n
                );
    J.Bab = triangle_to_right_triangle_jacob(
                p.B.x, p.B.y,
                p.a.x, p.a.y,
                p.a.x, p.a.y, n
                );
    J.BbC = triangle_to_right_triangle_jacob(
                p.b.x, p.b.y,
                p.c.x, p.c.y,
                p.B.x, p.B.y, n
                );
    J.Cbc = triangle_to_right_triangle_jacob(
                p.C.x, p.C.y,
                p.b.x, p.b.y,
                p.c.x, p.c.y, n
                );
    J.CcD = triangle_to_right_triangle_jacob(
                p.C.x, p.C.y,
                p.c.x, p.c.y,
                p.D.x, p.D.y, n
                );
    J.Dcd = triangle_to_right_triangle_jacob(
                p.D.x, p.D.y,
                p.c.x, p.c.y,
                p.d.x, p.d.y, n
                );
    J.DdA = triangle_to_right_triangle_jacob(
                p.D.x, p.D.y,
                p.d.x, p.d.y,
                p.A.x, p.A.y, n
                );
    J.Ada = triangle_to_right_triangle_jacob(
                p.A.x, p.A.y,
                p.a.x, p.a.y,
                p.d.x, p.d.y, n
                );
}
void
fill_us (Js &j, us &u)
{
    u.BbC = ultimate_scalar_counter (j.BbC, 1, 0, 0, 1, 0, 0);
    u.AaB = ultimate_scalar_counter (j.AaB, 1, 0, 0, 1, 0, 0);
    u.Bab = ultimate_scalar_counter (j.Bab, 1, 0, 0, 1, 0, 0);
    u.Cbc = ultimate_scalar_counter (j.Cbc, 1, 0, 0, 1, 0, 0);
    u.CcD = ultimate_scalar_counter (j.CcD, 1, 0, 0, 1, 0, 0);
    u.Dcd = ultimate_scalar_counter (j.Dcd, 1, 0, 0, 1, 0, 0);
    u.DdA = ultimate_scalar_counter (j.DdA, 1, 0, 0, 1, 0, 0);
    u.Ada = ultimate_scalar_counter (j.Ada, 1, 0, 0, 1, 0, 0);
}
