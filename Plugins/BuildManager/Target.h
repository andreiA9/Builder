#ifndef TARGET_H
#define TARGET_H

// local project headers
// ----------------------
#include "GccHandler.h"
#include "BuildStep.h"
#include "EventListener.h"
#include "ProjectInfo.h"

// standard C/C++ headers
// ----------------------
#include <QObject>

class Target : public QObject
{
    Q_OBJECT

public:
    Target(EventListener* eventListener, ProjectInfo* projectInfo);

    ~Target();

    inline bool isProcessReady() { return m_buildStep->isProcessReady(); }

    inline const QString& getBashOutput() { return m_buildStep->getBashOutput(); }

    void process(const QString& buildCommand, const QString& unitName);

    QVector<QString> getBuildCommandQueue(BuildRequest event, const QString& buildCommand,
                                          QString& resourceDir);

    void executeCommand(const QString& command);

    void execute();

    bool handleOperation(int selection);

private:
    EventListener* m_eventListener;
    ProjectInfo* m_projectInfo;

    GccHandler m_gccHandler;

    BuildStep* m_buildStep;
    QThread m_workerThread;
};

#endif // TARGET_H

