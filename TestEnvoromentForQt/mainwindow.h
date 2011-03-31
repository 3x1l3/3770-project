#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QWidget>
#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xresource.h>


#include "WidgetManager.h"

#include "BannerWidget.h"



class QLabel;
class PasswordEdit;
class QPushButton;

class MainWindow : public QMainWindow {

  Q_OBJECT
    QWidget* Q3MainWindow;
  
public:

  MainWindow(QWidget *parent=0);
  
private slots:

  void showPassword();
  void setTransparency();
  
signals:
  void setTransparencyOnWidgets();
  void sendOutMouseXY(int x, int y);
  
private:
  
  QLabel *label;
  PasswordEdit *password;
  QPushButton *button;
  QRegion *noArea;
  QRegion *fullArea;
  QPushButton *makeTrans;
  void setupAreas(QRegion* fullArea, QRegion* noArea);
  
protected:
  void mousePressEvent(QMouseEvent *event);
  void mouseReleaseEvent(QMouseEvent *event);
  void mouseMoveEvent(QMouseEvent *event);
  void paintEvent(QPaintEvent *event);
  bool x11Event(XEvent * event);
  
  void timerEvent(QTimerEvent *event);

  int x, y;
  int height, width;
  QPoint pos;
  bool underClick;
  bool fired;
  
  WidgetManager *manager;

};

#endif
