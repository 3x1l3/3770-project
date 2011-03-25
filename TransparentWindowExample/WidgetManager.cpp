

#include "WidgetManager.h"


WidgetManager::WidgetManager()
{
    /////////////////////////////////////////////////////////
    //setCentralWidget(new QMainWindow());
//     QDockWidget *dock = new QDockWidget(tr("Test"));
//     dock->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
//     dock->setAllowedAreas(Qt::NoDockWidgetArea);
//     
//     dock->setWindowOpacity(0.5);
    
    
//     QPushButton *button = new QPushButton(dock);
//     button->setFixedSize(50,50);
//     QPushButton *button2 = new QPushButton(dock);
//     button2->setFixedSize(50,50);
//     
//     QWidget *fuck = new QWidget(dock);
//     fuck->setFixedSize(60,60);
//     QVBoxLayout *layout = new QVBoxLayout();
    //layout->addWidget(button);
    //layout->addWidget(button2);
    //fuck->setLayout(layout);
    
    //dock->setWidget(fuck);
//     addDockWidget(Qt::TopDockWidgetArea, dock);
    
    /////////////////////////////////////////////////////////
    
//     dock = new QDockWidget(tr("Test"), this);
//     dock->setAllowedAreas(Qt::NoDockWidgetArea);
//     button = new QPushButton(dock);
//     dock->setWidget(button);
//     addDockWidget(Qt::TopDockWidgetArea, dock);
    

    
  }
  
  void WidgetManager::addNewWidget(QString label, int features, int allowedDockableArea, float windowOpacity, QWidget* mainWidget)
  {
    
    QDockWidget *dock = new QDockWidget("NOT WORKING YET");
    
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
  void WidgetManager::addWidgetsToMainWindow(QMainWindow* parent)
  {
    for (int i = 0; i < dockWidgets.size(); i ++)
    {
      parent->addDockWidget(Qt::TopDockWidgetArea, dockWidgets[i]);
    }
  }

