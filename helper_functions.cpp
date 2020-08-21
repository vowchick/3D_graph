#include "helper_functions.h"
double
triangle_to_right_triangle_jacob (
        double x1, double y1,     // ->(0, 1)
        double x2, double y2,     // -> (0, 0)
        double x3, double y3,
        int n)     // -> (1, 0)
{
    double J = (x3 - x2) * (y1 - y2) - (x1 - x2) * (y3 - y2);
    FIX_UNUSED(n);
    return fabs (J);
}

double which_side (point a, point b, point c)
{
    return (a.x - c.x) * (b.y - c.y) -
           (b.x - c.x) * (a.y - c.y);
}

bool is_in_triangle (point pt, point a, point b, point c)
{
    double d1, d2, d3;
    bool neg, pos;

    d1 = which_side (pt, a, b);
    d2 = which_side (pt, b, c);
    d3 = which_side (pt, c, a);

    if (fabs (d1) < 1e-16 ||
        fabs (d2) < 1e-16 ||
        fabs (d3) < 1e-16)
      return true;
    neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
    pos = (d1 > 0) || (d2 > 0) || (d3 > 0);

    return !(neg && pos);
}

int
get_k (int i, int j, int trapeze_num, int n)
{
#if (0)
    if (i + j < n)
      {
        return trapeze_num * (n * n - n) + (2 * n - i + 1) * i / 2 + j;
      }
    else
      {
        return trapeze_num * (n * n - n) + (n * (n + 1) / 2) + i * (i - 1) / 2 + (j - n + i);
      }
#else
    return trapeze_num * (n * n - n) + i * n + j;
#endif
}
void
get_ijtrapeze (int *i, int *j, int *trapeze_num, int k, int n)
{
  /**trapeze_num = k / (n * n - n);
    *
   k %= (n * n - n);
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
     }*/
  *trapeze_num = k / (n * n - n);
  k %= (n * n - n);
  *i = k / n;
  *j = k % n;
}

std::function<double (double, double)>
int_to_f (int f_)
{
  std::function<double (double, double)> f =
      [] (double x, double y)
  {
    FIX_UNUSED (x, y);
    return 0;
    };;
  switch (f_)
    {
    case 0:
      f = [] (double x, double y)
      {
        FIX_UNUSED (x, y);
        return 1;
        };
      return f;
    case 1:
      f = [] (double x, double y)
      {
        FIX_UNUSED (x, y);
        return x;
        };
      return f;
    case 2:
      f = [] (double x, double y)
      {
        FIX_UNUSED (x, y);
        return y;
        };
      return f;
    case 3:
      f = [] (double x, double y)
      {
        FIX_UNUSED (x, y);
        return x + y;
        };
      return f;;
    case 4:
      f = [] (double x, double y)
      {
        FIX_UNUSED (x, y);
        return sqrt (x * x + y * y);
        };
      return f;
    case 5:
      f = [] (double x, double y)
      {
        FIX_UNUSED (x, y);
        return x * x + y * y;
        };
      return f;
    case 6:
      f = [] (double x, double y)
      {
        FIX_UNUSED (x, y);
        return exp (x * x - y * y);
        };
      return f;
    case 7:
      f = [] (double x, double y)
      {
        FIX_UNUSED (x, y);
        return 1. / (25 * (x * x + y * y) + 1);
        };
      return f;
    }
  return f;
}

double
ultimate_scalar_counter (double J,
                         double f1, double f2, double f3,
                         double g1, double g2, double g3)
{
    double A = f1 - f3, B = f2 - f3, C = f3,
           D = g1 - g3, E = g2 - g3, F = g3;
    double integral = A * (2 * D + E + 4 * F) +
                      B * (D + 2 * E + 4 * F) +
                      4 * C * (D + E + 3 * F);
    return integral * J / 24.;
}
void
fill_js (Js &J, polygon *p, int n)
{
    J.AaB = triangle_to_right_triangle_jacob(
                p->A.x, p->A.y,
                p->a.x, p->a.y,
                p->B.x, p->B.y, n
                );
    J.Bab = triangle_to_right_triangle_jacob(
                p->B.x, p->B.y,
                p->a.x, p->a.y,
                p->a.x, p->a.y, n
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
void reduce_sum (int p, int *a, int n)
{
  static pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
  static pthread_cond_t c_in = PTHREAD_COND_INITIALIZER;
  static pthread_cond_t c_out = PTHREAD_COND_INITIALIZER;

  static int t_in = 0;
  static int t_out = 0;
  static int *p_a;
  int i = 0;

  if (p <= 1)
    return;
  pthread_mutex_lock (&m);

  if (!p_a) p_a = a;
  else
    if (a)
      {
        for (i = 0; i < n; i++)
          p_a[i] += a[i];
      }

  t_in++;

  if (t_in >= p)
    {
      t_out = 0;
      pthread_cond_broadcast (&c_in);
    }
  else
    while (t_in < p)
      pthread_cond_wait (&c_in, &m);

  if (p_a && p_a != a)
    {
      for (int i = 0; i < n; i++)
        {
          a[i] = p_a[i];
        }
    }
  t_out++;


  if (t_out >= p)
    {
      p_a = 0;
      t_in = 0;
      pthread_cond_broadcast (&c_out);
    }
  else
    {
      while (t_out < p)
        pthread_cond_wait (&c_out, &m);
    }
  pthread_mutex_unlock (&m);
}
int
allocation_size (int n)
{
    int size = 4 * (n * n - n);
    int al_size = 0;
    for (int i = 0; i < size; i++)
        al_size += get_num_of_diag (i, n);
    return size + al_size + 1;
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
/*int
find_ABCD1_points (polygon *p)
{
    auto find__1 = [](point Z,point z, point Q,
            point q, point *desired)->int
    {
      double k1, k2, b1, b2;
      // k = (y2 - y1) / (x2 - x1)
      bool is_vertical_1 = false, is_vertical_2 = false;
      if (fabs (Z.x - Q.x) < 1e-16)
          is_vertical_1 = true;
      if (fabs (Q.x - q.x) < 1e-16)
          is_vertical_2 = true;
      if (is_vertical_1 && is_vertical_2)
        {
            printf ("something is wron with the input figure\n");
            return 0;
        }
      if (is_vertical_1)
        {
          desired->x = Z.x;
          k2 = (Q.y - q.y) / (Q.x - q.x);
          b2 = z.y - k2 * z.x;
          desired->y = k2 * desired->x + b2;
        }
      else if (is_vertical_2)
        {
          desired->x = Q.x;
          k1 = (Q.y - Z.y) / (Q.x - Z.x);
          b1 = Z.y - k1 * Z.x;
          desired->y = k1 * desired->x + b1;
        }
      else
        {
          k1 = (Q.y - Z.y) / (Q.x - Z.x);
          b1 = Z.y - k1 * Z.x;
          k2 = (Q.y - q.y) / (Q.x - q.x);
          b2 = z.y - k2 * z.x;
          if (fabs (k1 - k2) < 1e-16)
            {
               printf ("Literally isn't supposed to happen\n");
               return -1;
            }
          desired->x = (b2 - b1) / (k1 - k2);
          desired->y = k1 * desired->x + b1;
        }
      return 0;
    };
    if (find__1 (p->A, p->a, p->B, p->b, &p->A1))
      {
        return -1;
      }
    if (find__1 (p->B, p->b, p->C, p->c, &p->B1))
      {
        return -1;
      }
    if (find__1 (p->C, p->c, p->D, p->d, &p->C1))
      {
        return -1;
      }
    if (find__1 (p->D, p->d, p->A, p->a, &p->D1))
      {
        return -1;
      }
    return 0;
}*/
