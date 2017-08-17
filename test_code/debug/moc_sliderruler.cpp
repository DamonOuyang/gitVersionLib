/****************************************************************************
** Meta object code from reading C++ file 'sliderruler.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../SliderRuler/sliderruler.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sliderruler.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_SliderRuler_t {
    QByteArrayData data[27];
    char stringdata0[292];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SliderRuler_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SliderRuler_t qt_meta_stringdata_SliderRuler = {
    {
QT_MOC_LITERAL(0, 0, 11), // "SliderRuler"
QT_MOC_LITERAL(1, 12, 12), // "valueChanged"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 5), // "value"
QT_MOC_LITERAL(4, 32, 14), // "resetVariables"
QT_MOC_LITERAL(5, 47, 8), // "setRange"
QT_MOC_LITERAL(6, 56, 8), // "minValue"
QT_MOC_LITERAL(7, 65, 8), // "maxValue"
QT_MOC_LITERAL(8, 74, 8), // "setValue"
QT_MOC_LITERAL(9, 83, 12), // "setPrecision"
QT_MOC_LITERAL(10, 96, 9), // "precision"
QT_MOC_LITERAL(11, 106, 7), // "setStep"
QT_MOC_LITERAL(12, 114, 8), // "longStep"
QT_MOC_LITERAL(13, 123, 9), // "shortStep"
QT_MOC_LITERAL(14, 133, 8), // "setSpace"
QT_MOC_LITERAL(15, 142, 5), // "space"
QT_MOC_LITERAL(16, 148, 10), // "setBgColor"
QT_MOC_LITERAL(17, 159, 12), // "bgColorStart"
QT_MOC_LITERAL(18, 172, 10), // "bgColorEnd"
QT_MOC_LITERAL(19, 183, 12), // "setLineColor"
QT_MOC_LITERAL(20, 196, 9), // "lineColor"
QT_MOC_LITERAL(21, 206, 14), // "setSliderColor"
QT_MOC_LITERAL(22, 221, 14), // "sliderColorTop"
QT_MOC_LITERAL(23, 236, 17), // "sliderColorBottom"
QT_MOC_LITERAL(24, 254, 13), // "setTipBgColor"
QT_MOC_LITERAL(25, 268, 10), // "tipBgColor"
QT_MOC_LITERAL(26, 279, 12) // "tipTextColor"

    },
    "SliderRuler\0valueChanged\0\0value\0"
    "resetVariables\0setRange\0minValue\0"
    "maxValue\0setValue\0setPrecision\0precision\0"
    "setStep\0longStep\0shortStep\0setSpace\0"
    "space\0setBgColor\0bgColorStart\0bgColorEnd\0"
    "setLineColor\0lineColor\0setSliderColor\0"
    "sliderColorTop\0sliderColorBottom\0"
    "setTipBgColor\0tipBgColor\0tipTextColor"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SliderRuler[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   79,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   82,    2, 0x08 /* Private */,
       5,    2,   83,    2, 0x0a /* Public */,
       5,    2,   88,    2, 0x0a /* Public */,
       8,    1,   93,    2, 0x0a /* Public */,
       8,    1,   96,    2, 0x0a /* Public */,
       9,    1,   99,    2, 0x0a /* Public */,
      11,    2,  102,    2, 0x0a /* Public */,
      14,    1,  107,    2, 0x0a /* Public */,
      16,    2,  110,    2, 0x0a /* Public */,
      19,    1,  115,    2, 0x0a /* Public */,
      21,    2,  118,    2, 0x0a /* Public */,
      24,    2,  123,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Double,    3,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double, QMetaType::Double,    6,    7,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    6,    7,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   12,   13,
    QMetaType::Void, QMetaType::Int,   15,
    QMetaType::Void, QMetaType::QColor, QMetaType::QColor,   17,   18,
    QMetaType::Void, QMetaType::QColor,   20,
    QMetaType::Void, QMetaType::QColor, QMetaType::QColor,   22,   23,
    QMetaType::Void, QMetaType::QColor, QMetaType::QColor,   25,   26,

       0        // eod
};

void SliderRuler::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SliderRuler *_t = static_cast<SliderRuler *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 1: _t->resetVariables(); break;
        case 2: _t->setRange((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 3: _t->setRange((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _t->setValue((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 5: _t->setValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->setPrecision((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->setStep((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 8: _t->setSpace((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->setBgColor((*reinterpret_cast< QColor(*)>(_a[1])),(*reinterpret_cast< QColor(*)>(_a[2]))); break;
        case 10: _t->setLineColor((*reinterpret_cast< QColor(*)>(_a[1]))); break;
        case 11: _t->setSliderColor((*reinterpret_cast< QColor(*)>(_a[1])),(*reinterpret_cast< QColor(*)>(_a[2]))); break;
        case 12: _t->setTipBgColor((*reinterpret_cast< QColor(*)>(_a[1])),(*reinterpret_cast< QColor(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (SliderRuler::*_t)(double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SliderRuler::valueChanged)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject SliderRuler::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_SliderRuler.data,
      qt_meta_data_SliderRuler,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *SliderRuler::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SliderRuler::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_SliderRuler.stringdata0))
        return static_cast<void*>(const_cast< SliderRuler*>(this));
    return QWidget::qt_metacast(_clname);
}

int SliderRuler::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void SliderRuler::valueChanged(double _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
