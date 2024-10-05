#ifndef PRJ_CONTROLLER_H
#define PRJ_CONTROLLER_H

// local project headers
// ----------------------
#include "PrjParser.h"
#include "Constants.h"

// standard C/C++ headers
// ----------------------
#include <QDir>
#include <QMap>

class PrjPerformer
{

public:
    PrjPerformer();

    // this finds the folder mapped to each BuildOperation
    // the mapping is done inside m_OperationToPathMap
    bool findResourceDirectory(int selection, QString& resourceDir);

    bool recompileFileIfModified(const QString& workingDir,
                                 const QStringList& sourceFiles,
                                 QVector<QString>& commandQueue);

    bool parseProjectFile(int selection, QString& workingDir, PrjTemplate& prjTemplate);

    QVector<QString> handleApp(const QString& workingDir, const QStringList& sourceFiles);

    QVector<QString> handleLib(const QString& workingDir, const QStringList& sourceFiles);

    QVector<QString>
    handleSubdirs(const QString& workingDir, const QStringList& sourceFiles);

    bool handle(PrjTemplate prjTemplate, QString& resourceDir);

private:
    QDir m_workingDirectory;
    QMap<PrjParser::PrjFileType, QString> m_OperationToPathMap;
    PrjParser m_prjParser;
};

#endif // PRJ_CONTROLLER_H

