#ifndef WIDGETMANAGER
#define WIDGETMANAGER

#include <QLineEdit>
#include <QMessageBox>
#include <QtGui>

#include <iostream>

#include<QPushButton>

#include "TransparentToolbar.h"

class ToolbarManager {


public:

  ToolbarManager(QMainWindow *parent); 
  void addNewToolbar(QString label, int features, int allowedDockableArea, float windowOpacity, QWidget* mainWindow);
  void drawToolbars();
  
  int initXPos;
  int initYPos;
  
  QList<QToolBar *> toolbars;

protected:


  QMainWindow *parent;
  
  
public slots:
  void toggleTransparency(bool);
    QVector<TransparentToolbar*> toolbarWidgets;
    
    

};

#endif

