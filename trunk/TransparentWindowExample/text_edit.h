#ifndef TEXT_EDIT_H
#define TEXT_EDIT_H

#include <QLineEdit>
#include <QMessageBox>

class TextEdit : public QLineEdit {

  Q_OBJECT

public:

  TextEdit(QWidget *parent = 0): QLineEdit(parent) {}

public slots:

  void receiveSymbol(Qt::Key symbol) { 
    if (symbol == Qt::Key_Backspace)
      backspace();
    else if (symbol == Qt::Key_Space)
      insert(" ");
    else if (symbol == Qt::Key_Enter)
      QMessageBox::information(this, "Message", text());
    else
      insert(QString("%1").arg( (char)symbol ));
  }

};

#endif

