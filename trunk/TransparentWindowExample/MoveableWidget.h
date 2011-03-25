#ifndef MOVEABLEWIDGET
#define MOVEABLEWIDGET

#include <QLineEdit>
#include <QMessageBox>
#include <QtGui>

#include <iostream>

class MoveableWidget : public QWidget {

  Q_OBJECT

public:

  MoveableWidget(QWidget *parent = 0);
  


public slots:

  
  
protected:
void mousePressEvent(QMouseEvent *event);

void mouseMoveEvent(QMouseEvent *event);
void mouseReleaseEvent(QMouseEvent *event);
void paintEvent(QPaintEvent * event);

QPoint clickLocation;

bool mouseDown;

bool mouseClickOverBanner;

QRectF banner;

QVector <QRectF> banners;

signals:
  void widgetClicked(int, int);




};

#endif

