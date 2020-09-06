#ifndef SURFACE_H
#define SURFACE_H

#include <QObject>
#include <QWidget>
#include <QGLWidget>
#include "grid.h"

class surface
{
public:
  surface(grid *gr, std::function<double (double, double)> f);
  double get_max () const {return f_range.max;}
  double get_min () const {return f_range.min;}
  ranges get_range () const {return f_range;}
  grid *get_grid () const {return gr;}

  void set_approx (std::vector<double> &approx);
  void set_f (std::function <double (double, double)> f);
  void update (std::unique_ptr<grid> &grid_ptr);
  void change_state ();
  double get_value (double x, double y, int trapeze_num, int odd);
  void draw ();
  void update_f_coeffs ();
  void update_coeffs ();
  void change_perturbation (int n);
  int get_perturbation ();
  void draw_shadow ();

private:
  void find_ranges ();
  void fill_f ();
  void set_error ();
  void draw_triangle (point &xy, point &second, point &third, int k1, int k2, int k3,
                      int odd1, int odd2, int odd3);
  void draw_bottom_triangle (Trapeze &trap, int k);
  void draw_top_triangle (Trapeze &trap, int k);

private:
  grid *gr = nullptr;
  std::unique_ptr<grid> grid_ptr;
  std::function<double (double, double)> f;
  std::vector<double> f_coeffs;
  std::vector<double> given_func;
  std::vector<double> approx;
  state st = given_function;
  ranges f_range = {1, -1}; //temporarily
  double max_z = 0.;
  double perturbation = 0.;
};

#endif // SURFACE_H
