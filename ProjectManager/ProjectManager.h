#ifndef PROJECT_MANAGER_H
#define PROJECT_MANAGER_H

// local project headers
// ----------------------
#include "ProjectController.h"

// standard C/C++ headers
// ----------------------
#include <QString>
#include <QList>

// !!!!
// THIS is the MODULE
class ProjectManager
{
public:
    ProjectManager();

    bool openFile(const QUrl& projectFileNameWithPath, QByteArray& buffer);

    void openProject(Project* project);

    void setProjectSettings(ProjectSettings& projectSettings);

    // UNSORTED from HERE

    void setActiveProject() {};

    bool saveproject() {};
    void closeAllProjects() {};

    void addProject(Project *project) {};

    void removeProject(Project *project) {};

    void removeProjects(const QList<Project *> &remove) {};

private:
    ProjectController m_projectController;
    QMap<QString, Project*> m_openProjects;
};

#endif // PROJECT_MANAGER_H
