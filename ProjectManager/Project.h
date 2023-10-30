#ifndef PROJECT_H
#define PROJECT_H

// local project headers
// ----------------------
#include "Document.h"
#include "ProjectNode.h"
#include "ProjectSettings.h"

// standard C/C++ headers
// ----------------------
#include <QString>

// !!!!
// THIS contains the sourceFiles of the project
// and other project related information
class Project
{
public:
    Project(const QUrl& projectFileNameWithPath);

    void operator=(const Project& other) {};

    inline QString& getProjectFileName() { return m_projectFileNameWithPath; }

    inline QString& getProjectPath() { return m_projectPath; }

    inline ProjectNode getProjectNode() const { return m_projectNode; };

    void setProjectSettings(ProjectSettings& projectSettings);

    void loadProject();

    void save() {};

    void addFile(QString& fileName) {};

    bool removeFile() const {};

    bool copyFile(const QString& file) const {};

    bool renameFile(const QString& file) const {};

private:
    QString m_projectFileNameWithPath;
    QString m_projectPath;
    ProjectNode m_projectNode;
    ProjectSettings m_projectSettings;
};

#endif // PROJECT_H
