/****************************************************************************
** Meta object code from reading C++ file 'main_interface.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "main_interface.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'main_interface.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_main_interface_t {
    QByteArrayData data[11];
    char stringdata0[112];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_main_interface_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_main_interface_t qt_meta_stringdata_main_interface = {
    {
QT_MOC_LITERAL(0, 0, 14), // "main_interface"
QT_MOC_LITERAL(1, 15, 12), // "send_udpflag"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 4), // "flag"
QT_MOC_LITERAL(4, 34, 8), // "set_pwd1"
QT_MOC_LITERAL(5, 43, 3), // "num"
QT_MOC_LITERAL(6, 47, 8), // "set_pwd2"
QT_MOC_LITERAL(7, 56, 7), // "receive"
QT_MOC_LITERAL(8, 64, 13), // "clock_3secrun"
QT_MOC_LITERAL(9, 78, 15), // "on_lock_clicked"
QT_MOC_LITERAL(10, 94, 17) // "on_manage_clicked"

    },
    "main_interface\0send_udpflag\0\0flag\0"
    "set_pwd1\0num\0set_pwd2\0receive\0"
    "clock_3secrun\0on_lock_clicked\0"
    "on_manage_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_main_interface[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   52,    2, 0x0a /* Public */,
       6,    1,   55,    2, 0x0a /* Public */,
       7,    0,   58,    2, 0x0a /* Public */,
       8,    0,   59,    2, 0x08 /* Private */,
       9,    0,   60,    2, 0x08 /* Private */,
      10,    0,   61,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void main_interface::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        main_interface *_t = static_cast<main_interface *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->send_udpflag((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->set_pwd1((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->set_pwd2((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->receive(); break;
        case 4: _t->clock_3secrun(); break;
        case 5: _t->on_lock_clicked(); break;
        case 6: _t->on_manage_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (main_interface::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&main_interface::send_udpflag)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject main_interface::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_main_interface.data,
      qt_meta_data_main_interface,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *main_interface::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *main_interface::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_main_interface.stringdata0))
        return static_cast<void*>(const_cast< main_interface*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int main_interface::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void main_interface::send_udpflag(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
