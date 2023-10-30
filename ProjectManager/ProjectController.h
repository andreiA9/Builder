#ifndef PROJECT_CONTROLLER_H
#define PROJECT_CONTROLLER_H

#include "Project.h"
#include "ProjectNode.h"

#include <QString>

// THIS handles the USECASES of PROJECT CREATION
class ProjectController
{
public:
    void setProjectSettings(ProjectSettings& projectSettings);

    bool openFile(const QUrl& projectFileNameWithPath, QByteArray& buffer);

    Project* openProject(Project* project);

    void createProject(const QString& directoryName) {};

    void removeProject(const QString& directoryName) {};

    // TODO: this function will set the current directory
    // for the source files
    void setWorkingDirectory() {};

private:
    Project* m_project;
};

#endif // PROJECT_CONTROLLER_H
