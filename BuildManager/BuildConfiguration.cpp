#include "BuildConfiguration.h"

BuildConfiguration::BuildConfiguration(Target* target)
    :   m_target(target)
{
}

void BuildConfiguration::executeBuildSteps()
{
    auto* target = static_cast<QmakeTarget*>(m_target);
    if (m_buildSteps.getCurrentBuildStep() == BuildSteps::QmakeBuildStep)
    {
        target->runQmake();
    }
    else if (m_buildSteps.getCurrentBuildStep() == BuildSteps::MakeBuildStep)
    {
        target->runMake();
    }
}

void BuildConfiguration::executeCleanSteps()
{
    auto* target = static_cast<QmakeTarget*>(m_target);
    if (m_buildSteps.getCurrentCleanStep() == BuildSteps::QmakeCleanStep)
    {
        target->runQmake();
    }
    else if (m_buildSteps.getCurrentCleanStep() == BuildSteps::MakeCleanStep)
    {
        target->runMake();
    }
}
