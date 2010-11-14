/****************************************************************************
** Meta object code from reading C++ file 'Animator.h'
**
** Created: Sun Nov 14 02:34:23 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "Animator.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Animator.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Animator[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x0a,
      25,    9,    9,    9, 0x0a,
      42,    9,    9,    9, 0x0a,
      56,    9,    9,    9, 0x0a,
      71,    9,    9,    9, 0x0a,
      86,    9,    9,    9, 0x0a,
     101,    9,    9,    9, 0x0a,
     116,    9,    9,    9, 0x0a,
     131,    9,    9,    9, 0x0a,
     146,    9,    9,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Animator[] = {
    "Animator\0\0updateMotion()\0updateWithFile()\0"
    "resetParams()\0setAngle0(int)\0"
    "setAngle1(int)\0setAngle2(int)\0"
    "setAngle3(int)\0setAngle4(int)\0"
    "setAngle5(int)\0tabSwitch(int)\0"
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
        case 0: updateMotion(); break;
        case 1: updateWithFile(); break;
        case 2: resetParams(); break;
        case 3: setAngle0((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: setAngle1((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: setAngle2((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: setAngle3((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: setAngle4((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: setAngle5((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: tabSwitch((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
