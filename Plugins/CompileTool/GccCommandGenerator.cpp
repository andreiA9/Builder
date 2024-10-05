// local project headers
// ----------------------
#include "GccCommandGenerator.h"

// standard C/C++ headers
// ----------------------
#include <QFileInfo>
#include <QDebug>

QString GccCommandGenerator::generateCompileCommand(const QString& sourceFile,
                                                    const QString& outputFile)
{
    QStringList compileArguments = {"gcc"};
    compileArguments << "-c" << "-o" << outputFile << sourceFile;
    QString command = compileArguments.join(' ');
    return command;
}

QString GccCommandGenerator::generateRebuildCommand(const QStringList& sourceFiles,
                                                    const QString& outputFile)
{
    QStringList compileArguments = {"g++"};
    compileArguments << "-o" << outputFile << sourceFiles;
    QString command = compileArguments.join(' ');
    return command;
}

QString GccCommandGenerator::generateBuildCommand(const QStringList& sourceFiles,
                                                  const QString& outputFile)
{
    QStringList compileArguments = {"gcc"};
    compileArguments << "-o" << outputFile << sourceFiles;
    QString command = compileArguments.join(' ');
    return command;
}

QString GccCommandGenerator::generateLibraryCommand(const QStringList& objectFiles,
                                                    const QString& outputFile)
{
    QStringList libraryArguments = {"ar", "rcs"};
    libraryArguments << outputFile << objectFiles;
    QString command = libraryArguments.join(' ');
    return command;
}
