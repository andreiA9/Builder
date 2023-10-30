// local project headers
// ----------------------
#include "ProjectManager.h"

// standard C/C++ headers
// ----------------------

// fiecare ID de PROIECT va avea
// "ProjectManager.Project.0"
static QString PROJECT_ID = "ProjectManager.Project";

ProjectManager::ProjectManager()
{

}

bool ProjectManager::openFile(const QUrl& projectFileNameWithPath, QByteArray& buffer)
{
    m_projectController.openFile(projectFileNameWithPath, buffer);
}

void ProjectManager::openProject(Project* project)
{
    m_projectController.openProject(project);
    QString projectPath = project->getProjectPath();
    m_openProjects.insert(projectPath, project);
}

void ProjectManager::setProjectSettings(ProjectSettings& projectSettings)
{
    m_projectController.setProjectSettings(projectSettings);
}
