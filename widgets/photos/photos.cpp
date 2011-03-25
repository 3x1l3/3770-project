#include "photos.h"

photos::photos(QWidget *parent)
    : QWidget(parent)
{
    this->currentfile = 0;
    filter << "*.png" << "*.jpg" << "*.gif" << "*.bmp";
    imageDialog = new QFileDialog(this);
    imageDialog->setAcceptMode(QFileDialog::AcceptOpen);
    imageDialog->setFileMode(QFileDialog::Directory);
    imageDialog->setOption(QFileDialog::ShowDirsOnly);
    label = new QLabel(this);
    label->setScaledContents(true);
    image = new QPixmap();
    this->setFixedSize(300, 200);

    imageDialog->show();

    context = new QMenu(this);
    context->addAction(new QAction("Test", context));

    label->setPixmap(*image);
    label->resize(0.25 * label->pixmap()->size());

    connect(imageDialog, SIGNAL(fileSelected(QString)), this, SLOT(loadImages(QString)));

}

void photos::loadImages(QString dir) {
  this->directory = dir;
  this->directory.append("/");
  directoryAccess = new QDir(dir);
  directoryAccess->setFilter(QDir::Files);
  this->files = directoryAccess->entryList(this->filter, QDir::Files);

  QStringList::const_iterator constIterator;
     for (constIterator = this->files.constBegin(); constIterator != this->files.constEnd();
            ++constIterator)
         std::cout << (*constIterator).toLocal8Bit().constData() << std::endl;

     startTimer(1000);


   this->currentfile = 0;

}

void photos::timerEvent(QTimerEvent *event) {

    delete this->image;
    this->image = new QPixmap();
    if (this->currentfile < this->files.size()-1) {

     image->load(this->directory + this->files.at(this->currentfile));
     this->currentfile++;

        }
    else {

        this->image->load(this->directory + this->files.at(this->currentfile) );
        this->currentfile = 0;
    }
    label->setPixmap(*image);
    label->resize(0.25 * label->pixmap()->size());

    this->update();

}

void photos::mousePressEvent(QMouseEvent *event) {
    QWidget::mousePressEvent(event);

    if (event->button() == Qt::RightButton) {
        this->context->move(event->pos().x(), event->pos().y()+20);
        this->context->exec();

    }

}


photos::~photos()
{

}
