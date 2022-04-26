/****************************************************************************
** Meta object code from reading C++ file 'open_interface.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../open_interface.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'open_interface.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_open_interface_t {
    QByteArrayData data[16];
    char stringdata0[212];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_open_interface_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_open_interface_t qt_meta_stringdata_open_interface = {
    {
QT_MOC_LITERAL(0, 0, 14), // "open_interface"
QT_MOC_LITERAL(1, 15, 10), // "sendsignal"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 14), // "on_clo_clicked"
QT_MOC_LITERAL(4, 42, 13), // "on_n1_clicked"
QT_MOC_LITERAL(5, 56, 13), // "on_n2_clicked"
QT_MOC_LITERAL(6, 70, 13), // "on_n3_clicked"
QT_MOC_LITERAL(7, 84, 13), // "on_n0_clicked"
QT_MOC_LITERAL(8, 98, 13), // "on_n4_clicked"
QT_MOC_LITERAL(9, 112, 13), // "on_n5_clicked"
QT_MOC_LITERAL(10, 126, 13), // "on_n6_clicked"
QT_MOC_LITERAL(11, 140, 14), // "on_ncl_clicked"
QT_MOC_LITERAL(12, 155, 13), // "on_n7_clicked"
QT_MOC_LITERAL(13, 169, 13), // "on_n8_clicked"
QT_MOC_LITERAL(14, 183, 13), // "on_n9_clicked"
QT_MOC_LITERAL(15, 197, 14) // "on_nok_clicked"

    },
    "open_interface\0sendsignal\0\0on_clo_clicked\0"
    "on_n1_clicked\0on_n2_clicked\0on_n3_clicked\0"
    "on_n0_clicked\0on_n4_clicked\0on_n5_clicked\0"
    "on_n6_clicked\0on_ncl_clicked\0on_n7_clicked\0"
    "on_n8_clicked\0on_n9_clicked\0on_nok_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_open_interface[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   85,    2, 0x08 /* Private */,
       4,    0,   86,    2, 0x08 /* Private */,
       5,    0,   87,    2, 0x08 /* Private */,
       6,    0,   88,    2, 0x08 /* Private */,
       7,    0,   89,    2, 0x08 /* Private */,
       8,    0,   90,    2, 0x08 /* Private */,
       9,    0,   91,    2, 0x08 /* Private */,
      10,    0,   92,    2, 0x08 /* Private */,
      11,    0,   93,    2, 0x08 /* Private */,
      12,    0,   94,    2, 0x08 /* Private */,
      13,    0,   95,    2, 0x08 /* Private */,
      14,    0,   96,    2, 0x08 /* Private */,
      15,    0,   97,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

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
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void open_interface::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<open_interface *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendsignal(); break;
        case 1: _t->on_clo_clicked(); break;
        case 2: _t->on_n1_clicked(); break;
        case 3: _t->on_n2_clicked(); break;
        case 4: _t->on_n3_clicked(); break;
        case 5: _t->on_n0_clicked(); break;
        case 6: _t->on_n4_clicked(); break;
        case 7: _t->on_n5_clicked(); break;
        case 8: _t->on_n6_clicked(); break;
        case 9: _t->on_ncl_clicked(); break;
        case 10: _t->on_n7_clicked(); break;
        case 11: _t->on_n8_clicked(); break;
        case 12: _t->on_n9_clicked(); break;
        case 13: _t->on_nok_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (open_interface::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&open_interface::sendsignal)) {
                *result = 0;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject open_interface::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_open_interface.data,
    qt_meta_data_open_interface,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *open_interface::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *open_interface::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_open_interface.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int open_interface::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void open_interface::sendsignal()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
