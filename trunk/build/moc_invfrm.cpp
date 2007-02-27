/****************************************************************************
** Meta object code from reading C++ file 'invfrm.h'
**
** Created: Tue Feb 27 17:25:09 2007
**      by: The Qt Meta Object Compiler version 59 (Qt 4.2.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/invfrm.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'invfrm.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.2.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_invfrm[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      11,    8,    7,    7, 0x08,
      36,    7,    7,    7, 0x0a,
      48,    7,    7,    7, 0x0a,
      58,    7,    7,    7, 0x0a,
      66,    7,    7,    7, 0x0a,
      81,    7,    7,    7, 0x0a,
      92,    7,    7,    7, 0x0a,
     101,    7,    7,    7, 0x0a,
     116,    7,    7,    7, 0x0a,
     127,    7,    7,    7, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_invfrm[] = {
    "invfrm\0\0ce\0closeEvent(QCloseEvent*)\0setchange()\0loadinv()\0print()\0"
    "printpreview()\0complete()\0newinv()\0viewcomments()\0savedata()\0"
    "loaddata()\0"
};

const QMetaObject invfrm::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_invfrm,
      qt_meta_data_invfrm, 0 }
};

const QMetaObject *invfrm::metaObject() const
{
    return &staticMetaObject;
}

void *invfrm::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_invfrm))
	return static_cast<void*>(const_cast<invfrm*>(this));
    if (!strcmp(_clname, "Ui::invfrm"))
	return static_cast<Ui::invfrm*>(const_cast<invfrm*>(this));
    return QWidget::qt_metacast(_clname);
}

int invfrm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: closeEvent((*reinterpret_cast< QCloseEvent*(*)>(_a[1]))); break;
        case 1: setchange(); break;
        case 2: loadinv(); break;
        case 3: print(); break;
        case 4: printpreview(); break;
        case 5: complete(); break;
        case 6: newinv(); break;
        case 7: viewcomments(); break;
        case 8: savedata(); break;
        case 9: loaddata(); break;
        }
        _id -= 10;
    }
    return _id;
}
