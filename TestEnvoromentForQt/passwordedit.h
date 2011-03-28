/****************************************************************
/// \brief The specification file of a passwordedit dialog.
///
/// QT Assignment 1
/// Question 1
/// Created By/Author: Adam Shepley
/// Student Number: 001125233
///
/// This file is: passwordedit.h
///
/// It is the definition file for the PasswordEdit widget
/// Subclasses QLineEdit.
///
/// \date February 1st
/// \author Adam Shepley
***************************************************************/
#ifndef PASSWORD_EDIT_H
#define PASSWORD_EDIT_H

#include <QLineEdit>

class PasswordEdit : public QLineEdit {
  
  Q_OBJECT
  
  public:
    

    PasswordEdit( QWidget * parent = 0 );
    
    ~PasswordEdit();
    
   
    void leaveEvent(QEvent * event);
    void paintEvent (QPaintEvent * event);
    void mouseMoveEvent (QMouseEvent * event);
    
    void setInvisible(bool setter);
    
    QRegion *noArea;
    QRegion *fullArea;
    
  private:
    

    
    bool isInvisible;
    int x;
    int y;
    
  
};

#endif