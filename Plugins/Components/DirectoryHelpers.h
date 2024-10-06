#ifndef DIRECTORY_HELPERS_H
#define DIRECTORY_HELPERS_H

#include <QString>
#include <QDirIterator>

bool findFolderInsideRoot(QDirIterator& dirIterator, QString& folderPath,
                          QString& resourceDir);

#endif // DIRECTORY_HELPERS_H
