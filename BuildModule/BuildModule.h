#ifndef BUILD_MODULE_H
#define BUILD_MODULE_H

#include "GccInterpreter.h"

#include <QStackedWidget>

class BuildModule
{
public:
    BuildModule(QStackedWidget* stackedWorkArea);

    inline void setWorkingFile(const QString& workingFile) { m_workingFile = workingFile; }

    void executeCommand(const QString& command, QString& bashOutput);

private:
    QStackedWidget* m_stackedWorkArea;
    GccInterpreter m_gccInterpreter;
    QString m_workingFile;
    QString m_buildCommand;
};

#endif // BUILD_MODULE_H
