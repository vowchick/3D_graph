#include <stdio.h>
#include <stdlib.h>
#include <memory>
#include "msr_matrix_builder.h"
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
  msr_matrix_builder builder (n, &pol);

  builder.fill_MSR_matrix (1, 0);

  return 0;
}
