#include <QApplication>
#include <QtGui>


#include <iostream>

#include "CustomQWidget.h"

#include <QRegion>

#include <QTime>

#include "MoveableWidget.h"

#include "WidgetManager.h"





int main(int argc, char **argv) {

  QApplication app(argc, argv);

  CustomQWidget *widget = new CustomQWidget();
  
  MoveableWidget *move = new MoveableWidget();
  MoveableWidget *move2 = new MoveableWidget();
  
/*  
  /////////////////////////////COrRECT TRANSPARENCY CODE
     widget->setWindowOpacity(1);
     widget->setStyleSheet("background:transparent");
     widget->setAttribute(Qt::WA_TranslucentBackground);
     widget->setWindowFlags(Qt::FramelessWindowHint);
     widget->setWindowFlags(Qt::WindowStaysOnTopHint );//| Qt::Tool);//-> Takes away minimiz/maximize
  ///////////////////////////////COrRECT TRANSPARENCY CODE*/
  
  
  QVBoxLayout * layout = new QVBoxLayout();
  layout->addWidget(move);
  layout->addWidget(move2);
  
  widget->setMinimumHeight(100);
  widget->setMinimumWidth(800);
  
  widget->move(0,0);
  widget->setLayout(layout);
  widget->show();

    
    

  return app.exec();

  
  
  
  

}

