TEMPLATE = lib

TARGET = Components

# Include the plugin configuration
CONFIG += plugin staticlib

SOURCES += \
    EventListener.cpp

HEADERS += \
    EventListener.h \
    CommonTypes.h

include(../../global.pri)

#QMAKE_CXXFLAGS += -pthread
#QMAKE_LFLAGS += -pthread
#LIBS += -lpthread

#CONFIG += thread
