

#include "WidgetManager.h"


WidgetManager::WidgetManager(QMainWindow *parent)
{
  this->parent = parent;
}
  
  void WidgetManager::addNewWidget(QString label, int features, int allowedDockableArea, float windowOpacity, QWidget* mainWidget)
  {
    DockableWidget *dock = new DockableWidget();
    dock->setWindowTitle(label);
    
    if(features == 0)
    {
      dock->setMovable(true);
      dock->setFloatable(true);
    }
    if(allowedDockableArea == 0)
    {
      dock->setAllowedAreas(Qt::NoToolBarArea);
    }
    
    dock->setWindowOpacity(windowOpacity);
    
    dock->addWidget(mainWidget);
    
    dock->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    
    dockWidgets.push_back(dock);
  }
  void WidgetManager::drawWidgets()
  {
    int right = 0;
    for (int i = 0; i < dockWidgets.size(); i ++)
    {
      dockWidgets[i]->move(right, 400);
      this->parent->addToolBar(Qt::TopToolBarArea, dockWidgets[i]);
      right += 65;
      dockWidgets[i]->hide();
    }
  }


  void WidgetManager::toggleTransparency(bool onOff)
  {

    for (int i = 0; i < dockWidgets.size(); i ++)
    {
      dockWidgets[i]->setInvisible(onOff);
    }
      
  }
