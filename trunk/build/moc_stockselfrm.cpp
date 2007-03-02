/****************************************************************************
** Meta object code from reading C++ file 'stockselfrm.h'
**
** Created: Thu Mar 1 12:04:28 2007
**      by: The Qt Meta Object Compiler version 59 (Qt 4.2.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/stockselfrm.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'stockselfrm.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.2.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_stockselfrm[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets

       0        // eod
};

static const char qt_meta_stringdata_stockselfrm[] = {
    "stockselfrm\0"
};

const QMetaObject stockselfrm::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_stockselfrm,
      qt_meta_data_stockselfrm, 0 }
};

const QMetaObject *stockselfrm::metaObject() const
{
    return &staticMetaObject;
}

void *stockselfrm::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_stockselfrm))
	return static_cast<void*>(const_cast<stockselfrm*>(this));
    if (!strcmp(_clname, "Ui::stockselfrm"))
	return static_cast<Ui::stockselfrm*>(const_cast<stockselfrm*>(this));
    return QDialog::qt_metacast(_clname);
}

int stockselfrm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
