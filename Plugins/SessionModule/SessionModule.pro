TEMPLATE = lib

TARGET = SessionModule

# Include the plugin configuration
CONFIG += plugin staticlib

SOURCES += \
    EditView.cpp \
    CompileView.cpp \
    SessionModule.cpp \
    TextEditor.cpp

HEADERS += \
    EditView.h \
    CompileView.h \
    SessionModule.h \
    TextEditor.h

QT += widgets core

include(../../global.pri)
