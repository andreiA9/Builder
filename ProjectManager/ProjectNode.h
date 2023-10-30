#ifndef PROJECT_NODE_H
#define PROJECT_NODE_H

#include "DirectoryNode.h"

#include <QUrl>

// !!!!
// THIS contains a sourceFile of the project
class ProjectNode : public DirectoryNode
{
public:
    ProjectNode();

    // parent project, will be nullptr for the top-level project
    ProjectNode *parentProjectNode() const;

    void setFilePath(const QUrl& filePath) { m_filePath = filePath; };

    void addFileToNode();

    void addDirectoryNode();

private:
    ProjectNode* m_parentFolderNode;
    QUrl m_filePath;
};

#endif // PROJECT_NODE_H
