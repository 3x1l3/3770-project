//Name = Jordan Peoples
//Student Number = 001149318
//Following is my .cpp file for the binary board.  this is for part 2 of assignment 2

#include "bin_board.h"

#include <QtGui>

#include <QX11Info>
#include <X11/Xlib.h>
#include <X11/extensions/shape.h>

bin_board::bin_board(QWidget *parent) : QWidget(parent)
{
  timer = new QTime(0,0,0,0);
  currentBinaryString = "";
  arrayOfBinaryStrings[0]  = "000000";
  arrayOfBinaryStrings[1]  = "000001";
  arrayOfBinaryStrings[2]  = "000010";
  arrayOfBinaryStrings[3]  = "000011";
  arrayOfBinaryStrings[4]  = "000100";
  arrayOfBinaryStrings[5]  = "000101";
  arrayOfBinaryStrings[6]  = "000110";
  arrayOfBinaryStrings[7]  = "000111";
  arrayOfBinaryStrings[8]  = "001000";
  arrayOfBinaryStrings[9]  = "001001";
  
  arrayOfBinaryStrings[10] = "001010";
  arrayOfBinaryStrings[11] = "001011";
  arrayOfBinaryStrings[12] = "001100";
  arrayOfBinaryStrings[13] = "001101";
  arrayOfBinaryStrings[14] = "001110";
  arrayOfBinaryStrings[15] = "001111";
  arrayOfBinaryStrings[16] = "010000";
  arrayOfBinaryStrings[17] = "010001";
  arrayOfBinaryStrings[18] = "010010";
  arrayOfBinaryStrings[19] = "010011";
  
  arrayOfBinaryStrings[20] = "010100";
  arrayOfBinaryStrings[21] = "010101";
  arrayOfBinaryStrings[22] = "010110";
  arrayOfBinaryStrings[23] = "010111";
  arrayOfBinaryStrings[24] = "011000";
  arrayOfBinaryStrings[25] = "011001";
  arrayOfBinaryStrings[26] = "011010";
  arrayOfBinaryStrings[27] = "011011";
  arrayOfBinaryStrings[28] = "011100";
  arrayOfBinaryStrings[29] = "011101";
  arrayOfBinaryStrings[30] = "011110";
  
  arrayOfBinaryStrings[31] = "011111";
  arrayOfBinaryStrings[32] = "100000";
  arrayOfBinaryStrings[33] = "100001";
  arrayOfBinaryStrings[34] = "100010";
  arrayOfBinaryStrings[35] = "100011";
  arrayOfBinaryStrings[36] = "100100";
  arrayOfBinaryStrings[37] = "100101";
  arrayOfBinaryStrings[38] = "100110";
  
  ////////////////////////////////////
  
  arrayOfQKeys[0] = Qt::Key_0;
  arrayOfQKeys[1] = Qt::Key_1;
  arrayOfQKeys[2] = Qt::Key_2;
  arrayOfQKeys[3] = Qt::Key_3;
  arrayOfQKeys[4] = Qt::Key_4;
  arrayOfQKeys[5] = Qt::Key_5;
  arrayOfQKeys[6] = Qt::Key_6;
  arrayOfQKeys[7] = Qt::Key_7;
  arrayOfQKeys[8] = Qt::Key_8;
  arrayOfQKeys[9] = Qt::Key_9;
  
  arrayOfQKeys[10] = Qt::Key_A;
  arrayOfQKeys[11] = Qt::Key_B;
  arrayOfQKeys[12] = Qt::Key_C;
  arrayOfQKeys[13] = Qt::Key_D;
  arrayOfQKeys[14] = Qt::Key_E;
  arrayOfQKeys[15] = Qt::Key_F;
  arrayOfQKeys[16] = Qt::Key_G;
  arrayOfQKeys[17] = Qt::Key_H;
  arrayOfQKeys[18] = Qt::Key_I;
  arrayOfQKeys[19] = Qt::Key_J;
  
  arrayOfQKeys[20] = Qt::Key_K;
  arrayOfQKeys[21] = Qt::Key_L;
  arrayOfQKeys[22] = Qt::Key_M;
  arrayOfQKeys[23] = Qt::Key_N;
  arrayOfQKeys[24] = Qt::Key_O;
  arrayOfQKeys[25] = Qt::Key_P;
  arrayOfQKeys[26] = Qt::Key_Q;
  arrayOfQKeys[27] = Qt::Key_R;
  arrayOfQKeys[28] = Qt::Key_S;
  arrayOfQKeys[29] = Qt::Key_T;
  
  arrayOfQKeys[30] = Qt::Key_U;
  arrayOfQKeys[31] = Qt::Key_V;
  arrayOfQKeys[32] = Qt::Key_W;
  arrayOfQKeys[33] = Qt::Key_X;
  arrayOfQKeys[34] = Qt::Key_Y;
  arrayOfQKeys[35] = Qt::Key_Z;
  arrayOfQKeys[36] = Qt::Key_Space;
  arrayOfQKeys[37] = Qt::Key_Backspace;
  arrayOfQKeys[38] = Qt::Key_Enter;
  
  QRegion region;
XShapeCombineRegion( QX11Info::display(), winId(), ShapeInput, 0, 0, region.handle(), ShapeSet );
}

void bin_board :: mousePressEvent(QMouseEvent *event)
{
  if(event->button() == Qt::LeftButton)
  {
    timer->start();
  }
  QWidget::mousePressEvent(event);
  
}

void bin_board :: mouseReleaseEvent(QMouseEvent *event)
{
  int elapsedTime = 0;
  if(event->button() == Qt::LeftButton)
  {
    elapsedTime = timer->elapsed();
    std::cout<<elapsedTime<<std::endl;
    
    delete timer;
    timer = new QTime(0,0,0,0);
  }
  
  
  
 
  if(elapsedTime < 200)
  {
    currentBinaryString += "0";
  }
  if(elapsedTime >= 200)
  {
    currentBinaryString += "1";
  }
 
  
  if(currentBinaryString.size() >= 6)
  {
    
    for(int i = 0; i < 39; i++ )
    {
      if(currentBinaryString == arrayOfBinaryStrings[i])
      {
	emit symbolEntered(arrayOfQKeys[i]);
      }
    }
    
    currentBinaryString = "";
  
  }
  
  this->update();
  
  QWidget::mouseReleaseEvent(event);
}
void bin_board::paintEvent(QPaintEvent * event)
{
  QPainter painter(this);
  painter.drawText(20,20, currentBinaryString);
}

