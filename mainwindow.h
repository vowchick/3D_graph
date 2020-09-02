#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets/QtWidgets>
class MainWindow : public QMainWindow
{
public:
  MainWindow();
  void closeEvent(QCloseEvent *event) override;
};

#endif // MAINWINDOW_H
