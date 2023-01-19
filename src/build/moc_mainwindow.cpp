/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../core/mainwindow.h"
#include <QtGui/qtextcursor.h>
#include <QScreen>
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Main_Window_t {
    uint offsetsAndSizes[34];
    char stringdata0[12];
    char stringdata1[16];
    char stringdata2[1];
    char stringdata3[15];
    char stringdata4[20];
    char stringdata5[36];
    char stringdata6[6];
    char stringdata7[36];
    char stringdata8[35];
    char stringdata9[36];
    char stringdata10[36];
    char stringdata11[25];
    char stringdata12[25];
    char stringdata13[25];
    char stringdata14[13];
    char stringdata15[11];
    char stringdata16[11];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_Main_Window_t::offsetsAndSizes) + ofs), len 
static const qt_meta_stringdata_Main_Window_t qt_meta_stringdata_Main_Window = {
    {
        QT_MOC_LITERAL(0, 11),  // "Main_Window"
        QT_MOC_LITERAL(12, 15),  // "press_start_gif"
        QT_MOC_LITERAL(28, 0),  // ""
        QT_MOC_LITERAL(29, 14),  // "press_stop_gif"
        QT_MOC_LITERAL(44, 19),  // "choose_file_pressed"
        QT_MOC_LITERAL(64, 35),  // "on_horizontalSlider_13_valueC..."
        QT_MOC_LITERAL(100, 5),  // "value"
        QT_MOC_LITERAL(106, 35),  // "on_horizontalSlider_10_valueC..."
        QT_MOC_LITERAL(142, 34),  // "on_horizontalSlider_9_valueCh..."
        QT_MOC_LITERAL(177, 35),  // "on_horizontalSlider_12_valueC..."
        QT_MOC_LITERAL(213, 35),  // "on_horizontalSlider_11_valueC..."
        QT_MOC_LITERAL(249, 24),  // "on_radioButton_3_pressed"
        QT_MOC_LITERAL(274, 24),  // "on_radioButton_4_pressed"
        QT_MOC_LITERAL(299, 24),  // "on_radioButton_5_pressed"
        QT_MOC_LITERAL(324, 12),  // "create_frame"
        QT_MOC_LITERAL(337, 10),  // "jpg_screen"
        QT_MOC_LITERAL(348, 10)   // "bmp_screen"
    },
    "Main_Window",
    "press_start_gif",
    "",
    "press_stop_gif",
    "choose_file_pressed",
    "on_horizontalSlider_13_valueChanged",
    "value",
    "on_horizontalSlider_10_valueChanged",
    "on_horizontalSlider_9_valueChanged",
    "on_horizontalSlider_12_valueChanged",
    "on_horizontalSlider_11_valueChanged",
    "on_radioButton_3_pressed",
    "on_radioButton_4_pressed",
    "on_radioButton_5_pressed",
    "create_frame",
    "jpg_screen",
    "bmp_screen"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Main_Window[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   98,    2, 0x08,    1 /* Private */,
       3,    0,   99,    2, 0x08,    2 /* Private */,
       4,    0,  100,    2, 0x08,    3 /* Private */,
       5,    1,  101,    2, 0x08,    4 /* Private */,
       7,    1,  104,    2, 0x08,    6 /* Private */,
       8,    1,  107,    2, 0x08,    8 /* Private */,
       9,    1,  110,    2, 0x08,   10 /* Private */,
      10,    1,  113,    2, 0x08,   12 /* Private */,
      11,    0,  116,    2, 0x08,   14 /* Private */,
      12,    0,  117,    2, 0x08,   15 /* Private */,
      13,    0,  118,    2, 0x08,   16 /* Private */,
      14,    0,  119,    2, 0x08,   17 /* Private */,
      15,    0,  120,    2, 0x08,   18 /* Private */,
      16,    0,  121,    2, 0x08,   19 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Main_Window::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Main_Window *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->press_start_gif(); break;
        case 1: _t->press_stop_gif(); break;
        case 2: _t->choose_file_pressed(); break;
        case 3: _t->on_horizontalSlider_13_valueChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 4: _t->on_horizontalSlider_10_valueChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 5: _t->on_horizontalSlider_9_valueChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 6: _t->on_horizontalSlider_12_valueChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 7: _t->on_horizontalSlider_11_valueChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 8: _t->on_radioButton_3_pressed(); break;
        case 9: _t->on_radioButton_4_pressed(); break;
        case 10: _t->on_radioButton_5_pressed(); break;
        case 11: _t->create_frame(); break;
        case 12: _t->jpg_screen(); break;
        case 13: _t->bmp_screen(); break;
        default: ;
        }
    }
}

const QMetaObject Main_Window::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_Main_Window.offsetsAndSizes,
    qt_meta_data_Main_Window,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_Main_Window_t
, QtPrivate::TypeAndForceComplete<Main_Window, std::true_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *Main_Window::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Main_Window::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Main_Window.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int Main_Window::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 14;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
