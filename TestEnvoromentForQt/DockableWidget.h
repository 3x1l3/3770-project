
#ifndef DOCKABLEWIDGET
#define DOCKABLEWIDGET

#include <QLineEdit>
#include <QDockWidget>
#include <QToolBar>

class DockableWidget : public QToolBar {
  
  Q_OBJECT
  
  public:
    

    DockableWidget( QWidget * parent = 0 );
    DockableWidget(QString label);
    
    ~DockableWidget();
    
   
    void leaveEvent(QEvent * event);
    void paintEvent (QPaintEvent * event);
    void mouseMoveEvent (QMouseEvent * event);
    
    void setInvisible(bool setter);
    
    QRegion *noArea;
    QRegion *fullArea;
    
    void emitUndock();
    void DropEvent(QDropEvent*);
    
  public slots:
    void recieveMouseXY(int x, int y);
    
    
  private:
    

    
    bool isInvisible;
    int x;
    int y;
    
  
};

#endif