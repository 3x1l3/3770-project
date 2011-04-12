#include "ControllerBar.h"


ControllerBar::ControllerBar(QWidget* parent): QWidget(parent)
{
  setMouseTracking(true);
  vertLay = new QVBoxLayout();
  QLabel *label = new QLabel("Hide/Show Widgets");
  QFont f( "Courrier", 8, QFont::Normal);
  label->setFont(f);
  label->setMouseTracking(true);
  vertLay->addWidget(label);
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
