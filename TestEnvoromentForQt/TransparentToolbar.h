
#ifndef TRANSPARENTTOOLBAR_H
#define TRANSPARENTTOOLBAR_H

#include <QLineEdit>
#include <QDockWidget>
#include <QToolBar>

class TransparentToolbar : public QToolBar {
  
  Q_OBJECT
  
  public:
    

    TransparentToolbar( QWidget * parent = 0 );
    TransparentToolbar(QString label);
    
    ~TransparentToolbar();
    
   
    void leaveEvent(QEvent * event);
    void paintEvent (QPaintEvent * event);
    void mouseMoveEvent (QMouseEvent * event);

    void setInvisible(bool setter);
    
    QRegion *noArea;
    QRegion *fullArea;
    
    void DropEvent(QDropEvent*);
    
  public slots:
    void recieveMouseXY(int x, int y);
    
    
  private:
    

    
    bool isInvisible;
    int x;
    int y;
    
  
};

#endif
