#ifndef WIDGETMANAGER
#define WIDGETMANAGER

#include <QLineEdit>
#include <QMessageBox>
#include <QtGui>

#include <iostream>

#include<QPushButton>

#include "DockableWidget.h"

class WidgetManager {


public:

  WidgetManager(QMainWindow *parent); 
  void addNewWidget(QString label, int features, int allowedDockableArea, float windowOpacity, QWidget* mainWindow);
  void drawWidgets();
  

protected:


  
  QMainWindow *parent;
  
public slots:
  void toggleTransparency(bool);
    QVector<DockableWidget*> dockWidgets;

};

#endif

