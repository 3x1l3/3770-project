#include "digitalClock.h"
#include <QPainter>

using namespace std;

digitalClock::digitalClock(QWidget *parent) : QWidget(parent)
{
  this->setMaximumSize(190,70);
  this->setMinimumSize(190,70);
  
  this->setWindowTitle("Digi Clock");
  
  clockFont = new QFont("Impact",35,1,false);

  startTimer(1000);
}


digitalClock::~digitalClock()
{

}

void digitalClock::mouseMoveEvent(QMouseEvent* event)
{
    QWidget::mouseMoveEvent(event);
    
    x = event->x();
    y = event->y();
}

void digitalClock::paintEvent(QPaintEvent* event)
{
  QWidget::paintEvent(event);
  QPainter *painter = new QPainter(this);
  
  painter->setPen(Qt::black);
  painter->setBrush(Qt::black);
  painter->drawRect(0,0,width(),height());
  
  painter->setBrush(Qt::green);
  painter->setPen(Qt::green);
  
  painter->setFont(*clockFont);

  painter->drawText(20,50,QTime::currentTime().toString("hh:mm AP"));

}

void digitalClock::timerEvent(QTimerEvent* event)
{
  update();
}
