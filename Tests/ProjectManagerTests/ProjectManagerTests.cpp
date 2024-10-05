#include "ProjectManagerTests.h"

void ProjectManagerTests::execute()
{
    PrjParser::PrjFileType selection =
            static_cast<PrjParser::PrjFileType>(m_prjMenu.displayMenuAndGetSelection());
    m_prjMenu.displayAction(selection);

    // RESURSELE se vor ACCESA.cu
    // :/CompileFolder/main.cpp
    // SAU
    // :/Resources/CompileFolder/main.cpp
    EventListener* eventListener = nullptr;
    Instance instance(eventListener);

    // Invoke GccCommandGenerator based on the user's menu selection
    // (1-compile, 2-recompile, 3-build executable, 4-create library)
    instance.execute(selection);
}

QTEST_MAIN(ProjectManagerTests)
