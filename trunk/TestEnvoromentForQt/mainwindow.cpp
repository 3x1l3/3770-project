#include "mainwindow.h"
#include "passwordedit.h"

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

  //startTimer(10);
 
  //QWidget::setWindowOpacity(0.5);
  
  
  
    /// Creating system tray icon and menu functionality ///
    QSystemTrayIcon *tray = new QSystemTrayIcon(QIcon(QPixmap("shutter.png")),this);
    QMenu *context_menu = new QMenu(this);
    QAction *exit = new QAction("Exit", this);
    exit->connect(exit, SIGNAL(triggered()), this, SLOT(close()));
    QAction *hide = new QAction("Hide", this);
    hide->connect(hide, SIGNAL(triggered()), this, SLOT(hide()));
    QAction *show = new QAction("Show", this);
    show->connect(show, SIGNAL(triggered()), this, SLOT(show() ) );
   
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
    
    
    manager = new WidgetManager(this);
    QPushButton *button1 = new QPushButton();
    QPushButton *button2 = new QPushButton();
    QPushButton *button3 = new QPushButton();
    QPushButton *button4 = new QPushButton();
    BannerWidget *banner1 = new BannerWidget();
    QTextEdit *textEdit1 = new QTextEdit();
    button1->setMouseTracking(true);
    button2->setMouseTracking(true);
    button3->setMouseTracking(true);
    button4->setMouseTracking(true);
    banner1->setMouseTracking(true);
    textEdit1->setMouseTracking(true);
    manager->addNewWidget("button1", 0, 0, 0.8, button1);
    manager->addNewWidget("button2", 0, 0, 0.7, button2);
    manager->addNewWidget("button3", 0, 0, 0.4, button3);
    manager->addNewWidget("", 0, 0, 0.2, button4);
    manager->addNewWidget("scrollin'", 0, 0, 0.5, banner1);
    manager->addNewWidget("textEdit1", 0,0,0.5, textEdit1);
    manager->drawWidgets();
	
    
    manager->toggleTransparency(true);
    manager->toggleTransparency(false);
    
    
}

void MainWindow::showPassword() {
  QMessageBox::information(this, "Password", QString("Your password is: %1").arg(password->text()));
}

void MainWindow::setTransparency()
{
  underClick = !underClick;
  if(underClick)
  {
    this->showFullScreen();
    password->setInvisible(true);
    manager->toggleTransparency(true);
  }
  else
  {
    this->showNormal();
    password->setInvisible(false);
    manager->toggleTransparency(false);
  }
  update();
}

void MainWindow::timerEvent(QTimerEvent * event)
{
 
  
}

void MainWindow::mouseMoveEvent( QMouseEvent * event)
{
  QWidget::mouseMoveEvent(event);
  setMouseTracking(true);
  x = event->x();
  y = event->y();
  //cout << "Mouse moved, x is " << x << "and y is " << y << " and mouse is: "<<endl ;
  
  
//   bool inWidget = false;
//   for(int i =0;i<manager->dockWidgets.size(); i ++)
//   {
//     //cout<<manager->dockWidgets[i]->pos().x()<<" "<<manager->dockWidgets[i]->pos().y()<<endl;
//     if (event->x() >= manager->dockWidgets[i]->pos().x()-20 && event->x() <= manager->dockWidgets[i]->width()+20 && event->y() >= manager->dockWidgets[i]->pos().y()-20 && event->y() <= manager->dockWidgets[i]->height()+20)
//     {
//       inWidget = true;
//       cout<<"IN MY LOOP"<<endl;
//       manager->dockWidgets[i]->setFocus();
//     }
//   }
// 
// 
//   if(inWidget == false)
//   {
    update();
    repaint();
//   }

}
  
void MainWindow::mousePressEvent(QMouseEvent * event)
{
    
    x= event->x();
    y = event->y();
    

}

void MainWindow::mouseReleaseEvent(QMouseEvent * event)
{

}


void MainWindow::paintEvent(QPaintEvent *event)
{
  QWidget::paintEvent(event);
  QPainter painter(this);
  
  
  
  //cout << "\n\nPainted: X " << x << " and Y " << y << endl;
  
  pos = QCursor::pos();
  painter.setOpacity(1.0);

  QPolygon myPolygon = QPolygon::QPolygon(QRect(0,0,QMainWindow::width(), QMainWindow::height()));
  QPolygon mousePolygon = QPolygon::QPolygon(QRect(x-6, y-6, 15, 15));
  
  
  
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
	cout<<"noArea"<<endl;
  }
  else
  {
        setMask(*fullArea);
	this->setWindowOpacity(1.0);
	cout<<"full"<<endl;
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