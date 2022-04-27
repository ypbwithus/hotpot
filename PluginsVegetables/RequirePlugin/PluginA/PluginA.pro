QT += core
QT -= gui

TEMPLATE = lib
CONFIG += plugin
TARGET = PluginA
DESTDIR = $$PWD/../../../bin/plugins

include($$PWD/../../../lib/libCTK/CTK.pri)

HEADERS += \
    $$PWD/plugin_a_service.h \
    $$PWD/plugin_a_impl.h \
    $$PWD/plugin_a_activator.h

SOURCES += \
    $$PWD/plugin_a_impl.cpp \
    $$PWD/plugin_a_activator.cpp

RESOURCES += Resource.qrc
