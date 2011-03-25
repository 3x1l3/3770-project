#include <QtGui/QApplication>
#include "photos.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    photos w;
    w.show();
    return a.exec();
}
