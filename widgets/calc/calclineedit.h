#ifndef CALCLINEEDIT_H
#define CALCLINEEDIT_H

#include <QLineEdit>

class CalcLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    CalcLineEdit();

public slots:
    void appendText(QString);
};

#endif // CALCLINEEDIT_H
