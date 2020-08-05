#include "matrix_operations.h"
int
msr_apply_preconditioner (double *A, int n,
                          double *x, double *b,
                          int k, int p,
                          pthread_barrier_t *barrier)
{
  int i1, i2, i;
  i1 = k * n; i1 /= p;
  i2 = (k + 1) * n; i2 = i2 / p - 1;

  for (i = i1; i <= i2; i++)
    x[i] = b[i] / A[i];

  pthread_barrier_wait (barrier);
  return 0;
}
double
scalar_product (double *x, double *y, int n,
                int p, int k, double *buf,
                pthread_barrier_t *barrier)
{
  int i1 = k * n; i1 /= p;
  int i2 = (k + 1) * n; i2 = i2 / p - 1;

  buf[k] = 0;
  for (int i = i1; i <= i2; i++)
    buf[k] += x[i] * y[i];

  pthread_barrier_wait (barrier);

  double s = 0;
  for (int i = 0; i < p; i++)
    s += buf[i];

  pthread_barrier_wait (barrier);
  return s;
}
void
msr_matrix_mult_vector (double *A, int *I, int M,
                       double *x, double *b, int k,
                       int p,
                       pthread_barrier_t *barrier)
{
  int i1, i2, i, j, l, m;
  double s;
  i1 = k * M;  i1 /= p;
  i2 = (k + 1) * M; i2 = i2 / p - 1;

  for (i = i1; i <= i2; i++)
    {
      s = A[i] * x[i];
      l = I[i + 1] - I[i];
      m = I[i];

      for (j = 0; j < l; j++)
        {
          s += A[m + j] * x[I[m + j]];
        }
      b[i] = s;
    }
  pthread_barrier_wait (barrier);
}
void
linear_combination (double *x, double *y,
                    int n, double a,
                    int p, int k,
                    pthread_barrier_t *barrier)
{
  int i1 = k * n; i1 /= p;
  int i2 = (k + 1) * n; i2 = i2 / p - 1;

  for (int i = i1; i <= i2; i++)
    x[i] -= a * y[i];

  pthread_barrier_wait (barrier);
}

void print_matrix (int matrix_size, double *a, int *I)
{
  int pos;
  int q;
  int pr_n = matrix_size > 200? 200: matrix_size;
  for (int i = 0; i < pr_n; i++)
    {
      pos = I[i];
      int raw_size = I[i+1] - I[i];
      for (int j = 0; j < pr_n; j++)
        {
          if (i != j)
            {
              for (q = 0; q < raw_size; q++)
                {
                  if (I[pos + q] == j)
                    {
                      printf ("%.3f ", a[pos + q]);
                      break;
                    }
                }


              if (q == raw_size)
                {
                  printf ("%.3f ", 0.);
                }
            }
          else
            {
              printf ("%.3f ", a[i]);
            }
        }
      printf ("\n");
    }
}

int check_matrix (double *a, int *I, int n, int p, int k)
{
  int i1, i2, i, j, J, error, len, l;
  i1 = k * n; i1 /= p;
  i2 = (k + 1) * n; i2 = i2 / p - 1;
  double val;
  for (i = i1; i <= i2; i++)
    {
      len = I[i + 1] - I[i];
      int offset = I[i];
      for (j = 0; j < len; j++)
        {
          J = I[offset + j];
          val = a[offset + j];
          int lenJ = I[J + 1] - I[J];
          int offsetJ = I[J];
          for (l = 0; l < lenJ; l++)
            {
              if (I[offsetJ + l] == i)
                {
                  if (fabs (val - a[offsetJ + l]) > 1e-16)
                    {
                      auto ss = a[offsetJ + l];
                      FIX_UNUSED(ss);
                      error = -2;
                    }
                  break;
                }
            }
          if (l >= lenJ)
            {
              error = -1;
              break;
            }
        }
      if (error < 0)
        break;
    }
  if (error < 0)
    return -1;
  return 0;
}
