#include <stdio.h>
#include <stdlib.h>
#include <memory>
#include "system_builder.h"
#include "system_solver.h"
#include "helper_functions.h"
#include "io.h"
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

  int alloc_size = allocation_size (n);
  double *matrix = new double [alloc_size];
  double *rhs = new double [4 * (n * n - n)];
  int *I = new int [alloc_size];

  system_builder *builder  = new system_builder (n, &pol, func, matrix, rhs, I);

  builder->fill_MSR_matrix (in.p, 0);
  builder->fill_rhs ();

  pthread_barrier_t barrier;
  pthread_barrier_init (&barrier, NULL, in.p);

  double *x = new double [4 * (n * n - n)];
  for (int i = 0; i < 4 * (n * n - n); i++)
      x[i] = 0.;
  system_solver solver (matrix, I, x, rhs, 4 * (n * n - n), &barrier, in.p, in.eps);
  solver.solve (MAX_IT, 0);

  delete builder;
  delete []x;
  delete []matrix;
  delete []rhs;
  delete []I;
  return 0;
}
