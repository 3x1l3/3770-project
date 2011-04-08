#include "TransparentToolbar.h"

using namespace std;

TransparentToolbar::TransparentToolbar( QWidget * parent) : QToolBar( parent )
{
  isInvisible = false;
  
  setMouseTracking(true);
  fullArea = new QRegion(0, 0, QWidget::width(), QWidget::height(),QRegion::Rectangle);
  noArea = new QRegion(15,15,50,50, QRegion::Rectangle);
  width = 100;
  height = 100;
  
  hidden = false;
}

TransparentToolbar::TransparentToolbar( QString label) : QToolBar( label )
{
  isInvisible = false;
  
  setMouseTracking(true);
  fullArea = new QRegion(0, 0, QWidget::width(), QWidget::height(),QRegion::Rectangle);
  noArea = new QRegion(15,15,50,50, QRegion::Rectangle);
  
  hidden = false;
}

TransparentToolbar::~TransparentToolbar()
{

}





void TransparentToolbar::setInvisible(bool setter)
{
  isInvisible = setter;
}

void TransparentToolbar::leaveEvent(QEvent* event)
{
  //QDockWidget::leaveEvent(event);
  //setMask(*fullArea);
  
}

void TransparentToolbar::mouseMoveEvent(QMouseEvent * event)
{
 QToolBar::mouseMoveEvent(event); 
 
 x = event->x();
 y = event->y();
 update();
  
}

void TransparentToolbar::paintEvent(QPaintEvent *event)
{
  QToolBar::paintEvent(event);
  QPainter painter(this);
    
  QPolygon myPolygon = QPolygon::QPolygon(QRect(0,0,QToolBar::width(),QToolBar::height()));
  QPolygon mousePolygon = QPolygon::QPolygon(QRect(x, y, 1, 1));
  
  myPolygon = myPolygon.subtracted(mousePolygon);

  *noArea = QRegion(myPolygon,Qt::OddEvenFill );
  *fullArea = QRegion(QRect(0,0,QToolBar::width(), QToolBar::height()));
  
  if(isInvisible == true && underMouse() == true)
  {
        setMask(*noArea);
  }

}

void TransparentToolbar::recieveMouseXY(int x, int y)
{
  this->x = x;
  this->y = y;
  update();
  adjustSize();
  updateGeometry();
}

void TransparentToolbar::DropEvent(QDropEvent* event)
{
  QWidget::dropEvent(event);
  setWindowFlags(Qt::X11BypassWindowManagerHint);
}

int TransparentToolbar::GetHeight()
{
  return height;
}

int TransparentToolbar::GetWidth()
{
  return width;
}

void TransparentToolbar::SetHeight(int h)
{
  height = h;
}

void TransparentToolbar::SetWidth(int w)
{
  width = w;
}

void TransparentToolbar::toggleHidden()
{
  hidden = !hidden;
  if(hidden)
  {
    this->hide();
  }
  else if (!hidden)
  {
    this->show();
  }
  repaint();
}

bool TransparentToolbar::CheckIfToolbarIsHidden()
{
  return hidden;
}



