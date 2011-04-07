
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
    
    void SetHeight(int);
    void SetWidth(int);
    int GetHeight();
    int GetWidth();
    
    bool CheckIfToolbarIsHidden();
    
  public slots:
    void recieveMouseXY(int x, int y);
    void toggleHidden();
    
  private:
    

    
    bool isInvisible;
    bool hidden;
    int x;
    int y;
    int width;
    int height;
    
  
};

#endif
