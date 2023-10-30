#ifndef PROJECT_SETTINGS_H
#define PROJECT_SETTINGS_H

#include <QString>

// !!!!
// this contains INFORMATION about what
// build system is used[qmake/cmake/prjmake/other]
// and other project info
class ProjectSettings
{
public:
    enum BuildSystemType
    {
        Qmake,
        Cmake,
        Prjmake
    };

    QString getRunConfiguration() {};

    BuildSystemType getBuildSystemType() { return m_buildSystemType; }

private:
    BuildSystemType m_buildSystemType;
};

#endif // PROJECT_SETTINGS_H
