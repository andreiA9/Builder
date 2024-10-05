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
    EventListener* eventListener = nullptr;
    ProjectInfo* projectInfo = nullptr;
    Target target(eventListener, projectInfo);

    // Invoke GccCommandGenerator based on the user's menu selection
    // (1-compile, 2-recompile, 3-build executable, 4-create library)
    target.handleOperation(selection);
}

QTEST_MAIN(BuildManagerTests)
