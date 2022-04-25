QT += core
QT -= gui

TEMPLATE = lib
CONFIG += plugin
TARGET = WelcomeCTK
DESTDIR = $$PWD/../../bin/plugins

include($$PWD/../../lib/libCTK/CTK.pri)

HEADERS += \
    welcome_ctk_impl.h \
    welcome_ctk_activator.h

SOURCES += \
    welcome_ctk_impl.cpp \
    welcome_ctk_activator.cpp

RESOURCES += Resource.qrc
