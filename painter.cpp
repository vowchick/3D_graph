#include "painter.h"

painter::painter(grid *gr, double *f_coeffs, QWidget *parent)
  :QGLWidget (parent)
{
  surf_ptr.reset (new surface (gr, f_coeffs));
  surf = surf_ptr.get ();
  //might need to multiply by 1.5
}
painter::~painter ()
{

}

QSize
painter::minimumSizeHint() const
{
    return QSize(500, 500);
}

QSize
painter::SizeHint() const
{
    return QSize(1000, 1000);
}

void
painter::initializeGL()
{
  qglClearColor(Qt::white); //clear Color buffer

  glEnable (GL_DEPTH_TEST);
  glEnable (GL_CULL_FACE);
  glShadeModel (GL_SMOOTH);
  glEnable (GL_LIGHTING);
  glEnable (GL_LIGHT0);
  glEnable (GL_MULTISAMPLE);
  GLfloat lightPosition0[4] = {0, 0, static_cast <float> (surf->get_max ()) + 1, 1.0};
  glLightfv (GL_LIGHT0, GL_POSITION, lightPosition0);
}

void
painter::resizeGL(int width, int height)
{
    int side = qMin(width, height);
    glViewport((width - side) / 2, (height - side) / 2, side, side);
    set_gl ();
}

void
painter::set_gl ()
{
  float depth = surf->get_max () - surf->get_min ();
  if (depth < 1e-16)
    {
      depth = 1;
    }
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
#ifdef QT_OPENGL_ES_1
  glOrtho(-2, 2, -1, 1, -1, 1);
#else
  glOrtho(-2, 2, -2, 2, -2, 2);
#endif
  glMatrixMode(GL_MODELVIEW);
}

void
painter::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    double max_z = fabs (surf-> get_max ());
    if (fabs (surf->get_min ()) > max_z)
      max_z = fabs (surf->get_min ());

    grid *gr;
    gr = surf->get_grid();

    double max_w = gr->get_width ();
    double max_h = gr->get_height ();

    auto replace_max = [] (double &max)
    {
        if (fabs (max) < 1e-16)
          {
            max = 1;
          }
      };
    replace_max (max_w);
    replace_max (max_h);
    replace_max (max_z);

    glRotated(xRot / 16.0, 1.0, 0.0, 0.0);
    glRotated(yRot / 16.0, 0.0, 1.0, 0.0);
    glScaled (scale / max_w, scale / max_h, scale / max_z);
    glEnableClientState (GL_VERTEX_ARRAY);
    glEnableClientState (GL_NORMAL_ARRAY);

    glColorMaterial (GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable (GL_COLOR_MATERIAL);

    glDisable (GL_CULL_FACE);
    draw_axes ();
    qglColor (Qt::red);
//    current_surface->draw ();

    glDisableClientState (GL_VERTEX_ARRAY);
    glDisableClientState (GL_NORMAL_ARRAY);
}

void
painter::draw_axes ()
{
  glLineWidth (3.0);


  qglColor (Qt::green);
  glBegin (GL_LINES);
  glVertex3d ( 20.0,  0.0,  0.0);
  glVertex3d (-20.0,  0.0,  0.0);
  glEnd ();
  qglColor (Qt::yellow);
  glBegin (GL_LINES);
  glVertex3d (0.0,   20.0,  0.0);
  glVertex3d (0.0, -20.0,  0.0);
  glEnd ();
  qglColor (Qt::blue);
  glBegin (GL_LINES);
  glVertex3d ( 0.0,  0.0,  20.0);
  glVertex3d ( 0.0,  0.0, -20.0);
  glEnd ();

}

static void qNormalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 360)
        angle -= 360 * 16;
}

void
painter::setXRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != xRot) {
        xRot = angle;
        updateGL();
    }
}

void
painter::setYRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != yRot) {
        yRot = angle;
        updateGL();
    }
}

void
painter::setZRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != zRot) {
        zRot = angle;
        updateGL();
    }
}

void
painter::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}

void
painter::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    if (event->buttons() & Qt::LeftButton) {
        setXRotation(xRot + 8 * dy);
        setYRotation(yRot + 8 * dx);
    } else if (event->buttons() & Qt::RightButton) {
        setXRotation(xRot + 8 * dy);
        setZRotation(zRot + 8 * dx);
    }

    lastPos = event->pos();
}

void
painter::set_f_coeffs (double *f_coeffs)
{
  surf->set_f_coeffs (f_coeffs);
}
