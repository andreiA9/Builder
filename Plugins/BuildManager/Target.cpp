// local project headers
// ----------------------
#include "Target.h"

// standard C/C++ headers
// ----------------------
#include <QDebug>
#include <QUrl>
#include <QThread>

static const char* CPP_SOURCES_EXTENSION = "*.cpp";

static QStringList getSourceFiles(const QDir& directory)
{
    QStringList sourceFilters;
    sourceFilters << CPP_SOURCES_EXTENSION;
    return directory.entryList(sourceFilters, QDir::Files);
}

Target::Target(ProjectInfo* projectInfo)
    : m_projectInfo(projectInfo)
{
}

Target::~Target()
{
}

QVector<QString> Target::getBuildCommandQueue(BuildRequest event, const QString& buildCommand,
                                              QString& resourceDir)
{
    QDir resourceDirectory(resourceDir);
    QStringList sourceFiles = getSourceFiles(resourceDirectory);

    QVector<QString> commandQueue;
    qDebug() << "Build request: " << event;
    switch (event)
    {
        case ExecuteCompileFile:
        {
            QStringList objectFiles;
            commandQueue = m_gccHandler.startCompiling(sourceFiles, objectFiles);
            break;
        }
        case ExecuteRecompileFile:
        {
            // USECASE-ul.acesta se TESTEAZA doar cu DEBUGGING
            // BREAKPOINT-ul va fi pe INSTRUCTIUNEA
            // QMap<QString, QDateTime> finalLastModifiedMap = getLastModifiedForFiles(workingDir, sourceFiles);
            commandQueue.append(
                        m_gccHandler.rebuildFileIfModified(resourceDir, sourceFiles));
            break;
        }
        case ExecuteBuildDirectory:
        {
            commandQueue.append(
                        m_gccHandler.buildFolder(sourceFiles));
            break;
        }
        case ExecuteGenerateLib:
        {
            commandQueue.append(
                        m_gccHandler.createLibrary(sourceFiles));
            break;
        }
        case ExecuteCommand:
        {
            executeCommand(buildCommand);
            break;
        }
        default:
            break;
    }

    return commandQueue;
}

void Target::executeCommand(const QString& command)
{
    Q_UNUSED(command);
}

bool Target::handleOperation(BuildRequest event, QString& resourceDir, QVector<QString>& commandQueue)
{
    if (!m_gccHandler.findResourceDirectory(event, resourceDir))
    {
        return false;
    }

    commandQueue = m_gccHandler.getCommandQueue(event, resourceDir);
    return true;
}

void Target::executeCommandQueue(QString resourceDir, QVector<QString> commandQueue)
{
    qDebug() << "Entering directory:" << resourceDir;
    foreach (const QString &command, commandQueue)
    {
        qDebug() << "Executing Build command:" << command;
        m_gccHandler.executeCommand(resourceDir, command);
    }
    qDebug() << "Leaving directory:" << resourceDir;
}
