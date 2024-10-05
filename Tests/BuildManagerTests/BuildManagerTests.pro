TEMPLATE = app

TARGET = BuildManagerTests

# ASTA trebuie pentru QTest FRAMEWORK
QT += testlib

#CONFIG += console

SOURCES += \
    BuildManagerTests.cpp

HEADERS += \
    BuildManagerTests.h

# Link the necessary library
LIBS += -L../../Plugins/BuildManager -lBuildManager
LIBS += -L../../Plugins/CompileTool -lCompileTool
LIBS += -L../../Plugins/Components -lComponents

# Specify the dependencies
PRE_TARGETDEPS += \
    ../../Plugins/BuildManager/libBuildManager.a \
    ../../Plugins/CompileTool/libCompileTool.a \
    ../../Plugins/Components/libComponents.a

include(../../global.pri)
# ASTA iti este COMMON-cu MENIUL
include(../common/common.pri)

RESOURCES_PATH = ../../BuildResources/

RESOURCES += $$RESOURCES_PATH/resources.qrc

# AICI ii spui unde INSTALEAZA FISIERUL.tau
resource_files.files = $$RESOURCES_PATH/*
resource_files.path = $$OUT_PWD/BuildResources

# ASTA este ADAUGAREA.la LISTA de INSTALL-uri pentru PROIECT
INSTALLS += resource_files
