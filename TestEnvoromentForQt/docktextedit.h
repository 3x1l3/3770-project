#ifndef DOCKTEXTEDIT_H
#define DOCKTEXTEDIT_H

#include <QTextEdit>
#include <QPainter>
#include <QMouseEvent>
#include <QDockWidget>
class DockTextEdit : public virtual QTextEdit
{
  
  public:
    DockTextEdit(QWidget* parent = 0);
    virtual ~DockTextEdit();
    
    
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


#endif //DOCKTEXTEDIT_H