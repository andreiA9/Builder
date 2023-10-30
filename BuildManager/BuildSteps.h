#ifndef BUILD_STEP_H
#define BUILD_STEP_H

// local project headers
// ----------------------
#include "Process.h"

// standard C/C++ headers
// ----------------------

// !!!!
// for Cmake the build steps are:
// cmake --build . --target all
// cmake --build . --target install
//  |
//  | SAU
//  |
// "QtProjectManager.QMakeBuildStep"
// "Qt4ProjectManager.MakeStep"
//
// !!!!
// ASTA ar trebui sa contina si comenzile pentru fiecare din steps
class BuildSteps : public Process
{
public:
    enum BuildStepType
    {
        QmakeBuildStep,
        MakeBuildStep
    };

    enum CleanStepType
    {
        QmakeCleanStep,
        MakeCleanStep
    };

    inline BuildStepType getCurrentBuildStep() { return m_CurrentBuildStep; }

    inline CleanStepType getCurrentCleanStep() { return m_CurrentCleanStep; }

private:
    BuildStepType m_CurrentBuildStep;
    CleanStepType m_CurrentCleanStep;
};

#endif // BUILD_STEP_H
