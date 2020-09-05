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
  double max = f_coeffs[0], min = f_coeffs[0];
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
surface::update (std::unique_ptr<grid> &grid_ptr)
{
  this->grid_ptr.swap (grid_ptr);
  gr = this->grid_ptr.get ();
  int n = gr->get_n ();
  f_coeffs.resize (4 * n * (n - 1));
}

void
surface::update_coeffs ()
{
  update_f_coeffs ();
  find_ranges ();
  int n = gr->get_n (), diag_length = 4 * n * (n - 1);
  f_coeffs[diag_length>>1] += perturbation / 10. * f_range.max;
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
//  int n = gr->get_n ();
//  int diag_length = 4 * n * (n - 1);
//  this->approx.resize (diag_length);
//  for (int i = 0; i < diag_length; i++)
//    {
//      this->approx[i] = approx[i];
//    }
  this->approx = approx;
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
  glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

  max_z = fabs (get_max ());
  if (fabs (get_min ()) > max_z)
    max_z = fabs (get_min ());

  if (fabs (max_z) < 1e-16)
    {
      max_z = 1e-16;
    }

  for (int k = 0; k < 4; k++)
    {
      point A, B, C, D;
      gr->fill_points (A, B, C, D, k);

      Trapeze trap (A, B, C, D);
      draw_bottom_triangle (trap, k);
      draw_top_triangle (trap, k);
    }
}

void
surface::draw_shadow ()
{

  auto draw_trapeze = [this] (int trapeze)
  {
      point A, B, C, D;
      this->gr->fill_points (A, B, C, D, trapeze);
      glBegin(GL_POLYGON);
          glVertex3d(A.x, A.y, 0.);
          glVertex3d(B.x, B.y, 0.);
          glVertex3d(C.x, C.y, 0.);
          glVertex3d(D.x, D.y, 0.);
      glEnd();
    };
  for (int i = 0; i < 4; i++)
    {
      draw_trapeze (i);
    }
}
void
surface::draw_bottom_triangle (Trapeze trap, int k)
{
  point A = trap.A, B = trap.B, D = trap.D;
  int size = PAINT_SIZE, size_ = size - 1;

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

          draw_triangle (xy, second, third, k, k, k, 0, 0, 0);
        }
      point moveDB (B.x - D.x, B.y - D.y);
      for (int j = 1; j < size - i - 1; j++)
        {
          xy.x = A.x + j * moveAD.x / size_ + i * moveAB.x / size_;
          xy.y = A.y + j * moveAD.y / size_ + i * moveAB.y / size_;

          second.x = xy.x + moveDB.x / size_;
          second.y = xy.y + moveDB.y / size_;

          third.x = second.x + moveAD.x / size_;
          third.y = second.y + moveAD.y / size_;

          draw_triangle (xy, second, third, k, k, k, 0, 0, 0);
        }
    }

  xy.x = A.x + (size - 2) * moveAB.x / size_;
  xy.y = A.y + (size - 2) * moveAB.y / size_;

  second.x = xy.x + moveAB.x / size_;
  second.y = xy.y + moveAB.y / size_;

  third.x = xy.x + moveAD.x / size_;
  third.y = xy.y + moveAD.y / size_;

  draw_triangle (xy, second, third, k, (k + 1) % 4, k, 0, 0, 0);
}

void
surface::draw_top_triangle (Trapeze trap, int k)
{
  point B = trap.B, C = trap.C, D = trap.D;
  int size = PAINT_SIZE, size_ = size - 1;

  point moveDC (C.x - D.x, C.y - D.y),
        moveCB (B.x - C.x, B.y - C.y),
        moveDB (B.x - D.x, B.y - D.y);
  point xy(D), second, third;

  for (int i = 0; i < size - 2; i++)
    {
      for (int j = 0; j < i + 1; j++)
        {
          xy.x = D.x + i * moveDC.x / size_ + j * moveCB.x / size_;
          xy.y = D.y + i * moveDC.y / size_ + j * moveCB.y / size_;

          second.x = xy.x + moveDC.x / size_;
          second.y = xy.y + moveDC.y / size_;

          third.x = xy.x + moveDB.x / size_;
          third.y = xy.y + moveDB.y / size_;

          draw_triangle (xy, second, third, k, k, k, 1, 1, 1);
        }
      for (int j = 0; j < i; j++)
        {
          xy.x = D.x + i * moveDC.x / size_ + j * moveCB.x / size_;
          xy.y = D.y + i * moveDC.y / size_ + j * moveCB.y / size_;

          second.x = xy.x + moveCB.x / size_;
          second.y = xy.y + moveCB.y / size_;

          third.x = second.x + moveDC.x / size_;
          third.y = second.y + moveDC.y / size_;

          draw_triangle (xy, second, third, k, k, k, 1, 1, 1);
        }
    }
  int i = size - 2;
  for (int j = 0; j < i + 1; j++)
    {
      xy.x = D.x + i * moveDC.x / size_ + j * moveCB.x / size_;
      xy.y = D.y + i * moveDC.y / size_ + j * moveCB.y / size_;

      second.x = xy.x + moveDC.x / size_;
      second.y = xy.y + moveDC.y / size_;

      third.x = xy.x + moveDB.x / size_;
      third.y = xy.y + moveDB.y / size_;

      draw_triangle (xy, second, third, k, (k + 1) % 4, (k + 1) % 4, 1, 0, 0);
    }
  for (int j = 0; j < i; j++)
    {
      xy.x = D.x + i * moveDC.x / size_ + j * moveCB.x / size_;
      xy.y = D.y + i * moveDC.y / size_ + j * moveCB.y / size_;

      second.x = xy.x + moveCB.x / size_;
      second.y = xy.y + moveCB.y / size_;

      third.x = second.x + moveDC.x / size_;
      third.y = second.y + moveDC.y / size_;

      draw_triangle (xy, second, third, k, k, (k + 1) % 4, 1, 1, 0);
    }
}

void
surface::draw_triangle (point xy, point second, point third, int k1, int k2, int k3,
                        int odd1, int odd2, int odd3)
{
  double val1, val2, val3;
  val1 = gr->get_value (f_coeffs, xy.x, xy.y, k1, odd1);
  val2 = gr->get_value (f_coeffs, second.x, second.y, k2, odd2);
  val3 = gr->get_value (f_coeffs, third.x, third.y, k3, odd3);

  glBegin(GL_TRIANGLES);
      glVertex3d(xy.x, xy.y, val1 / max_z);
      glVertex3d(second.x, second.y, val2 / max_z);
      glVertex3d(third.x, third.y, val3 / max_z);
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
  find_ranges ();
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

void
surface::change_perturbation (int n)
{
  if (n == 0)
    perturbation++;
  else
    perturbation--;
}

int
surface::get_perturbation ()
{
  return perturbation;
}
