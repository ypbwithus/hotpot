QT += core
QT -= gui

TEMPLATE = lib
CONFIG += plugin
TARGET = BlogManager
DESTDIR = $$PWD/../../../bin/plugins

include($$PWD/../../../lib/libCTK/CTK.pri)

HEADERS += \
    $$PWD/blog_manager.h \
    $$PWD/blog_manager_activator.h


SOURCES += \
    $$PWD/blog_manager.cpp \
    $$PWD/blog_manager_activator.cpp

RESOURCES += Resource.qrc
