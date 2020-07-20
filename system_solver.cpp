#include "system_solver.h"

system_solver::~system_solver ()
{
  delete []u;
  delete []r;
  delete []buf;
}
system_solver::system_solver (double *matrix_, int *I_,
                              double *x_, double *rhs_, int n_,
                              pthread_barrier_t *barrier_,
                              int p_,
                              double eps_)
{
  matrix = matrix_;
  I = I_;
  rhs = rhs_;
  n = n_;
  barrier = barrier_;
  x = x_;
  p = p_;
  eps = eps_;

  u = new double[n];
  r = new double[n];
  buf = new double[p];
}
int
system_solver::solve_stage (int k, int maxit)
{
  double c1, c2, tau;
  int it;
  msr_matrix_mult_vector (matrix, I, n, x,
                          rhs, k, p, barrier);
  linear_combination (r, rhs, n, 1, p, k, barrier);

  for (it = 0; it < maxit; it++)
    {
      msr_apply_preconditioner (matrix, n, r, r, k, p, barrier); // точно в обоих метсах r?
      msr_matrix_mult_vector (matrix, I, n, r, u, k, p, barrier);

      c1 = scalar_product (u, r, n, p, k, buf, barrier);

      c2 = scalar_product (u, u, n, p, k, buf, barrier);

      if (c1 < eps * eps || c2 < eps * eps)
        break;

      tau = c1 / c2;
      linear_combination (x, r, n, tau, p, k, barrier);
      linear_combination (r, u, n, tau, p, k, barrier);
    }
  if (it >= max_it)
      return -1;

  return it;
}

int
system_solver::solve (int MAXIT, int k)
{
  int maxit = max_it;
  int res = 0, it;

  for (it = 0; it < MAXIT; it += maxit)
    {
      res = solve_stage (k, maxit);

      if (res >= 0)
        break;
    }

  if (it >= MAXIT)
    return -1;

  return it;
}
