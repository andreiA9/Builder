#ifndef BUILD_MANAGER_H
#define BUILD_MANAGER_H

// local project headers
// ----------------------
#include "Target.h"
#include "EventListener.h"

// standard C/C++ headers
// ----------------------
#include <QObject>

class BuildManager : public QObject
{
    // TODO: remove this once this line has been removed, and the implementation changed
    // connect(m_BuildManager, &BuildManager::compileOutputChanged, this, &ApplicationWindow::updateOutputTextEdit);
    Q_OBJECT

public:
    BuildManager(EventListener* eventListener, ProjectInfo* projectInfo);

    ~BuildManager();

    inline bool isProcessReady() { return false; }

    QString getBashOutput() { return {}; }

    void process(const QString& buildCommand, const QString& unitName);

    void executeCommand(const QString& command);

    void setBuildSystemType() {};

    void setRunConfiguration() {};

    void setProjectPath() {};

private:
    Target* m_target;
};

#endif // BUILD_MANAGER_H

