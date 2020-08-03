#ifndef SURFACE_H
#define SURFACE_H

#include "grid.h"
class surface
{
public:
  surface(grid *gr,  double *f_coeffs);
  double get_max () const {return f_range.max;}
  double get_min () const {return f_range.min;}
  ranges get_range () const {return f_range;}
  grid *get_grid () const {return gr;}

  void set_f_coeffs (double *f_coeffs);

private:
  void find_ranges ();

private:
  grid *gr = nullptr;
  double *f_coeffs;
  ranges f_range = {1, -1}; //temporarily
};

#endif // SURFACE_H
