#ifndef SESSION_MODULE_H
#define SESSION_MODULE_H

// local project headers
// ----------------------
#include "BuildManager.h"
#include "ProjectManager.h"

// standard C/C++ headers
// ----------------------

class Events
{
public:
    enum ProjectRequests
    {
        Request,
        ExecuteCommand,
        ExecuteCompileFile,
        ExecuteBuildDirectory,
    };

};


class SessionModule : public QObject
{
    Q_OBJECT

public:

    SessionModule();

    void setBuildCommand(Events::ProjectRequests projectRequest, const QString& buildCommand);

    void executeCommand(const QString& command);

    void executeCompileFile(const QString& fileName);

    void executeBuildDirectory(const QString& directoryName);

    bool openFile(const QUrl& projectFileNameWithPath, QByteArray& buffer);

    void openProject(const QUrl& projectFileNameWithPath);

    void saveProject();

    void run();

private:
    void checkForRequestsFromUi();

    void checkForResponsesToUi();

signals:
    void compileOutputReady(const QString&);

private:
    BuildManager* m_buildManager;
    ProjectManager m_projectManager;
    Project* m_project;

    Events::ProjectRequests m_projectRequest;
    QString m_buildCommand;
};

#endif // SESSION_MODULE_H
