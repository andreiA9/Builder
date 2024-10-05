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

static bool getResourceDirFromUnitName(const QString& unitName, QString& resourceDir)
{
   if (unitName.isEmpty())
   {
       return false;
   }

   // extract the path
   QUrl unitPath = unitName;
   resourceDir = unitPath.toString(QUrl::RemoveFilename);
   return true;
}

Target::Target(EventListener* eventListener, ProjectInfo* projectInfo)
    : m_eventListener(eventListener), m_projectInfo(projectInfo)
{
    m_buildStep = new BuildStep;
//    m_buildStep->moveToThread(&m_workerThread);
//    QObject::connect(&m_workerThread, &QThread::started, m_buildStep, &BuildStep::run);
//    QObject::connect(&m_workerThread, &QThread::finished, m_buildStep, &QObject::deleteLater);
//    m_workerThread.start();

//    QObject::connect(m_buildStep, &BuildStep::compileOutputChanged, this,
//                     &GccController::updateOutputTextEdit);
}

Target::~Target()
{
//    m_workerThread.quit();
//    m_workerThread.wait();

    delete m_buildStep;
}

void Target::process(const QString& buildCommand, const QString& unitName)
{
    if (!m_eventListener->hasEvents())
    {
        return;
    }

    QString resourceDir;
    if (!getResourceDirFromUnitName(unitName, resourceDir))
    {
        return;
    }

    BuildRequest event = m_eventListener->getRequestEvent();
    QVector<QString> commandQueue =
            getBuildCommandQueue(event, buildCommand, resourceDir);

    m_eventListener->clearCurrentEvent();
    m_buildStep->setCommandQueue(resourceDir, commandQueue);
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

bool Target::handleOperation(int selection)
{
    QString resourceDir;
    if (!m_gccHandler.findResourceDirectory(selection, resourceDir))
    {
        return false;
    }

    BuildRequest event = static_cast<BuildRequest>(selection);
    QVector<QString> commandQueue = m_gccHandler.getCommandQueue(event, resourceDir);
    qDebug() << "Entering directory:" << resourceDir;
    foreach (const QString &command, commandQueue)
    {
        qDebug() << "Executing Build command:" << command;
        m_gccHandler.executeCommand(resourceDir, command);
    }
    qDebug() << "Leaving directory:" << resourceDir;

    return true;
}
