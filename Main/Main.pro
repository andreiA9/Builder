TEMPLATE = app

# Specify the target name
TARGET = Builder

# Specify the source file
SOURCES += main.cpp

# Enable C++11, Qt, and the widgets module
QT += gui widgets core

# Link the necessary library
LIBS += -L../Plugins/ApplicationWindow -lApplicationWindow
LIBS += -L../Plugins/SessionModule -lSessionModule
LIBS += -L../Plugins/BuildManager -lBuildManager
LIBS += -L../Plugins/CompileTool -lCompileTool
LIBS += -L../Plugins/ProjectManager -lProjectManager
LIBS += -L../Plugins/PrjTool -lPrjTool
LIBS += -L../Plugins/Components -lComponents

# Specify the dependencies
PRE_TARGETDEPS += \
    ../Plugins/ApplicationWindow/libApplicationWindow.a \
    ../Plugins/SessionModule/libSessionModule.a \
    ../Plugins/BuildManager/libBuildManager.a \
    ../Plugins/CompileTool/libCompileTool.a \
    ../Plugins/ProjectManager/libProjectManager.a \
    ../Plugins/PrjTool/libPrjTool.a \
    ../Plugins/Components/libComponents.a

include(../global.pri)

# ASTA ai NEVOIE.de EA>INCAT sa SCAPI de niste WARNINGS
# qstyleoption.h
# trebuie doar unde ai ELEMENTE.de UI.in Qt
QMAKE_CXXFLAGS += -Wno-deprecated-copy

RESOURCES_PATH = ../BuildResources/

RESOURCES += $$RESOURCES_PATH/resources.qrc

# AICI ii spui unde INSTALEAZA FISIERUL.tau
resource_files.files = $$RESOURCES_PATH/*
resource_files.path = $$OUT_PWD/BuildResources

# ASTA este ADAUGAREA.la LISTA de INSTALL-uri pentru PROIECT
INSTALLS += resource_files
