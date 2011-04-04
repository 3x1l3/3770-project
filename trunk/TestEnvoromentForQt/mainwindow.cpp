#include "mainwindow.h"
#include "passwordedit.h"
#include <QDragLeaveEvent>


using namespace std;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  
  settingsFile = new QFile("./settings.txt");

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
    QAction *toggleActive = new QAction("Toggle Active", this);
    toggleActive->connect(toggleActive, SIGNAL(triggered()), this, SLOT(setTransparency()));
    
    leftcontext_menu = new QWidget(this);
    leftcontext_menu->setWindowFlags(Qt::Popup);
    leftcontext_menulayout = new QHBoxLayout();
    activeSlider = new QSlider();
    inactiveSlider = new QSlider();
    activeSlider->setMaximum(100);
    activeSlider->setMinimum(0);
    inactiveSlider->setMaximum(100);
    inactiveSlider->setMinimum(0);

    leftcontext_menu->setLayout(leftcontext_menulayout);
    leftcontext_menulayout->addWidget(activeSlider);
    leftcontext_menulayout->addWidget(inactiveSlider);

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
    photos* thing = new photos();
    DockTextEdit* dockText = new DockTextEdit();
    BannerWidget *banner1 = new BannerWidget();
    Calc *calc = new Calc();

    //set Properties
    banner1->setMouseTracking(true);

    //Add to manager
    manager->addNewToolbar("test", 0, 0, this->inactiveOpacity, thing);
    manager->addNewToolbar("scrollin'", 0, 0, this->inactiveOpacity, banner1);
    manager->addNewToolbar("Notepad", 0, 0, this->inactiveOpacity, dockText);
    manager->addNewToolbar("Calculator", 0, 0, this->inactiveOpacity, calc);
    manager->drawToolbars();
    
    banner1->setMinimumWidth( QApplication::desktop()->screenGeometry().width() * 0.9 );

    /*
    //Initial widget positioning
    manager->toolbarWidgets.at(0)->move( QApplication::desktop()->screenGeometry().right() - thing->width() , 39);
    manager->toolbarWidgets.at(1)->setMinimumWidth( QApplication::desktop()->screenGeometry().width() );
    banner1->setMinimumWidth( QApplication::desktop()->screenGeometry().width() );
    manager->toolbarWidgets.at(1)->window()->setMinimumWidth( QApplication::desktop()->screenGeometry().width() );
    manager->toolbarWidgets.at(2)->move(0, manager->toolbars.at(0)->close() );
    
	
	*/
    
    for (int i = 0; i < manager->toolbarWidgets.size();i ++)
    {
      connect(this, SIGNAL(sendOutMouseXY(int, int)), manager->toolbarWidgets[i], SLOT(recieveMouseXY(int, int)));
      manager->toolbarWidgets.at(i)->setWindowFlags(Qt::Window | Qt::FramelessWindowHint |Qt::X11BypassWindowManagerHint);
      manager->toolbarWidgets.at(i)->setAllowedAreas(Qt::NoToolBarArea);
      manager->toolbarWidgets.at(i)->show();
    }
 

    manager->toggleTransparency(true);
    underClick = true; 
    QMainWindow::hide();
    
    this->openSettings();
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


void MainWindow::openSettings()
{

  
  int tempX = 40;
  int tempY = 40;
  
  
  if (!settingsFile->open(QIODevice::ReadOnly | QIODevice::Text))
    return;
  if(settingsFile->atEnd())
    return;

  QTextStream in(settingsFile);
  QString line;
  
  for(int i = 0; i < manager->toolbarWidgets.size(); i++)
  {
    //line = in.readLine();
    in >> tempX; in >> tempY;
    manager->toolbarWidgets.at(i)->move(tempX, tempY);
  }
  
  settingsFile->close();
}

void MainWindow::close()
{
  saveSettings();
  QMainWindow::close();
}

void MainWindow::saveSettings()
{
    settingsFile->open(QIODevice::Truncate | QIODevice::Text | QIODevice::ReadWrite);
    QTextStream out(settingsFile);
    
    for(int i = 0; i < manager->toolbarWidgets.size(); i++)
    {
      out << manager->toolbarWidgets.at(i)->pos().x() << " " << manager->toolbarWidgets.at(i)->pos().y() << endl;
    }
    
    settingsFile->close();
 
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
  
  saveSettings();
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
  //TODO relative path calculations here?
  
  /*char abspath[PATH_MAX];
  realpath("/shutter.png", abspath);
  QString str = QString("notify-send -i ");
  str = str + abspath;
  str = str + " Alert! \"You have a new message.\" ";
  
  system(str.toStdString().c_str());
  */
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
    for(int i = 0; i < manager->toolbarWidgets.size(); i++)
    {
      manager->toolbarWidgets.at(i)->setWindowOpacity(this->activeOpacity);
    }
      this->tray->setIcon(inactiveIcon);

    this->update();
}

void MainWindow::inactiveTransparencyChange(int value) {
    this->inactiveOpacity = (float)value/100;
    for(int i = 0; i < manager->toolbarWidgets.size(); i++)
    {
      manager->toolbarWidgets.at(i)->setWindowOpacity(this->inactiveOpacity);
    }
      this->tray->setIcon(inactiveIcon);

    this->update();
}
