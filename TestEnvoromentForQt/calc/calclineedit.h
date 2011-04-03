#ifndef CALCLINEEDIT_H
#define CALCLINEEDIT_H

#include <QLineEdit>
#include <QVariant>

class CalcLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    CalcLineEdit();

public slots:
    void appendText(QString);
    void negateText();
    void doBackspace();
};

#endif // CALCLINEEDIT_H
