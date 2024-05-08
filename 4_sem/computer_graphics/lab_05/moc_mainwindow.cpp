/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "mainwindow.h"
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
namespace {
struct qt_meta_stringdata_MainWindow_t {
    uint offsetsAndSizes[36];
    char stringdata0[11];
    char stringdata1[31];
    char stringdata2[1];
    char stringdata3[28];
    char stringdata4[20];
    char stringdata5[13];
    char stringdata6[19];
    char stringdata7[23];
    char stringdata8[13];
    char stringdata9[6];
    char stringdata10[34];
    char stringdata11[27];
    char stringdata12[32];
    char stringdata13[22];
    char stringdata14[18];
    char stringdata15[39];
    char stringdata16[33];
    char stringdata17[32];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_MainWindow_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
        QT_MOC_LITERAL(0, 10),  // "MainWindow"
        QT_MOC_LITERAL(11, 30),  // "on_addPoint_pushButton_clicked"
        QT_MOC_LITERAL(42, 0),  // ""
        QT_MOC_LITERAL(43, 27),  // "on_clear_pushButton_clicked"
        QT_MOC_LITERAL(71, 19),  // "draw_figure_borders"
        QT_MOC_LITERAL(91, 12),  // "fill_figures"
        QT_MOC_LITERAL(104, 18),  // "fill_figures_delay"
        QT_MOC_LITERAL(123, 22),  // "painter_widget_clicked"
        QT_MOC_LITERAL(146, 12),  // "QMouseEvent*"
        QT_MOC_LITERAL(159, 5),  // "event"
        QT_MOC_LITERAL(165, 33),  // "on_closeFigure_pushButton_cli..."
        QT_MOC_LITERAL(199, 26),  // "on_fill_pushButton_clicked"
        QT_MOC_LITERAL(226, 31),  // "on_fillDelay_pushButton_clicked"
        QT_MOC_LITERAL(258, 21),  // "on_pushButton_clicked"
        QT_MOC_LITERAL(280, 17),  // "show_fill_results"
        QT_MOC_LITERAL(298, 38),  // "on_background_color_pushButto..."
        QT_MOC_LITERAL(337, 32),  // "on_line_color_pushButton_clicked"
        QT_MOC_LITERAL(370, 31)   // "on_fillColor_pushButton_clicked"
    },
    "MainWindow",
    "on_addPoint_pushButton_clicked",
    "",
    "on_clear_pushButton_clicked",
    "draw_figure_borders",
    "fill_figures",
    "fill_figures_delay",
    "painter_widget_clicked",
    "QMouseEvent*",
    "event",
    "on_closeFigure_pushButton_clicked",
    "on_fill_pushButton_clicked",
    "on_fillDelay_pushButton_clicked",
    "on_pushButton_clicked",
    "show_fill_results",
    "on_background_color_pushButton_clicked",
    "on_line_color_pushButton_clicked",
    "on_fillColor_pushButton_clicked"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_MainWindow[] = {

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
       5,    0,  101,    2, 0x08,    4 /* Private */,
       6,    0,  102,    2, 0x08,    5 /* Private */,
       7,    1,  103,    2, 0x08,    6 /* Private */,
      10,    0,  106,    2, 0x08,    8 /* Private */,
      11,    0,  107,    2, 0x08,    9 /* Private */,
      12,    0,  108,    2, 0x08,   10 /* Private */,
      13,    0,  109,    2, 0x08,   11 /* Private */,
      14,    0,  110,    2, 0x08,   12 /* Private */,
      15,    0,  111,    2, 0x08,   13 /* Private */,
      16,    0,  112,    2, 0x08,   14 /* Private */,
      17,    0,  113,    2, 0x08,   15 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    9,
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

Q_CONSTINIT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.offsetsAndSizes,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_MainWindow_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<MainWindow, std::true_type>,
        // method 'on_addPoint_pushButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_clear_pushButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'draw_figure_borders'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'fill_figures'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'fill_figures_delay'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'painter_widget_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QMouseEvent *, std::false_type>,
        // method 'on_closeFigure_pushButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_fill_pushButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_fillDelay_pushButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'show_fill_results'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_background_color_pushButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_line_color_pushButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_fillColor_pushButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_addPoint_pushButton_clicked(); break;
        case 1: _t->on_clear_pushButton_clicked(); break;
        case 2: _t->draw_figure_borders(); break;
        case 3: _t->fill_figures(); break;
        case 4: _t->fill_figures_delay(); break;
        case 5: _t->painter_widget_clicked((*reinterpret_cast< std::add_pointer_t<QMouseEvent*>>(_a[1]))); break;
        case 6: _t->on_closeFigure_pushButton_clicked(); break;
        case 7: _t->on_fill_pushButton_clicked(); break;
        case 8: _t->on_fillDelay_pushButton_clicked(); break;
        case 9: _t->on_pushButton_clicked(); break;
        case 10: _t->show_fill_results(); break;
        case 11: _t->on_background_color_pushButton_clicked(); break;
        case 12: _t->on_line_color_pushButton_clicked(); break;
        case 13: _t->on_fillColor_pushButton_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
