/****************************************************************************
** Meta object code from reading C++ file 'docopenfrm.h'
**
** Created: Tue Feb 27 17:25:17 2007
**      by: The Qt Meta Object Compiler version 59 (Qt 4.2.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/docopenfrm.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'docopenfrm.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.2.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_docopenfrm[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x08,
      29,   11,   11,   11, 0x08,
      40,   11,   11,   11, 0x08,
      58,   11,   11,   11, 0x08,
      70,   11,   11,   11, 0x08,
      79,   11,   11,   11, 0x08,
      89,   11,   11,   11, 0x08,
      97,   11,   11,   11, 0x08,
     109,   11,   11,   11, 0x08,
     123,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_docopenfrm[] = {
    "docopenfrm\0\0adressbtnonoff()\0loaddocs()\0loaddocsdetails()\0"
    "deletedoc()\0newdoc()\0editdoc()\0print()\0searchdoc()\0clearsearch()\0"
    "openseladressfrm()\0"
};

const QMetaObject docopenfrm::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_docopenfrm,
      qt_meta_data_docopenfrm, 0 }
};

const QMetaObject *docopenfrm::metaObject() const
{
    return &staticMetaObject;
}

void *docopenfrm::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_docopenfrm))
	return static_cast<void*>(const_cast<docopenfrm*>(this));
    if (!strcmp(_clname, "Ui::docopenfrm"))
	return static_cast<Ui::docopenfrm*>(const_cast<docopenfrm*>(this));
    return QWidget::qt_metacast(_clname);
}

int docopenfrm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: adressbtnonoff(); break;
        case 1: loaddocs(); break;
        case 2: loaddocsdetails(); break;
        case 3: deletedoc(); break;
        case 4: newdoc(); break;
        case 5: editdoc(); break;
        case 6: print(); break;
        case 7: searchdoc(); break;
        case 8: clearsearch(); break;
        case 9: openseladressfrm(); break;
        }
        _id -= 10;
    }
    return _id;
}
