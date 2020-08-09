#ifndef SURFACE_H
#define SURFACE_H

#include "grid.h"
class surface
{
public:
  surface(grid *gr, std::function<double (double, double)> f);
  double get_max () const {return f_range.max;}
  double get_min () const {return f_range.min;}
  ranges get_range () const {return f_range;}
  grid *get_grid () const {return gr;}

  void set_approx (std::vector<double> approx);
  void set_f (std::function <double (double, double)> f);
  void update (grid *gr_);
  void change_state ();

private:
  void find_ranges ();
  void fill_f ();
  void set_error ();

private:
  grid *gr = nullptr;
  std::function<double (double, double)> f;
  std::vector<double> f_coeffs;
  std::vector<double> given_func;
  std::vector<double> approx;
  state st = given_function;
  ranges f_range = {1, -1}; //temporarily
};

#endif // SURFACE_H
