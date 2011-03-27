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

public slots:
   void isPressed();

};

#endif // CALCBUTTON_H
