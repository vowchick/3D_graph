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

private:
  void find_ranges ();

private:
  grid *gr = nullptr;
  std::function<double (double, double)> f;
  ranges f_range = {1, -1}; //temporarily
};

#endif // SURFACE_H
