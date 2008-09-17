/****************************************************************************
** Meta object code from reading C++ file 'main.h'
**
** Created: Tue 16. Sep 15:08:24 2008
**      by: The Qt Meta Object Compiler version 59 (Qt 4.3.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../src/main.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'main.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.3.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_main[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets

       0        // eod
};

static const char qt_meta_stringdata_main[] = {
    "main\0"
};

const QMetaObject main::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_main,
      qt_meta_data_main, 0 }
};

const QMetaObject *main::metaObject() const
{
    return &staticMetaObject;
}

void *main::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_main))
	return static_cast<void*>(const_cast< main*>(this));
    if (!strcmp(_clname, "Ui::main"))
	return static_cast< Ui::main*>(const_cast< main*>(this));
    return QWidget::qt_metacast(_clname);
}

int main::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
