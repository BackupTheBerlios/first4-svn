/****************************************************************************
** Meta object code from reading C++ file 'dataeditfrm.h'
**
** Created: Tue Feb 27 17:24:54 2007
**      by: The Qt Meta Object Compiler version 59 (Qt 4.2.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/dataeditfrm.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dataeditfrm.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.2.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_dataeditfrm[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x0a,
      26,   12,   12,   12, 0x0a,
      39,   12,   12,   12, 0x0a,
      50,   12,   12,   12, 0x0a,
      61,   12,   12,   12, 0x0a,
      73,   12,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_dataeditfrm[] = {
    "dataeditfrm\0\0acceptdata()\0seladdress()\0contmenu()\0acceptsp()\0"
    "removerow()\0addrow()\0"
};

const QMetaObject dataeditfrm::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_dataeditfrm,
      qt_meta_data_dataeditfrm, 0 }
};

const QMetaObject *dataeditfrm::metaObject() const
{
    return &staticMetaObject;
}

void *dataeditfrm::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_dataeditfrm))
	return static_cast<void*>(const_cast<dataeditfrm*>(this));
    if (!strcmp(_clname, "Ui::dataeditfrm"))
	return static_cast<Ui::dataeditfrm*>(const_cast<dataeditfrm*>(this));
    return QDialog::qt_metacast(_clname);
}

int dataeditfrm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: acceptdata(); break;
        case 1: seladdress(); break;
        case 2: contmenu(); break;
        case 3: acceptsp(); break;
        case 4: removerow(); break;
        case 5: addrow(); break;
        }
        _id -= 6;
    }
    return _id;
}
