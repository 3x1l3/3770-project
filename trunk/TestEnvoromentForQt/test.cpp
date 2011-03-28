#include <QApplication>

#include "mainwindow.h"

int main(int argc, char **argv) {

  QApplication app(argc, argv);
  MainWindow *window = new MainWindow();
  
  window->show();
  window->setMouseTracking(true);
  return app.exec();
}