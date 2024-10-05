#ifndef SESSION_MODULE_H
#define SESSION_MODULE_H

// local project headers
// ----------------------
#include "BuildManager.h"
#include "ProjectManager.h"
#include "EventListener.h"
#include "ProjectInfo.h"

// standard C/C++ headers
// ----------------------
#include <QObject>

class SessionModule : public QObject
{
    Q_OBJECT

public:
    enum UiRequest
    {
        BuildUiRequest,
        ProjectRequest
    };

    SessionModule(EventListener* eventListener);

    ~SessionModule();

    void setBuildCommand(const QString& buildCommand);

    void setUnitName(const QString& unitName);

    void run();

    void checkForResponsesToUi();

    void checkForRequestsFromUi();

    bool openFile(const QUrl& projectFileNameWithPath, QByteArray& buffer);

    void openProject(const QUrl& projectFileNameWithPath);

//signals:
//    void compileOutputReady(const QString&);

private:
    BuildManager* m_buildManager;
    ProjectManager* m_projectManager;
    ProjectInfo* m_projectInfo;

    EventListener* m_eventListener;
    UiRequest m_uiRequest;

    QString m_buildCommand;
    QString m_unitName;
};

#endif // SESSION_MODULE_H
