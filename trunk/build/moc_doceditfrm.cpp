/****************************************************************************
** Meta object code from reading C++ file 'doceditfrm.h'
**
** Created: Thu Mar 1 14:30:15 2007
**      by: The Qt Meta Object Compiler version 59 (Qt 4.2.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/doceditfrm.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'doceditfrm.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.2.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_doceditfrm[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
      19,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x08,
      28,   11,   11,   11, 0x08,
      43,   11,   11,   11, 0x08,
      54,   11,   11,   11, 0x08,
      65,   11,   11,   11, 0x08,
      77,   11,   11,   11, 0x08,
      88,   11,   11,   11, 0x08,
      98,   11,   11,   11, 0x08,
     111,   11,   11,   11, 0x08,
     134,  125,   11,   11, 0x08,
     152,   11,   11,   11, 0x08,
     181,  169,   11,   11, 0x08,
     206,   11,   11,   11, 0x08,
     223,   11,   11,   11, 0x08,
     241,   11,   11,   11, 0x08,
     255,   11,   11,   11, 0x08,
     265,   11,   11,   11, 0x0a,
     284,   11,   11,   11, 0x0a,
     295,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_doceditfrm[] = {
    "doceditfrm\0\0selectaddress()\0printpreview()\0printesr()\0contmenu()\0"
    "removerow()\0navtable()\0checkdb()\0clearlblid()\0completedoc()\0"
    "complete\0printreport(bool)\0registeramount()\0dbID,amount\0"
    "revenue(QString,QString)\0refreshstockdb()\0savecompletedoc()\0"
    "newdocument()\0opendoc()\0selecteddocument()\0calc_tot()\0print()\0"
};

const QMetaObject doceditfrm::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_doceditfrm,
      qt_meta_data_doceditfrm, 0 }
};

const QMetaObject *doceditfrm::metaObject() const
{
    return &staticMetaObject;
}

void *doceditfrm::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_doceditfrm))
	return static_cast<void*>(const_cast<doceditfrm*>(this));
    if (!strcmp(_clname, "Ui::doceditfrm"))
	return static_cast<Ui::doceditfrm*>(const_cast<doceditfrm*>(this));
    return QWidget::qt_metacast(_clname);
}

int doceditfrm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: selectaddress(); break;
        case 1: printpreview(); break;
        case 2: printesr(); break;
        case 3: contmenu(); break;
        case 4: removerow(); break;
        case 5: navtable(); break;
        case 6: checkdb(); break;
        case 7: clearlblid(); break;
        case 8: completedoc(); break;
        case 9: printreport((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: registeramount(); break;
        case 11: revenue((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 12: refreshstockdb(); break;
        case 13: savecompletedoc(); break;
        case 14: newdocument(); break;
        case 15: opendoc(); break;
        case 16: selecteddocument(); break;
        case 17: calc_tot(); break;
        case 18: print(); break;
        }
        _id -= 19;
    }
    return _id;
}
