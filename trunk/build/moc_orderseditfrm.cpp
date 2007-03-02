/****************************************************************************
** Meta object code from reading C++ file 'orderseditfrm.h'
**
** Created: Thu Mar 1 12:04:26 2007
**      by: The Qt Meta Object Compiler version 59 (Qt 4.2.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/orderseditfrm.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'orderseditfrm.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.2.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_orderseditfrm[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x08,
      26,   14,   14,   14, 0x08,
      40,   37,   14,   14, 0x0a,
      59,   14,   14,   14, 0x0a,
      73,   14,   14,   14, 0x0a,
      86,   14,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_orderseditfrm[] = {
    "orderseditfrm\0\0newentry()\0updentry()\0ID\0editentry(QString)\0"
    "changeprice()\0clearstock()\0checkstock()\0"
};

const QMetaObject orderseditfrm::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_orderseditfrm,
      qt_meta_data_orderseditfrm, 0 }
};

const QMetaObject *orderseditfrm::metaObject() const
{
    return &staticMetaObject;
}

void *orderseditfrm::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_orderseditfrm))
	return static_cast<void*>(const_cast<orderseditfrm*>(this));
    if (!strcmp(_clname, "Ui::orderseditfrm"))
	return static_cast<Ui::orderseditfrm*>(const_cast<orderseditfrm*>(this));
    return QDialog::qt_metacast(_clname);
}

int orderseditfrm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: newentry(); break;
        case 1: updentry(); break;
        case 2: editentry((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: changeprice(); break;
        case 4: clearstock(); break;
        case 5: checkstock(); break;
        }
        _id -= 6;
    }
    return _id;
}
