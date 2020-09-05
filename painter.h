#ifndef PAINTER_H
#define PAINTER_H

#include "surface.h"
#include "QMouseEvent"
#define COEFF 1.2
#define COEFF2 2

class painter : public QGLWidget
{
public:
  painter(grid *gr, std::function<double (double, double)> f, QWidget *parent = nullptr);
 ~painter ();
  void set_approx (std::vector<double> f_coeffs);
  void update_surface (std::unique_ptr<grid> &grid_ptr);
  void set_f (std::function<double (double, double)> f);
  void change_state ();
  void update_surface_coeffs ();
  double get_fabs_max ();
  void increase ();
  void decrease ();

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
  void wheelEvent(QWheelEvent* pe);

private:
  void set_gl();
  void draw_axes();
  void draw_surface ();
  void scale_inc ();
  void scale_dec ();

private:
  std::unique_ptr<surface> surf_ptr;
  surface *surf;

  int xRot = 0;
  int yRot = 0;
  int zRot = 0;

  double scale = 1.;
  QPoint lastPos;
};

#endif // PAINTER_H
