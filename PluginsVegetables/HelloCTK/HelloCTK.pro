QT += core
QT -= gui

TEMPLATE = lib
CONFIG += plugin \
          c++11 \
          
TARGET = HelloCTK
DESTDIR = $$PWD/../../bin/plugins

include($$PWD/../../lib/libCTK/CTK.pri)

HEADERS += \
    $$PWD/HelloActivator.h \
    HelloImpl.h \
    HelloService.h

SOURCES += \
    $$PWD/HelloActivator.cpp \
    HelloImpl.cpp

RESOURCES += \
    $$PWD/HelloCTK.qrc
