#include <stdio.h>
#include <stdlib.h>
#include <memory>
#include "matrix_operations.h"
#include "helper_functions.h"
int main (int argc, char *argv[])
{
  if (argc != 3)
    {
      printf ("usage ./a.out a.txt nx\n");
      return -1;
    }
  int nx = atoi (argv[2]);
  if (nx <= 0)
    {
      printf ("n should be a positive integer\n");
      return 0;
    }
  char *file_name = argv[1];
  polygon Polygon;
  if (read_polygon_from_file (
                          file_name,
                          &Polygon))
    {
      return -1;
    }
  if (find_inside_points (&Polygon))
    {
      return -1;
    }
  print_polygon(Polygon);
  int n = nx + 1;
  int len = allocation_size (n);
  std::unique_ptr<double[]> matrix = std::make_unique <double []> (len);
  std::unique_ptr<int[]> I = std::make_unique <int[]> (len);
  carcass (n, I.get());
  fill_the_matrix_msr_format (matrix.get (), nx + 1,
                              Polygon);
//  for (int k = 0; k < (nx + 1) * (nx + 1) ; k++)
//  {
//      int i, j, tr;
//      get_ijtrapeze(&i, &j, &tr, k, nx + 1);
//      printf ("%d %d %d\n", i, j, tr);
//  }
  return 0;
}
