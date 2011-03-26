
#include "BannerWidget.h"


#include <QtGui>



BannerWidget::BannerWidget(QWidget *parent): QWidget(parent)
{
  
  setContextMenuPolicy(Qt::CustomContextMenu);

  connect(this, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(showContextMenu(const QPoint &)));

  
  bannerString = QString("Right Click Me To Edit.");
  
  banner = new QLabel();
  banner->setText(bannerString);

  
  QHBoxLayout *layout = new QHBoxLayout();
  layout->addWidget(banner);
    
  setLayout(layout);
  //setCentralWidget(banner);
  
  
  openEditWindowAction = new QAction("&Settings", this);
  openEditWindowAction->setStatusTip("Opens the settings for this widget");
  connect (openEditWindowAction, SIGNAL(triggered()), this, SLOT(openEditWindow()));
  
  setFixedSize(150,40);
}

void BannerWidget::showContextMenu(const QPoint &pos) {
    QMenu *menu = new QMenu;
    menu->addAction(openEditWindowAction);
    menu->exec(mapToGlobal(pos));
}

void BannerWidget::mousePressEvent(QMouseEvent *event)
{
  emit customContextMenuRequested(event->pos());
}

void BannerWidget::openEditWindow()
{
  
  bool ok;
  QString result = QInputDialog::getText(0, "Settings", 
     "Enter banner text:", QLineEdit::Normal, bannerString, &ok);
  
  if (ok)
  {
    bannerString=result;
    updateBannerText();
    
  }
  else
  {
    //user pressed cancel in the edit screen.
  }

  
  
}

void BannerWidget::updateBannerText()
{
  banner->setText(bannerString);
  this->update();
}

