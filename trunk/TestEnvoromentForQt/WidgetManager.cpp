

#include "WidgetManager.h"


WidgetManager::WidgetManager(QMainWindow *parent)
{
  this->parent = parent;
}
  
  void WidgetManager::addNewWidget(QString label, int features, int allowedDockableArea, float windowOpacity, QWidget* mainWidget)
  {
    
    DockableWidget *dock = new DockableWidget();
    dock->setWindowTitle(label);
    
    QWidget *titlebar = new QWidget();
    dock->setTitleBarWidget(titlebar);


    if(features == 0)
    {
      dock->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
    }
    if(allowedDockableArea == 0)
    {
      dock->setAllowedAreas(Qt::NoDockWidgetArea);
    }
    
    dock->setWindowOpacity(windowOpacity);
    
    dock->setWidget(mainWidget);
    
    dockWidgets.push_back(dock);
  }

  void WidgetManager::drawWidgets()
  {
    for (int i = 0; i < dockWidgets.size(); i ++)
    {
      this->parent->addDockWidget(Qt::TopDockWidgetArea, dockWidgets[i]);
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
