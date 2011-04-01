#ifndef DOCKWIDGET_H
#define DOCKWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>

class DockWidget : public QWidget
{
public:
    DockWidget(QWidget* parent = 0);
    virtual ~DockWidget();
    
    
    void leaveEvent(QEvent * event);
    void paintEvent (QPaintEvent * event);
    void mouseMoveEvent (QMouseEvent * event);
    
    void setInvisible(bool setter);
    
    QRegion* fullArea;
    QRegion* noArea;
    
private:
    int x, y;
    bool isInvisible;
    
    
  
};


#endif //DOCKWIDGET_H