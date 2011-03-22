#include <QApplication>
#include <QtGui>

#include "bin_board.h"
#include "text_edit.h"
#include <iostream>

#include "CustomQWidget.h"

#include <QRegion>

#include <QTime>





int main(int argc, char **argv) {

  QApplication app(argc, argv);

  
  QTime *timer = new QTime(0,0,0,0);
  
  
  TextEdit *e = new TextEdit();
  bin_board *t = new bin_board();

  QObject::connect(t, SIGNAL(symbolEntered(Qt::Key)), e, SLOT(receiveSymbol(Qt::Key)));

  QVBoxLayout *layout = new QVBoxLayout(); 
  layout->addWidget(e);
  layout->addWidget(t);

  CustomQWidget *widget = new CustomQWidget();
  
  
  ///////////////////////////////COrRECT TRANSPARENCY CODE
     widget->setWindowOpacity(0.25);
     widget->setStyleSheet("background:transparent");
     widget->setAttribute(Qt::WA_TranslucentBackground);
     widget->setWindowFlags(Qt::FramelessWindowHint);
     widget->setWindowFlags(Qt::WindowStaysOnTopHint );//| Qt::Tool);//-> Takes away minimiz/maximize
  ///////////////////////////////COrRECT TRANSPARENCY CODE
  
  
  
  
  //widget->setFocusPolicy( Qt::NoFocus);
  
  //widget->setAttribute(Qt::WA_TransparentForMouseEvents);

  widget->setLayout(layout);

  widget->setMinimumHeight(100);
  widget->setMinimumWidth(800);
  
  widget->move(0,0);
  
//   widget->setWindowModality(Qt::WindowModal);
  
//     widget->show();
//     widget->showNormal();
//     widget->raise();
//     widget->activateWindow();
  
//     timer->start();
//     int elapsedTime;
    
//     while(true)
//     {
//       elapsedTime= timer->elapsed();
//     }
    
//     while((elapsedTime % 100) != 1)
//       widget->bringToFront();
//   
      widget->show();
    
    

  return app.exec();

  
  
  
  

}

