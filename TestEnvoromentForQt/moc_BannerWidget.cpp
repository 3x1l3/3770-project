/****************************************************************************
** Meta object code from reading C++ file 'BannerWidget.h'
**
** Created: Fri Apr 15 16:05:12 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "BannerWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'BannerWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_BannerWidget[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x05,

 // slots: signature, parameters, type, tag, flags
      49,   13,   13,   13, 0x08,
      73,   13,   13,   13, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_BannerWidget[] = {
    "BannerWidget\0\0customContextMenuRequested(QPoint)\0"
    "showContextMenu(QPoint)\0openEditWindow()\0"
};

const QMetaObject BannerWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_BannerWidget,
      qt_meta_data_BannerWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &BannerWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *BannerWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *BannerWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_BannerWidget))
        return static_cast<void*>(const_cast< BannerWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int BannerWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: customContextMenuRequested((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 1: showContextMenu((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 2: openEditWindow(); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void BannerWidget::customContextMenuRequested(const QPoint & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
