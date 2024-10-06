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
    instance.execute(selection);
}

QTEST_MAIN(ProjectManagerTests)
