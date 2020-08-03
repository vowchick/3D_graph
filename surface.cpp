#include "surface.h"

surface::surface(grid *gr, double *f_coeffs)
{
  this->gr = gr;
  this->f_coeffs = f_coeffs;
  find_ranges ();
}

void
surface::find_ranges ()
{
  int n = gr->get_n ();
  int diag_lenght = 4 * n * (n - 1);
  double max = f_coeffs[0], min = f_coeffs[1];
  for (int i = 1; i < diag_lenght; i++)
    {
      if (max < f_coeffs[i])
        max = f_coeffs[i];

      if (min > f_coeffs[i])
        min = f_coeffs[i];
    }
  f_range.max = max;
  f_range.min = min;
}
