#include <QApplication>

#include "mainwindow.h"

int main(int argc, char **argv) {

  QApplication app(argc, argv);
//  QMainWindow *topWindow = new QMainWindow();
  MainWindow *window = new MainWindow();
  
  window->show();
  window->setMouseTracking(true);
  return app.exec();
}