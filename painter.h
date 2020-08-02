#ifndef PAINTER_H
#define PAINTER_H

#include <QObject>
#include <QWidget>
#include <QGLWidget>
#include "surface.h"

class painter : public QGLWidget
{
public:
  painter(grid *gr, std::function<double (double, double)> f, QWidget *parent = nullptr);
 ~painter ();
protected:
  void initializeGL() {};
  void paintGL() {};
  void resizeGL(int width, int height) {FIX_UNUSED(width, height);};

private:
  std::unique_ptr<surface> surf;

  int xRot = 0;
  int yRot = 0;
  int zRot = 0;

  double width = 0.;
  double height = 0.;
  double depth = 0.;

  double scale = 1.;
};

#endif // PAINTER_H
