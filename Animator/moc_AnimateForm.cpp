/****************************************************************************
** Meta object code from reading C++ file 'AnimateForm.h'
**
** Created: Wed Dec 8 00:44:25 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "AnimateForm.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'AnimateForm.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_AnimateForm[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x0a,
      24,   12,   12,   12, 0x0a,
      31,   12,   12,   12, 0x0a,
      43,   12,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_AnimateForm[] = {
    "AnimateForm\0\0loadFile()\0loop()\0"
    "playPress()\0stopPress()\0"
};

const QMetaObject AnimateForm::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_AnimateForm,
      qt_meta_data_AnimateForm, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &AnimateForm::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *AnimateForm::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *AnimateForm::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AnimateForm))
        return static_cast<void*>(const_cast< AnimateForm*>(this));
    if (!strcmp(_clname, "AbstractWindow"))
        return static_cast< AbstractWindow*>(const_cast< AnimateForm*>(this));
    return QObject::qt_metacast(_clname);
}

int AnimateForm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: loadFile(); break;
        case 1: loop(); break;
        case 2: playPress(); break;
        case 3: stopPress(); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
