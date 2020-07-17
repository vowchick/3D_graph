#include <stdio.h>
#include <stdlib.h>
#include <memory>
#include "matrix_operations.h"
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
  int len = allocation_size (n);

  std::unique_ptr<double[]> matrix = std::make_unique <double []> (len);
  std::unique_ptr<int[]> I = std::make_unique <int[]> (len);
  carcass (n, I.get());
  fill_the_matrix_msr_format (matrix.get (), I.get (),in.nx + 1,
                              pol);
  return 0;
}
