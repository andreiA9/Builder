#include "ProjectController.h"
#include "ProjectImporter.h"

#include <QFile>
#include <QDebug>

bool ProjectController::openFile(const QUrl& projectFileNameWithPath, QByteArray& buffer)
{
    QString fileName = projectFileNameWithPath.toString();
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << QStringLiteral("Could not open %1 for reading, error: %2").arg(fileName, file.errorString());
    }

    if (file.error())
    {
        qDebug() << QStringLiteral("Could not read from %1, error: %2").arg(fileName, file.errorString());
        return false;
    }
    buffer = file.readAll();
    return true;
}

Project* ProjectController::openProject(Project* project)
{
    ProjectImporter projectImporter;
    projectImporter.parsePrjFile(project);
    m_project = project;
}

void ProjectController::setProjectSettings(ProjectSettings& projectSettings)
{
    m_project->setProjectSettings(projectSettings);
}
