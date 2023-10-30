#include "SessionModule.h"

#include <unistd.h>
#include <QDebug>

SessionModule::SessionModule()
{
    m_buildManager = new BuildManager;
}

void SessionModule::setBuildCommand(Events::ProjectRequests projectRequest,
                                    const QString& buildCommand)
{
    m_projectRequest = projectRequest;
    m_buildCommand = buildCommand;
}

void SessionModule::executeCommand(const QString& command)
{
    m_buildManager->executeCommand(command);
}

void SessionModule::executeCompileFile(const QString& fileName)
{
    m_buildManager->executeCompileFile(fileName);
}

void SessionModule::executeBuildDirectory(const QString& directoryName)
{
    m_buildManager->executeBuildDirectory(directoryName);
}

bool SessionModule::openFile(const QUrl& projectFileNameWithPath, QByteArray& buffer)
{
    return m_projectManager.openFile(projectFileNameWithPath, buffer);
}

void SessionModule::openProject(const QUrl& projectFileNameWithPath)
{
    /*
    ProjectController::openProject()
     | POPULEAZA.pe
    \ /
    ProjectNode
     | PASEAZA.la
    \ /
    BuildSystem

    BuildSystem::startBuild()
     |
    \ /
    Target::build()
     |
    \ /
    ia toate Sursele.din Project.ProjectNode
    */
    m_project = new Project(projectFileNameWithPath);
    m_projectManager.openProject(m_project);
    m_project->getProjectNode();
    m_buildManager->setProjectNode();

    // these are populated from the UI
    /*
    ProjectController
     | POPULEAZA.pe
    \ /
    PROJECT SETTINGS.cu TIPUL.de TARGET
     | PASEAZA.la
    \ /
    BuildSystem
    */
    ProjectSettings settings;
    settings.getBuildSystemType();
    m_buildManager->setBuildSystemType();

    /*
    ProjectController::open()
     |
     |
     |
    \ /
    RunConfiguration o sa aiba executabilele din fisierul pro
    QList<QString> m_targetNames; // binary names
     ||
    ASTA e TARGET-ul pentru fiecare binar creat
    Target::setName()
     |
    \ /
    se va alege ce TIP.de TARGET.din ProjectSettings[Qmake/Cmake/Prjmake]
    */
    settings.getRunConfiguration();
    m_buildManager->setRunConfiguration();
}

void SessionModule::saveProject()
{
    m_project->save();
}

void SessionModule::run()
{
    while (true)
    {
        checkForRequestsFromUi();

        checkForResponsesToUi();

        usleep(100);
    }
}

void SessionModule::checkForRequestsFromUi()
{
    switch (m_projectRequest)
    {
        case Events::ExecuteCommand:
        {
            executeCommand(m_buildCommand);
            break;
        }
        case Events::ExecuteCompileFile:
        {
            executeCompileFile(m_buildCommand);
            break;
        }
        case Events::ExecuteBuildDirectory:
        {
            executeBuildDirectory(m_buildCommand);
            break;
        }
    }
}

void SessionModule::checkForResponsesToUi()
{
    if (m_buildManager->isProcessReady())
    {
        qDebug() << "DA";
        emit compileOutputReady(m_buildManager->getBashOutput());
    }
    // this will emit the SIGNAL>to UPDATE the text edit in the EditorModule
}
