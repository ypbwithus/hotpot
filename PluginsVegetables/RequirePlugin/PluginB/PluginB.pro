QT += core
QT -= gui

TEMPLATE = lib
CONFIG += plugin
TARGET = PluginB
DESTDIR = $$PWD/../../../bin/plugins

include($$PWD/../../../lib/libCTK/CTK.pri)

HEADERS += \
    plugin_b_service.h \
    plugin_b_impl.h \
    plugin_b_activator.h

SOURCES += \
    plugin_b_impl.cpp \
    plugin_b_activator.cpp

RESOURCES += Resource.qrc
