#ifndef GCC_CONTROLLER_H
#define GCC_CONTROLLER_H

// local project headers
// ----------------------
#include "CommonTypes.h"

// standard C/C++ headers
// ----------------------
#include <QString>
#include <QStringList>
#include <QDir>
#include <QMap>
#include <QThread>

//class GccController : public QObject
//{
//    Q_OBJECT
class GccHandler
{
public:
    GccHandler();

    bool executeCommand(const QString& workingDirectory, const QString& command);

    // goes through a list of source files, and then performs the compiling on
    // each of them
    // output: list of object files
    QVector<QString>
    startCompiling(const QStringList& sourceFiles, QStringList& objectFiles);

    // Recompiles a source file only if it has been modified since the last compilation.
    QString rebuildFileIfModified(const QString& workingDir,
                                    const QStringList& sourceFiles);

    // Builds and links an executable from a list of object files.
    QString buildFolder(const QStringList& sourceFiles);

    // Builds and links a library from a list of object files.
    QVector<QString>
    createLibrary(const QStringList& sourceFiles);

    // this finds the folder mapped to each BuildRequest
    // the mapping is done inside m_OperationToPathMap
    bool findResourceDirectory(int selection, QString& resourceDir);

    // peform the operation in gcc for the respective directory
    QVector<QString>
    getCommandQueue(BuildRequest event, const QString& resourceDir);

private:
    bool findFolderInsideRoot(QDirIterator& dirIterator, QString& folderPath,
                              QString& resourceDir);

//signals:
//    void compileOutputChanged();

//private slots:
//    void updateOutputTextEdit();

private:
    QDir m_workingDirectory;
    QMap<BuildRequest, QString> m_OperationToPathMap;
};

#endif // GCC_CONTROLLER_H
