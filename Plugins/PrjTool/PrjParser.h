#ifndef PRJ_PARSER_H
#define PRJ_PARSER_H

// local project headers
// ----------------------
#include "PrjReader.h"
#include "Process.h"

// standard C/C++ headers
// ----------------------
#include <QDir>
#include <QStringList>

QStringList getSourceFiles(const QDir& directory);

class PrjParser
{
public:
    enum PrjFileType
    {
        ProjectPrj = 1,
        BinaryPrj = 2,
        LibraryPrj = 3,
        SubdirsPrj = 4,
        RecompileFiles = 5
    };

    PrjParser();

    PrjTemplate getPrjTemplate();

    // Parses a top level .prj file
    bool parseProjectPrj(const QString& workingDir, const QStringList& sourceFiles);

    // Parses a .prj file for a binary or library template
    bool parsePrjFile(const QString& workingDir, const QStringList& sourceFiles);

    // Parses a .prj file for a subdirs template
    bool parseSubdirsPrj(const QString& workingDir, const QStringList& sourceFiles);

    // This is the gcc action to be performed
    bool performOperation(int selection);

    // peform the operation in gcc for the respective directory
    bool performOperation(int selection, const QString& resourceDir);

private:
    PrjReader m_prjReader;
};

#endif // PRJ_PARSER_H
