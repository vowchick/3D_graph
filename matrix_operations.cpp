#include "matrix_operations.h"
double
triangle_to_right_triangle_jacob (
        double x1, double y1,     // ->(0, 1)
        double x2, double y2,     // -> (0, 0)
        double x3, double y3)     // -> (1, 0)
{
    double J = (x3 - x2) * (y1 - y2) - (x1 - x2) * (y3 - y2);
    return fabs (J);
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

    //Здесь n = nx + 1 - количество точек на ребре, не количество отрезков разбиения
    double J_AaB, J_Bab, J_BbC, J_Cbc,
            J_CcD, J_Dcd, J_DdA, J_Ada;
    fill_js (&J_AaB, &J_Bab, &J_BbC, &J_Cbc,
             &J_CcD, &J_Dcd, &J_DdA, &J_Ada, p);
    double u_BbC = ultimate_scalar_counter (J_BbC, 1, 0, 0, 1, 0, 0);
    double u_AaB = ultimate_scalar_counter (J_AaB, 1, 0, 0, 1, 0, 0);
    double u_Bab = ultimate_scalar_counter (J_Bab, 1, 0, 0, 1, 0, 0);
//    double u_Cbc = ultimate_scalar_counter (J_Cbc, 1, 0, 0, 1, 0, 0);
//    double u_CcD = ultimate_scalar_counter (J_CcD, 1, 0, 0, 1, 0, 0);
//    double u_Dcd = ultimate_scalar_counter (J_Dcd, 1, 0, 0, 1, 0, 0);
    double u_DdA = ultimate_scalar_counter (J_DdA, 1, 0, 0, 1, 0, 0);
    double u_Ada = ultimate_scalar_counter (J_Ada, 1, 0, 0, 1, 0, 0);
    //A->a и параллельно идем к B и от A к a
    // затем от B к a и так далее

    //Заполнение скалярных произведений сам с собой
    //Заполняем ребро Aa
    int start = 0;
    starting_fill (matrix, &start, n, u_Ada, u_AaB, u_Bab, u_DdA);
    //Закончили заполнять ребро Aa
    //Заполняем внутренности треугольника AaB
    for (int i = 1; i < n - 1; i++)
      {
        matrix[start] = 3 * u_AaB;
        for (int j = start + 1; j < start + n - i - 1; j++)
          {
            matrix[j] = 6 * u_AaB;
          }
        matrix[start + n - i - 1] = 3 * (u_AaB + u_Bab);
        start += (n - i);
      }
    matrix[start++] = u_AaB + u_Bab + u_BbC;
    //заполняем внутренности треугольника Bab
    for (int i = 0; i < n - 1; i++)
      {
        start += i;
        for (int j = start; j < start + i; j++)
          {
             matrix[j] = 6 * u_Bab;
          }
        matrix[start + i] = 3 * u_Bab;
      }
}
void
fill_trapeze ()
{

}
void
starting_fill (double *matrix, int *start, int n, double u_second,
               double u_main, double u_last, double u_first)
{
    //Заполняем ребро Aa/Bb/Cc/Dd
    matrix[*start] = (u_main + u_second + u_first);
    for (int i = 1; i < n - 1; i++)
    {
        matrix[i + *start] = 3 * u_main + 3 * u_second;
    }
    matrix[*start + n - 1] = (u_main + 2 * u_second + u_last);
    *start += n;
}
int
get_k (int i, int j, int trapeze_num, int n)
{
    if (i + j < n)
      {
        return trapeze_num * (n * n - n + 1)+ (2 * n - i + 1) * i / 2 + j;
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
    printf ("%d\n", size + al_size + 1);
    return size + al_size + 1;
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
fill_js (double *J_AaB, double *J_Bab, double *J_BbC,
         double *J_Cbc, double *J_CcD, double *J_Dcd,
         double *J_DdA, double *J_Ada, polygon p)
{
*J_AaB = triangle_to_right_triangle_jacob(
                p.A.x, p.A.y,
                p.a.x, p.a.y,
                p.B.x, p.B.y
            );
*J_Bab = triangle_to_right_triangle_jacob(
                p.B.x, p.B.y,
                p.a.x, p.a.y,
                p.a.x, p.a.y
            );
*J_BbC = triangle_to_right_triangle_jacob(
                p.b.x, p.b.y,
                p.c.x, p.c.y,
                p.B.x, p.B.y
            );
*J_Cbc = triangle_to_right_triangle_jacob(
                p.C.x, p.C.y,
                p.b.x, p.b.y,
                p.c.x, p.c.y
            );
*J_CcD = triangle_to_right_triangle_jacob(
                p.C.x, p.C.y,
                p.c.x, p.c.y,
                p.D.x, p.D.y
            );
*J_Dcd = triangle_to_right_triangle_jacob(
                p.D.x, p.D.y,
                p.c.x, p.c.y,
                p.d.x, p.d.y
            );
*J_DdA = triangle_to_right_triangle_jacob(
                p.D.x, p.D.y,
                p.d.x, p.d.y,
                p.A.x, p.A.y
            );
*J_Ada = triangle_to_right_triangle_jacob(
                p.A.x, p.A.y,
                p.a.x, p.a.y,
                p.d.x, p.d.y
            );
}
