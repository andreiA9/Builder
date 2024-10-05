TEMPLATE = lib

# Specify the target name
TARGET = PrjTool

# Include the plugin configuration
CONFIG += plugin staticlib

SOURCES += \
    PrjPerformer.cpp \
    PrjParser.cpp \
    PrjReader.cpp

HEADERS += \
    PrjPerformer.h \
    PrjParser.h \
    PrjReader.h \
    Constants.h \
    Process.h

include(../../global.pri)
