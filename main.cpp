#include <stdio.h>
#include <stdlib.h>
#include <memory>
#include "system_builder.h"
#include "system_solver.h"
#include "helper_functions.h"
#include "io.h"
struct thread_info
{
  system_solver *solver;
  system_builder *builder;
  int n;
  int p;
  int idx;
  std::function<double (double, double)> f;
  double eps;
  pthread_barrier_t *barrier;
};

void *
pthread_func (void *arg)
{
    thread_info *info = static_cast<thread_info *> (arg);

    auto builder = info->builder;
    auto solver = info->solver;
    auto barrier = info->barrier;
    auto idx = info->idx;

    builder->fill_MSR_matrix (info->p, idx);
    builder->fill_rhs (info->p, idx);

    pthread_barrier_wait (barrier);

    solver->solve (MAX_IT, idx);

    return 0;
}
int main (int argc, char *argv[])
{
  if (argc != 7)
    {
      printf ("usage ./a.out a.txt nx ny k eps p\n");
      return -1;
    }
  input in;
  polygon pol;
  int res = process_input (argv, in, pol);
  if (res < 0)
    {
      printf ("Couldn't init\n");
      return -1;
    }

  print_polygon(pol);

  int n = in.nx + 1;
  auto func = [] (double x, double y)
  {
    FIX_UNUSED(x, y);
    return 1;
  };



  pthread_barrier_t barrier;
  pthread_t tid;
  pthread_barrier_init (&barrier, NULL, in.p);

  thread_info *info = new thread_info [in.p];
  grid *gr = new grid (&pol, n);
  int alloc_size = allocation_size (n);

  double *matrix = new double [alloc_size];
  int *I = new int [alloc_size];
  double *rhs = new double [4 * (n * n - n)];
  double *x = new double [4 * (n * n - n)];
  double *u = new double [4 * (n * n - n)];
  double *r = new double [4 * (n * n - n)];
  double *v = new double [4 * (n * n - n)];
  for (int i = 0; i < 4 * (n * n - n); i++)
    {
      x[i] = 0.;
      r[i] = 0.;
      v[i] = 0.;
      u[i] = 0.;
    }
  double *buf = new double [in.p];
  system_builder *builder = new system_builder (gr, func, matrix, rhs, I);
  system_solver *solver = new system_solver (matrix, I, x, rhs,
                                             4 * (n * n - n),
                                             u, r, v, buf,
                                             &barrier, in.p, in.eps);

  for (int i = 0; i < in.p; i++)
    {
      info[i].n = n;
      info[i].idx = i;
      info[i].f = func;
      info[i].eps = in.eps;
      info[i].barrier = &barrier;
      info[i].solver = solver;
      info[i].builder = builder;
      info[i].p = in.p;
    }

  for (int i = 1; i < in.p; i++)
    {
      if (pthread_create (&tid, 0, pthread_func, info + i))
        {
          fprintf (stderr, "cannot create thread #%d!\n", i);
          abort ();
        }
    }
  pthread_func (info + 0);
  pthread_barrier_destroy(&barrier);

  delete builder;
  delete gr;
  delete []info;
  delete []matrix;
  delete []x;
  delete []rhs;
  delete []I;
  delete []u;
  delete []r;
  delete []v;
  delete []buf;
  return 0;
}
