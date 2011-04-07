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
#include <stdlib.h>
#include <calc/calc.h>
#include <QSlider>

#include <QFile>


#include "ToolbarManager.h"

#include "BannerWidget.h"
#include "dockwidget.h"
#include "photos.h"
#include "docktextedit.h"

#include "photos.h"

#include "digiclock/digitalClock.h"

#include "ControllerBar.h"


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
  void clickActivation(QSystemTrayIcon::ActivationReason);
  void activeTransparencyChange(int);
  void inactiveTransparencyChange(int);

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
  QIcon activeIcon;
  QIcon inactiveIcon;
  QSystemTrayIcon *tray;

  float activeOpacity;
  float inactiveOpacity;
  QSlider *activeSlider;
  QSlider *inactiveSlider;
  QLabel *inactiveLabel;
  QLabel *activeLabel;
  QWidget* leftcontext_menu;
  QVBoxLayout* leftcontext_menulayout;
  

  
  void openSettings();
  void saveSettings();

    void leftcontextSwitch();
  
  QFile *settingsFile;
  void close();

};

#endif
