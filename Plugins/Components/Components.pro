TEMPLATE = lib

TARGET = Components

# Include the plugin configuration
CONFIG += plugin staticlib

SOURCES += \
    EventListener.cpp \
    DirectoryHelpers.cpp

HEADERS += \
    EventListener.h \
    DirectoryHelpers.h \
    CommonTypes.h

include(../../global.pri)

#QMAKE_CXXFLAGS += -pthread
#QMAKE_LFLAGS += -pthread
#LIBS += -lpthread

#CONFIG += thread
