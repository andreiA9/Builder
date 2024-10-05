TEMPLATE = lib

TARGET = ProjectManager

# Include the plugin configuration
CONFIG += plugin staticlib

SOURCES += \
    ProjectManager.cpp \
    ProjectInfo.cpp \
    Instance.cpp

HEADERS += \
    ProjectManager.h \
    ProjectInfo.h \
    Instance.h

include(../../global.pri)

QT += core
