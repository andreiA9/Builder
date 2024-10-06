#include "BuildManagerTests.h"

void BuildManagerTests::execute()
{
    BuildRequest selection =
            static_cast<BuildRequest>(m_buildMenu.displayMenuAndGetSelection());
    m_buildMenu.displayAction(selection);

    // RESURSELE se vor ACCESA.cu
    // :/CompileFolder/main.cpp
    // SAU
    // :/Resources/CompileFolder/main.cpp
    ProjectInfo* projectInfo = nullptr;
    Target target(projectInfo);

    QString resourceDir;
    QVector<QString> commandQueue;
    BuildRequest event = static_cast<BuildRequest>(selection);
    target.handleOperation(event, resourceDir, commandQueue);
    target.executeCommandQueue(resourceDir, commandQueue);
}

QTEST_MAIN(BuildManagerTests)
