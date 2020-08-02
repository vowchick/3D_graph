#ifndef PAINTER_H
#define PAINTER_H

#include <QObject>
#include <QWidget>
#include <QOpenGLWidget>
#include "grid.h"

class painter : public QOpenGLWidget
{
public:
  painter(grid *gr, std::function<double (double, double)> f, QWidget *parent = nullptr);
 ~painter ();
protected:
  void initializeGL() {};
  void paintGL() {};
  void resizeGL(int width, int height) {FIX_UNUSED(width, height);};

private:

};

#endif // PAINTER_H
