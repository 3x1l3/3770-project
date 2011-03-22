#ifndef CUSTOMQWIDGET
#define CUSTOMQWIDGET

#include <QLineEdit>
#include <QMessageBox>
#include <QtGui>

class CustomQWidget : public QWidget {

  Q_OBJECT

public:

  CustomQWidget(QWidget *parent = 0): QWidget(parent) 
  {
  }
  
void bringToFront()
{
//     this->show();
//     this->showNormal();
    this->raise();
    this->activateWindow();
}

public slots:

protected:
void mousePressEvent(QMouseEvent *event)
  {
//     this->show();
//     this->showNormal();
    this->raise();
    this->activateWindow();

  }

void mouseMoveEvent(QMouseEvent *event)
  {
//     this->show();
//     this->showNormal();
    this->raise();
    this->activateWindow();

  }
void mouseReleaseEvent(QMouseEvent *event)
  {
//     this->show();
//     this->showNormal();
    this->raise();
    this->activateWindow();

  }
  

};

#endif

