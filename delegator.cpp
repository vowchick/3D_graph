#include "delegator.h"

delegator::delegator()
{

}
delegator::delegator (pthread_barrier_t *barrier_, polygon *pol_, int p_)
{
  barrier = barrier_;
  pol = pol_;
  p = p_;
}
void
delegator::erase ()
{
  delete []matrix;
  delete []I;
  delete []rhs;
  delete []x;
  delete solver;
  delete builder;
}
int
delegator::allocate (int n_, std::function<double (double, double)> f_, double eps_)
{
  n = n_;
  f = f_;
  eps = eps_;
  int alloc_size = allocation_size (n);
  matrix = new double [alloc_size];
  if (!matrix)
    return -1;
  int N = 4 * (n * n - n);
  rhs = new double [N];
  if (!rhs)
    {
      delete []matrix;
      return -1;
    }
  x = new double [N];
  if (!x)
    {
      delete []matrix;
      delete []rhs;
      return -1;
    }
  I = new int [alloc_size];
  if (!I)
    {
      delete []matrix;
      delete []rhs;
      delete []x;
      return -1;
    }
  return 0;
}
void
delegator::solve (int k)
{
  if (k == 0)
    builder = new system_builder (n, pol, f, matrix, rhs, I);

  pthread_barrier_wait (barrier);

  builder->fill_MSR_matrix(p, k);
  builder->fill_rhs (p, k);

  solver = new system_solver (matrix, I, x, rhs, 4 * (n * n - n), barrier, p, eps);
  solver->solve (MAX_IT, k);
}
