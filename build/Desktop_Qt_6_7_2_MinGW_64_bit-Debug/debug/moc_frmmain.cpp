/****************************************************************************
** Meta object code from reading C++ file 'frmmain.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../frmmain.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'frmmain.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSFrmMainENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSFrmMainENDCLASS = QtMocHelpers::stringData(
    "FrmMain",
    "loadTestData",
    "",
    "addGeraet",
    "deleteGeraet",
    "showAddPage",
    "onNavChanged",
    "currentRow",
    "openEditForIndex",
    "QModelIndex",
    "index",
    "on_btnAddUser_clicked",
    "on_btnEditUser_clicked",
    "on_btnDeleteUser_clicked",
    "on_btnApproveUser_clicked",
    "on_btnAusleihen_clicked",
    "on_btnRueckgabe_clicked"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSFrmMainENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   86,    2, 0x08,    1 /* Private */,
       3,    0,   87,    2, 0x08,    2 /* Private */,
       4,    0,   88,    2, 0x08,    3 /* Private */,
       5,    0,   89,    2, 0x08,    4 /* Private */,
       6,    1,   90,    2, 0x08,    5 /* Private */,
       8,    1,   93,    2, 0x08,    7 /* Private */,
      11,    0,   96,    2, 0x08,    9 /* Private */,
      12,    0,   97,    2, 0x08,   10 /* Private */,
      13,    0,   98,    2, 0x08,   11 /* Private */,
      14,    0,   99,    2, 0x08,   12 /* Private */,
      15,    0,  100,    2, 0x08,   13 /* Private */,
      16,    0,  101,    2, 0x08,   14 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject FrmMain::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSFrmMainENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSFrmMainENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSFrmMainENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<FrmMain, std::true_type>,
        // method 'loadTestData'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'addGeraet'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'deleteGeraet'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'showAddPage'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onNavChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'openEditForIndex'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QModelIndex &, std::false_type>,
        // method 'on_btnAddUser_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btnEditUser_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btnDeleteUser_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btnApproveUser_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btnAusleihen_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btnRueckgabe_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void FrmMain::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<FrmMain *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->loadTestData(); break;
        case 1: _t->addGeraet(); break;
        case 2: _t->deleteGeraet(); break;
        case 3: _t->showAddPage(); break;
        case 4: _t->onNavChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 5: _t->openEditForIndex((*reinterpret_cast< std::add_pointer_t<QModelIndex>>(_a[1]))); break;
        case 6: _t->on_btnAddUser_clicked(); break;
        case 7: _t->on_btnEditUser_clicked(); break;
        case 8: _t->on_btnDeleteUser_clicked(); break;
        case 9: _t->on_btnApproveUser_clicked(); break;
        case 10: _t->on_btnAusleihen_clicked(); break;
        case 11: _t->on_btnRueckgabe_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject *FrmMain::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FrmMain::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSFrmMainENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int FrmMain::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 12;
    }
    return _id;
}
QT_WARNING_POP
