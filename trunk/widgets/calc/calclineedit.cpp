#include "calclineedit.h"

CalcLineEdit::CalcLineEdit()
{
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
