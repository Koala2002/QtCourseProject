/****************************************************************************
** Meta object code from reading C++ file 'painter.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../painter.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'painter.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Painter_t {
    QByteArrayData data[20];
    char stringdata0[251];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Painter_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Painter_t qt_meta_stringdata_Painter = {
    {
QT_MOC_LITERAL(0, 0, 7), // "Painter"
QT_MOC_LITERAL(1, 8, 13), // "addGraphLayer"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 3), // "img"
QT_MOC_LITERAL(4, 27, 3), // "pos"
QT_MOC_LITERAL(5, 31, 15), // "mergeGraphLayer"
QT_MOC_LITERAL(6, 47, 14), // "hideGraphLayer"
QT_MOC_LITERAL(7, 62, 16), // "deleteGraphLayer"
QT_MOC_LITERAL(8, 79, 14), // "copyGraphLayer"
QT_MOC_LITERAL(9, 94, 8), // "SaveFile"
QT_MOC_LITERAL(10, 103, 8), // "OpenFile"
QT_MOC_LITERAL(11, 112, 13), // "BackToPreStep"
QT_MOC_LITERAL(12, 126, 18), // "CancelBackToAction"
QT_MOC_LITERAL(13, 145, 11), // "ColorChange"
QT_MOC_LITERAL(14, 157, 10), // "ToolChange"
QT_MOC_LITERAL(15, 168, 25), // "on_ColorDisplayer_clicked"
QT_MOC_LITERAL(16, 194, 33), // "on_GraphLayerDisplayerItemCli..."
QT_MOC_LITERAL(17, 228, 14), // "autoScrollDown"
QT_MOC_LITERAL(18, 243, 3), // "min"
QT_MOC_LITERAL(19, 247, 3) // "max"

    },
    "Painter\0addGraphLayer\0\0img\0pos\0"
    "mergeGraphLayer\0hideGraphLayer\0"
    "deleteGraphLayer\0copyGraphLayer\0"
    "SaveFile\0OpenFile\0BackToPreStep\0"
    "CancelBackToAction\0ColorChange\0"
    "ToolChange\0on_ColorDisplayer_clicked\0"
    "on_GraphLayerDisplayerItemClicked\0"
    "autoScrollDown\0min\0max"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Painter[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   94,    2, 0x08 /* Private */,
       1,    1,   99,    2, 0x28 /* Private | MethodCloned */,
       1,    0,  102,    2, 0x28 /* Private | MethodCloned */,
       5,    0,  103,    2, 0x08 /* Private */,
       6,    0,  104,    2, 0x08 /* Private */,
       7,    0,  105,    2, 0x08 /* Private */,
       8,    0,  106,    2, 0x08 /* Private */,
       9,    0,  107,    2, 0x08 /* Private */,
      10,    0,  108,    2, 0x08 /* Private */,
      11,    0,  109,    2, 0x08 /* Private */,
      12,    0,  110,    2, 0x08 /* Private */,
      13,    0,  111,    2, 0x08 /* Private */,
      14,    0,  112,    2, 0x08 /* Private */,
      15,    0,  113,    2, 0x08 /* Private */,
      16,    0,  114,    2, 0x08 /* Private */,
      17,    2,  115,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::QImage, QMetaType::QPoint,    3,    4,
    QMetaType::Void, QMetaType::QImage,    3,
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
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   18,   19,

       0        // eod
};

void Painter::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Painter *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->addGraphLayer((*reinterpret_cast< QImage(*)>(_a[1])),(*reinterpret_cast< QPoint(*)>(_a[2]))); break;
        case 1: _t->addGraphLayer((*reinterpret_cast< QImage(*)>(_a[1]))); break;
        case 2: _t->addGraphLayer(); break;
        case 3: _t->mergeGraphLayer(); break;
        case 4: _t->hideGraphLayer(); break;
        case 5: _t->deleteGraphLayer(); break;
        case 6: _t->copyGraphLayer(); break;
        case 7: _t->SaveFile(); break;
        case 8: _t->OpenFile(); break;
        case 9: _t->BackToPreStep(); break;
        case 10: _t->CancelBackToAction(); break;
        case 11: _t->ColorChange(); break;
        case 12: _t->ToolChange(); break;
        case 13: _t->on_ColorDisplayer_clicked(); break;
        case 14: _t->on_GraphLayerDisplayerItemClicked(); break;
        case 15: _t->autoScrollDown((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Painter::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_Painter.data,
    qt_meta_data_Painter,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Painter::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Painter::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Painter.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int Painter::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
