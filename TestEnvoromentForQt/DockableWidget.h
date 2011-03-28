
#ifndef DOCKABLEWIDGET
#define DOCKABLEWIDGET

#include <QLineEdit>
#include <QDockWidget>

class DockableWidget : public QDockWidget {
  
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
    
  private:
    

    
    bool isInvisible;
    int x;
    int y;
    
  
};

#endif