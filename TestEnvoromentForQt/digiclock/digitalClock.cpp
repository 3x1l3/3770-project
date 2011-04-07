#include "digitalClock.h"
#include <QPainter>
#include <QColorDialog>

using namespace std;

digitalClock::digitalClock(QWidget *parent) : QWidget(parent)
{
  this->setMaximumSize(170,50);
  this->setMinimumSize(170,50);
  
  this->setWindowTitle("Digi Clock");
  
  clockFont = new QFont("Impact",25,1,false);
  this->setMouseTracking(true);

  startTimer(1000);
  
  currentColor = Qt::green;
  
  setContextMenuPolicy(Qt::CustomContextMenu);
  
  connect(this, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(showContextMenu(const QPoint &)));
    
  openEditWindowAction = new QAction("&Settings", this);
  openEditWindowAction->setStatusTip("Opens the settings for this widget");
  connect (openEditWindowAction, SIGNAL(triggered()), this, SLOT(openEditWindow()));
}


digitalClock::~digitalClock()
{

}

void digitalClock::mousePressEvent(QMouseEvent *event)
{
  if(event->button() == Qt::RightButton)
  {
    emit customContextMenuRequested(event->pos());
  }
}

void digitalClock::showContextMenu(const QPoint &pos) {
    QMenu *menu = new QMenu;
    menu->addAction(openEditWindowAction);
    menu->exec(mapToGlobal(pos));
}

void digitalClock::openEditWindow()
{
  QColorDialog *chooseColor = new QColorDialog();
  chooseColor->setCurrentColor(1);
  chooseColor->exec();
  if(chooseColor->result() == QDialog::Accepted)
  {
    currentColor = chooseColor->currentColor();
    update();  
  }
  else if (chooseColor->result() == QDialog::Rejected)
  {
    update();
  }
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
  
  painter->setBrush(currentColor);
  painter->setPen(currentColor);
  
  painter->setFont(*clockFont);


  painter->drawText(10,37,QTime::currentTime().toString("hh:mm AP"));

}

void digitalClock::timerEvent(QTimerEvent* event)
{
  update();
}
