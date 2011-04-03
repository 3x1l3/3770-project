#ifndef CALCLINEEDIT_H
#define CALCLINEEDIT_H

#include <QLineEdit>
#include <QVariant>
#include <QMouseEvent>

class CalcLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    CalcLineEdit();

    void leaveEvent(QEvent * event);
    void paintEvent (QPaintEvent * event);
    void mouseMoveEvent (QMouseEvent * event);
    
    void setInvisible(bool setter);
    
    QRegion* fullArea;
    QRegion* noArea;
    
    
public slots:
    void appendText(QString);
    void negateText();
    void doBackspace();
    
private:
    int x, y;
    bool isInvisible;
    
};

#endif // CALCLINEEDIT_H