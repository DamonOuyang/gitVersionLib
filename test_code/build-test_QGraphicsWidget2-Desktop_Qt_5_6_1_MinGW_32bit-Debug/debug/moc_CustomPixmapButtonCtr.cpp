/****************************************************************************
** Meta object code from reading C++ file 'CustomPixmapButtonCtr.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../test_QGraphicsWidget2/CustomPixmapButtonCtr.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CustomPixmapButtonCtr.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CustomPixmapButtonCtr_t {
    QByteArrayData data[5];
    char stringdata0[65];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CustomPixmapButtonCtr_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CustomPixmapButtonCtr_t qt_meta_stringdata_CustomPixmapButtonCtr = {
    {
QT_MOC_LITERAL(0, 0, 21), // "CustomPixmapButtonCtr"
QT_MOC_LITERAL(1, 22, 20), // "sig_chooseThisButton"
QT_MOC_LITERAL(2, 43, 0), // ""
QT_MOC_LITERAL(3, 44, 2), // "id"
QT_MOC_LITERAL(4, 47, 17) // "slot_chooseButton"

    },
    "CustomPixmapButtonCtr\0sig_chooseThisButton\0"
    "\0id\0slot_chooseButton"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CustomPixmapButtonCtr[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   27,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,

       0        // eod
};

void CustomPixmapButtonCtr::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CustomPixmapButtonCtr *_t = static_cast<CustomPixmapButtonCtr *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sig_chooseThisButton((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->slot_chooseButton((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (CustomPixmapButtonCtr::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CustomPixmapButtonCtr::sig_chooseThisButton)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject CustomPixmapButtonCtr::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_CustomPixmapButtonCtr.data,
      qt_meta_data_CustomPixmapButtonCtr,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CustomPixmapButtonCtr::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CustomPixmapButtonCtr::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CustomPixmapButtonCtr.stringdata0))
        return static_cast<void*>(const_cast< CustomPixmapButtonCtr*>(this));
    return QObject::qt_metacast(_clname);
}

int CustomPixmapButtonCtr::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void CustomPixmapButtonCtr::sig_chooseThisButton(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
