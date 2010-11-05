/****************************************************************************
** Meta object code from reading C++ file 'Animator.h'
**
** Created: Thu Nov 4 15:29:08 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "Animator.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Animator.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Animator[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x0a,
      25,    9,    9,    9, 0x0a,
      40,    9,    9,    9, 0x0a,
      55,    9,    9,    9, 0x0a,
      70,    9,    9,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Animator[] = {
    "Animator\0\0setAngle1(int)\0setAngle2(int)\0"
    "setAngle3(int)\0setAngle4(int)\0"
    "setAngle5(int)\0"
};

const QMetaObject Animator::staticMetaObject = {
    { &QCoin::staticMetaObject, qt_meta_stringdata_Animator,
      qt_meta_data_Animator, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Animator::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Animator::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Animator::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Animator))
        return static_cast<void*>(const_cast< Animator*>(this));
    return QCoin::qt_metacast(_clname);
}

int Animator::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCoin::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: setAngle1((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: setAngle2((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: setAngle3((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: setAngle4((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: setAngle5((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
