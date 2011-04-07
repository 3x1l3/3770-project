#ifndef CONTROLLERBAR_H
#define CONTROLLERBAR_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QPushButton>
#include "TransparentToolbar.h"
#include <QVBoxLayout>

class ControllerBar : public QWidget
{
public:
    ControllerBar(QWidget* parent = 0);
    ~ControllerBar();
    QVector <QPushButton*> controlButtons;
    
    void addControlPoint(QString windowTitle, TransparentToolbar *toolBarToConnectTo);
    
    QVBoxLayout *vertLay;
    
private:
    
    
  
};


#endif //DOCKWIDGET_H