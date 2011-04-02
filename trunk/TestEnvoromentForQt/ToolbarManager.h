#ifndef WIDGETMANAGER
#define WIDGETMANAGER

#include <QLineEdit>
#include <QMessageBox>
#include <QtGui>

#include <iostream>

#include<QPushButton>

#include "ToolbarManager.h"
#include "TransparentToolbar.h"

class ToolbarManager {


public:

  ToolbarManager(QMainWindow *parent); 
  void addNewToolbar(QString label, int features, int allowedDockableArea, float windowOpacity, QWidget* mainWindow);
  void drawToolbars();
  

protected:


  QMainWindow *parent;
  
  
public slots:
  void toggleTransparency(bool);
    QVector<TransparentToolbar*> toolbarWidgets;

};

#endif

