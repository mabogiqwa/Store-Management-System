/****************************************************************************
** Meta object code from reading C++ file 'udpbroadcaster.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../udpbroadcaster.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'udpbroadcaster.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.9.0. It"
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
struct qt_meta_tag_ZN14UdpBroadcasterE_t {};
} // unnamed namespace

template <> constexpr inline auto UdpBroadcaster::qt_create_metaobjectdata<qt_meta_tag_ZN14UdpBroadcasterE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "UdpBroadcaster",
        "broadcastSent",
        "",
        "data",
        "dataRequested",
        "broadcastData"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'broadcastSent'
        QtMocHelpers::SignalData<void(const QString &)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 3 },
        }}),
        // Signal 'dataRequested'
        QtMocHelpers::SignalData<void()>(4, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'broadcastData'
        QtMocHelpers::SlotData<void()>(5, 2, QMC::AccessPrivate, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<UdpBroadcaster, qt_meta_tag_ZN14UdpBroadcasterE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject UdpBroadcaster::staticMetaObject = { {
    QMetaObject::SuperData::link<QThread::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN14UdpBroadcasterE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN14UdpBroadcasterE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN14UdpBroadcasterE_t>.metaTypes,
    nullptr
} };

void UdpBroadcaster::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<UdpBroadcaster *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->broadcastSent((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 1: _t->dataRequested(); break;
        case 2: _t->broadcastData(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (UdpBroadcaster::*)(const QString & )>(_a, &UdpBroadcaster::broadcastSent, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (UdpBroadcaster::*)()>(_a, &UdpBroadcaster::dataRequested, 1))
            return;
    }
}

const QMetaObject *UdpBroadcaster::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UdpBroadcaster::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN14UdpBroadcasterE_t>.strings))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int UdpBroadcaster::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void UdpBroadcaster::broadcastSent(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}

// SIGNAL 1
void UdpBroadcaster::dataRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
