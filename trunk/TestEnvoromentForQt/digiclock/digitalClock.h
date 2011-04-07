#ifndef DIGITALCLOCK_H
#define DIGITALCLOCK_H

#include <QtGui/QWidget>
#include <QLabel>
#include <QBitmap>
#include <QString>
#include <QFileDialog>
#include <QStringList>
#include <iostream>
#include <QDir>
#include <QTimerEvent>
#include <QMouseEvent>
#include <QMenu>
#include <QAction>
#include <QMessageBox>

#include <QTime>
#include <QColor>

class digitalClock : public QWidget
{
    Q_OBJECT


public:
    QStringList files;
    int currentfile;

    digitalClock(QWidget *parent = 0);
    ~digitalClock();
    QLabel *label;
    QTimer *timer;
    QMenu *context;
    
    QRegion *fullArea;
    QRegion *noArea;

    QFont *clockFont;
    

    
protected:
    void paintEvent(QPaintEvent*);
    void mouseMoveEvent(QMouseEvent*);
    void mousePressEvent(QMouseEvent *event);
    
    QAction *openEditWindowAction;


private:
    void timerEvent(QTimerEvent * event);

    bool isInvisible;
    int x;
    int y;
    QColor currentColor;
    
    
signals:
  void customContextMenuRequested(const QPoint&);

private slots:
  void showContextMenu(const QPoint &);
  void openEditWindow();
  
};

#endif // DIGITALCLOCK_H