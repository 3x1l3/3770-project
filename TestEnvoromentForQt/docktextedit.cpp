#include "docktextedit.h"


DockTextEdit::DockTextEdit(QWidget* parent): QTextEdit(parent)
{
 
  isInvisible = false;
   isInvisible = true;
  setMouseTracking(true);
  fullArea = new QRegion(0, 0, width(), height(), QRegion::Rectangle);
  noArea = new QRegion(15,15,50,50, QRegion::Rectangle);

  
  
}


DockTextEdit::~DockTextEdit()
{

}


void DockTextEdit::leaveEvent(QEvent* event)
{
    QTextEdit::leaveEvent(event);
    setMask(*fullArea);
}

void DockTextEdit::mouseMoveEvent(QMouseEvent* event)
{ 
    if(isInvisible)
    {
      event->ignore();
    }
  
    QTextEdit::mouseMoveEvent(event);
    
    x = event->x();
    y = event->y();
    update();
}


void DockTextEdit::paintEvent(QPaintEvent* event)
{
    QTextEdit::paintEvent(event);
    
    //QPainter painter(this);
    
    QPolygon myPolygon = QPolygon::QPolygon(QRect(0,0,width(), height()));
    QPolygon mousePolygon = QPolygon::QPolygon(QRect(x, y, 3, 3));
    
    myPolygon = myPolygon.subtracted(mousePolygon);
  //   cout << x << " " << y << " " << isInvisible << " " << true << " " << underMouse() <<  endl;
    *noArea = QRegion(myPolygon,Qt::OddEvenFill );
    *fullArea = QRegion(QRect(0,0,width(),height()));
    
    if(isInvisible && underMouse())
    {
  //     cout << "\nIS UNDER MOUSE\n";
	  setMask(*noArea);
    }   
}

void DockTextEdit::setInvisible(bool setter)
{
  isInvisible = setter;
}

