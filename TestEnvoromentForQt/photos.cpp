#include "photos.h"

photos::photos(QWidget *parent) : QWidget(parent)
{
    this->currentfile = 0;
    filter << "*.png" << "*.jpg" << "*.gif" << "*.bmp";
    imageDialog = new QFileDialog(this);
    imageDialog->setAcceptMode(QFileDialog::AcceptOpen);
    imageDialog->setFileMode(QFileDialog::Directory);
    imageDialog->setOption(QFileDialog::ShowDirsOnly);
    label = new QLabel(this);
    
    QLabel *info = new QLabel(this);
    
    info->setText("Photo Viewer. Right click to change.");
    
    info->show();
    
    label->setScaledContents(true);
    image = new QPixmap();
    this->setFixedSize(300, 250);
    this->setContextMenuPolicy(Qt::CustomContextMenu);

    context = new QMenu();
    changedirAct = new QAction(tr("Select pictures directory"), this);
    context->addAction(changedirAct);

    label->setPixmap(*image);
    label->resize(0.25 * label->pixmap()->size());

    nofiles = new QMessageBox(this);
    nofiles->setText("No files found in directory");

    connect(changedirAct, SIGNAL(triggered()), this, SLOT(changeDir()));

    connect(this, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(showContextMenu(const QPoint&)));
    connect(imageDialog, SIGNAL(fileSelected(QString)), this, SLOT(loadImages(QString)));

    isInvisible = true;
    this->setMouseTracking(true);
    label->setMouseTracking(true);
}

void photos::loadImages(QString dir) {
  this->directory = dir;
  this->directory.append("/");
  directoryAccess = new QDir(dir);
  directoryAccess->setFilter(QDir::Files);
  this->files = directoryAccess->entryList(this->filter, QDir::Files);

  if (this->files.empty()) {
      this->nofiles->show();
  } else {
     startTimer(8000);
 }

   this->currentfile = 0;

}

void photos::timerEvent(QTimerEvent *event) {

    delete this->image;
    this->image = new QPixmap();
    if (!this->files.empty()) {
    if (this->currentfile < this->files.size()-1) {

     image->load(this->directory + this->files.at(this->currentfile));
     this->currentfile++;

        }
    else {

        this->image->load(this->directory + this->files.at(this->currentfile) );
        this->currentfile = 0;
    }
}
    label->setPixmap(*image);
    label->resize(0.25 * label->pixmap()->size());

    this->update();

}



void photos::showContextMenu(const QPoint & pos) {
    QPoint globalpos = this->mapToGlobal(pos);

    QAction* selecteditem = this->context->exec(globalpos);
    if (selecteditem) {

    }
}

void photos::changeDir() {
    this->imageDialog->show();
}

photos::~photos()
{

}

void photos::paintEvent(QPaintEvent* e)
{
  QWidget::paintEvent(e);

}

void photos::mouseMoveEvent(QMouseEvent* e)
{
    QWidget::mouseMoveEvent(e);
    
    x = e->x();
    y = e->y();
}

