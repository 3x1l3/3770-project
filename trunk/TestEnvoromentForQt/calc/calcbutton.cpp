#include "calcbutton.h"

CalcButton::CalcButton() {
    connect(this, SIGNAL(clicked()), this, SLOT(isPressed()));
    setMouseTracking(true);
}

void CalcButton::isPressed() {
    emit buttonText(this->text());
}

void CalcButton::negate() {

}

