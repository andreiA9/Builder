// local project headers
// ----------------------
#include "Project.h"

// standard C/C++ headers
// ----------------------

Project::Project(const QUrl& projectFileNameWithPath)
{
    m_projectFileNameWithPath = projectFileNameWithPath.toString();
    m_projectPath = projectFileNameWithPath.toString(QUrl::RemoveFilename);
}

void Project::loadProject()
{

}

void Project::setProjectSettings(ProjectSettings& projectSettings)
{
    m_projectSettings = projectSettings;
    projectSettings.getBuildSystemType();
}
