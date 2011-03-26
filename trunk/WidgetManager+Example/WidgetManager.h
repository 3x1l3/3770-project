#ifndef WIDGETMANAGER
#define WIDGETMANAGER

#include <QLineEdit>
#include <QMessageBox>
#include <QtGui>

#include <iostream>

#include<QPushButton>



class WidgetManager {

  //Q_OBJECT

public:

  WidgetManager(); 
  void addNewWidget(QString label, int features, int allowedDockableArea, float windowOpacity, QWidget* mainWindow);
  void addWidgetsToMainWindow(QMainWindow* parent);
  

protected:

  QVector<QDockWidget*> dockWidgets;

};

#endif

