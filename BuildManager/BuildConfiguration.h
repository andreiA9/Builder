#ifndef BUILD_CONFIGURATION_H
#define BUILD_CONFIGURATION_H

// local project headers
// ----------------------
#include "BuildSteps.h"
#include "Target.h"
#include "PrjmakeTarget.h"
#include "QmakeTarget.h"
#include "CmakeTarget.h"

// standard C/C++ headers
// ----------------------

class BuildConfiguration
{
public:
    BuildConfiguration(Target* target);

    void executeBuildSteps();

    void executeCleanSteps();

private:
    BuildSteps m_buildSteps;
    Target* m_target;
};

#endif // BUILD_CONFIGURATION_H
