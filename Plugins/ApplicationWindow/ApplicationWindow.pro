TEMPLATE = lib

TARGET = ApplicationWindow

# Include the plugin configuration
CONFIG += plugin staticlib

SOURCES += \
    ApplicationWindow.cpp \
    WindowContainer.cpp \
    ClickableLabel.cpp \

HEADERS += \
    ApplicationWindow.h \
    WindowContainer.h \
    ClickableLabel.h

QT += widgets core

include(../../global.pri)
