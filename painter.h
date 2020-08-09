#ifndef PAINTER_H
#define PAINTER_H

#include <QObject>
#include <QWidget>
#include <QGLWidget>
#include "surface.h"
#include "QMouseEvent"
enum state
{
  the_func,
  the_approx,
  the_error,
};

class painter : public QGLWidget
{
public:
  painter(grid *gr, double *f_coeffs, QWidget *parent = nullptr);
 ~painter ();
  void set_f_coeffs (double *f_coeffs);
  void update_surface (grid *gr, double *f_coeffs);

public slots:
  void setXRotation(int angle);
  void setYRotation(int angle);
  void setZRotation(int angle);


protected:
  void initializeGL();
  void paintGL();
  void resizeGL(int width, int height);
  QSize minimumSizeHint() const;
  QSize SizeHint() const;
  void mouseMoveEvent(QMouseEvent *event);
  void mousePressEvent(QMouseEvent *event);

private:
  void set_gl();
  void draw_axes();
  void draw_surface ();

private:
  std::unique_ptr<surface> surf_ptr;
  surface *surf;

  int xRot = 0;
  int yRot = 0;
  int zRot = 0;

  double scale = 1.;
  QPoint lastPos;
  state st = the_func;
};

#endif // PAINTER_H
