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
surface::update_f_coeffs ()
{
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
  //probably works
  int n = gr->get_n ();
  int diag_lenght = 4 * n * (n - 1);
  given_func.resize (diag_lenght);
  for (int k = 0; k < diag_lenght; k++)
    {
      int trapeze_num, i, j;
      get_ijtrapeze (&i, &j, &trapeze_num, k, n);
      given_func [k] = gr->get_f_value_by_ijtr (f, i, j, trapeze_num, n);
    }
}

void
surface::draw ()
{
  int size = PAINT_SIZE, size_ = size - 1;
  FIX_UNUSED (size, gr);
  glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

  for (int k = 0; k < 4; k++)
    {
      point A, B, C, D;
      gr->fill_points (A, B, C, D, k);

      point moveAB (B.x - A.x, B.y - A.y),
            moveAD (D.x - A.x, D.y - A.y);
      point xy(A), second, third;
      for (int i = 0; i < size - 2; i++)
        {
          for (int j = 0; j < size - i - 1; j++)
            {
              xy.x = A.x + j * moveAD.x / size_ + i * moveAB.x / size_;
              xy.y = A.y + j * moveAD.y / size_ + i * moveAB.y / size_;

              second.x = xy.x + moveAB.x / size_;
              second.y = xy.y + moveAB.y / size_;

              third.x = xy.x + moveAD.x / size_;
              third.y = xy.y + moveAD.y / size_;

              double val1, val2, val3;
              val1 = gr->get_value (f_coeffs, xy.x, xy.y, k, 0);
              val2 = gr->get_value (f_coeffs, second.x, second.y, k, 0);
              val3 = gr->get_value (f_coeffs, third.x, third.y, k, 0);

              glBegin(GL_TRIANGLES);
                  glVertex3d(xy.x, xy.y, val1);
                  glVertex3d(second.x, second.y, val2);
                  glVertex3d(third.x, third.y, val3);
              glEnd();
            }  
        }
    }

  glBegin(GL_TRIANGLES);
      glVertex3d(0, 0, 1);
      glVertex3d(0, 1, 0);
      glVertex3d(1, 0, 0);
  glEnd();
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
  update_f_coeffs ();
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
