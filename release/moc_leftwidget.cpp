/****************************************************************************
** Meta object code from reading C++ file 'leftwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../leftwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'leftwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_LeftWidget_t {
    QByteArrayData data[7];
    char stringdata0[57];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_LeftWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_LeftWidget_t qt_meta_stringdata_LeftWidget = {
    {
QT_MOC_LITERAL(0, 0, 10), // "LeftWidget"
QT_MOC_LITERAL(1, 11, 9), // "clearshow"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 15), // "treeSelectIndex"
QT_MOC_LITERAL(4, 38, 6), // "assign"
QT_MOC_LITERAL(5, 45, 4), // "nRow"
QT_MOC_LITERAL(6, 50, 6) // "nColum"

    },
    "LeftWidget\0clearshow\0\0treeSelectIndex\0"
    "assign\0nRow\0nColum"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_LeftWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x06 /* Public */,
       3,    1,   30,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    2,   33,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    5,    6,

       0        // eod
};

void LeftWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        LeftWidget *_t = static_cast<LeftWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->clearshow(); break;
        case 1: _t->treeSelectIndex((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->assign((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (LeftWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&LeftWidget::clearshow)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (LeftWidget::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&LeftWidget::treeSelectIndex)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject LeftWidget::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata_LeftWidget.data,
      qt_meta_data_LeftWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *LeftWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LeftWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_LeftWidget.stringdata0))
        return static_cast<void*>(const_cast< LeftWidget*>(this));
    return QFrame::qt_metacast(_clname);
}

int LeftWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
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
void LeftWidget::clearshow()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void LeftWidget::treeSelectIndex(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
