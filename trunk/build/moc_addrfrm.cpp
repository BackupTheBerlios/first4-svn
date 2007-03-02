/****************************************************************************
** Meta object code from reading C++ file 'addrfrm.h'
**
** Created: Thu Mar 1 12:04:14 2007
**      by: The Qt Meta Object Compiler version 59 (Qt 4.2.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/addrfrm.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'addrfrm.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.2.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_addrfrm[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
      22,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      12,    9,    8,    8, 0x08,
      37,    8,    8,    8, 0x08,
      54,    8,    8,    8, 0x08,
      66,    8,    8,    8, 0x08,
      81,    8,    8,    8, 0x08,
      95,    8,    8,    8, 0x08,
     109,    8,    8,    8, 0x08,
     123,    8,    8,    8, 0x08,
     137,    8,    8,    8, 0x08,
     151,    8,    8,    8, 0x08,
     165,    8,    8,    8, 0x08,
     175,    8,    8,    8, 0x08,
     186,    8,    8,    8, 0x08,
     196,    8,    8,    8, 0x08,
     210,    8,    8,    8, 0x08,
     219,    8,    8,    8, 0x08,
     231,    8,    8,    8, 0x08,
     241,    8,    8,    8, 0x08,
     253,    8,    8,    8, 0x08,
     264,    8,    8,    8, 0x08,
     284,  279,    8,    8, 0x08,
     302,    8,    8,    8, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_addrfrm[] = {
    "addrfrm\0\0ce\0closeEvent(QCloseEvent*)\0loadaddrdetail()\0loadaddrs()\0"
    "loaddocsdata()\0openauftrag()\0changecust1()\0changecust2()\0"
    "changecust3()\0changecust4()\0changecust5()\0newaddr()\0saveaddr()\0"
    "deladdr()\0clearsearch()\0search()\0printaddr()\0opendoc()\0deletedoc()\0"
    "contmenu()\0contmenuaddr()\0dest\0moveaddr(QString)\0impexp()\0"
};

const QMetaObject addrfrm::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_addrfrm,
      qt_meta_data_addrfrm, 0 }
};

const QMetaObject *addrfrm::metaObject() const
{
    return &staticMetaObject;
}

void *addrfrm::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_addrfrm))
	return static_cast<void*>(const_cast<addrfrm*>(this));
    if (!strcmp(_clname, "Ui::addrfrm"))
	return static_cast<Ui::addrfrm*>(const_cast<addrfrm*>(this));
    return QWidget::qt_metacast(_clname);
}

int addrfrm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: closeEvent((*reinterpret_cast< QCloseEvent*(*)>(_a[1]))); break;
        case 1: loadaddrdetail(); break;
        case 2: loadaddrs(); break;
        case 3: loaddocsdata(); break;
        case 4: openauftrag(); break;
        case 5: changecust1(); break;
        case 6: changecust2(); break;
        case 7: changecust3(); break;
        case 8: changecust4(); break;
        case 9: changecust5(); break;
        case 10: newaddr(); break;
        case 11: saveaddr(); break;
        case 12: deladdr(); break;
        case 13: clearsearch(); break;
        case 14: search(); break;
        case 15: printaddr(); break;
        case 16: opendoc(); break;
        case 17: deletedoc(); break;
        case 18: contmenu(); break;
        case 19: contmenuaddr(); break;
        case 20: moveaddr((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 21: impexp(); break;
        }
        _id -= 22;
    }
    return _id;
}
