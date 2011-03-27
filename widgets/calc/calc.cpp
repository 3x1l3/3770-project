#include "calc.h"

Calc::Calc(QWidget *parent)
    : QWidget(parent)
{
    layout = new QGridLayout(this);
    outputbox = new CalcLineEdit();
    outputbox->setFont(QFont("verdana",20));
    outputbox->setAlignment(Qt::AlignRight);
    layout->addWidget(outputbox, 0, 0, 1, 4);
    this->buildButtons();
    bc = new QProcess(this);

    connect(this, SIGNAL(result(QString)), outputbox, SLOT(setText(QString)));
}

void Calc::buildButtons() {

    one = new CalcButton();
    one->setText("1");
    layout->addWidget(one, 5, 0, 1, 1);
    connect(one, SIGNAL(buttonText(QString)), outputbox, SLOT(appendText(QString)));

    two = new CalcButton();
    two->setText("2");
    layout->addWidget(two, 5, 1, 1, 1);
     connect(two, SIGNAL(buttonText(QString)), outputbox, SLOT(appendText(QString)));

    three = new CalcButton();
    three->setText("3");
    layout->addWidget(three, 5, 2, 1, 1);
     connect(three, SIGNAL(buttonText(QString)), outputbox, SLOT(appendText(QString)));

    four = new CalcButton();
    four->setText("4");
    layout->addWidget(four, 4, 0, 1, 1);
     connect(four, SIGNAL(buttonText(QString)), outputbox, SLOT(appendText(QString)));

    five = new CalcButton();
    five->setText("5");
    layout->addWidget(five, 4, 1, 1, 1);
     connect(five, SIGNAL(buttonText(QString)), outputbox, SLOT(appendText(QString)));

    six = new CalcButton();
    six->setText("6");
    layout->addWidget(six, 4, 2, 1, 1);
     connect(six, SIGNAL(buttonText(QString)), outputbox, SLOT(appendText(QString)));

     seven = new CalcButton();
    seven->setText("7");
    layout->addWidget(seven, 3, 0, 1, 1);
 connect(seven, SIGNAL(buttonText(QString)), outputbox, SLOT(appendText(QString)));

    eight = new CalcButton();
    eight->setText("8");
    layout->addWidget(eight, 3, 1, 1, 1);
     connect(eight, SIGNAL(buttonText(QString)), outputbox, SLOT(appendText(QString)));

    nine = new CalcButton();
    nine->setText("9");
    layout->addWidget(nine, 3, 2, 1, 1);
     connect(nine, SIGNAL(buttonText(QString)), outputbox, SLOT(appendText(QString)));

    clear = new CalcButton();
    clear->setText("Clear");
    layout->addWidget(clear, 2, 2, 1, 1);
     connect(two, SIGNAL(buttonText(QString)), outputbox, SLOT(setText(QString)));

    add = new CalcButton();
    add->setText("+");
    layout->addWidget(add, 6, 3, 1, 1);
    connect(add, SIGNAL(buttonText(QString)), outputbox, SLOT(appendText(QString)));

    subtract = new CalcButton();
    subtract->setText("-");
    layout->addWidget(subtract, 5, 3, 1, 1);
     connect(subtract, SIGNAL(buttonText(QString)), outputbox, SLOT(appendText(QString)));

    multiply = new CalcButton();
    multiply->setText("*");
    layout->addWidget(multiply, 4, 3, 1, 1);
     connect(multiply, SIGNAL(buttonText(QString)), outputbox, SLOT(appendText(QString)));

    negate = new CalcButton();
    negate->setText("Negate");
    layout->addWidget(negate, 2, 3, 1, 1);

    divide = new CalcButton();
    divide->setText("/");
    layout->addWidget(divide, 3, 3, 1, 1);
     connect(divide, SIGNAL(buttonText(QString)), outputbox, SLOT(appendText(QString)));

    clearentry = new CalcButton();
    clearentry->setText("CE");
    layout->addWidget(clearentry, 2, 1, 1, 1);

    backspace = new CalcButton();
    backspace->setText("BKSP");
    layout->addWidget(backspace, 2, 0, 1, 1);

    decimal = new CalcButton();
    decimal->setText(".");
    layout->addWidget(decimal, 6, 1, 1, 1);
     connect(decimal, SIGNAL(buttonText(QString)), outputbox, SLOT(appendText(QString)));

    zero = new CalcButton();
    zero->setText("0");
    layout->addWidget(zero, 6, 0, 1, 1);
     connect(zero, SIGNAL(buttonText(QString)), outputbox, SLOT(appendText(QString)));

    equal = new CalcButton();
    equal->setText("=");
    layout->addWidget(equal, 6, 2, 1, 1);
    connect(equal, SIGNAL(clicked()), this, SLOT(calculateResult()));

}

void Calc::buttonPressed(const QPushButton& button) {



}

void Calc::calculateResult() {
    QStringList list;
    list << "-c" << "echo " + this->outputbox->text() + " | /usr/bin/bc";
    bc->start("/bin/sh", list);
    bc->waitForFinished();
    QString output = QString(bc->readAllStandardOutput());
    emit result(output);
    bc->terminate();
}

Calc::~Calc()
{

}
