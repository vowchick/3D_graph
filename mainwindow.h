#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets/QtWidgets>
#include "window.h"
class MainWindow : public QMainWindow
{
public:
  MainWindow();
  void closeEvent(QCloseEvent *event) override;
  void set_window (Window *window) {this->window = window;}
private:
  Window *window;
};

#endif // MAINWINDOW_H
