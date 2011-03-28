/****************************************************************
/// \brief The implimentation file of a passwordedit dialog.
/// QT Assignment 1
/// Question 1
/// Created By/Author: Adam Shepley
/// Student Number: 001125233
///
/// This file is: passwordedit.cpp
///
/// It is the definition file for the PasswordEdit widget
/// Subclasses QLineEdit.
///
/// \date February 1st
/// \author Adam Shepley
***************************************************************/

#include "passwordedit.h"
#include <QtGui>
#include <iostream>
using namespace std;

PasswordEdit::PasswordEdit( QWidget * parent) : QLineEdit( parent )
{
  isInvisible = false;
  
  setMouseTracking(true);
  fullArea = new QRegion(0, 0, QWidget::width(), QWidget::height(),QRegion::Rectangle);
  noArea = new QRegion(15,15,50,50, QRegion::Rectangle);
}

PasswordEdit::~PasswordEdit()
{

}





void PasswordEdit::setInvisible(bool setter)
{
  isInvisible = setter;
}

void PasswordEdit::leaveEvent(QEvent* event)
{
  QLineEdit::leaveEvent(event);
  setMask(*fullArea);
  
}

void PasswordEdit::mouseMoveEvent(QMouseEvent * event)
{
 QLineEdit::mouseMoveEvent(event); 
 
 x = event->x();
 y = event->y();
 update();
  
}

void PasswordEdit::paintEvent(QPaintEvent *event)
{
  QLineEdit::paintEvent(event);
  QPainter painter(this);
    
  QPolygon myPolygon = QPolygon::QPolygon(QRect(0,0,QLineEdit::width(),QLineEdit::height()));
  QPolygon mousePolygon = QPolygon::QPolygon(QRect(x-6, y-6, 15, 15));
  
  myPolygon = myPolygon.subtracted(mousePolygon);
//   cout << x << " " << y << " " << isInvisible << " " << true << " " << underMouse() <<  endl;
  *noArea = QRegion(myPolygon,Qt::OddEvenFill );
  *fullArea = QRegion(QRect(0,0,QLineEdit::width(), QLineEdit::height()));
  
  if(isInvisible == true && underMouse() == true)
  {
//     cout << "\nIS UNDER MOUSE\n";
        setMask(*noArea);
  }

}