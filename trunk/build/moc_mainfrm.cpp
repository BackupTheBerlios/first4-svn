/****************************************************************************
** Meta object code from reading C++ file 'mainfrm.h'
**
** Created: Tue Feb 27 17:24:41 2007
**      by: The Qt Meta Object Compiler version 59 (Qt 4.2.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/mainfrm.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainfrm.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.2.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_mainfrm[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      12,    9,    8,    8, 0x08,
      37,    8,    8,    8, 0x0a,
      48,    8,    8,    8, 0x0a,
      57,    8,    8,    8, 0x0a,
      65,    8,    8,    8, 0x0a,
      78,    8,    8,    8, 0x0a,
      91,    8,    8,    8, 0x0a,
     104,    8,    8,    8, 0x0a,
     116,    8,    8,    8, 0x0a,
     126,    8,    8,    8, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_mainfrm[] = {
    "mainfrm\0\0ce\0closeEvent(QCloseEvent*)\0checkmsg()\0config()\0about()\0"
    "browseaddr()\0browsedata()\0vieworders()\0inventory()\0opendoc()\0"
    "newdoc()\0"
};

const QMetaObject mainfrm::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_mainfrm,
      qt_meta_data_mainfrm, 0 }
};

const QMetaObject *mainfrm::metaObject() const
{
    return &staticMetaObject;
}

void *mainfrm::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_mainfrm))
	return static_cast<void*>(const_cast<mainfrm*>(this));
    if (!strcmp(_clname, "Ui::mainfrm"))
	return static_cast<Ui::mainfrm*>(const_cast<mainfrm*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int mainfrm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: closeEvent((*reinterpret_cast< QCloseEvent*(*)>(_a[1]))); break;
        case 1: checkmsg(); break;
        case 2: config(); break;
        case 3: about(); break;
        case 4: browseaddr(); break;
        case 5: browsedata(); break;
        case 6: vieworders(); break;
        case 7: inventory(); break;
        case 8: opendoc(); break;
        case 9: newdoc(); break;
        }
        _id -= 10;
    }
    return _id;
}
