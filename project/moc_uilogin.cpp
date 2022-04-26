/****************************************************************************
** Meta object code from reading C++ file 'uilogin.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "uilogin.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'uilogin.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_UiLogin_t {
    QByteArrayData data[15];
    char stringdata0[198];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_UiLogin_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_UiLogin_t qt_meta_stringdata_UiLogin = {
    {
QT_MOC_LITERAL(0, 0, 7), // "UiLogin"
QT_MOC_LITERAL(1, 8, 13), // "on_n1_clicked"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 13), // "on_n2_clicked"
QT_MOC_LITERAL(4, 37, 13), // "on_n3_clicked"
QT_MOC_LITERAL(5, 51, 13), // "on_n0_clicked"
QT_MOC_LITERAL(6, 65, 13), // "on_n4_clicked"
QT_MOC_LITERAL(7, 79, 13), // "on_n5_clicked"
QT_MOC_LITERAL(8, 93, 13), // "on_n6_clicked"
QT_MOC_LITERAL(9, 107, 16), // "on_login_clicked"
QT_MOC_LITERAL(10, 124, 13), // "on_n7_clicked"
QT_MOC_LITERAL(11, 138, 13), // "on_n8_clicked"
QT_MOC_LITERAL(12, 152, 13), // "on_n9_clicked"
QT_MOC_LITERAL(13, 166, 16), // "on_exit1_clicked"
QT_MOC_LITERAL(14, 183, 14) // "on_ncl_clicked"

    },
    "UiLogin\0on_n1_clicked\0\0on_n2_clicked\0"
    "on_n3_clicked\0on_n0_clicked\0on_n4_clicked\0"
    "on_n5_clicked\0on_n6_clicked\0"
    "on_login_clicked\0on_n7_clicked\0"
    "on_n8_clicked\0on_n9_clicked\0"
    "on_exit1_clicked\0on_ncl_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_UiLogin[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x08 /* Private */,
       3,    0,   80,    2, 0x08 /* Private */,
       4,    0,   81,    2, 0x08 /* Private */,
       5,    0,   82,    2, 0x08 /* Private */,
       6,    0,   83,    2, 0x08 /* Private */,
       7,    0,   84,    2, 0x08 /* Private */,
       8,    0,   85,    2, 0x08 /* Private */,
       9,    0,   86,    2, 0x08 /* Private */,
      10,    0,   87,    2, 0x08 /* Private */,
      11,    0,   88,    2, 0x08 /* Private */,
      12,    0,   89,    2, 0x08 /* Private */,
      13,    0,   90,    2, 0x08 /* Private */,
      14,    0,   91,    2, 0x08 /* Private */,

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

void UiLogin::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        UiLogin *_t = static_cast<UiLogin *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_n1_clicked(); break;
        case 1: _t->on_n2_clicked(); break;
        case 2: _t->on_n3_clicked(); break;
        case 3: _t->on_n0_clicked(); break;
        case 4: _t->on_n4_clicked(); break;
        case 5: _t->on_n5_clicked(); break;
        case 6: _t->on_n6_clicked(); break;
        case 7: _t->on_login_clicked(); break;
        case 8: _t->on_n7_clicked(); break;
        case 9: _t->on_n8_clicked(); break;
        case 10: _t->on_n9_clicked(); break;
        case 11: _t->on_exit1_clicked(); break;
        case 12: _t->on_ncl_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject UiLogin::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_UiLogin.data,
      qt_meta_data_UiLogin,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *UiLogin::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UiLogin::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_UiLogin.stringdata0))
        return static_cast<void*>(const_cast< UiLogin*>(this));
    return QDialog::qt_metacast(_clname);
}

int UiLogin::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE
