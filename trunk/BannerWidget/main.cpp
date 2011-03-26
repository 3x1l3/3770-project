#include <QApplication>
#include <QtGui>


#include <iostream>


#include <QRegion>

#include <QTime>

#include "BannerWidget.h"


int main(int argc, char **argv) {

  QApplication app(argc, argv);

  QWidget *widget = new QWidget();
  
  BannerWidget *banner = new BannerWidget();

  /*/////////////////////////////COrRECT TRANSPARENCY CODE
     widget->setWindowOpacity(1);
     widget->setStyleSheet("background:transparent");
     widget->setAttribute(Qt::WA_TranslucentBackground);
     widget->setWindowFlags(Qt::FramelessWindowHint);
     widget->setWindowFlags(Qt::WindowStaysOnTopHint );//| Qt::Tool);//-> Takes away minimiz/maximize
  ///////////////////////////////COrRECT TRANSPARENCY CODE*/
  
  
  QVBoxLayout * layout = new QVBoxLayout();
  layout->addWidget(banner);

  
//   widget->setMinimumHeight(100);
//   widget->setMinimumWidth(800);
  
  widget->move(0,0);
  widget->setLayout(layout);
  widget->show();

    
    

  return app.exec();

  
  
  
  

}

