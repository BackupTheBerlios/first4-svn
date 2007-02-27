/****************************************************************************
** Meta object code from reading C++ file 'procfrm.h'
**
** Created: Tue Feb 27 17:24:53 2007
**      by: The Qt Meta Object Compiler version 59 (Qt 4.2.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/procfrm.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'procfrm.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.2.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_procfrm[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets

       0        // eod
};

static const char qt_meta_stringdata_procfrm[] = {
    "procfrm\0"
};

const QMetaObject procfrm::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_procfrm,
      qt_meta_data_procfrm, 0 }
};

const QMetaObject *procfrm::metaObject() const
{
    return &staticMetaObject;
}

void *procfrm::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_procfrm))
	return static_cast<void*>(const_cast<procfrm*>(this));
    if (!strcmp(_clname, "Ui::Form"))
	return static_cast<Ui::Form*>(const_cast<procfrm*>(this));
    return QWidget::qt_metacast(_clname);
}

int procfrm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
