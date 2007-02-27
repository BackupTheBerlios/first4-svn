/****************************************************************************
** Meta object code from reading C++ file 'datafrm.h'
**
** Created: Tue Feb 27 17:24:51 2007
**      by: The Qt Meta Object Compiler version 59 (Qt 4.2.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/datafrm.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'datafrm.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.2.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_datafrm[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
       9,    8,    8,    8, 0x08,
      21,    8,    8,    8, 0x08,
      33,    8,    8,    8, 0x08,
      44,    8,    8,    8, 0x08,
      56,    8,    8,    8, 0x08,
      70,   67,    8,    8, 0x08,
      95,    8,    8,    8, 0x08,
     111,    8,    8,    8, 0x08,
     128,    8,    8,    8, 0x08,
     144,    8,    8,    8, 0x08,
     152,    8,    8,    8, 0x08,
     167,    8,    8,    8, 0x08,
     183,    8,    8,    8, 0x08,
     195,    8,    8,    8, 0x08,
     211,    8,    8,    8, 0x08,
     225,    8,    8,    8, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_datafrm[] = {
    "datafrm\0\0changecmb()\0loadstock()\0loaddata()\0savetable()\0"
    "navtable()\0ce\0closeEvent(QCloseEvent*)\0newstockentry()\0"
    "editstockentry()\0delstockentry()\0print()\0contmenudata()\0"
    "contmenustock()\0removerow()\0searchentries()\0clearsearch()\0impexp()\0"
};

const QMetaObject datafrm::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_datafrm,
      qt_meta_data_datafrm, 0 }
};

const QMetaObject *datafrm::metaObject() const
{
    return &staticMetaObject;
}

void *datafrm::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_datafrm))
	return static_cast<void*>(const_cast<datafrm*>(this));
    if (!strcmp(_clname, "Ui::datafrm"))
	return static_cast<Ui::datafrm*>(const_cast<datafrm*>(this));
    return QWidget::qt_metacast(_clname);
}

int datafrm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: changecmb(); break;
        case 1: loadstock(); break;
        case 2: loaddata(); break;
        case 3: savetable(); break;
        case 4: navtable(); break;
        case 5: closeEvent((*reinterpret_cast< QCloseEvent*(*)>(_a[1]))); break;
        case 6: newstockentry(); break;
        case 7: editstockentry(); break;
        case 8: delstockentry(); break;
        case 9: print(); break;
        case 10: contmenudata(); break;
        case 11: contmenustock(); break;
        case 12: removerow(); break;
        case 13: searchentries(); break;
        case 14: clearsearch(); break;
        case 15: impexp(); break;
        }
        _id -= 16;
    }
    return _id;
}
