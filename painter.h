#ifndef PAINTER_H
#define PAINTER_H

#include <QObject>
#include <QWidget>
#include <QGLWidget>
#include "surface.h"
#include "QMouseEvent"

class painter : public QGLWidget
{
public:
  painter(grid *gr, std::function<double (double, double)> f, QWidget *parent = nullptr);
 ~painter ();

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

private:
  std::unique_ptr<surface> surf_ptr;
  surface *surf;

  int xRot = 0;
  int yRot = 0;
  int zRot = 0;

  double width = 0.;
  double height = 0.;
  double depth = 0.;

  double scale = 1.;
  QPoint lastPos;
};

#endif // PAINTER_H
