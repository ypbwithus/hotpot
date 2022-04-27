QT += core
QT -= gui

TEMPLATE = lib
CONFIG += plugin
TARGET = BlogEventHandler
DESTDIR = $$PWD/../../../bin/plugins

include($$PWD/../../../lib/libCTK/CTK.pri)

HEADERS += \
    $$PWD/blog_event_handler.h \
    $$PWD/blog_event_handler_activator.h

SOURCES += \
    $$PWD/blog_event_handler_activator.cpp

RESOURCES += Resource.qrc
