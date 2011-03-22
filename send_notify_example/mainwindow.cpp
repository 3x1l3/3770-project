#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *widget = new QWidget();
    QPushButton *button = new QPushButton();
    button->setText("I'M HERE CLICK ME");

    connect(button, SIGNAL(clicked()), this, SLOT(clicked()));

    this->setCentralWidget(button);



}

MainWindow::~MainWindow()
{

}

void MainWindow::clicked() {
    QProcess *process = new QProcess(this);

    QStringList list = QStringList();
    list << "-i  << "Summary What?" << "STFU!"; 
    process->start("/usr/bin/notify-send", list);
}
