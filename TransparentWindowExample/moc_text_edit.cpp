/****************************************************************************
** Meta object code from reading C++ file 'text_edit.h'
**
** Created: Mon Mar 21 18:52:10 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "text_edit.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'text_edit.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_TextEdit[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      17,   10,    9,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_TextEdit[] = {
    "TextEdit\0\0symbol\0receiveSymbol(Qt::Key)\0"
};

const QMetaObject TextEdit::staticMetaObject = {
    { &QLineEdit::staticMetaObject, qt_meta_stringdata_TextEdit,
      qt_meta_data_TextEdit, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &TextEdit::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *TextEdit::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *TextEdit::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TextEdit))
        return static_cast<void*>(const_cast< TextEdit*>(this));
    return QLineEdit::qt_metacast(_clname);
}

int TextEdit::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLineEdit::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: receiveSymbol((*reinterpret_cast< Qt::Key(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
