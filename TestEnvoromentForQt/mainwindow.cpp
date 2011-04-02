#include "mainwindow.h"
#include "passwordedit.h"
#include <QDragLeaveEvent>

#include <QtGui>
#include <iostream>

using namespace std;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {

  label = new QLabel("Type password: ");
  password = new PasswordEdit();
  button = new QPushButton("Show");
  
  makeTrans = new QPushButton("Click Through Window!");
  
  label->setMouseTracking(true);
  password->setMouseTracking(true);
  button->setMouseTracking(true);
  makeTrans->setMouseTracking(true);

  //centralWidget()->setMouseTracking(true);
 // parentWidget()->setMouseTracking(true);

  
  QHBoxLayout *layout = new QHBoxLayout();
  layout->addWidget(label);
  layout->addWidget(password);
  layout->addWidget(button);
  layout->addWidget(makeTrans);
  
  
  setCentralWidget(new QWidget());
  centralWidget()->setLayout(layout);
  centralWidget()->setMouseTracking(true);
  
  connect(button, SIGNAL(clicked()), this, SLOT(showPassword()));
  connect(makeTrans, SIGNAL(clicked()), this, SLOT(setTransparency()));
  
  fullArea = new QRegion(0, 0, QMainWindow::width(), QMainWindow::height(), QRegion::Rectangle);
  noArea = new QRegion(15,15,50,50, QRegion::Rectangle);
  
  
  underClick = false;
  
  this->setMouseTracking(true);

  x = 0;
  
  y = 0;
  setWindowFlags(Qt::WindowStaysOnTopHint);
/*  setAttribute(Qt::WA_MouseTracking);
  setAttribute(Qt::WA_MouseNoMask);
  setAttribute(Qt::WA_Hover);*/
  //setAttribute(Qt::WA_X11DoNotAcceptFocus);
  fired = false;

  startTimer(100);
 
  //QWidget::setWindowOpacity(0.5);
  
  
  
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
    
    tray->show();
    context_menu->addAction(show);
    context_menu->addAction(hide);
    context_menu->addSeparator();
    context_menu->addAction(toggleActive);
    context_menu->addSeparator();
    tray->setContextMenu(context_menu);
    context_menu->addAction(exit);
    
    cout<<"BEFORE"<<endl;
    manager = new ToolbarManager(this);
    cout<<"BEFORE1"<<endl;
    QPushButton *button1 = new QPushButton();
    cout<<"BEFORE2"<<endl;
    QPushButton *button2 = new QPushButton();
    QPushButton *button3 = new QPushButton();
    QPushButton *button4 = new QPushButton();
    BannerWidget *banner1 = new BannerWidget();
    cout<<"BEFORE3"<<endl;
    QTextEdit *textEdit1 = new QTextEdit();
    

    
    textEdit1->setFixedSize(100,100);
    cout<<"BEFORE4"<<endl;
    button1->setMouseTracking(true);
    cout<<"BEFORE5"<<endl;
    button2->setMouseTracking(true);
    cout<<"BEFORE6"<<endl;
    button3->setMouseTracking(true);
    cout<<"BEFORE7"<<endl;
    button4->setMouseTracking(true);
    cout<<"BEFORE8"<<endl;
    banner1->setMouseTracking(true);
    cout<<"BEFORE9"<<endl;
    textEdit1->setMouseTracking(true);
    cout<<"BEFORE10"<<endl;
    manager->addNewToolbar("button1", 0, 0, 0.8, button1);
    cout<<"BEFORE11"<<endl;
    manager->addNewToolbar("button2", 0, 0, 0.7, button2);
    cout<<"BEFORE12"<<endl;
    manager->addNewToolbar("button3", 0, 0, 0.4, button3);
    cout<<"BEFORE13"<<endl;
    manager->addNewToolbar("", 0, 0, 0.2, button4);
    cout<<"BEFORE14"<<endl;
    manager->addNewToolbar("scrollin'", 0, 0, 0.5, banner1);
    cout<<"BEFORE15"<<endl;
    manager->addNewToolbar("textEdit1", 0,0,0.5, textEdit1);
    cout<<"BEFORE16"<<endl;
    
    photos* thing = new photos();
    thing->setMinimumSize(300, 300);
    manager->addNewToolbar("test", 0, 0, 0.5, thing);
    
    DockTextEdit* dockText = new DockTextEdit();
    
    
    DockWidget* DW = new DockWidget();
    /*
    QHBoxLayout* lay = new QHBoxLayout(DW);
    lay->addWidget(dockText);
    
    DW->setLayout(lay);
    DW->setMouseTracking(true); */
    //dockText->setMouseTracking(true);
    //dockText->setInvisible(true);
   // DW->setInvisible(true);
    
    //manager->addNewWidget("fuck", 0, 0, 0.5, DW);
 
    
    manager->addNewToolbar("damn", 0, 0, 0.5, dockText);
    manager->drawToolbars();
    cout<<"AFTER"<<endl;
    
    
    for (int i = 0; i < manager->toolbarWidgets.size();i ++)
    {
      connect(this, SIGNAL(sendOutMouseXY(int, int)), manager->toolbarWidgets[i], SLOT(recieveMouseXY(int, int)));
      manager->toolbarWidgets.at(i)->setWindowFlags(Qt::Window | Qt::FramelessWindowHint |Qt::X11BypassWindowManagerHint);
      manager->toolbarWidgets.at(i)->setAllowedAreas(Qt::NoToolBarArea);
      
      manager->toolbarWidgets.at(i)->show();
      //might be useful in the future for RANDOM POSITIONING of Widgets
   //   manager->dockWidgets.at(i)->setFocus();
   //   manager->dockWidgets.at(i)->move(manager->dockWidgets.at(i)->pos().x()+1,manager->dockWidgets.at(i)->pos().y()+1);
    }

    cout<<"AFTER1"<<endl;
    
    
    //for loop here to connect all the widgets to the time event emitting the mouse position
	/*
    
    manager->toggleTransparency(true);
    manager->toggleTransparency(false);
    */
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
}




void MainWindow::showPassword() {
  QMessageBox::information(this, "Password", QString("Your password is: %1").arg(password->text()));
}

void MainWindow::setTransparency()
{
  underClick = !underClick;
  if(underClick)
  {
    //this->showFullScreen();
    password->setInvisible(true);
    manager->toggleTransparency(true);
  }
  else
  {
    //this->showNormal();
    password->setInvisible(false);
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

void MainWindow::mouseMoveEvent( QMouseEvent * event)
{
  QWidget::mouseMoveEvent(event);

//   x = event->x();
//   y = event->y();
 
  update();
  repaint();


}
  
void MainWindow::mousePressEvent(QMouseEvent * event)
{
    
//     x= event->x();
//     y = event->y();
    

}

void MainWindow::mouseReleaseEvent(QMouseEvent * event)
{

}


void MainWindow::paintEvent(QPaintEvent *event)
{
  QWidget::paintEvent(event);
  QPainter painter(this);
//  this->showNormal();
//  this->hide();
  
  //cout << "\n\nPainted: X " << x << " and Y " << y << endl;
  
  pos = QCursor::pos();
  painter.setOpacity(1.0);

  QPolygon myPolygon = QPolygon::QPolygon(QRect(0,0,QMainWindow::width(), QMainWindow::height()));
  QPolygon mousePolygon = QPolygon::QPolygon(QRect(x-15, y-15, 30, 30));
  
  
  
  myPolygon = myPolygon.subtracted(mousePolygon);
  
  
//   for(int i =0;i<manager->dockWidgets.size(); i ++)
//    {
//      mousePolygon = QPolygon::QPolygon(QRect(manager->dockWidgets[i]->pos().x(), manager->dockWidgets[i]->pos().y(),manager->dockWidgets[i]->width(), manager->dockWidgets[i]->height()));
//      myPolygon = myPolygon.subtracted(mousePolygon);
//    }
  
  *noArea = QRegion(myPolygon,Qt::OddEvenFill );
  *fullArea = QRegion(QRect(0, 0, QMainWindow::width(), QMainWindow::height()));
  
  if(underClick == true)
  {
        setMask(*noArea);
	this->setWindowOpacity(0.5);
	//cout << "\nlolmask\n";
	//cout<<"noArea"<<endl;
  }
  else
  {
        setMask(*fullArea);
	this->setWindowOpacity(1.0);
	//cout<<"full"<<endl;
  }
 
  
}

bool MainWindow::x11Event(XEvent * event)
{
  QWidget::x11Event(event);
}

void MainWindow::setupAreas(QRegion *fullArea, QRegion *noArea)
{
  fullArea = new QRegion(0, 0, QMainWindow::width(), QMainWindow::height(), QRegion::Rectangle);
  noArea = new QRegion( 15,15,50,50, QRegion::Rectangle);
}