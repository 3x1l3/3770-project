#include "DockableWidget.h"
#include <QtGui>
#include <iostream>
using namespace std;

DockableWidget::DockableWidget( QWidget * parent) : QDockWidget( parent )
{
  isInvisible = false;
  
  setMouseTracking(true);
  fullArea = new QRegion(0, 0, QWidget::width(), QWidget::height(),QRegion::Rectangle);
  noArea = new QRegion(15,15,50,50, QRegion::Rectangle);
}

DockableWidget::DockableWidget( QString label) : QDockWidget( label )
{
  isInvisible = false;
  
  setMouseTracking(true);
  fullArea = new QRegion(0, 0, QWidget::width(), QWidget::height(),QRegion::Rectangle);
  noArea = new QRegion(15,15,50,50, QRegion::Rectangle);
}

DockableWidget::~DockableWidget()
{

}





void DockableWidget::setInvisible(bool setter)
{
  isInvisible = setter;
}

void DockableWidget::leaveEvent(QEvent* event)
{
  //QDockWidget::leaveEvent(event);
  //setMask(*fullArea);
  
}

void DockableWidget::mouseMoveEvent(QMouseEvent * event)
{
 QDockWidget::mouseMoveEvent(event); 
 
 x = event->x();
 y = event->y();
 update();
  
}

void DockableWidget::paintEvent(QPaintEvent *event)
{
  QDockWidget::paintEvent(event);
  QPainter painter(this);
    
  QPolygon myPolygon = QPolygon::QPolygon(QRect(0,0,QDockWidget::width(),QDockWidget::height()));
  QPolygon mousePolygon = QPolygon::QPolygon(QRect(x-10, y-10, 20, 20));
  
  myPolygon = myPolygon.subtracted(mousePolygon);
  //cout << x << " " << y << " " << isInvisible << " " << true << " " << underMouse() <<  endl;
  *noArea = QRegion(myPolygon,Qt::OddEvenFill );
  *fullArea = QRegion(QRect(0,0,QDockWidget::width(), QDockWidget::height()));
  
  if(isInvisible == true && underMouse() == true)
  {
    //cout << "\nIS UNDER MOUSE\n";
        setMask(*noArea);
  }

}