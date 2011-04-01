#include "dockwidget.h"


DockWidget::DockWidget(QWidget* parent): QWidget(parent)
{
  isInvisible = false;
  setMouseTracking(true);
  fullArea = new QRegion(0, 0, width(), height(), QRegion::Rectangle);
  noArea = new QRegion(15,15,50,50, QRegion::Rectangle);

}


DockWidget::~DockWidget()
{

}


void DockWidget::leaveEvent(QEvent* event)
{
    QWidget::leaveEvent(event);
    setMask(*fullArea);
}


void DockWidget::mouseMoveEvent(QMouseEvent* event)
{
    QWidget::mouseMoveEvent(event);
    
    x = event->x();
    y = event->y();
    update();
}


void DockWidget::paintEvent(QPaintEvent* event)
{
    QWidget::paintEvent(event);
    
    QPainter painter(this);
    
    QPolygon myPolygon = QPolygon::QPolygon(QRect(0,0,width(), height()));
    QPolygon mousePolygon = QPolygon::QPolygon(QRect(x, y, 3, 3));
    
    myPolygon = myPolygon.subtracted(mousePolygon);
  //   cout << x << " " << y << " " << isInvisible << " " << true << " " << underMouse() <<  endl;
    *noArea = QRegion(myPolygon,Qt::OddEvenFill );
    *fullArea = QRegion(QRect(0,0,width(),height()));
    
    if(isInvisible == true && underMouse() == true)
    {
  //     cout << "\nIS UNDER MOUSE\n";
	  setMask(*noArea);
    }
    
}

void DockWidget::setInvisible(bool setter)
{
  isInvisible = setter;
}



