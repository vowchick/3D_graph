#include <stdio.h>
#include <stdlib.h>
#include <memory>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QAction>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QMessageBox>
#include "system_builder.h"
#include "system_solver.h"
#include "helper_functions.h"
#include "io.h"
#include "window.h"

int main (int argc, char *argv[])
{
  QApplication app (argc, argv);

  if (argc != 7)
    {
      QMessageBox::warning (0, "Wrong input arguments!",
                                  "Wrong input arguments!");
      printf ("usage ./a.out a.txt nx ny k eps p\n");
      return -1;
    }
  input in;
  polygon pol;
  int res = process_input (argv, in, pol);
  if (res < 0)
    {
      printf ("Couldn't init\n");
      return -1;
    }

  print_polygon(pol);

  int n = in.nx + 1;

  QMainWindow *window = new QMainWindow;
   QMenuBar *tool_bar = new QMenuBar (window);
   Window *graph_area = new Window (&pol, n, in.p, in.eps, in.k - 1, window);
   QAction *action;

   action = tool_bar->addAction ("&Double n", graph_area, SLOT (double_n ()));
   action->setShortcut (QString ("4"));

   action = tool_bar->addAction ("&Undouble n", graph_area, SLOT (undouble_n ()));
   action->setShortcut (QString ("5"));

   action = tool_bar->addAction ("&Change function", graph_area, SLOT (change_function ()));
   action->setShortcut (QString ("0"));

   tool_bar->setMaximumHeight (30);

   window->setMenuBar (tool_bar);
   window->setCentralWidget (graph_area);
   window->setWindowTitle ("Graph");
   window->show ();
   app.exec ();
   delete window;

  /*pthread_barrier_t barrier;
  pthread_t tid;
  pthread_barrier_init (&barrier, NULL, in.p);

  thread_info *info = new thread_info [in.p];
  grid *gr = new grid (&pol, n);
  int alloc_size = allocation_size (n);

  double *matrix = new double [alloc_size];
  int *I = new int [alloc_size];
  double *rhs = new double [4 * (n * n - n)];
  double *x = new double [4 * (n * n - n)];
  double *u = new double [4 * (n * n - n)];
  double *r = new double [4 * (n * n - n)];
  double *v = new double [4 * (n * n - n)];
  for (int i = 0; i < 4 * (n * n - n); i++)
    {
      x[i] = 0.;
      r[i] = 0.;
      v[i] = 0.;
      u[i] = 0.;
    }
  double *buf = new double [in.p];
  system_builder *builder = new system_builder (gr, func, matrix, rhs, I);
  system_solver *solver = new system_solver (matrix, I, x, rhs,
                                             4 * (n * n - n),
                                             u, r, v, buf,
                                             &barrier, in.p, in.eps);

  for (int i = 0; i < in.p; i++)
    {
      info[i].n = n;
      info[i].idx = i;
      info[i].f = func;
      info[i].eps = in.eps;
      info[i].barrier = &barrier;
      info[i].solver = solver;
      info[i].builder = builder;
      info[i].p = in.p;
    }

  for (int i = 1; i < in.p; i++)
    {
      if (pthread_create (&tid, 0, pthread_func, info + i))
        {
          fprintf (stderr, "cannot create thread #%d!\n", i);
          abort ();
        }
    }
  pthread_func (info + 0);
  pthread_barrier_destroy(&barrier);

  delete builder;
  delete gr;
  delete []info;
  delete []matrix;
  delete []x;
  delete []rhs;
  delete []I;
  delete []u;
  delete []r;
  delete []v;
  delete []buf;*/
  return 0;
}
