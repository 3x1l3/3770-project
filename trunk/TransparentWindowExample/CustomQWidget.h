#ifndef CUSTOMQWIDGET
#define CUSTOMQWIDGET

#include <QLineEdit>
#include <QMessageBox>
#include <QtGui>

#include <iostream>

#include<QPushButton>

#include "MoveableWidget.h"

#include "WidgetManager.h"


class CustomQWidget : public QMainWindow {

  Q_OBJECT

public:

  CustomQWidget(QWidget *parent = 0): QMainWindow(parent) 
  {
    /////////////////////////////////////////////////////////
    //THIS IS THE CODE TO INITIALIZE THE WIDGET MANAGER AND USE IT
    
    QPushButton *button = new QPushButton("this is a button");
    QTextEdit * edit = new QTextEdit("this is a text edit");
    QLabel *label = new QLabel("this is a label");
    MoveableWidget *move = new MoveableWidget();
    
    
    QPushButton *button2 = new QPushButton("this is a button");
    QTextEdit * edit2 = new QTextEdit("this is a text edit");
    QLabel *label2 = new QLabel("this is a label");
    QWidget *layoutWidget = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(button2);
    layout->addWidget(edit2);
    layout->addWidget(label2);
    layoutWidget->setLayout(layout);
    
    WidgetManager *manager = new WidgetManager();
    manager->addNewWidget("blah Blah", 0, 0, 0.5, button);
    manager->addNewWidget("blah Blah", 0, 0, 0.9, edit);
    manager->addNewWidget("blah Blah", 0, 0, 0.7, label);
    manager->addNewWidget("blah Blah", 0, 0, 0.1, move);
    manager->addNewWidget("blah Blah", 0, 0, 0.3, layoutWidget);
    manager->addWidgetsToMainWindow(this);
    //END WIDGET MANAGER EXAMPLE
    //
  }
  
};

#endif

