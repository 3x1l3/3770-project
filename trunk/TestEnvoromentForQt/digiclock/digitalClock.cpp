#include "digitalClock.h"
#include <QPainter>

using namespace std;

digitalClock::digitalClock(QWidget *parent) : QWidget(parent)
{
  this->setMaximumSize(170,50);
  this->setMinimumSize(170,50);
  
  this->setWindowTitle("Digi Clock");
  
  clockFont = new QFont("Impact",25,1,false);
  this->setMouseTracking(true);

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

  painter->drawText(10,37,QTime::currentTime().toString("hh:mm AP"));

}

void digitalClock::timerEvent(QTimerEvent* event)
{
  update();
}
