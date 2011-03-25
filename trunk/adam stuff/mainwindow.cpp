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
  
  fullArea = new QRegion(0, 0, QWidget::width(), QWidget::height(),QRegion::Rectangle);
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
	
}

void MainWindow::showPassword() {
  QMessageBox::information(this, "Password", QString("Your password is: %1").arg(password->text()));
}

void MainWindow::setTransparency()
{
  underClick = !underClick;
  this->showFullScreen();
  password->setInvisible(true);
  update();
}

void MainWindow::timerEvent(QTimerEvent * event)
{
 
  pos = QPoint(x, y);
  
  QMouseEvent mouseevent(QEvent::MouseMove, pos, Qt::LeftButton, 0, 0);
  cerr << "\nEvent Created!\n";
  QApplication::sendEvent(this, &mouseevent);
  
  //update();
  //repaint();
  cout << "\ntimer\n";
  
}

void MainWindow::mouseMoveEvent( QMouseEvent * event)
{
  
  QWidget::mouseMoveEvent(event);
  setMouseTracking(true);
  x = event->x();
  y = event->y();
  cout << "Mouse moved, x is " << x << "and y is " << y << " and mouse is: " << hasMouseTracking() << " " << false << endl;
  


  
  update();
  repaint();
}
  
void MainWindow::mousePressEvent(QMouseEvent * event)
{
    
    x= event->x();
    y = event->y();
    
    

    

    
    //this->hide();
   // this->setVisible(false);

    /*
   if(sendBack == true)
   {
     pos = event->pos();
     cerr << "x is " << x << " and y is " << y;
     QMouseEvent mouseevent(QEvent::MouseButtonPress, pos, event->button(), event->buttons(), 0);
     cerr << "\nEvent Created!\n";
     QApplication::sendEvent(this, &mouseevent);
    // QTest::mouseClick( this, Qt::LeftButton, 0, pos);

          QMouseEvent mouseevent2(QEvent::MouseButtonRelease, pos, event->button(), event->buttons(), 0);
     cerr << "\nEvent Created!\n";
     QApplication::sendEvent(this, &mouseevent2);
     cerr << "\nEvent Sent! \n";
     this->show();

   }
    
    */
   // this->show();
}

void MainWindow::mouseReleaseEvent(QMouseEvent * event)
{

}


void MainWindow::paintEvent(QPaintEvent *event)
{
  QWidget::paintEvent(event);
  QPainter painter(this);
  
  cout << "\n\nPainted: X " << x << " and Y " << y << endl;
  
  pos = QCursor::pos();
  painter.setOpacity(1.0);
  //x = pos.x();
  //y = pos.y();
  
  /*QVector <QPoint> wholeVector (4);
  wholeVector.append(QPoint::QPoint(0,0));
  wholeVector.append(QPoint::QPoint(0, QWidget::height()));
  wholeVector.append(QPoint::QPoint(QWidget::width(), QWidget::height()));
  wholeVector.append(QPoint::QPoint(QWidget::width(), 0));

  
  QPolygon myPolygon = QPolygon::QPolygon(wholeVector);
  
  QVector <QPoint> mouseBox (4);
  mouseBox.append(QPoint::QPoint(x-8, y-8));
  mouseBox.append(QPoint::QPoint(x-8, y+8));
  mouseBox.append(QPoint::QPoint(x+8, y+8));
  mouseBox.append(QPoint::QPoint(x+8, y-8));
  */
  
  QPolygon myPolygon = QPolygon::QPolygon(QRect(0,0,width(),height()));
  QPolygon mousePolygon = QPolygon::QPolygon(QRect(x-6, y-6, 15, 15));
  
  
  
  myPolygon = myPolygon.subtracted(mousePolygon);
  
  *noArea = QRegion(myPolygon,Qt::OddEvenFill );
  
  if(underClick == true)
  {
        setMask(*noArea);
	this->setWindowOpacity(0.5);
	cout << "\nlolmask\n";
  }
  else
  {
        setMask(*fullArea);
	this->setWindowOpacity(1.0);
  }
 
  
}

bool MainWindow::x11Event(XEvent * event)
{
  QWidget::x11Event(event);
}