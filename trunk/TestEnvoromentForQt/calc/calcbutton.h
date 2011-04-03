#ifndef CALCBUTTON_H
#define CALCBUTTON_H

#include <QPushButton>

class CalcButton : public QPushButton
{

    Q_OBJECT

public:
    CalcButton();

private:
   void pressed();

signals:
   void buttonText(QString);
   void clearText();
   void negateText();

public slots:
   void isPressed();
   void negate();

};

#endif // CALCBUTTON_H
