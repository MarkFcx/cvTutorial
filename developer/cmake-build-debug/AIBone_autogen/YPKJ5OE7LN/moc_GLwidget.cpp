/****************************************************************************
** Meta object code from reading C++ file 'GLwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/ui/GLwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GLwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_GLWidget_t {
    QByteArrayData data[44];
    char stringdata0[826];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GLWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GLWidget_t qt_meta_stringdata_GLWidget = {
    {
QT_MOC_LITERAL(0, 0, 8), // "GLWidget"
QT_MOC_LITERAL(1, 9, 18), // "on_loadBtn_clicked"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 21), // "on_loadBinary_clicked"
QT_MOC_LITERAL(4, 51, 22), // "on_save3DPhoto_clicked"
QT_MOC_LITERAL(5, 74, 18), // "on_savePDF_clicked"
QT_MOC_LITERAL(6, 93, 22), // "on_resetCamera_clicked"
QT_MOC_LITERAL(7, 116, 18), // "on_Azimuth_clicked"
QT_MOC_LITERAL(8, 135, 20), // "on_Azimuth_2_clicked"
QT_MOC_LITERAL(9, 156, 15), // "on_Roll_clicked"
QT_MOC_LITERAL(10, 172, 17), // "on_Roll_2_clicked"
QT_MOC_LITERAL(11, 190, 20), // "on_Elevation_clicked"
QT_MOC_LITERAL(12, 211, 22), // "on_Elevation_2_clicked"
QT_MOC_LITERAL(13, 234, 16), // "on_Dolly_clicked"
QT_MOC_LITERAL(14, 251, 18), // "on_Dolly_2_clicked"
QT_MOC_LITERAL(15, 270, 15), // "on_Zoom_clicked"
QT_MOC_LITERAL(16, 286, 17), // "on_Zoom_2_clicked"
QT_MOC_LITERAL(17, 304, 16), // "on_Yaw_l_clicked"
QT_MOC_LITERAL(18, 321, 16), // "on_Yaw_r_clicked"
QT_MOC_LITERAL(19, 338, 18), // "on_Pitch_l_clicked"
QT_MOC_LITERAL(20, 357, 18), // "on_Pitch_r_clicked"
QT_MOC_LITERAL(21, 376, 15), // "testSetDistance"
QT_MOC_LITERAL(22, 392, 15), // "testSetPosition"
QT_MOC_LITERAL(23, 408, 17), // "testSetFocalPoint"
QT_MOC_LITERAL(24, 426, 13), // "testSetViewUp"
QT_MOC_LITERAL(25, 440, 1), // "x"
QT_MOC_LITERAL(26, 442, 1), // "y"
QT_MOC_LITERAL(27, 444, 1), // "z"
QT_MOC_LITERAL(28, 446, 18), // "on_setRoll_clicked"
QT_MOC_LITERAL(29, 465, 35), // "on_setParallelProjection_on_c..."
QT_MOC_LITERAL(30, 501, 36), // "on_setParallelProjection_off_..."
QT_MOC_LITERAL(31, 538, 16), // "testSetViewAngle"
QT_MOC_LITERAL(32, 555, 20), // "testSetClippingRange"
QT_MOC_LITERAL(33, 576, 19), // "testSetWindowCenter"
QT_MOC_LITERAL(34, 596, 16), // "testSetFocalDisk"
QT_MOC_LITERAL(35, 613, 23), // "TestSetScreenBottomLeft"
QT_MOC_LITERAL(36, 637, 33), // "on_useOffAxisProjectionOn_cli..."
QT_MOC_LITERAL(37, 671, 34), // "on_useOffAxisProjectionOff_cl..."
QT_MOC_LITERAL(38, 706, 16), // "setParallelScale"
QT_MOC_LITERAL(39, 723, 20), // "TestSetEyeSeparation"
QT_MOC_LITERAL(40, 744, 18), // "testSetEyePosition"
QT_MOC_LITERAL(41, 763, 16), // "testSetViewShear"
QT_MOC_LITERAL(42, 780, 15), // "testSetEyeAngle"
QT_MOC_LITERAL(43, 796, 29) // "testSetUseHorizontalViewAngle"

    },
    "GLWidget\0on_loadBtn_clicked\0\0"
    "on_loadBinary_clicked\0on_save3DPhoto_clicked\0"
    "on_savePDF_clicked\0on_resetCamera_clicked\0"
    "on_Azimuth_clicked\0on_Azimuth_2_clicked\0"
    "on_Roll_clicked\0on_Roll_2_clicked\0"
    "on_Elevation_clicked\0on_Elevation_2_clicked\0"
    "on_Dolly_clicked\0on_Dolly_2_clicked\0"
    "on_Zoom_clicked\0on_Zoom_2_clicked\0"
    "on_Yaw_l_clicked\0on_Yaw_r_clicked\0"
    "on_Pitch_l_clicked\0on_Pitch_r_clicked\0"
    "testSetDistance\0testSetPosition\0"
    "testSetFocalPoint\0testSetViewUp\0x\0y\0"
    "z\0on_setRoll_clicked\0"
    "on_setParallelProjection_on_clicked\0"
    "on_setParallelProjection_off_clicked\0"
    "testSetViewAngle\0testSetClippingRange\0"
    "testSetWindowCenter\0testSetFocalDisk\0"
    "TestSetScreenBottomLeft\0"
    "on_useOffAxisProjectionOn_clicked\0"
    "on_useOffAxisProjectionOff_clicked\0"
    "setParallelScale\0TestSetEyeSeparation\0"
    "testSetEyePosition\0testSetViewShear\0"
    "testSetEyeAngle\0testSetUseHorizontalViewAngle"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GLWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      39,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  209,    2, 0x0a /* Public */,
       3,    0,  210,    2, 0x0a /* Public */,
       4,    0,  211,    2, 0x0a /* Public */,
       5,    0,  212,    2, 0x0a /* Public */,
       6,    0,  213,    2, 0x0a /* Public */,
       7,    0,  214,    2, 0x0a /* Public */,
       8,    0,  215,    2, 0x0a /* Public */,
       9,    0,  216,    2, 0x0a /* Public */,
      10,    0,  217,    2, 0x0a /* Public */,
      11,    0,  218,    2, 0x0a /* Public */,
      12,    0,  219,    2, 0x0a /* Public */,
      13,    0,  220,    2, 0x0a /* Public */,
      14,    0,  221,    2, 0x0a /* Public */,
      15,    0,  222,    2, 0x0a /* Public */,
      16,    0,  223,    2, 0x0a /* Public */,
      17,    0,  224,    2, 0x0a /* Public */,
      18,    0,  225,    2, 0x0a /* Public */,
      19,    0,  226,    2, 0x0a /* Public */,
      20,    0,  227,    2, 0x0a /* Public */,
      21,    0,  228,    2, 0x0a /* Public */,
      22,    0,  229,    2, 0x0a /* Public */,
      23,    0,  230,    2, 0x0a /* Public */,
      24,    3,  231,    2, 0x0a /* Public */,
      28,    0,  238,    2, 0x0a /* Public */,
      29,    0,  239,    2, 0x0a /* Public */,
      30,    0,  240,    2, 0x0a /* Public */,
      31,    0,  241,    2, 0x0a /* Public */,
      32,    0,  242,    2, 0x0a /* Public */,
      33,    0,  243,    2, 0x0a /* Public */,
      34,    0,  244,    2, 0x0a /* Public */,
      35,    0,  245,    2, 0x0a /* Public */,
      36,    0,  246,    2, 0x0a /* Public */,
      37,    0,  247,    2, 0x0a /* Public */,
      38,    0,  248,    2, 0x0a /* Public */,
      39,    0,  249,    2, 0x0a /* Public */,
      40,    0,  250,    2, 0x0a /* Public */,
      41,    0,  251,    2, 0x0a /* Public */,
      42,    0,  252,    2, 0x0a /* Public */,
      43,    0,  253,    2, 0x0a /* Public */,

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
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   25,   26,   27,
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
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void GLWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        GLWidget *_t = static_cast<GLWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_loadBtn_clicked(); break;
        case 1: _t->on_loadBinary_clicked(); break;
        case 2: _t->on_save3DPhoto_clicked(); break;
        case 3: _t->on_savePDF_clicked(); break;
        case 4: _t->on_resetCamera_clicked(); break;
        case 5: _t->on_Azimuth_clicked(); break;
        case 6: _t->on_Azimuth_2_clicked(); break;
        case 7: _t->on_Roll_clicked(); break;
        case 8: _t->on_Roll_2_clicked(); break;
        case 9: _t->on_Elevation_clicked(); break;
        case 10: _t->on_Elevation_2_clicked(); break;
        case 11: _t->on_Dolly_clicked(); break;
        case 12: _t->on_Dolly_2_clicked(); break;
        case 13: _t->on_Zoom_clicked(); break;
        case 14: _t->on_Zoom_2_clicked(); break;
        case 15: _t->on_Yaw_l_clicked(); break;
        case 16: _t->on_Yaw_r_clicked(); break;
        case 17: _t->on_Pitch_l_clicked(); break;
        case 18: _t->on_Pitch_r_clicked(); break;
        case 19: _t->testSetDistance(); break;
        case 20: _t->testSetPosition(); break;
        case 21: _t->testSetFocalPoint(); break;
        case 22: _t->testSetViewUp((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 23: _t->on_setRoll_clicked(); break;
        case 24: _t->on_setParallelProjection_on_clicked(); break;
        case 25: _t->on_setParallelProjection_off_clicked(); break;
        case 26: _t->testSetViewAngle(); break;
        case 27: _t->testSetClippingRange(); break;
        case 28: _t->testSetWindowCenter(); break;
        case 29: _t->testSetFocalDisk(); break;
        case 30: _t->TestSetScreenBottomLeft(); break;
        case 31: _t->on_useOffAxisProjectionOn_clicked(); break;
        case 32: _t->on_useOffAxisProjectionOff_clicked(); break;
        case 33: _t->setParallelScale(); break;
        case 34: _t->TestSetEyeSeparation(); break;
        case 35: _t->testSetEyePosition(); break;
        case 36: _t->testSetViewShear(); break;
        case 37: _t->testSetEyeAngle(); break;
        case 38: _t->testSetUseHorizontalViewAngle(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject GLWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_GLWidget.data,
      qt_meta_data_GLWidget,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *GLWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GLWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_GLWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int GLWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 39)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 39;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 39)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 39;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
