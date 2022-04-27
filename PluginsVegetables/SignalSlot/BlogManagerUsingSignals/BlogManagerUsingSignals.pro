QT += core
QT -= gui

TEMPLATE = lib
CONFIG += plugin
TARGET = BlogManagerUsingSignals
DESTDIR = $$PWD/../../../bin/plugins

include($$PWD/../../../lib/libCTK/CTK.pri)

HEADERS += \
    $$PWD/blog_manager_using_signals.h \
    $$PWD/blog_manager_using_signals_activator.h

SOURCES += \
    $$PWD/blog_manager_using_signals.cpp \
    $$PWD/blog_manager_using_signals_activator.cpp

RESOURCES += Resource.qrc
