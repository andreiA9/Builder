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
    Target(ProjectInfo* projectInfo);

    ~Target();

    QVector<QString> getBuildCommandQueue(BuildRequest event, const QString& buildCommand,
                                          QString& resourceDir);

    void executeCommand(const QString& command);

    void execute();

    bool handleOperation(BuildRequest event, QString& resourceDir, QVector<QString>& commandQueue);

    void executeCommandQueue(QString resourceDir, QVector<QString> commandQueue);

private:
    ProjectInfo* m_projectInfo;

    GccHandler m_gccHandler;
};

#endif // TARGET_H
