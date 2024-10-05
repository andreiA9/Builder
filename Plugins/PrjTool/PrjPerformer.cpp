#include "PrjPerformer.h"

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

bool PrjPerformer::findResourceDirectory(int selection, QString& resourceDir)
{
    // Create a QDirIterator to iterate through a directory and its subdirectories
    // You can pass additional filters such as QDir::Files, QDir::Dirs, etc.,
    // and flags such as QDirIterator::Subdirectories to the constructor if needed.
    QDirIterator dirIterator(m_workingDirectory.absolutePath(), QDir::Dirs | QDir::NoDotAndDotDot);

    qDebug() << "dirIterator.hasNext(): " << dirIterator.hasNext();
    // Get the root directory
    qDebug() << "rootDir: " << dirIterator.path();

    // each build operation is mapped to a folder path, so we need to get
    // the folder for the current operation
    QString mappedFolderPath = m_OperationToPathMap[static_cast<PrjParser::PrjFileType>(selection)];

    bool result = false;
    while (dirIterator.hasNext())
    {
        // this is put at the beginning of the function because the first entry is always "."
        dirIterator.next();

        // the name of the current directory
        QFileInfo fileInfo = dirIterator.fileInfo();
        // we want to exclude these entries: ".", ".."
        QString fullPath = fileInfo.absoluteFilePath();
        // this is the path we need, where the specific resources are placed
        if (fullPath.contains(mappedFolderPath))
        {
            resourceDir = fullPath;
            result = true;
        }
    }

    return result;
}

bool PrjPerformer::parseProjectFile(int selection, QString& workingDir, PrjTemplate& prjTemplate)
{
    if (!m_prjParser.performOperation(selection, workingDir))
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
