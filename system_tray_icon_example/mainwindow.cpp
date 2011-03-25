#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{


    QSystemTrayIcon *tray = new QSystemTrayIcon(QIcon(QPixmap("shutter.png")),this);
    QMenu *context_menu = new QMenu(this);
    QAction *exit = new QAction("Exit", this);
    exit->connect(exit, SIGNAL(triggered()), this, SLOT(close()));
    //tray->setIcon(QIcon(QPixmap("shutter.png")));
    tray->show();

    context_menu->addAction(exit);

    tray->setContextMenu(context_menu);

}

MainWindow::~MainWindow()
{

}
