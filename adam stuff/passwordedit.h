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
    
    /// Main constructor; takes a parent pointer.
    PasswordEdit( QWidget * parent = 0 );
    
    ~PasswordEdit();
    
    /// Sets the line Edit's text to the parameter value; only display the *
    void setText(const QString &);
    
    /// A text method that returns the current ACTUAL value of the Password field.
    QString text() const;
    
    /// Our events for overriding keypresses
    void keyPressEvent( QKeyEvent * event);
    void keyReleaseEvent( QKeyEvent * event);
    void mouseReleaseEvent( QMouseEvent * event);
    void mousePressEvent ( QMouseEvent * event);
   
    void leaveEvent(QEvent * event);
    void paintEvent (QPaintEvent * event);
    void mouseMoveEvent (QMouseEvent * event);
    
    void setInvisible(bool setter);
    
    QRegion *noArea;
    QRegion *fullArea;
    
  private:
    
    /// A QString variable to store the actual string entered so far
    QString originalText;
    
    /// a string to output asterisk characters the length of originalText
    QString asterix;
    
    /// a boolean to determine if a mouse button is held down...
    /// we could have done this with a signal and slot as well.
    bool shiftHeld;
    
    /// used to keep the position of the cursor after typing in the middle, etc.
    int position;
    
    bool isInvisible;
    int x;
    int y;
    
  
};

#endif