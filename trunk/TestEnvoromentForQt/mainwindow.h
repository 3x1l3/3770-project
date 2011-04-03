#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QWidget>
#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xresource.h>
#include <QTimer>

#include "ToolbarManager.h"

#include "BannerWidget.h"
#include "dockwidget.h"
#include "photos.h"
#include "docktextedit.h"

#include "photos.h"


class MainWindow : public QMainWindow {

  Q_OBJECT
    QWidget* Q3MainWindow;
  
public:

  MainWindow(QWidget *parent=0);
  
public slots:
  
  void myhide();
  void myshow();
  
private slots:
  void setTransparency();
  void sendNotification();

signals:
  void sendOutMouseXY(int x, int y);
  
protected:
  void timerEvent(QTimerEvent *event);
  int x, y;
  bool underClick;

private:
  QRegion* fullArea;
  QRegion* noArea;

  void paintEvent(QPaintEvent *);
  void mouseMoveEvent(QMouseEvent *);
  QPoint pos;
  
  QTimer *timer;
  
  ToolbarManager *manager;

};

#endif
