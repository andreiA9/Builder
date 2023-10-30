#ifndef BUILD_SYSTEM_H
#define BUILD_SYSTEM_H

// local project headers
// ----------------------
#include "BuildConfiguration.h"

// standard C/C++ headers
// ----------------------
#include <QString>

// !!!!
// THIS contains INFORMATION about
// the build system: qmake, cmake, your .prj system
//  |
// \ /
// o sa trebuiasca sa ai cate o clasa derivata pentru fiecare
// incat sa apeleze buildQmakeTarget, buildCmakeTarget
class BuildSystem
{
public:
    enum BuildSystemType
    {
        Qmake,
        Cmake,
        Prjmake
    };

    BuildSystem(Target* target);

    // ASTEA sunt ISSUES din Qt Creator
    void getProjectIssues() {};

    // ASTEA este tot Compile Output din Qt Creator
    void getCompileOutput() {};

    // these will be used for the Build command
    void addFile(QString& fileName) {};
    //  |
    // \ /
    // USED when BUILDING
    void buildTarget();

    void cleanTarget();

private:
    BuildConfiguration* m_buildConfiguration;
    // TODO: this should be removed when BuildConfiguration is finalized
    Target* m_target;
};

#endif // BUILD_SYSTEM_H
