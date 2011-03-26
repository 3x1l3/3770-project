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


QAction *openEditWindowAction;


void updateBannerText();

signals:
  void customContextMenuRequested(const QPoint &);




};

#endif

