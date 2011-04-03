#include "calclineedit.h"

CalcLineEdit::CalcLineEdit()
{
  isInvisible = false;
   isInvisible = true;
  setMouseTracking(true);
  fullArea = new QRegion(0, 0, width(), height(), QRegion::Rectangle);
  noArea = new QRegion(15,15,50,50, QRegion::Rectangle); 
}

void CalcLineEdit::leaveEvent(QEvent* event)
{
    QLineEdit::leaveEvent(event);
    setMask(*fullArea);
}

void CalcLineEdit::mouseMoveEvent(QMouseEvent* event)
{ 
    if(isInvisible)
    {
      event->ignore();
    }
  
    QLineEdit::mouseMoveEvent(event);
    
    x = event->x();
    y = event->y();
    update();
}


void CalcLineEdit::paintEvent(QPaintEvent* event)
{
    QLineEdit::paintEvent(event);
    
   // QPainter painter(this);
    
    QPolygon myPolygon = QPolygon::QPolygon(QRect(0,0,width(), height()));
    QPolygon mousePolygon = QPolygon::QPolygon(QRect(x, y, 3, 3));
    
    myPolygon = myPolygon.subtracted(mousePolygon);
  //   cout << x << " " << y << " " << isInvisible << " " << true << " " << underMouse() <<  endl;
    *noArea = QRegion(myPolygon,Qt::OddEvenFill );
    *fullArea = QRegion(QRect(0,0,width(),height()));
    
    if(isInvisible && underMouse())
    {
  //     cout << "\nIS UNDER MOUSE\n";
	  setMask(*noArea);
    }
    
}

void CalcLineEdit::setInvisible(bool setter)
{
  isInvisible = setter;
}


void CalcLineEdit::appendText(QString text) {

    this->setText(this->text()+ text);

}

void CalcLineEdit::doBackspace() {
    this->backspace();
}

void CalcLineEdit::negateText() {
    float num = this->text().toFloat();
    num*=-1;
    QVariant v(num);
    this->setText(v.toString());

}