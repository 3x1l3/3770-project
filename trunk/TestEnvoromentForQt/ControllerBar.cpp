#include "ControllerBar.h"


ControllerBar::ControllerBar(QWidget* parent): QWidget(parent)
{
  setMouseTracking(true);
  vertLay = new QVBoxLayout();
  this->setLayout(vertLay);
}


ControllerBar::~ControllerBar()
{

}

void ControllerBar::addControlPoint(QString windowTitle, TransparentToolbar *toolbarToConnectTo)
{
  QPushButton *but = new QPushButton(windowTitle);
  but->setMouseTracking(true);
  connect(but, SIGNAL(clicked()), toolbarToConnectTo, SLOT(toggleHidden()));
  controlButtons.push_back(but);
  vertLay->addWidget(but);
}
