#include "painter.h"

painter::painter(grid *gr, std::function <double (double, double)> f, QWidget *parent)
  :QGLWidget (parent)
{
  FIX_UNUSED (gr, f );
}
painter::~painter ()
{

}
