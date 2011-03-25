
#include "MoveableWidget.h"




MoveableWidget::MoveableWidget(QWidget *parent): QWidget(parent)
{
  clickLocation = QPoint(0,0);
  mouseDown = false;
  banner = QRectF(2,2,40,5);
  mouseClickOverBanner = false;
  
  
}
  
void MoveableWidget::mousePressEvent(QMouseEvent *event)
{
  mouseDown = true;
  clickLocation = event->pos();
  if(banner.contains(clickLocation) == true)
  {
    mouseClickOverBanner = true;
    std::cout<<"true"<<std::endl;
  }
  else
  {
    mouseClickOverBanner = false;
    std::cout<<"false"<<std::endl;
    std::cout<<"x"<<clickLocation.x()<<std::endl;
    std::cout<<"y"<<clickLocation.y()<<std::endl;
    
  }
  
}

void MoveableWidget::mouseMoveEvent(QMouseEvent *event)
{
  QWidget::mouseMoveEvent(event);
  if(mouseDown == true && mouseClickOverBanner == true)
  {
    banner = QRect(event->x(), event->y(), 40, 5);
    
  }
  
  if(mouseDown == true)
  {
    emit widgetClicked(event->x(), event->y());
  }
  
  this->update();
}
void MoveableWidget::mouseReleaseEvent(QMouseEvent * event)
{
  mouseDown = false;
}

void MoveableWidget::paintEvent(QPaintEvent *event)
{
  QPainter painter(this);
    
  painter.setBrush( QBrush (Qt::red) );
  painter.setPen  ( QPen   (Qt::red) );
  
  
  painter.drawRect(banner);
  
}