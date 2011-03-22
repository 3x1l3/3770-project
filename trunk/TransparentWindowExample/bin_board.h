//Name = Jordan Peoples
//Student Number = 001149318
//Following is my .h file for the binary board.  this is for part 2 of assignment 2

#ifndef BIN_BOARD_H
#define BIN_BOARD_H



#include <QTime>
#include <QWidget>
#include <iostream>

class bin_board : public QWidget {

  Q_OBJECT

public:

  bin_board(QWidget *parent = 0);

signals:
  void symbolEntered(Qt::Key);
  
protected:
  QTime *timer;
  void mousePressEvent(QMouseEvent *event);
  void mouseReleaseEvent(QMouseEvent *event);
  void paintEvent(QPaintEvent *event);
  QString currentBinaryString;
  QString arrayOfBinaryStrings[39];
  Qt::Key arrayOfQKeys[39];
  
  

};

#endif

