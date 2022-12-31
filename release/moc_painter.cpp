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
    char stringdata0[276];
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
QT_MOC_LITERAL(14, 157, 11), // "ShapeChange"
QT_MOC_LITERAL(15, 169, 10), // "ToolChange"
QT_MOC_LITERAL(16, 180, 25), // "on_ColorDisplayer_clicked"
QT_MOC_LITERAL(17, 206, 30), // "on_PenSizeControl_valueChanged"
QT_MOC_LITERAL(18, 237, 4), // "arg1"
QT_MOC_LITERAL(19, 242, 33) // "on_GraphLayerDisplayerItemCli..."

    },
    "Painter\0addGraphLayer\0\0img\0pos\0"
    "mergeGraphLayer\0hideGraphLayer\0"
    "deleteGraphLayer\0copyGraphLayer\0"
    "SaveFile\0OpenFile\0BackToPreStep\0"
    "CancelBackToAction\0ColorChange\0"
    "ShapeChange\0ToolChange\0on_ColorDisplayer_clicked\0"
    "on_PenSizeControl_valueChanged\0arg1\0"
    "on_GraphLayerDisplayerItemClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Painter[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   99,    2, 0x08 /* Private */,
       1,    1,  104,    2, 0x28 /* Private | MethodCloned */,
       1,    0,  107,    2, 0x28 /* Private | MethodCloned */,
       5,    0,  108,    2, 0x08 /* Private */,
       6,    0,  109,    2, 0x08 /* Private */,
       7,    0,  110,    2, 0x08 /* Private */,
       8,    0,  111,    2, 0x08 /* Private */,
       9,    0,  112,    2, 0x08 /* Private */,
      10,    0,  113,    2, 0x08 /* Private */,
      11,    0,  114,    2, 0x08 /* Private */,
      12,    0,  115,    2, 0x08 /* Private */,
      13,    0,  116,    2, 0x08 /* Private */,
      14,    0,  117,    2, 0x08 /* Private */,
      15,    0,  118,    2, 0x08 /* Private */,
      16,    0,  119,    2, 0x08 /* Private */,
      17,    1,  120,    2, 0x08 /* Private */,
      19,    0,  123,    2, 0x08 /* Private */,

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
    QMetaType::Void, QMetaType::Int,   18,
    QMetaType::Void,

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
        case 12: _t->ShapeChange(); break;
        case 13: _t->ToolChange(); break;
        case 14: _t->on_ColorDisplayer_clicked(); break;
        case 15: _t->on_PenSizeControl_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: _t->on_GraphLayerDisplayerItemClicked(); break;
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
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 17;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
