/****************************************************************************
** Meta object code from reading C++ file 'aboutfrm.h'
**
** Created: Tue Feb 27 17:24:44 2007
**      by: The Qt Meta Object Compiler version 59 (Qt 4.2.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/aboutfrm.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'aboutfrm.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.2.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_aboutfrm[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_aboutfrm[] = {
    "aboutfrm\0\0on_okButton_clicked()\0"
};

const QMetaObject aboutfrm::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_aboutfrm,
      qt_meta_data_aboutfrm, 0 }
};

const QMetaObject *aboutfrm::metaObject() const
{
    return &staticMetaObject;
}

void *aboutfrm::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_aboutfrm))
	return static_cast<void*>(const_cast<aboutfrm*>(this));
    if (!strcmp(_clname, "Ui::aboutfrm"))
	return static_cast<Ui::aboutfrm*>(const_cast<aboutfrm*>(this));
    return QDialog::qt_metacast(_clname);
}

int aboutfrm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_okButton_clicked(); break;
        }
        _id -= 1;
    }
    return _id;
}
