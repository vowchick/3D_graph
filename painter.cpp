#include "painter.h"

painter::painter(grid *gr, std::function <double (double, double)> f, QWidget *parent)
  :QGLWidget (parent)
{
  surf.reset (new surface (gr, f));
  //should set width and height
//  width = grid.u.x() + grid.v.x();
//  height = grid.u.y() + grid.v.y();
//  width *= PROPORTION;
//  height *= PROPORTION;
  //depth = m_surface->get_max () - m_surface->get_min ();
  depth *= 5;
}
painter::~painter ()
{

}
