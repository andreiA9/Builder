TEMPLATE = lib

TARGET = BuildManager

# Include the plugin configuration
CONFIG += plugin staticlib

SOURCES += \
    BuildManager.cpp \
    Target.cpp

HEADERS += \
    BuildManager.h \
    Target.h

include(../../global.pri)

QT += core
