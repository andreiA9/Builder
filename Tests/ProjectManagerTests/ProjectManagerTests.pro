TEMPLATE = app

TARGET = ProjectManagerTests

# ASTA trebuie pentru QTest FRAMEWORK
QT += testlib

#CONFIG += console

SOURCES += \
    ProjectManagerTests.cpp

HEADERS += \
    ProjectManagerTests.h

# Link the necessary library
LIBS += -L../../Plugins/ProjectManager -lProjectManager
LIBS += -L../../Plugins/PrjTool -lPrjTool
LIBS += -L../../Plugins/Components -lComponents

# Specify the dependencies
PRE_TARGETDEPS += \
    ../../Plugins/ProjectManager/libProjectManager.a \
    ../../Plugins/PrjTool/libPrjTool.a \
    ../../Plugins/Components/libComponents.a

include(../../global.pri)
# ASTA iti este COMMON-cu MENIUL
include(../common/common.pri)

RESOURCES_PATH = ../../PrjResources/

RESOURCES += $$RESOURCES_PATH/resources.qrc

# AICI ii spui unde INSTALEAZA FISIERUL.tau
resource_files.files = $$RESOURCES_PATH/*
resource_files.path = $$OUT_PWD/PrjResources

# ASTA este ADAUGAREA.la LISTA de INSTALL-uri pentru PROIECT
INSTALLS += resource_files
