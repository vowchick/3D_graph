#include "mainwindow.h"

MainWindow::MainWindow()
{

}
void
MainWindow::closeEvent(QCloseEvent *event)
{
  event->ignore ();
//  if (calculating)
//    event->ignore ();
//  else
//    {
//      for (int i = 0; i < threads_num; i++)
//        {
//          info[i].proceed = false;
//        }
//      p_out++;
//      pthread_cond_broadcast (&cond);
//      event->accept ();
//    }

}
