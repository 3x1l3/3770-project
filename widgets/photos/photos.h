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

class photos : public QWidget
{
    Q_OBJECT

public slots:
    void loadImages(QString);

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



private:
    void timerEvent(QTimerEvent * event);
    void mousePressEvent(QMouseEvent *event);

};

#endif // PHOTOS_H
