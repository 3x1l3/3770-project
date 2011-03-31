

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
    
//     dock->show();
    
    dock->move(400, 600);
    
    dockWidgets.push_back(dock);
  }
  void WidgetManager::drawWidgets()
  {
    for (int i = 0; i < dockWidgets.size(); i ++)
    {
      this->parent->addToolBar(Qt::TopToolBarArea, dockWidgets[i]);
      
      //this is for trying to get the widgets to undock when the program starts,
      //but so far no progress.
      dockWidgets[i]->emitUndock();
      

    }
  }


  void WidgetManager::toggleTransparency(bool onOff)
  {
    if(onOff == true)
    {
      for (int i = 0; i < dockWidgets.size(); i ++)
      {
	dockWidgets[i]->setInvisible(onOff);
      }
    }
    else
    {
      for (int i = 0; i < dockWidgets.size(); i ++)
      {
	dockWidgets[i]->setInvisible(onOff);
      }
    }
      
  }
