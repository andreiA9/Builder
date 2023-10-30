#ifndef DIRECTORY_NODE_H
#define DIRECTORY_NODE_H

// local project headers
// ----------------------

// standard C/C++ headers
// ----------------------
#include <QUrl>

// !!!!
// THIS contains a sourceFile of the project
class DirectoryNode
{
public:
    DirectoryNode();

    // parent project, will be nullptr for the top-level project
    DirectoryNode *parentProjectNode() const;

    // parent folder or project
    DirectoryNode* parentFolderNode() const { return m_parentFolderNode; };

    void setFilePath(const QUrl& filePath) { m_filePath = filePath; };

    void addFileToNode();

    void addDirectoryNode();

private:
    DirectoryNode* m_parentFolderNode;
    QUrl m_filePath;
};

#endif // DIRECTORY_NODE_H
