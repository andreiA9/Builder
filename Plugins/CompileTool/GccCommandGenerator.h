#ifndef GCC_COMMAND_GENERATOR_H
#define GCC_COMMAND_GENERATOR_H

// local project headers
// ----------------------

// standard C/C++ headers
// ----------------------
#include <QStringList>
#include <QMap>
#include <QDateTime>

class GccCommandGenerator
{
public:
    // Generate GCC command for compiling source files
    static QString generateCompileCommand(const QString& sourceFile,
                                          const QString& outputFile);

    // Generate GCC command for compiling source files that have been modified
    static QString generateRebuildCommand(const QStringList& sourceFiles,
                                          const QString& outputFile);

    // Generate GCC command for building an executable from source files
    static QString generateBuildCommand(const QStringList& sourceFiles,
                                        const QString& outputFile);

    // Generate GCC command for creating a library from source files
    static QString generateLibraryCommand(const QStringList& objectFiles,
                                          const QString& outputFile);
};

#endif // GCC_COMMAND_GENERATOR_H
