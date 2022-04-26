/****************************************************************************
** Meta object code from reading C++ file 'motorthread.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "motorthread.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'motorthread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_motorthread_t {
    QByteArrayData data[6];
    char stringdata0[57];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_motorthread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_motorthread_t qt_meta_stringdata_motorthread = {
    {
QT_MOC_LITERAL(0, 0, 11), // "motorthread"
QT_MOC_LITERAL(1, 12, 11), // "finish_init"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 13), // "set_func_flag"
QT_MOC_LITERAL(4, 39, 4), // "flag"
QT_MOC_LITERAL(5, 44, 12) // "set_run_flag"

    },
    "motorthread\0finish_init\0\0set_func_flag\0"
    "flag\0set_run_flag"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_motorthread[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    1,   30,    2, 0x0a /* Public */,
       5,    1,   33,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Bool,    4,

       0        // eod
};

void motorthread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        motorthread *_t = static_cast<motorthread *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->finish_init(); break;
        case 1: _t->set_func_flag((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->set_run_flag((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (motorthread::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&motorthread::finish_init)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject motorthread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_motorthread.data,
      qt_meta_data_motorthread,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *motorthread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *motorthread::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_motorthread.stringdata0))
        return static_cast<void*>(const_cast< motorthread*>(this));
    return QThread::qt_metacast(_clname);
}

int motorthread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void motorthread::finish_init()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
