// local project headers
// ----------------------
#include "PrjPerformer.h"
#include "DirectoryHelpers.h"

// standard C/C++ headers
// ----------------------
#include <QDebug>
#include <QDirIterator>

static const char* RESOURCES_PATH = "PrjResources";

PrjPerformer::PrjPerformer()
{
    // initialize working directory, i.e. the "PrjResources" directory
    QDir currentDir = QDir::current();
    m_workingDirectory.setPath(currentDir.filePath(RESOURCES_PATH));
    if (!m_workingDirectory.exists())
    {
        qDebug() << "Directory " << m_workingDirectory.absolutePath() << " does not exist.";
    }

    m_OperationToPathMap = {
        { PrjParser::ProjectPrj, "TopLevelPrj" },
        { PrjParser::BinaryPrj, "BinaryPrj" },
        { PrjParser::LibraryPrj, "LibraryPrj" },
        { PrjParser::SubdirsPrj, "SubdirsPrj" },
        { PrjParser::SubdirsPrj, "RecompileFolder"}
    };
}

bool PrjPerformer::findResourceDirectory(PrjParser::PrjFileType event, QString& resourceDir)
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
    1. Parse project prj          -> TopLevelPrj
    2. Parse binary prj           -> BinaryPrj
    3. Parse library prj          -> LibraryPrj
    4. Parse subdirs prj          -> SubdirsPrj
    */
    QString mappedFolderPath = m_OperationToPathMap[event];
    result = findFolderInsideRoot(dirIterator, mappedFolderPath, resourceDir);
    return result;
}

bool PrjPerformer::parseProjectFile(PrjParser::PrjFileType event, QString& workingDir,
                                    PrjTemplate& prjTemplate)
{
    if (!m_prjParser.performOperation(event, workingDir))
    {
        qDebug() << "Could not perform requested operation!";
        return false;
    }

    prjTemplate = m_prjParser.getPrjTemplate();
    return true;
}

QVector<QString> PrjPerformer::handleApp(const QString& workingDir, const QStringList& sourceFiles)
{
    Q_UNUSED(workingDir);
    Q_UNUSED(sourceFiles);
    qDebug() << "Handling App project...";
    return {};
}

QVector<QString> PrjPerformer::handleLib(const QString& workingDir, const QStringList& sourceFiles)
{
    Q_UNUSED(workingDir);
    Q_UNUSED(sourceFiles);
    qDebug() << "Handling Lib project...";
    return {};
}

QVector<QString>
PrjPerformer::handleSubdirs(const QString& workingDir, const QStringList& sourceFiles)
{
    Q_UNUSED(workingDir);
    Q_UNUSED(sourceFiles);
    qDebug() << "Handling Subdirs project...";
    return {};
}

bool PrjPerformer::handle(PrjTemplate prjTemplate, QString& resourceDir)
{
    QDir resourceDirectory(resourceDir);
    QStringList sourceFiles = getSourceFiles(resourceDirectory);

    /*
    USECASE-urile care iti MERG AICI sunt doar[App/Lib]
    */
    switch (prjTemplate)
    {
        case PrjTemplate::App:
            handleApp(resourceDir, sourceFiles);
            return true;
        case PrjTemplate::Lib:
            handleLib(resourceDir, sourceFiles);
            return true;
        case PrjTemplate::Subdirs:
            handleSubdirs(resourceDir, sourceFiles);
            return true;
        default:
            return false;
    }
}
