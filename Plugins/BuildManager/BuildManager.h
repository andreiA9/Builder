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

    inline bool isProcessReady() { return m_buildStep->isProcessReady(); }

    inline const QString& getBashOutput() { return m_buildStep->getBashOutput(); }

    void process(const QString& unitName);

    void setBuildSystemType() {};

    void setRunConfiguration() {};

    void setProjectPath() {};

private:
    EventListener* m_eventListener;
    Target* m_target;

    BuildStep* m_buildStep;
    QThread m_workerThread;
};

#endif // BUILD_MANAGER_H

