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
    return x + y;
  };

  double *matrix = nullptr, *rhs = nullptr;
  int *I = nullptr;
  system_builder *builder  = new system_builder (n, &pol, func, matrix, rhs, I);

  //надо вот с этим разобраться пожалуй (с матрицей правой частью и т.д.
  builder->fill_MSR_matrix (in.p, 0);
  builder->fill_rhs ();

  pthread_barrier_t barrier;
  pthread_barrier_init (&barrier, NULL, in.p);

  double *x = new double [4 * (n * n - n)];
  system_solver solver (matrix, I, x, rhs, 4 * (n * n - n), &barrier, in.p, in.eps);
//  solver.solve (MAX_IT, 0);

  delete builder;
  delete []x;
  return 0;
}
