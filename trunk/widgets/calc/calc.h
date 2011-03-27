#ifndef CALC_H
#define CALC_H

#include <QtGui/QWidget>
#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QProcess>
#include <QStringList>
#include <QFile>
#include <iostream>

#include "calcbutton.h"
#include "calclineedit.h"

class Calc : public QWidget
{
    Q_OBJECT

public:
    Calc(QWidget *parent = 0);
    ~Calc();

private:
    QLineEdit *outputbox;
    QGridLayout *layout;

    QProcess *bc;

    void buildButtons();
    void buttonPressed(const QPushButton&);

    CalcButton *one;
    QPushButton *two;
    QPushButton *three;
    QPushButton *four;
    QPushButton *five;
    QPushButton *six;
    QPushButton *seven;
    QPushButton *eight;
    QPushButton *nine;
    QPushButton *clear;
    QPushButton *backspace;
    QPushButton *decimal;
    QPushButton *equal;
    QPushButton *add;
    QPushButton *subtract;
    QPushButton *multiply;
    QPushButton *divide;
    QPushButton *clearentry;
    QPushButton *negate;
    QPushButton *zero;



signals:
    void result(QString);
public slots:
    void calculateResult();

};

#endif // CALC_H
