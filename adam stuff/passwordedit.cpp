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

/// Default Constructor
/// sets everything to blank/null/false
PasswordEdit::PasswordEdit( QWidget * parent) 
	    : QLineEdit( parent )
{
  originalText = "";
  asterix = "";
  shiftHeld = false;
  position = 0;
}

PasswordEdit::~PasswordEdit()
{

}


/// Encapsulates the LineEdit setText function.
void PasswordEdit::setText(const QString &input)
{
  QLineEdit::setText(input);
}

/// Returns the original text (used for peeking)
QString PasswordEdit::text() const
{
   return originalText;
}

/// Overrides the KeyPressEvent
/// This determines what happens after a given keyboard stroke
void PasswordEdit::keyPressEvent(QKeyEvent * event)
{
  /// used to accept all proper ASCII non-spec input chars
  QLineEdit::keyPressEvent(event);
  
  /// prevent the Delete and Backspace characters from being appended. WHY do they have text values?
  /// Also, remove the proper letter in the string
  if(event->key() != Qt::Key_Backspace && event->key() != Qt::Key_Delete)
    originalText.insert(position, event->text());
  
  /// make sure we go back if we backspace
  else if(event->key() == Qt::Key_Backspace)
    originalText.remove(position-1, 1);
  
  /// maintain proper position based on the Delete key
  else if(event->key() == Qt::Key_Delete)
    originalText.remove(position, 1);

  /// deprecated implimentation of hiding/peeking at chars.
  //Original implimentation of hiding the characters and revealing with shift.
  
    /* if( ( event->key() >= Qt::Key_A ) && ( event->key() <= Qt::Key_Z ) )
	  setText("*");   
	  
      if ( event->key() == Qt::Key_Shift || ( ( event->key() == Qt::Key_Shift ) && (event->count() >= 1 ) ) )
      {
         setText(originalText);
      }  
	  
   */
  
    
  /// Reverse implimentation; used to discard all other keys
  /// impliments peek feature.
  /// Note: We only show if BOTH the mouse is pressed down AND shift is held; 
  /// order does not matter.
  if ( event->key() == Qt::Key_Shift)
  {
      shiftHeld = true;
  }

  /// make sure we keep typing in the same spot
  if(event->key() == Qt::Key_Backspace || event->key() == Qt::Key_Left)
    position -= 1;
  else if( event->key() != Qt::Key_Delete || event->key() == Qt::Key_Right)
    position += 1;
  
}

void PasswordEdit::keyReleaseEvent(QKeyEvent * event)
{
  
  /// old method. Unfortunately, we either add for ALL keys 
  /// such as capslock, etc. or we have an ugly caseset in 
  /// the if statement. This is much more elegant than the loop though.
  /*
  if(event->key() != Qt::Key_Shift)
    asterix += "*";
  
  if(event->key() == Qt::Key_Backspace || event->key() == Qt::Key_Delete)
    asterix.truncate(asterix.length()-1);
  */
  
  /// ensure our asterisk amount is empty
  asterix = "";
  /// create the Asterisk string based on our textlength
  for(int i=0; i<originalText.length(); i++)
  {
    /// normally we would += the char, but append is technically
    /// faster and we use its speed
    /// to make up for the slowness introduced by the loop.
    asterix.append("*");
  }
  
  /// set the shift hold status back to false;
  if(event->key() == Qt::Key_Shift)
    shiftHeld = false;
  
  /// replace the textfield with our Asterisks.
  setText(asterix);
  
  /// reset the cursor position/ensure positioning proper
  QLineEdit::setCursorPosition(position);

}

/// overrides what happens when we press down a mouse button
void PasswordEdit::mousePressEvent(QMouseEvent * event)
{
  /// if we are also holding shift...show the right text
  /// Note: Distinguishment is not made between MB's as we also
  /// do not distinguish shifts;
  /// To do so would not make sense when having a left-handed user.
  if ( shiftHeld == true)
    setText(text());
  
  /// or just do the normal mouse event stuff
  else
   QLineEdit::mousePressEvent(event);

}

/// What we do when we release the mouse buttons.
void PasswordEdit::mouseReleaseEvent(QMouseEvent * event)
{
  /// gather the position of the cursor
  position = QLineEdit::cursorPosition();
  
  ///perform the normal release-event stuff
  QLineEdit::mouseReleaseEvent(event);
  
  /// reset the field to our asterisks
  setText(asterix);
  
  /// and finally, set the cursor position to the prior spot
  /// set text makes this an issue.
  QLineEdit::setCursorPosition(position);
  
}