/****************************************************************************
** Meta object code from reading C++ file 'ColorForm.h'
**
** Created: Thu Nov 18 16:30:56 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "ColorForm.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ColorForm.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ColorForm[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x0a,
      25,   10,   10,   10, 0x0a,
      37,   10,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ColorForm[] = {
    "ColorForm\0\0updateColor()\0loadColor()\0"
    "saveColor()\0"
};

const QMetaObject ColorForm::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ColorForm,
      qt_meta_data_ColorForm, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ColorForm::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ColorForm::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ColorForm::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ColorForm))
        return static_cast<void*>(const_cast< ColorForm*>(this));
    if (!strcmp(_clname, "AbstractWindow"))
        return static_cast< AbstractWindow*>(const_cast< ColorForm*>(this));
    return QObject::qt_metacast(_clname);
}

int ColorForm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: updateColor(); break;
        case 1: loadColor(); break;
        case 2: saveColor(); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
