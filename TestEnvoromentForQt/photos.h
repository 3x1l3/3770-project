#ifndef PHOTOS_H
#define PHOTOS_H

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


class photos : public QWidget
{
    Q_OBJECT

public slots:
    void loadImages(QString);
    void showContextMenu(const QPoint&);
    void changeDir();

public:
    QStringList files;
    int currentfile;

    photos(QWidget *parent = 0);
    ~photos();
    QLabel *label;
    QPixmap *image;
    QFileDialog *imageDialog;
    QDir *directoryAccess;
    QStringList filter;
    QTimer *timer;
    QString directory;
    QMenu *context;
    QMessageBox *nofiles;

    QAction *changedirAct;
    
    QRegion *fullArea;
    QRegion *noArea;
    
protected:
    void paintEvent(QPaintEvent*);
    void mouseMoveEvent(QMouseEvent*);


private:
    void timerEvent(QTimerEvent * event);

    bool isInvisible;
    int x;
    int y;

};

#endif // PHOTOS_H
