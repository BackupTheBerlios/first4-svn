/****************************************************************************
** Meta object code from reading C++ file 'ordersfrm.h'
**
** Created: Thu Mar 1 12:04:25 2007
**      by: The Qt Meta Object Compiler version 59 (Qt 4.2.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/ordersfrm.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ordersfrm.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.2.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_ordersfrm[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x0a,
      25,   10,   10,   10, 0x0a,
      36,   10,   10,   10, 0x0a,
      48,   10,   10,   10, 0x0a,
      62,   10,   10,   10, 0x0a,
      73,   10,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ordersfrm[] = {
    "ordersfrm\0\0loadentries()\0newentry()\0editentry()\0deleteentry()\0"
    "complete()\0contmenu()\0"
};

const QMetaObject ordersfrm::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ordersfrm,
      qt_meta_data_ordersfrm, 0 }
};

const QMetaObject *ordersfrm::metaObject() const
{
    return &staticMetaObject;
}

void *ordersfrm::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ordersfrm))
	return static_cast<void*>(const_cast<ordersfrm*>(this));
    if (!strcmp(_clname, "Ui::ordersfrm"))
	return static_cast<Ui::ordersfrm*>(const_cast<ordersfrm*>(this));
    return QWidget::qt_metacast(_clname);
}

int ordersfrm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: loadentries(); break;
        case 1: newentry(); break;
        case 2: editentry(); break;
        case 3: deleteentry(); break;
        case 4: complete(); break;
        case 5: contmenu(); break;
        }
        _id -= 6;
    }
    return _id;
}
