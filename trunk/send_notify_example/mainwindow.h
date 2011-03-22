#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QPushButton>
#include <QProcess>
#include <QStringList>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public slots:
   void clicked();

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
};

#endif // MAINWINDOW_H
