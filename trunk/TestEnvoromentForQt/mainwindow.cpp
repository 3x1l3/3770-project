#include "mainwindow.h"
#include "passwordedit.h"
#include <QDragLeaveEvent>

#include <QtGui>
#include <iostream>

using namespace std;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  underClick = false; 
  x = 0;
  y = 0;
  this->setWindowFlags(Qt::WindowStaysOnTopHint);
  startTimer(100); 

    /// Creating system tray icon and menu functionality ///
    QSystemTrayIcon *tray = new QSystemTrayIcon(QIcon(QPixmap("shutter.png")),this);
    QMenu *context_menu = new QMenu(this);
    QAction *exit = new QAction("Exit", this);
    exit->connect(exit, SIGNAL(triggered()), this, SLOT(close()));
    QAction *hide = new QAction("Hide", this);
    hide->connect(hide, SIGNAL(triggered()), this, SLOT(myhide()));
    QAction *show = new QAction("Show", this);
    show->connect(show, SIGNAL(triggered()), this, SLOT(myshow()) );
    //Action to toggle whether or not the application is 'active', i.e. accepts mouse events
    QAction *toggleActive = new QAction("Toggle Active", this);
    toggleActive->connect(toggleActive, SIGNAL(triggered()), this, SLOT(setTransparency()));
    

    context_menu->addAction(show);
    context_menu->addAction(hide);
    context_menu->addSeparator();
    context_menu->addAction(toggleActive);
    context_menu->addSeparator();
    context_menu->addAction(exit);
    
    tray->setContextMenu(context_menu);

    tray->show();

    //make widgets
    manager = new ToolbarManager(this);
    photos* thing = new photos();
    DockTextEdit* dockText = new DockTextEdit();
    BannerWidget *banner1 = new BannerWidget();

    //set Properties
    banner1->setMouseTracking(true);
    thing->setMinimumSize(300, 300);

    //Add to manager
    manager->addNewToolbar("test", 0, 0, 0.5, thing);
    manager->addNewToolbar("scrollin'", 0, 0, 0.5, banner1);
    manager->addNewToolbar("damn", 0, 0, 0.5, dockText);
    manager->drawToolbars();
    
    
    for (int i = 0; i < manager->toolbarWidgets.size();i ++)
    {
      connect(this, SIGNAL(sendOutMouseXY(int, int)), manager->toolbarWidgets[i], SLOT(recieveMouseXY(int, int)));
      manager->toolbarWidgets.at(i)->setWindowFlags(Qt::Window | Qt::FramelessWindowHint |Qt::X11BypassWindowManagerHint);
      manager->toolbarWidgets.at(i)->setAllowedAreas(Qt::NoToolBarArea);
      manager->toolbarWidgets.at(i)->show();
    }

    this->hide();

}

void MainWindow::myhide()
{

  for(int i = 0; i < manager->toolbarWidgets.size(); i++)
  {
    manager->toolbarWidgets.at(i)->hide();
  }
  QMainWindow::hide();
}

void MainWindow::myshow()
{

  for(int i = 0; i < manager->toolbarWidgets.size(); i++)
  {
    manager->toolbarWidgets.at(i)->show();
  }
}






void MainWindow::setTransparency()
{
  underClick = !underClick;
  if(underClick)
  {
    manager->toggleTransparency(true);
  }
  else
  {
    manager->toggleTransparency(false);
  }
  update();
}

void MainWindow::timerEvent(QTimerEvent * event)
{
  //emit the signla here with the global x and y mouse coordinates
  Display *d;
  Window inwin;      /* root window the pointer is in */
  Window inchildwin; /* child win the pointer is in */
  int rootx, rooty; /* relative to the "root" window; we are not interested in these,
                       but we can't pass NULL */
  int childx, childy;  /* the values we are interested in */
  Atom atom_type_prop; /* not interested */
  int actual_format;   /* should be 32 after the call */
  unsigned int mask;   /* status of the buttons */
  unsigned long n_items, bytes_after_ret;
  Window *props; /* since we are interested just in the first value, which is
		    a Window id */
 
  /* default DISPLAY */
  d = XOpenDisplay(NULL); 
 
  /* ask for active window (no error check); the client must be freedesktop
     compliant */
  (void)XGetWindowProperty(d, DefaultRootWindow(d),
			   XInternAtom(d, "_NET_ACTIVE_WINDOW", True),
			   0, 1, False, AnyPropertyType,
			   &atom_type_prop, &actual_format,
			   &n_items, &bytes_after_ret, (unsigned char**)&props);

  XQueryPointer(d, props[0], &inwin,  &inchildwin,
		&rootx, &rooty, &childx, &childy, &mask);

 	//printf("relative to active window: %d,%d\n", rootx, rooty);

  XFree(props);           /* free mem */
  (void)XCloseDisplay(d); /* and close the display */
  
  
  //cout<<rootx<<" "<<rooty<<endl;
  this->x = rootx;
  this->y = rooty;
  emit this->sendOutMouseXY(rootx,rooty);
  
}
