#include "painter.h"

painter::painter(grid *gr, std::function <double (double, double)> f, QWidget *parent)
  :QGLWidget (parent)
{
  surf_ptr.reset (new surface (gr, f));
  surf = surf_ptr.get ();
  //might need to multiply by 1.5
  width = gr->get_width ();
  height = gr->get_height ();

  depth = surf->get_max() - surf->get_min ();
  depth *= 5;
}
painter::~painter ()
{

}
