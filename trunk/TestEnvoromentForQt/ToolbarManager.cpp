

#include "ToolbarManager.h"


ToolbarManager::ToolbarManager(QMainWindow *parent)
{
  this->parent = parent;
  toolbars.clear();
}
  
  void ToolbarManager::addNewToolbar(QString label, int features, int allowedDockableArea, float windowOpacity, QWidget* mainWidget)
  {
    //if we send in a parent to each tool bar here, we loos the individual opacity levels of each tool bar
    //becasue the opacity is derrived from the parent class window, which we dont even show anymore.
    //TransparentToolbar *toolbar = new TransparentToolbar(parent);
    TransparentToolbar *toolbar = new TransparentToolbar();
    toolbar->setWindowTitle(label);
    
    if(features == 0)
    {
      toolbar->setMovable(true);
      toolbar->setFloatable(true);
    }
    if(allowedDockableArea == 0)
    {
      toolbar->setAllowedAreas(Qt::NoToolBarArea);
    }
    
    
    
    toolbar->setWindowOpacity(windowOpacity);
    
    toolbar->addWidget(mainWidget);
    
    toolbar->setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::X11BypassWindowManagerHint);
    
    toolbarWidgets.push_back(toolbar);
  }
  void ToolbarManager::drawToolbars()
  {
    int right = 0;
    for (int i = 0; i < toolbarWidgets.size(); i ++)
    {
     // toolbarWidgets[i]->move(right, 400);
      this->parent->addToolBar(Qt::TopToolBarArea, toolbarWidgets[i]);
      
      right += 65;
      toolbarWidgets[i]->hide();
    }
    toolbars = this->parent->findChildren<QToolBar *>("");

  }


  void ToolbarManager::toggleTransparency(bool onOff)
  {

    for (int i = 0; i < toolbarWidgets.size(); i ++)
    {
      toolbarWidgets[i]->setInvisible(onOff);
    }
      
  }
