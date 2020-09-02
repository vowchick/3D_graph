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
#include "mainwindow.h"
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

   MainWindow *window = new MainWindow;
   QMenuBar *tool_bar = new QMenuBar (window);
   Window *graph_area = new Window (&pol, n, in.p, in.eps, in.k - 1, window);
   QAction *action;

   action = tool_bar->addAction ("&Double n", graph_area, SLOT (double_n ()));
   action->setShortcut (QString ("4"));

   action = tool_bar->addAction ("&Undouble n", graph_area, SLOT (undouble_n ()));
   action->setShortcut (QString ("5"));

   action = tool_bar->addAction ("&Change function", graph_area, SLOT (change_function ()));
   action->setShortcut (QString ("0"));

   action = tool_bar->addAction ("&Change state", graph_area, SLOT (change_state ()));
   action->setShortcut (QString ("1"));

   tool_bar->setMaximumHeight (30);

   window->setMenuBar (tool_bar);
   window->setCentralWidget (graph_area);
   window->setWindowTitle ("Graph");
   window->show ();
   app.exec ();
   delete window;


  return 0;
}
