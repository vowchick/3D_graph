#include "surface.h"

surface::surface(grid *gr, std::function<double (double, double)> f)
{
  this->gr = gr;
  this->f = f;
  fill_f ();
  f_coeffs = given_func;
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
void
surface::update (grid *gr)
{
  this->gr = gr;
  int n = gr->get_n ();
  f_coeffs.resize (4 * n * (n - 1));
}
void
surface::set_approx (std::vector<double> approx)
{
  int n = gr->get_n ();
  int diag_length = 4 * n * (n - 1);
  this->approx.resize (diag_length);
  for (int i = 0; i < diag_length; i++)
    {
      this->approx[i] = approx[i];
    }
}

void
surface::fill_f ()
{
  int n = gr->get_n ();
  int diag_lenght = 4 * n * (n - 1);
  given_func.resize (diag_lenght);
  //needs to be finished
}

double
surface::get_value (double x, double y, int trapeze_num, int odd)
{
  return gr->get_value (f_coeffs, x, y, trapeze_num, odd);
}
void
surface::set_f(std::function <double (double, double)> f)
{
  this->f = f;
}
void
surface::change_state ()
{
  st = static_cast<state> ((st + 1) % 3);
  switch (st)
    {
    case given_function:
      fill_f ();
      f_coeffs = given_func;
      break;
    case approximation:
      f_coeffs = approx;
      break;
    case error:
      fill_f ();
      set_error ();
      break;
    }
}
void
surface::set_error ()
{
  int size = given_func.size ();
  for (int i = 0; i < size; i++)
    {
      f_coeffs[i] = fabs (given_func[i] - approx[i]);
    }
}
