#ifndef BANNERWIDGET
#define BANNERWIDGET

#include <QLineEdit>
#include <QMessageBox>
#include <QtGui>

#include <iostream>

#include <QString>
#include<QLabel>

class BannerWidget : public QWidget {

  Q_OBJECT

public:

  BannerWidget(QWidget *parent = 0);
  


private slots:
  void showContextMenu(const QPoint &);
  void openEditWindow();

  
  
protected:
QString bannerString;
QLabel *banner;

void mousePressEvent(QMouseEvent *event);
void paintEvent(QPaintEvent *event);
void timerEvent(QTimerEvent * event);


QAction *openEditWindowAction;


void updateBannerText();


int bannerXCoordinate;
int bannerYCoordinate;

signals:
  void customContextMenuRequested(const QPoint &);




};

#endif

