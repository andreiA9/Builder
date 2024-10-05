DEPENDPATH += $$PWD/Plugins/Components/
DEPENDPATH += $$PWD/Plugins/CompileTool/
DEPENDPATH += $$PWD/Plugins/BuildManager/
DEPENDPATH += $$PWD/Plugins/PrjTool/
DEPENDPATH += $$PWD/Plugins/ProjectManager/
DEPENDPATH += $$PWD/Plugins/SessionModule/
DEPENDPATH += $$PWD/Plugins/ApplicationWindow/

INCLUDEPATH += $$PWD/Plugins/Components/
INCLUDEPATH += $$PWD/Plugins/CompileTool/
INCLUDEPATH += $$PWD/Plugins/BuildManager/
INCLUDEPATH += $$PWD/Plugins/PrjTool/
INCLUDEPATH += $$PWD/Plugins/ProjectManager/
INCLUDEPATH += $$PWD/Plugins/SessionModule/
INCLUDEPATH += $$PWD/Plugins/ApplicationWindow/

# ASTA ai NEVOIE.de EA>INCAT sa SCAPI de niste WARNINGS.din URMATOARELE
# qstyleoption.h / qvariant.h
# trebuie doar unde ai ELEMENTE.de UI.in Qt
QMAKE_CXXFLAGS += -Wno-deprecated-copy
