#include "surface.h"

surface::surface(grid *gr, std::function<double (double, double)> f)
{
  this->gr = gr;
  this->f = f;
  find_ranges ();
}

void
surface::find_ranges ()
{
  //to be implemented
}
