TEMPLATE = lib

# Specify the target name
TARGET = CompileTool

# Include the plugin configuration
CONFIG += plugin staticlib

SOURCES += \
    BuildStep.cpp \
    GccCommandGenerator.cpp \
    GccHandler.cpp

HEADERS += \
    BuildStep.h \
    GccCommandGenerator.h \
    GccHandler.h

include(../../global.pri)
