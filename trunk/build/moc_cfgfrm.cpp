/****************************************************************************
** Meta object code from reading C++ file 'cfgfrm.h'
**
** Created: Thu Mar 1 12:04:07 2007
**      by: The Qt Meta Object Compiler version 59 (Qt 4.2.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/cfgfrm.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cfgfrm.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.2.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_cfgfrm[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
      23,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
       8,    7,    7,    7, 0x0a,
      20,    7,    7,    7, 0x0a,
      37,    7,    7,    7, 0x0a,
      50,    7,    7,    7, 0x0a,
      63,    7,    7,    7, 0x0a,
      76,    7,    7,    7, 0x0a,
      89,    7,    7,    7, 0x0a,
      99,    7,    7,    7, 0x0a,
     116,    7,    7,    7, 0x0a,
     140,    7,    7,    7, 0x0a,
     157,    7,    7,    7, 0x0a,
     181,    7,    7,    7, 0x0a,
     204,    7,    7,    7, 0x0a,
     215,    7,    7,    7, 0x0a,
     225,    7,    7,    7, 0x0a,
     235,    7,    7,    7, 0x0a,
     248,    7,    7,    7, 0x0a,
     257,    7,    7,    7, 0x0a,
     266,    7,    7,    7, 0x0a,
     282,    7,    7,    7, 0x0a,
     300,    7,    7,    7, 0x0a,
     318,    7,    7,    7, 0x0a,
     333,    7,    7,    7, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_cfgfrm[] = {
    "cfgfrm\0\0changepwd()\0selectlangfile()\0addservers()\0delservers()\0"
    "opendbspec()\0selectuser()\0newuser()\0saveuserchange()\0"
    "loadressourcesdetails()\0seldoctemplate()\0applyresourcesdetails()\0"
    "saveresourcesdetails()\0contmenu()\0newaddr()\0newdata()\0newaccount()\0"
    "rentab()\0deltab()\0selectdocpath()\0selecttemplpath()\0"
    "savedefaultpath()\0savesettings()\0saveowndata()\0"
};

const QMetaObject cfgfrm::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_cfgfrm,
      qt_meta_data_cfgfrm, 0 }
};

const QMetaObject *cfgfrm::metaObject() const
{
    return &staticMetaObject;
}

void *cfgfrm::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_cfgfrm))
	return static_cast<void*>(const_cast<cfgfrm*>(this));
    if (!strcmp(_clname, "Ui::cfgfrm"))
	return static_cast<Ui::cfgfrm*>(const_cast<cfgfrm*>(this));
    return QWidget::qt_metacast(_clname);
}

int cfgfrm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: changepwd(); break;
        case 1: selectlangfile(); break;
        case 2: addservers(); break;
        case 3: delservers(); break;
        case 4: opendbspec(); break;
        case 5: selectuser(); break;
        case 6: newuser(); break;
        case 7: saveuserchange(); break;
        case 8: loadressourcesdetails(); break;
        case 9: seldoctemplate(); break;
        case 10: applyresourcesdetails(); break;
        case 11: saveresourcesdetails(); break;
        case 12: contmenu(); break;
        case 13: newaddr(); break;
        case 14: newdata(); break;
        case 15: newaccount(); break;
        case 16: rentab(); break;
        case 17: deltab(); break;
        case 18: selectdocpath(); break;
        case 19: selecttemplpath(); break;
        case 20: savedefaultpath(); break;
        case 21: savesettings(); break;
        case 22: saveowndata(); break;
        }
        _id -= 23;
    }
    return _id;
}
