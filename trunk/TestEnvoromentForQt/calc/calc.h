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
#include "../dockwidget.h"

class Calc : public DockWidget
{
    Q_OBJECT

public:
    Calc(DockWidget *parent = 0);
    ~Calc();

private:
    CalcLineEdit *outputbox;
    QGridLayout *layout;

    QProcess *bc;

    void buildButtons();
    void buttonPressed(const QPushButton&);

    CalcButton *one;
    CalcButton *two;
    CalcButton *three;
    CalcButton *four;
    CalcButton *five;
    CalcButton *six;
    CalcButton *seven;
    CalcButton *eight;
    CalcButton *nine;
    CalcButton *clear;
    CalcButton *backspace;
    CalcButton *decimal;
    CalcButton *equal;
    CalcButton *add;
    CalcButton *subtract;
    CalcButton *multiply;
    CalcButton *divide;
    CalcButton *clearentry;
    CalcButton *negate;
    CalcButton *zero;



signals:
    void result(QString);
public slots:
    void calculateResult();

};

#endif // CALC_H
