// local project headers
// ----------------------
#include "GccHandler.h"
#include "GccCommandGenerator.h"
#include "DirectoryHelpers.h"

// standard C/C++ headers
// ----------------------
#include <QProcess>
#include <QFileInfo>
#include <QDateTime>
#include <QDebug>
#include <QDirIterator>
#include <QThread>

static const char* CPP_SOURCES_EXTENSION = "*.cpp";
static const char* RESOURCES_PATH = "BuildResources";

static QStringList getSourceFiles(const QDir& directory)
{
    QStringList sourceFilters;
    sourceFilters << CPP_SOURCES_EXTENSION;
    return directory.entryList(sourceFilters, QDir::Files);
}

static QMap<QString, QDateTime> getLastModifiedForFiles(const QString& workingDir, const QStringList& sourceFiles)
{
    QMap<QString, QDateTime> lastModifiedMap;
    for (const QString& source : sourceFiles)
    {
        // compose the file name with path
        QString fileNameWithPath = workingDir + "/" + source;
        QFileInfo fileInfo(fileNameWithPath);
        QDateTime lastModified = fileInfo.lastModified();
        lastModifiedMap[source] = lastModified;
    }

    return lastModifiedMap;
}

GccHandler::GccHandler()
{
    // initialize working directory, i.e. the "BuildResources" directory
    QDir currentDir = QDir::current();
    m_workingDirectory.setPath(currentDir.filePath(RESOURCES_PATH));
    if (!m_workingDirectory.exists())
    {
        qWarning() << "Directory " << m_workingDirectory.absolutePath() << " does not exist.";
    }

    m_OperationToPathMap = {
        { BuildRequest::ExecuteCompileFile, "CompileFolder" },
        { BuildRequest::ExecuteRecompileFile, "RecompileFolder" },
        { BuildRequest::ExecuteBuildDirectory, "ExecutableFolder" },
        { BuildRequest::ExecuteGenerateLib, "LibraryFolder" }
    };
}

bool GccHandler::executeCommand(const QString& workingDirectory, const QString& command)
{
    QProcess bashProcess;

    bashProcess.setWorkingDirectory(workingDirectory);
    bashProcess.start(command);
    // this ensures that the application will wait until the process is ended
    bashProcess.waitForFinished(-1);

    // TODO: ca iti TREBUI DOCUMENTATIE si pentru "qDebug().noquote()"

    // ASTA e pe ERROR
    if(bashProcess.exitCode() != 0)
    {
        QString errorMessages = bashProcess.readAllStandardError();
        qDebug() << "Command resulted in errors!";
        qDebug().noquote() << " Error " << bashProcess.exitCode()
                           << "\n" << errorMessages;
//        m_bashOutput = errorMessages;
        return false;
    }
    // ASTA e pe WARNING
    else
    {
        // this clears the stderr
        QString errorMessages = bashProcess.readAllStandardError();
        qDebug() << "Command successful!";
        qDebug().noquote() << " Ok " << bashProcess.readAllStandardOutput()
                           << "\n" << errorMessages;
//        m_bashOutput = errorMessages;
        return true;
    }
}

QVector<QString>
GccHandler::startCompiling(const QStringList& sourceFiles, QStringList& objectFiles)
{
    QVector<QString> commandQueue;
    // AICI se vor COMPILA toate SURSELE
    // gcc -c PrintMessage.cpp -o PrintMessage.o
    // gcc -c main.cpp -o main.o
    for(const QString &sourceFile : sourceFiles)
    {
        QString objectFile = sourceFile;
        // AICI FISIER:SURSA va DEVENI OBIECT>
        // INCAT sa fie GENERATA COMANDA.de COMPILARE.pentru FISIER:OBIECT
        objectFile.replace(QRegExp("\\.cpp$"), ".o");
        QString command = GccCommandGenerator::generateCompileCommand(sourceFile, objectFile);
        commandQueue.push_back(command);
        objectFiles << objectFile;
    }

    return commandQueue;
}

QString GccHandler::rebuildFileIfModified(const QString& workingDir,
                                               const QStringList& sourceFiles)
{
    QMap<QString, QDateTime> initialLastModifiedMap = getLastModifiedForFiles(workingDir, sourceFiles);

    QStringList sourceFilesToRecompile;
    bool containsModified = false;

    // !!!!
    // !!!!
    // trebuie un BREAKPOINT AICI
    // = la LINIA.cu
    // QMap<QString, QDateTime>
    QMap<QString, QDateTime> finalLastModifiedMap = getLastModifiedForFiles(workingDir, sourceFiles);
    for (auto it = finalLastModifiedMap.begin(); it != finalLastModifiedMap.end(); it++)
    {
        QString fileNameWithPath = it.key();
        QDateTime finalLastModified = it.value();
        QDateTime initialLastModified = initialLastModifiedMap[fileNameWithPath];
        qDebug() << "File name: " << fileNameWithPath;
        qDebug() << "Initial modified: " << initialLastModified;
        qDebug() << "Last modified: " << finalLastModified;
        if (initialLastModifiedMap.contains(fileNameWithPath)
                && initialLastModified < finalLastModified)
        {
            containsModified = true;
            sourceFilesToRecompile.append(fileNameWithPath);
            initialLastModifiedMap[fileNameWithPath] = finalLastModified; // Update the last modified time
        }
    }

    if (!containsModified)
    {
        return QString();
    }

    QString command = GccCommandGenerator::generateRebuildCommand(sourceFilesToRecompile, "myMain");
//    executeCommand(workingDir, command);

    return command;
}

QString GccHandler::buildFolder(const QStringList& sourceFiles)
{
    QString command = GccCommandGenerator::generateBuildCommand(sourceFiles, "myMain");

    return command;
}

QVector<QString>
GccHandler::createLibrary(const QStringList& sourceFiles)
{
    QVector<QString> commandQueue;
    QStringList objectFiles;
    commandQueue = startCompiling(sourceFiles, objectFiles);

    // AICI se va CREA un LIB=din FISIERE:OBJ:
    // ar rcs myLibrary.a PrintMessage.o main.cpp
    commandQueue.push_back(GccCommandGenerator::generateLibraryCommand(objectFiles, "myLibrary.a"));

    return commandQueue;
}

bool GccHandler::findResourceDirectory(BuildRequest event, QString& resourceDir)
{
    bool result;
    /*
    AICI va fi DIRECTORUL:ROOT.pentru RESURSE
    "Plugins/Tests/BuildManagerTests/BuildResources"
     _
    UNDE vei avea fiecare FOLDER;pe CARE se pot RULA TESTELE
    */
    QDirIterator dirIterator(m_workingDirectory.absolutePath(), QDir::Dirs | QDir::NoDotAndDotDot);
    if (dirIterator.hasNext())
    {
        qDebug() << "Checking for corresponding test directory inside root folder...";

    }
    else
    {
        qDebug() << "Could not find root directory: " << dirIterator.path();
        result = false;
    }

    /*
    ACESTEA iti vor fi MAPARILE.de la MENIU.la fiecare BUILD OPERATION
    1. Compile file               -> CompileFolder
    2. Recompile file if modified -> RecompileFolder
    3. Build folder               -> ExecutableFolder
    4. Create library             -> LibraryFolder
    */
    QString mappedFolderPath = m_OperationToPathMap[event];
    result = findFolderInsideRoot(dirIterator, mappedFolderPath, resourceDir);
    return result;
}

QVector<QString>
GccHandler::getCommandQueue(BuildRequest event, const QString& resourceDir)
{
    QDir resourceDirectory(resourceDir);
    QStringList sourceFiles = getSourceFiles(resourceDirectory);

    QVector<QString> commandQueue;
    qDebug() << "Build request: " << event;
    switch (event)
    {
        case BuildRequest::ExecuteCompileFile:
        {
            QStringList objectFiles;
            commandQueue = startCompiling(sourceFiles, objectFiles);
            break;
        }
        case BuildRequest::ExecuteRecompileFile:
        {
            // USECASE-ul.acesta se TESTEAZA doar cu DEBUGGING
            commandQueue.push_back(rebuildFileIfModified(resourceDir, sourceFiles));
            break;
        }
        case BuildRequest::ExecuteBuildDirectory:
        {
            commandQueue.push_back(buildFolder(sourceFiles));
            break;
        }
        case BuildRequest::ExecuteGenerateLib:
        {
            commandQueue = createLibrary(sourceFiles);
            break;
        }
        case BuildRequest::ExecuteCommand:
        {
            break;
        }
        default:
            qDebug() << "Invalid selection";
            break;
    }

    return commandQueue;
}

//void GccController::updateOutputTextEdit()
//{
//    emit compileOutputChanged();
//}
