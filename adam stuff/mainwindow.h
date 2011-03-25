#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QWidget>
#include <X11/X.h>

class QLabel;
class PasswordEdit;
class QPushButton;

class MainWindow : public QMainWindow {

  Q_OBJECT
  
public:

  MainWindow(QWidget *parent=0);
  
private slots:

  void showPassword();
  void setTransparency();
  
private:
  
  QLabel *label;
  PasswordEdit *password;
  QPushButton *button;
  QRegion *noArea;
  QRegion *fullArea;
  QPushButton *makeTrans;
  
protected:
  void mousePressEvent(QMouseEvent *event);
  void mouseReleaseEvent(QMouseEvent *event);
  void mouseMoveEvent(QMouseEvent *event);
  void paintEvent(QPaintEvent *event);
  bool x11Event(XEvent * event);
  
  void timerEvent(QTimerEvent *event);

  
  
  
  int x, y;
  QPoint pos;
  bool underClick;
  bool fired;

};

#endif
