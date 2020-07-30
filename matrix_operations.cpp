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
