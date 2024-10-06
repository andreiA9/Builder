// local project headers
// ----------------------
#include "PrjParser.h"

// standard C/C++ headers
// ----------------------
#include <QProcess>
#include <QFileInfo>
#include <QDateTime>
#include <QDebug>

static const char* CPP_SOURCES_EXTENSION = "*.cpp";
static const char* PRJ_FILE_EXTENSION = "*.prj";

QStringList getSourceFiles(const QDir& directory)
{
    QStringList sourceFilters;
    sourceFilters << CPP_SOURCES_EXTENSION;
    sourceFilters << PRJ_FILE_EXTENSION;
    return directory.entryList(sourceFilters, QDir::Files);
}

PrjParser::PrjParser()
{

}

PrjTemplate PrjParser::getPrjTemplate()
{
    return m_prjReader.getTemplate();
}

bool PrjParser::parseProjectPrj(const QString& workingDir, const QStringList& sourceFiles)
{
    Q_UNUSED(workingDir);
    Q_UNUSED(sourceFiles);
    qDebug() << "Parsing project prj";

    return true;
}

bool PrjParser::parsePrjFile(const QString& workingDir, const QStringList& sourceFiles)
{
    Q_UNUSED(workingDir);
    Q_UNUSED(sourceFiles);
    qDebug() << "Parsing binary prj";
    for (const auto& file : sourceFiles)
    {
        if (file.endsWith(".prj"))
        {
            m_prjReader.readPrjFile(QString(workingDir + "/" + file));
        }
    }
    
    return true;
}

bool PrjParser::parseSubdirsPrj(const QString& workingDir, const QStringList& sourceFiles)
{
    Q_UNUSED(workingDir);
    Q_UNUSED(sourceFiles);
    qDebug() << "Parsing subdirs prj";

    return true;
}

bool PrjParser::performOperation(PrjFileType event, const QString& resourceDir)
{
    QDir resourceDirectory(resourceDir);
    QStringList sourceFiles = getSourceFiles(resourceDirectory);

    switch (event)
    {
        case PrjFileType::ProjectPrj:
        {
            parseProjectPrj(resourceDir, sourceFiles);
            break;
        }
        case PrjFileType::BinaryPrj:
        case PrjFileType::LibraryPrj:
        {
            parsePrjFile(resourceDir, sourceFiles);
            break;
        }
        case PrjFileType::SubdirsPrj:
        {
            parseSubdirsPrj(resourceDir, sourceFiles);
            break;
        }
        default:
        {
            qDebug() << "Invalid selection";
            break;
        }
    }

    return true;
}
