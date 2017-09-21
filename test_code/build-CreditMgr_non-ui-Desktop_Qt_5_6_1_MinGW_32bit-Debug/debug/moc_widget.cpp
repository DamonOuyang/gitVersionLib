/****************************************************************************
** Meta object code from reading C++ file 'widget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../CreditMgr_non-ui/widget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'widget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Widget_t {
    QByteArrayData data[13];
    char stringdata0[246];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Widget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Widget_t qt_meta_stringdata_Widget = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Widget"
QT_MOC_LITERAL(1, 7, 21), // "on_OpnRdr_Btn_clicked"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 22), // "on_ShwName_Btn_clicked"
QT_MOC_LITERAL(4, 53, 21), // "on_ClsRdr_Btn_clicked"
QT_MOC_LITERAL(5, 75, 21), // "on_Intliz_Btn_clicked"
QT_MOC_LITERAL(6, 97, 23), // "on_ChngName_Btn_clicked"
QT_MOC_LITERAL(7, 121, 22), // "on_SrlNmbr_Btn_clicked"
QT_MOC_LITERAL(8, 144, 21), // "on_Charge_Btn_clicked"
QT_MOC_LITERAL(9, 166, 23), // "on_Recharge_Btn_clicked"
QT_MOC_LITERAL(10, 190, 19), // "on_Blnc_Btn_clicked"
QT_MOC_LITERAL(11, 210, 19), // "on_Data_Btn_clicked"
QT_MOC_LITERAL(12, 230, 15) // "slot_check_Card"

    },
    "Widget\0on_OpnRdr_Btn_clicked\0\0"
    "on_ShwName_Btn_clicked\0on_ClsRdr_Btn_clicked\0"
    "on_Intliz_Btn_clicked\0on_ChngName_Btn_clicked\0"
    "on_SrlNmbr_Btn_clicked\0on_Charge_Btn_clicked\0"
    "on_Recharge_Btn_clicked\0on_Blnc_Btn_clicked\0"
    "on_Data_Btn_clicked\0slot_check_Card"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Widget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x08 /* Private */,
       3,    0,   70,    2, 0x08 /* Private */,
       4,    0,   71,    2, 0x08 /* Private */,
       5,    0,   72,    2, 0x08 /* Private */,
       6,    0,   73,    2, 0x08 /* Private */,
       7,    0,   74,    2, 0x08 /* Private */,
       8,    0,   75,    2, 0x08 /* Private */,
       9,    0,   76,    2, 0x08 /* Private */,
      10,    0,   77,    2, 0x08 /* Private */,
      11,    0,   78,    2, 0x08 /* Private */,
      12,    0,   79,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Widget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Widget *_t = static_cast<Widget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_OpnRdr_Btn_clicked(); break;
        case 1: _t->on_ShwName_Btn_clicked(); break;
        case 2: _t->on_ClsRdr_Btn_clicked(); break;
        case 3: _t->on_Intliz_Btn_clicked(); break;
        case 4: _t->on_ChngName_Btn_clicked(); break;
        case 5: _t->on_SrlNmbr_Btn_clicked(); break;
        case 6: _t->on_Charge_Btn_clicked(); break;
        case 7: _t->on_Recharge_Btn_clicked(); break;
        case 8: _t->on_Blnc_Btn_clicked(); break;
        case 9: _t->on_Data_Btn_clicked(); break;
        case 10: _t->slot_check_Card(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject Widget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Widget.data,
      qt_meta_data_Widget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Widget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Widget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Widget.stringdata0))
        return static_cast<void*>(const_cast< Widget*>(this));
    return QWidget::qt_metacast(_clname);
}

int Widget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
