// local project headers
// ----------------------
#include "BuildSystem.h"

// standard C/C++ headers
// ----------------------

BuildSystem::BuildSystem(Target* target)
{
    BuildSystemType buildSystemType;
    switch (buildSystemType)
    {
        case Qmake:
        {
            m_target = new QmakeTarget;
            break;
        }
        case Cmake:
        {
            m_target = new CmakeTarget;
            break;
        }
        case Prjmake:
        {
            m_target = new PrjmakeTarget;
            break;
        }
    }

    m_buildConfiguration = new BuildConfiguration(target);
}

void BuildSystem::buildTarget()
{
    BuildSystemType buildSystemType;
    switch (buildSystemType)
    {
        case Qmake:
        {
            m_buildConfiguration->executeBuildSteps();
            m_target->build();
            break;
        }
        case Cmake:
        {
            m_target->build();
            break;
        }
        case Prjmake:
        {
            m_target->build();
            break;
        }
    }
}

void BuildSystem::cleanTarget()
{
    BuildSystemType buildSystemType;
    switch (buildSystemType)
    {
        case Qmake:
        {
            m_buildConfiguration->executeCleanSteps();
            m_target->clean();
            break;
        }
        case Cmake:
        {
            CmakeTarget target;
            m_target->clean();
            break;
        }
        case Prjmake:
        {
            PrjmakeTarget target;
            m_target->clean();
            break;
        }
    }
}
