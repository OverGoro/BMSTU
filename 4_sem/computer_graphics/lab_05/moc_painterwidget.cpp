/****************************************************************************
** Meta object code from reading C++ file 'painterwidget.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "painterwidget.h"
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'painterwidget.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_PainterWidget_t {
    uint offsetsAndSizes[64];
    char stringdata0[14];
    char stringdata1[12];
    char stringdata2[1];
    char stringdata3[13];
    char stringdata4[17];
    char stringdata5[13];
    char stringdata6[13];
    char stringdata7[6];
    char stringdata8[10];
    char stringdata9[5];
    char stringdata10[2];
    char stringdata11[3];
    char stringdata12[3];
    char stringdata13[12];
    char stringdata14[20];
    char stringdata15[8];
    char stringdata16[9];
    char stringdata17[12];
    char stringdata18[4];
    char stringdata19[4];
    char stringdata20[4];
    char stringdata21[4];
    char stringdata22[6];
    char stringdata23[4];
    char stringdata24[4];
    char stringdata25[25];
    char stringdata26[25];
    char stringdata27[23];
    char stringdata28[13];
    char stringdata29[11];
    char stringdata30[8];
    char stringdata31[6];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_PainterWidget_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_PainterWidget_t qt_meta_stringdata_PainterWidget = {
    {
        QT_MOC_LITERAL(0, 13),  // "PainterWidget"
        QT_MOC_LITERAL(14, 11),  // "paintSignal"
        QT_MOC_LITERAL(26, 0),  // ""
        QT_MOC_LITERAL(27, 12),  // "resizeSignal"
        QT_MOC_LITERAL(40, 16),  // "paintEndedSignal"
        QT_MOC_LITERAL(57, 12),  // "mouseClicked"
        QT_MOC_LITERAL(70, 12),  // "QMouseEvent*"
        QT_MOC_LITERAL(83, 5),  // "event"
        QT_MOC_LITERAL(89, 9),  // "roundSide"
        QT_MOC_LITERAL(99, 4),  // "Line"
        QT_MOC_LITERAL(104, 1),  // "l"
        QT_MOC_LITERAL(106, 2),  // "p1"
        QT_MOC_LITERAL(109, 2),  // "p2"
        QT_MOC_LITERAL(112, 11),  // "roundFigure"
        QT_MOC_LITERAL(124, 19),  // "std::vector<Figure>"
        QT_MOC_LITERAL(144, 7),  // "figures"
        QT_MOC_LITERAL(152, 8),  // "drawLine"
        QT_MOC_LITERAL(161, 11),  // "drawResults"
        QT_MOC_LITERAL(173, 3),  // "x_1"
        QT_MOC_LITERAL(177, 3),  // "y_1"
        QT_MOC_LITERAL(181, 3),  // "x_2"
        QT_MOC_LITERAL(185, 3),  // "y_2"
        QT_MOC_LITERAL(189, 5),  // "color"
        QT_MOC_LITERAL(195, 3),  // "p_1"
        QT_MOC_LITERAL(199, 3),  // "p_2"
        QT_MOC_LITERAL(203, 24),  // "drawOpenedFiguresBorders"
        QT_MOC_LITERAL(228, 24),  // "drawClosedFiguresBorders"
        QT_MOC_LITERAL(253, 22),  // "fillFiguresListAndFlag"
        QT_MOC_LITERAL(276, 12),  // "border_color"
        QT_MOC_LITERAL(289, 10),  // "fill_color"
        QT_MOC_LITERAL(300, 7),  // "start_y"
        QT_MOC_LITERAL(308, 5)   // "end_y"
    },
    "PainterWidget",
    "paintSignal",
    "",
    "resizeSignal",
    "paintEndedSignal",
    "mouseClicked",
    "QMouseEvent*",
    "event",
    "roundSide",
    "Line",
    "l",
    "p1",
    "p2",
    "roundFigure",
    "std::vector<Figure>",
    "figures",
    "drawLine",
    "drawResults",
    "x_1",
    "y_1",
    "x_2",
    "y_2",
    "color",
    "p_1",
    "p_2",
    "drawOpenedFiguresBorders",
    "drawClosedFiguresBorders",
    "fillFiguresListAndFlag",
    "border_color",
    "fill_color",
    "start_y",
    "end_y"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_PainterWidget[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      21,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  140,    2, 0x06,    1 /* Public */,
       3,    0,  141,    2, 0x06,    2 /* Public */,
       4,    0,  142,    2, 0x06,    3 /* Public */,
       5,    1,  143,    2, 0x06,    4 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       8,    1,  146,    2, 0x0a,    6 /* Public */,
       8,    2,  149,    2, 0x0a,    8 /* Public */,
      13,    1,  154,    2, 0x0a,   11 /* Public */,
      16,    5,  157,    2, 0x0a,   13 /* Public */,
      16,    4,  168,    2, 0x2a,   19 /* Public | MethodCloned */,
      16,    3,  177,    2, 0x0a,   24 /* Public */,
      16,    2,  184,    2, 0x2a,   28 /* Public | MethodCloned */,
      25,    2,  189,    2, 0x0a,   31 /* Public */,
      25,    1,  194,    2, 0x2a,   34 /* Public | MethodCloned */,
      26,    2,  197,    2, 0x0a,   36 /* Public */,
      26,    1,  202,    2, 0x2a,   39 /* Public | MethodCloned */,
      27,    3,  205,    2, 0x0a,   41 /* Public */,
      27,    2,  212,    2, 0x2a,   45 /* Public | MethodCloned */,
      27,    1,  217,    2, 0x2a,   48 /* Public | MethodCloned */,
      27,    5,  220,    2, 0x0a,   50 /* Public */,
      27,    4,  231,    2, 0x2a,   56 /* Public | MethodCloned */,
      27,    3,  240,    2, 0x2a,   61 /* Public | MethodCloned */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    7,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void, QMetaType::QPoint, QMetaType::QPoint,   11,   12,
    QMetaType::Void, 0x80000000 | 14,   15,
    0x80000000 | 17, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::QColor,   18,   19,   20,   21,   22,
    0x80000000 | 17, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,   18,   19,   20,   21,
    0x80000000 | 17, QMetaType::QPoint, QMetaType::QPoint, QMetaType::QColor,   23,   24,    2,
    0x80000000 | 17, QMetaType::QPoint, QMetaType::QPoint,   23,   24,
    0x80000000 | 17, 0x80000000 | 14, QMetaType::QColor,   15,   22,
    0x80000000 | 17, 0x80000000 | 14,   15,
    0x80000000 | 17, 0x80000000 | 14, QMetaType::QColor,   15,   22,
    0x80000000 | 17, 0x80000000 | 14,   15,
    0x80000000 | 17, 0x80000000 | 14, QMetaType::QColor, QMetaType::QColor,   15,   28,   29,
    0x80000000 | 17, 0x80000000 | 14, QMetaType::QColor,   15,   28,
    0x80000000 | 17, 0x80000000 | 14,   15,
    0x80000000 | 17, 0x80000000 | 14, QMetaType::Int, QMetaType::Int, QMetaType::QColor, QMetaType::QColor,   15,   30,   31,   28,   29,
    0x80000000 | 17, 0x80000000 | 14, QMetaType::Int, QMetaType::Int, QMetaType::QColor,   15,   30,   31,   28,
    0x80000000 | 17, 0x80000000 | 14, QMetaType::Int, QMetaType::Int,   15,   30,   31,

       0        // eod
};

Q_CONSTINIT const QMetaObject PainterWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_PainterWidget.offsetsAndSizes,
    qt_meta_data_PainterWidget,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_PainterWidget_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<PainterWidget, std::true_type>,
        // method 'paintSignal'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'resizeSignal'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'paintEndedSignal'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'mouseClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QMouseEvent *, std::false_type>,
        // method 'roundSide'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<Line, std::false_type>,
        // method 'roundSide'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QPoint, std::false_type>,
        QtPrivate::TypeAndForceComplete<QPoint, std::false_type>,
        // method 'roundFigure'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const std::vector<Figure> &, std::false_type>,
        // method 'drawLine'
        QtPrivate::TypeAndForceComplete<drawResults, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<QColor, std::false_type>,
        // method 'drawLine'
        QtPrivate::TypeAndForceComplete<drawResults, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'drawLine'
        QtPrivate::TypeAndForceComplete<drawResults, std::false_type>,
        QtPrivate::TypeAndForceComplete<QPoint, std::false_type>,
        QtPrivate::TypeAndForceComplete<QPoint, std::false_type>,
        QtPrivate::TypeAndForceComplete<QColor, std::false_type>,
        // method 'drawLine'
        QtPrivate::TypeAndForceComplete<drawResults, std::false_type>,
        QtPrivate::TypeAndForceComplete<QPoint, std::false_type>,
        QtPrivate::TypeAndForceComplete<QPoint, std::false_type>,
        // method 'drawOpenedFiguresBorders'
        QtPrivate::TypeAndForceComplete<drawResults, std::false_type>,
        QtPrivate::TypeAndForceComplete<const std::vector<Figure> &, std::false_type>,
        QtPrivate::TypeAndForceComplete<QColor, std::false_type>,
        // method 'drawOpenedFiguresBorders'
        QtPrivate::TypeAndForceComplete<drawResults, std::false_type>,
        QtPrivate::TypeAndForceComplete<const std::vector<Figure> &, std::false_type>,
        // method 'drawClosedFiguresBorders'
        QtPrivate::TypeAndForceComplete<drawResults, std::false_type>,
        QtPrivate::TypeAndForceComplete<const std::vector<Figure> &, std::false_type>,
        QtPrivate::TypeAndForceComplete<QColor, std::false_type>,
        // method 'drawClosedFiguresBorders'
        QtPrivate::TypeAndForceComplete<drawResults, std::false_type>,
        QtPrivate::TypeAndForceComplete<const std::vector<Figure> &, std::false_type>,
        // method 'fillFiguresListAndFlag'
        QtPrivate::TypeAndForceComplete<drawResults, std::false_type>,
        QtPrivate::TypeAndForceComplete<const std::vector<Figure> &, std::false_type>,
        QtPrivate::TypeAndForceComplete<QColor, std::false_type>,
        QtPrivate::TypeAndForceComplete<QColor, std::false_type>,
        // method 'fillFiguresListAndFlag'
        QtPrivate::TypeAndForceComplete<drawResults, std::false_type>,
        QtPrivate::TypeAndForceComplete<const std::vector<Figure> &, std::false_type>,
        QtPrivate::TypeAndForceComplete<QColor, std::false_type>,
        // method 'fillFiguresListAndFlag'
        QtPrivate::TypeAndForceComplete<drawResults, std::false_type>,
        QtPrivate::TypeAndForceComplete<const std::vector<Figure> &, std::false_type>,
        // method 'fillFiguresListAndFlag'
        QtPrivate::TypeAndForceComplete<drawResults, std::false_type>,
        QtPrivate::TypeAndForceComplete<const std::vector<Figure> &, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<QColor, std::false_type>,
        QtPrivate::TypeAndForceComplete<QColor, std::false_type>,
        // method 'fillFiguresListAndFlag'
        QtPrivate::TypeAndForceComplete<drawResults, std::false_type>,
        QtPrivate::TypeAndForceComplete<const std::vector<Figure> &, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<QColor, std::false_type>,
        // method 'fillFiguresListAndFlag'
        QtPrivate::TypeAndForceComplete<drawResults, std::false_type>,
        QtPrivate::TypeAndForceComplete<const std::vector<Figure> &, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>
    >,
    nullptr
} };

void PainterWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PainterWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->paintSignal(); break;
        case 1: _t->resizeSignal(); break;
        case 2: _t->paintEndedSignal(); break;
        case 3: _t->mouseClicked((*reinterpret_cast< std::add_pointer_t<QMouseEvent*>>(_a[1]))); break;
        case 4: _t->roundSide((*reinterpret_cast< std::add_pointer_t<Line>>(_a[1]))); break;
        case 5: _t->roundSide((*reinterpret_cast< std::add_pointer_t<QPoint>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QPoint>>(_a[2]))); break;
        case 6: _t->roundFigure((*reinterpret_cast< std::add_pointer_t<std::vector<Figure>>>(_a[1]))); break;
        case 7: { drawResults _r = _t->drawLine((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<QColor>>(_a[5])));
            if (_a[0]) *reinterpret_cast< drawResults*>(_a[0]) = std::move(_r); }  break;
        case 8: { drawResults _r = _t->drawLine((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[4])));
            if (_a[0]) *reinterpret_cast< drawResults*>(_a[0]) = std::move(_r); }  break;
        case 9: { drawResults _r = _t->drawLine((*reinterpret_cast< std::add_pointer_t<QPoint>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QPoint>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QColor>>(_a[3])));
            if (_a[0]) *reinterpret_cast< drawResults*>(_a[0]) = std::move(_r); }  break;
        case 10: { drawResults _r = _t->drawLine((*reinterpret_cast< std::add_pointer_t<QPoint>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QPoint>>(_a[2])));
            if (_a[0]) *reinterpret_cast< drawResults*>(_a[0]) = std::move(_r); }  break;
        case 11: { drawResults _r = _t->drawOpenedFiguresBorders((*reinterpret_cast< std::add_pointer_t<std::vector<Figure>>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QColor>>(_a[2])));
            if (_a[0]) *reinterpret_cast< drawResults*>(_a[0]) = std::move(_r); }  break;
        case 12: { drawResults _r = _t->drawOpenedFiguresBorders((*reinterpret_cast< std::add_pointer_t<std::vector<Figure>>>(_a[1])));
            if (_a[0]) *reinterpret_cast< drawResults*>(_a[0]) = std::move(_r); }  break;
        case 13: { drawResults _r = _t->drawClosedFiguresBorders((*reinterpret_cast< std::add_pointer_t<std::vector<Figure>>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QColor>>(_a[2])));
            if (_a[0]) *reinterpret_cast< drawResults*>(_a[0]) = std::move(_r); }  break;
        case 14: { drawResults _r = _t->drawClosedFiguresBorders((*reinterpret_cast< std::add_pointer_t<std::vector<Figure>>>(_a[1])));
            if (_a[0]) *reinterpret_cast< drawResults*>(_a[0]) = std::move(_r); }  break;
        case 15: { drawResults _r = _t->fillFiguresListAndFlag((*reinterpret_cast< std::add_pointer_t<std::vector<Figure>>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QColor>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QColor>>(_a[3])));
            if (_a[0]) *reinterpret_cast< drawResults*>(_a[0]) = std::move(_r); }  break;
        case 16: { drawResults _r = _t->fillFiguresListAndFlag((*reinterpret_cast< std::add_pointer_t<std::vector<Figure>>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QColor>>(_a[2])));
            if (_a[0]) *reinterpret_cast< drawResults*>(_a[0]) = std::move(_r); }  break;
        case 17: { drawResults _r = _t->fillFiguresListAndFlag((*reinterpret_cast< std::add_pointer_t<std::vector<Figure>>>(_a[1])));
            if (_a[0]) *reinterpret_cast< drawResults*>(_a[0]) = std::move(_r); }  break;
        case 18: { drawResults _r = _t->fillFiguresListAndFlag((*reinterpret_cast< std::add_pointer_t<std::vector<Figure>>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<QColor>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<QColor>>(_a[5])));
            if (_a[0]) *reinterpret_cast< drawResults*>(_a[0]) = std::move(_r); }  break;
        case 19: { drawResults _r = _t->fillFiguresListAndFlag((*reinterpret_cast< std::add_pointer_t<std::vector<Figure>>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<QColor>>(_a[4])));
            if (_a[0]) *reinterpret_cast< drawResults*>(_a[0]) = std::move(_r); }  break;
        case 20: { drawResults _r = _t->fillFiguresListAndFlag((*reinterpret_cast< std::add_pointer_t<std::vector<Figure>>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3])));
            if (_a[0]) *reinterpret_cast< drawResults*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (PainterWidget::*)();
            if (_t _q_method = &PainterWidget::paintSignal; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (PainterWidget::*)();
            if (_t _q_method = &PainterWidget::resizeSignal; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (PainterWidget::*)();
            if (_t _q_method = &PainterWidget::paintEndedSignal; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (PainterWidget::*)(QMouseEvent * );
            if (_t _q_method = &PainterWidget::mouseClicked; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject *PainterWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PainterWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PainterWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int PainterWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 21)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 21;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 21)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 21;
    }
    return _id;
}

// SIGNAL 0
void PainterWidget::paintSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void PainterWidget::resizeSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void PainterWidget::paintEndedSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void PainterWidget::mouseClicked(QMouseEvent * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
