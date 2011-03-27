#include "calcbutton.h"

CalcButton::CalcButton() {
    connect(this, SIGNAL(clicked()), this, SLOT(isPressed()));
}

void CalcButton::isPressed() {
    emit buttonText(this->text());
}

