#include "surface.h"

surface::surface(grid *gr, double *f_coeffs)
{
  this->gr = gr;
  this->f_coeffs = f_coeffs;
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
void
surface::update (grid *gr, double *f_coeffs)
{
  this->gr = gr;
  this->f_coeffs = f_coeffs;
}
void
surface::set_f_coeffs (double *f_coeffs)
{
  int n = gr->get_n ();
  int diag_length = 4 * n * (n - 1);
  for (int i = 0; i < diag_length; i++)
    {
      this->f_coeffs[i] = f_coeffs[i];
    }
  find_ranges ();
}
