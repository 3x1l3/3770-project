#include "mainwindow.h"
#include "passwordedit.h"
#include <QDragLeaveEvent>


using namespace std;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  

    timer = new QTimer();
    timer->setInterval(30000);
    timer->start();
    connect(timer, SIGNAL(timeout()), this, SLOT(sendNotification()));
    this->x = 0;
    this->y = 0;
    this->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    startTimer(100); 
    this->setWindowOpacity(1);
    this->setMouseTracking(true);
    this->fullArea = new QRegion(0, 0, QMainWindow::width(), QMainWindow::height(), QRegion::Rectangle);
    this->noArea = new QRegion(15,15,50,50, QRegion::Rectangle);
    this->underClick = true;
    this->setFixedSize(1,1);
    this->activeOpacity = 0.6;
    this->inactiveOpacity = 0.3;

    /// Creating system tray icon and menu functionality ///
    activeIcon = QIcon(QPixmap("shutter.png"));
    inactiveIcon = QIcon(QPixmap("shutter_inactive.png"));
    tray = new QSystemTrayIcon(inactiveIcon,this);
    QMenu *context_menu = new QMenu(this);
    QAction *exit = new QAction("Exit", this);
    exit->connect(exit, SIGNAL(triggered()), this, SLOT(close()));
    QAction *hide = new QAction("Hide", this);
    hide->connect(hide, SIGNAL(triggered()), this, SLOT(myhide()));
    QAction *show = new QAction("Show", this);
    show->connect(show, SIGNAL(triggered()), this, SLOT(myshow()) );
    //Action to toggle whether or not the application is 'active', i.e. accepts mouse events
    QAction *toggleActive = new QAction("Active", this);
    toggleActive->setCheckable(true);
    toggleActive->connect(toggleActive, SIGNAL(triggered()), this, SLOT(setTransparency()));
    
    
    this->leftcontext_menu = new QWidget(this);
    this->leftcontext_menu->setWindowFlags(Qt::Popup);
    this->leftcontext_menulayout = new QVBoxLayout();
    this->activeSlider = new QSlider();
    this->inactiveSlider = new QSlider();
    this->inactiveLabel = new QLabel("Inactive");
    this->activeLabel = new QLabel("Active");
    this->activeSlider->setMaximum(100);
    this->activeSlider->setMinimum(0);
    this->activeSlider->setValue(this->activeOpacity*100);
    this->inactiveSlider->setMaximum(100);
    this->inactiveSlider->setMinimum(0);
    this->inactiveSlider->setValue(this->inactiveOpacity*100);

    this->leftcontext_menu->setLayout(this->leftcontext_menulayout);
    this->leftcontext_menulayout->addWidget(this->inactiveLabel);
    this->leftcontext_menulayout->addWidget(this->inactiveSlider);
    this->leftcontext_menulayout->addWidget(this->activeLabel);
    this->leftcontext_menulayout->addWidget(this->activeSlider);

    this->activeSlider->setVisible(false);
    this->activeLabel->setVisible(false);

    connect(tray, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(clickActivation(QSystemTrayIcon::ActivationReason)));

    connect(activeSlider, SIGNAL(valueChanged(int)), this, SLOT(activeTransparencyChange(int)));
    connect(inactiveSlider, SIGNAL(valueChanged(int)), this, SLOT(inactiveTransparencyChange(int)));

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
    photos* slideShow = new photos();
    DockTextEdit* dockText = new DockTextEdit();
    BannerWidget *banner1 = new BannerWidget();
    Calc *calc = new Calc();
    digitalClock *digiClock = new digitalClock();
    //for controlling the widgets on or off.
    //MAKE THIS THE LAST WIDGET ADDED TO THE TOOLBAR MANAGER ... OR ELSE!
    ControllerBar *controlBar = new ControllerBar();
    

    //set Properties
    banner1->setMouseTracking(true);

    //Add to manager
    manager->addNewToolbar("SlideShow", 0, 0, this->inactiveOpacity, slideShow);
    manager->addNewToolbar("Banner", 0, 0, this->inactiveOpacity, banner1);
    manager->addNewToolbar("Notepad", 0, 0, this->inactiveOpacity, dockText);
    manager->addNewToolbar("Calculator", 0, 0, this->inactiveOpacity, calc);
    manager->addNewToolbar("Clock", 0, 0, this->inactiveOpacity, digiClock);
    //CONTROL BAR MUST BE THE LAST WIDGET ADDED INTO OUR PROGRAM ... OR ELSE!!!
    manager->addNewToolbar("Controller", 0, 0, this->inactiveOpacity, controlBar);
    manager->drawToolbars();
    
    banner1->setMinimumWidth( QApplication::desktop()->screenGeometry().width() * 0.9 );


    
    
    for (int i = 0; i < manager->toolbarWidgets.size();i ++)
    {
      connect(this, SIGNAL(sendOutMouseXY(int, int)), manager->toolbarWidgets[i], SLOT(recieveMouseXY(int, int)));
      manager->toolbarWidgets.at(i)->setWindowFlags(Qt::Window | Qt::FramelessWindowHint |Qt::X11BypassWindowManagerHint);
      manager->toolbarWidgets.at(i)->setAllowedAreas(Qt::NoToolBarArea);
      manager->toolbarWidgets.at(i)->show();
      
      //this is so we dont add the toggler controller to itself.
      if(i<manager->toolbarWidgets.size()-1)
    	controlBar->addControlPoint(manager->toolbarWidgets[i]->windowTitle(), manager->toolbarWidgets[i]);
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
  update();
}

void MainWindow::myshow()
{
  QMainWindow::show();
  
  for(int i = 0; i < manager->toolbarWidgets.size(); i++)
  {
    if(manager->toolbarWidgets[i]->CheckIfToolbarIsHidden() != true)
    {
      manager->toolbarWidgets.at(i)->show();
    }
  }

  update();
}

void MainWindow::close()
{
  QMainWindow::close();
}


void MainWindow::setTransparency()
{
  underClick = !underClick;
  if(underClick)
  {
    manager->toggleTransparency(true);
    for(int i = 0; i < manager->toolbarWidgets.size(); i++)
    {
      manager->toolbarWidgets.at(i)->setWindowOpacity(this->inactiveOpacity);
    }
      this->tray->setIcon(inactiveIcon);

  }
  else
  {
    manager->toggleTransparency(false);
    for(int i = 0; i < manager->toolbarWidgets.size(); i++)
    {
      manager->toolbarWidgets.at(i)->setWindowOpacity(this->activeOpacity);
    }
    this->tray->setIcon(activeIcon);

  }
  
  
  this->leftcontextSwitch();

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



  XFree(props);           /* free mem */
  (void)XCloseDisplay(d); /* and close the display */
  
  
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
  system( "notify-send Alert \"You have a new email and/or message and or incoming call!\" ");
}

void MainWindow::clickActivation(QSystemTrayIcon::ActivationReason event) {
    
    if (event == QSystemTrayIcon::Trigger) 
    {
      this->leftcontext_menu->show();
    
      if(tray->geometry().y() > 50)
	this->leftcontext_menu->move(tray->geometry().x(), tray->geometry().y()-leftcontext_menu->geometry().height());
      
      else
	this->leftcontext_menu->move(tray->geometry().x(), tray->geometry().y()+tray->geometry().height());


    }
}

void MainWindow::activeTransparencyChange(int value) {
    this->activeOpacity = (float)value/100;

    if (!this->underClick) {
    for(int i = 0; i < manager->toolbarWidgets.size(); i++)
    {
      manager->toolbarWidgets.at(i)->setWindowOpacity(this->activeOpacity);
    }
}


    this->update();
}

void MainWindow::inactiveTransparencyChange(int value) {
    this->inactiveOpacity = (float)value/100;

    if (this->underClick)
    {
    for(int i = 0; i < manager->toolbarWidgets.size(); i++)
    {
      manager->toolbarWidgets.at(i)->setWindowOpacity(this->inactiveOpacity);
    }
}
    this->update();
}

void MainWindow::leftcontextSwitch() {
cout << "here" << endl;
    if (this->underClick) 
    {
        this->activeLabel->setVisible(false);
        this->activeSlider->setVisible(false);
        this->inactiveSlider->setVisible(true);
        this->inactiveLabel->setVisible(true);
    } 
    else 
    {
        this->inactiveSlider->setVisible(false);
        this->inactiveLabel->setVisible(false);
        this->activeSlider->setVisible(true);
        this->activeLabel->setVisible(true);
    }

}

void MainWindow::showControllerBar()
{
  if(this->manager->toolbars.back()->isHidden())
    this->manager->toolbars.back()->show();
  else
    this->manager->toolbars.back()->hide();
  
  repaint();
}

