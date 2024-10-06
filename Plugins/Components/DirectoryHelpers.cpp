// local project headers
// ----------------------

// standard C/C++ headers
// ----------------------

#include "DirectoryHelpers.h"

#include <QDebug>

bool findFolderInsideRoot(QDirIterator& dirIterator, QString& folderPath,
                          QString& resourceDir)
{
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
        if (fullPath.contains(folderPath))
        {
            resourceDir = fullPath;
            qDebug() << "Found resource directory: " << resourceDir;
            result = true;
            break;
        }
    }

    return result;
}
