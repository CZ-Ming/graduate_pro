/****************************************************************************
** Meta object code from reading C++ file 'manager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "manager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'manager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_manager_t {
    QByteArrayData data[14];
    char stringdata0[137];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_manager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_manager_t qt_meta_stringdata_manager = {
    {
QT_MOC_LITERAL(0, 0, 7), // "manager"
QT_MOC_LITERAL(1, 8, 10), // "sendsignal"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 8), // "sendpwd1"
QT_MOC_LITERAL(4, 29, 3), // "num"
QT_MOC_LITERAL(5, 33, 8), // "sendpwd2"
QT_MOC_LITERAL(6, 42, 17), // "on_finger_clicked"
QT_MOC_LITERAL(7, 60, 15), // "on_pass_clicked"
QT_MOC_LITERAL(8, 76, 15), // "on_rfid_clicked"
QT_MOC_LITERAL(9, 92, 8), // "set_pwd2"
QT_MOC_LITERAL(10, 101, 4), // "pwd2"
QT_MOC_LITERAL(11, 106, 8), // "set_pwd1"
QT_MOC_LITERAL(12, 115, 4), // "pwd1"
QT_MOC_LITERAL(13, 120, 16) // "on_exit1_clicked"

    },
    "manager\0sendsignal\0\0sendpwd1\0num\0"
    "sendpwd2\0on_finger_clicked\0on_pass_clicked\0"
    "on_rfid_clicked\0set_pwd2\0pwd2\0set_pwd1\0"
    "pwd1\0on_exit1_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_manager[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x06 /* Public */,
       3,    1,   60,    2, 0x06 /* Public */,
       5,    1,   63,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   66,    2, 0x08 /* Private */,
       7,    0,   67,    2, 0x08 /* Private */,
       8,    0,   68,    2, 0x08 /* Private */,
       9,    1,   69,    2, 0x08 /* Private */,
      11,    1,   72,    2, 0x08 /* Private */,
      13,    0,   75,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void,

       0        // eod
};

void manager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        manager *_t = static_cast<manager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendsignal(); break;
        case 1: _t->sendpwd1((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->sendpwd2((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->on_finger_clicked(); break;
        case 4: _t->on_pass_clicked(); break;
        case 5: _t->on_rfid_clicked(); break;
        case 6: _t->set_pwd2((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->set_pwd1((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->on_exit1_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (manager::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&manager::sendsignal)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (manager::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&manager::sendpwd1)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (manager::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&manager::sendpwd2)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject manager::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_manager.data,
      qt_meta_data_manager,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *manager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *manager::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_manager.stringdata0))
        return static_cast<void*>(const_cast< manager*>(this));
    return QWidget::qt_metacast(_clname);
}

int manager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void manager::sendsignal()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void manager::sendpwd1(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void manager::sendpwd2(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
