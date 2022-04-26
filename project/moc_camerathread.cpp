/****************************************************************************
** Meta object code from reading C++ file 'camerathread.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "camerathread.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'camerathread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CameraThread_t {
    QByteArrayData data[10];
    char stringdata0[84];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CameraThread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CameraThread_t qt_meta_stringdata_CameraThread = {
    {
QT_MOC_LITERAL(0, 0, 12), // "CameraThread"
QT_MOC_LITERAL(1, 13, 10), // "send_image"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 3), // "Mat"
QT_MOC_LITERAL(4, 29, 3), // "mmm"
QT_MOC_LITERAL(5, 33, 8), // "send_res"
QT_MOC_LITERAL(6, 42, 11), // "set_runflag"
QT_MOC_LITERAL(7, 54, 4), // "flag"
QT_MOC_LITERAL(8, 59, 11), // "set_udpflag"
QT_MOC_LITERAL(9, 71, 12) // "set_faceflag"

    },
    "CameraThread\0send_image\0\0Mat\0mmm\0"
    "send_res\0set_runflag\0flag\0set_udpflag\0"
    "set_faceflag"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CameraThread[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,
       5,    0,   42,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   43,    2, 0x0a /* Public */,
       8,    1,   46,    2, 0x0a /* Public */,
       9,    1,   49,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void, QMetaType::Bool,    7,

       0        // eod
};

void CameraThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CameraThread *_t = static_cast<CameraThread *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->send_image((*reinterpret_cast< Mat(*)>(_a[1]))); break;
        case 1: _t->send_res(); break;
        case 2: _t->set_runflag((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->set_udpflag((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->set_faceflag((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (CameraThread::*_t)(Mat );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CameraThread::send_image)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (CameraThread::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CameraThread::send_res)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject CameraThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_CameraThread.data,
      qt_meta_data_CameraThread,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CameraThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CameraThread::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CameraThread.stringdata0))
        return static_cast<void*>(const_cast< CameraThread*>(this));
    return QThread::qt_metacast(_clname);
}

int CameraThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void CameraThread::send_image(Mat _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CameraThread::send_res()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
