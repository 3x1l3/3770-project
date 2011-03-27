#include "calclineedit.h"

CalcLineEdit::CalcLineEdit()
{
}
void CalcLineEdit::appendText(QString text) {

    this->setText(this->text()+ text);

}
