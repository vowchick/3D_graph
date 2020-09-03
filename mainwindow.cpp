#include "mainwindow.h"

MainWindow::MainWindow()
{

}
void
MainWindow::closeEvent(QCloseEvent *event)
{
  window->closeEvent (event);
}
