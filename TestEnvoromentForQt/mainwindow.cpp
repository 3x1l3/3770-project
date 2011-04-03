#include "mainwindow.h"
#include "passwordedit.h"
#include <QDragLeaveEvent>

#include <QtGui>
#include <iostream>

using namespace std;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {

  timer = new QTimer();
  timer->setInterval(30000);
  timer->start();
  connect(timer, SIGNAL(timeout()), this, SLOT(sendNotification()));
  x = 0;
  y = 0;
  this->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
  this->setAttribute(Qt::WA_TranslucentBackground);
  startTimer(100); 
  this->setWindowOpacity(1);
  this->setMouseTracking(true);
  this->fullArea = new QRegion(0, 0, QMainWindow::width(), QMainWindow::height(), QRegion::Rectangle);
  this->noArea = new QRegion(15,15,50,50, QRegion::Rectangle);
  this->underClick = true;
  this->setFixedSize(1,1);

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
    manager->addNewToolbar("Notepad", 0, 0, 0.5, dockText);
    manager->drawToolbars();

    
    
    //Initial widget positioning
    manager->toolbarWidgets.at(0)->move( QApplication::desktop()->screenGeometry().right() - thing->width() , 39);
    manager->toolbarWidgets.at(1)->setMinimumWidth( QApplication::desktop()->screenGeometry().width() );
    	banner1->setMinimumWidth( QApplication::desktop()->screenGeometry().width() );
        manager->toolbarWidgets.at(1)->window()->setMinimumWidth( QApplication::desktop()->screenGeometry().width() );
	manager->toolbarWidgets.at(2)->move(0, 39);
    
	
    
    for (int i = 0; i < manager->toolbarWidgets.size();i ++)
    {
      connect(this, SIGNAL(sendOutMouseXY(int, int)), manager->toolbarWidgets[i], SLOT(recieveMouseXY(int, int)));
      manager->toolbarWidgets.at(i)->setWindowFlags(Qt::Window | Qt::FramelessWindowHint |Qt::X11BypassWindowManagerHint);
      manager->toolbarWidgets.at(i)->setAllowedAreas(Qt::NoToolBarArea);
      manager->toolbarWidgets.at(i)->show();
      manager->toolbarWidgets.at(1)->setMinimumHeight(300);
    }
 

    manager->toggleTransparency(true);
    underClick = true; 
    QMainWindow::hide();
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
    QMainWindow::show();
  for(int i = 0; i < manager->toolbarWidgets.size(); i++)
  {
    manager->toolbarWidgets.at(i)->show();
  }
  
  system("notify-send test \"Testing\" ");
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
    QMainWindow::timerEvent(event);
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

void MainWindow::paintEvent(QPaintEvent *event)
{
  QWidget::paintEvent(event);
  QPainter painter(this);
  pos = QCursor::pos();
  painter.setOpacity(1.0);

  QPolygon myPolygon = QPolygon::QPolygon(QRect(0,0,QMainWindow::width(), QMainWindow::height()));
  QPolygon mousePolygon = QPolygon::QPolygon(QRect(0, 1, QMainWindow::width(), QMainWindow::height()));



  myPolygon = myPolygon.subtracted(mousePolygon);

  *noArea = QRegion(myPolygon,Qt::OddEvenFill );
  *fullArea = QRegion(QRect(0, 0, QMainWindow::width(), QMainWindow::height()));

  if(underClick == true)
  {
        setMask(*noArea);
        this->setWindowOpacity(0.5);

  }
  else
  {
        setMask(*fullArea);
        this->setWindowOpacity(1.0);
  }


}

void MainWindow::mouseMoveEvent( QMouseEvent * event)
{
  QWidget::mouseMoveEvent(event);
  update();
  repaint();
}

void MainWindow::sendNotification()
{
  system("notify-send Alert \"You have a new email and/or message and/or phone call! *gasp*\" ");
}

