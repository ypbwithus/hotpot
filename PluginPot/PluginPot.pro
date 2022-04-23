QT += core \
      gui \
      widgets \

CONFIG += c++11 \
          console \

TARGET = PluginPot
TEMPLATE = app

SOURCES += \
        main.cpp

DESTDIR = $$PWD/../bin

include($$PWD/../lib/libCTK/CTK.pri)
