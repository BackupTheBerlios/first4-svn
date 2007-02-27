/****************************************************************************
** Meta object code from reading C++ file 'newdatatabfrm.h'
**
** Created: Tue Feb 27 17:24:48 2007
**      by: The Qt Meta Object Compiler version 59 (Qt 4.2.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/newdatatabfrm.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'newdatatabfrm.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.2.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_newdatatabfrm[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x08,
      36,   14,   14,   14, 0x08,
      60,   14,   14,   14, 0x08,
      80,   14,   14,   14, 0x08,
     102,   14,   14,   14, 0x08,
     115,   14,   14,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_newdatatabfrm[] = {
    "newdatatabfrm\0\0on_btnadd_released()\0on_btnremove_released()\0"
    "on_btnup_released()\0on_btndown_released()\0change_rdb()\0createtable()\0"
};

const QMetaObject newdatatabfrm::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_newdatatabfrm,
      qt_meta_data_newdatatabfrm, 0 }
};

const QMetaObject *newdatatabfrm::metaObject() const
{
    return &staticMetaObject;
}

void *newdatatabfrm::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_newdatatabfrm))
	return static_cast<void*>(const_cast<newdatatabfrm*>(this));
    if (!strcmp(_clname, "Ui::newdatatabfrm"))
	return static_cast<Ui::newdatatabfrm*>(const_cast<newdatatabfrm*>(this));
    return QDialog::qt_metacast(_clname);
}

int newdatatabfrm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_btnadd_released(); break;
        case 1: on_btnremove_released(); break;
        case 2: on_btnup_released(); break;
        case 3: on_btndown_released(); break;
        case 4: change_rdb(); break;
        case 5: createtable(); break;
        }
        _id -= 6;
    }
    return _id;
}
