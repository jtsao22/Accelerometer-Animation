/****************************************************************************
** Meta object code from reading C++ file 'MotionForm.h'
**
** Created: Thu Nov 11 12:27:04 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "MotionForm.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MotionForm.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MotionForm[] = {

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
      12,   11,   11,   11, 0x0a,
      27,   11,   11,   11, 0x0a,
      44,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MotionForm[] = {
    "MotionForm\0\0updateMotion()\0updateWithFile()\0"
    "resetParams()\0"
};

const QMetaObject MotionForm::staticMetaObject = {
    { &QCoin::staticMetaObject, qt_meta_stringdata_MotionForm,
      qt_meta_data_MotionForm, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MotionForm::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MotionForm::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MotionForm::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MotionForm))
        return static_cast<void*>(const_cast< MotionForm*>(this));
    return QCoin::qt_metacast(_clname);
}

int MotionForm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCoin::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: updateMotion(); break;
        case 1: updateWithFile(); break;
        case 2: resetParams(); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
