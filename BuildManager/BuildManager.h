#ifndef BUILD_MODULE_H
#define BUILD_MODULE_H

#include "Target.h"

#include <QStackedWidget>

class BuildManager : public QObject
{
    // TODO: remove this once this line has been removed, and the implementation changed
    // connect(m_BuildManager, &BuildManager::compileOutputChanged, this, &ApplicationWindow::updateOutputTextEdit);
    Q_OBJECT

public:
    BuildManager();

    inline bool isProcessReady() { return m_target->isProcessReady(); }

    inline const QString& getBashOutput() { return m_target->getBashOutput(); }

    void setBuildSystemType() {};

    void setRunConfiguration() {};

    void setProjectNode() {};

    void executeCommand(const QString& command);

    void executeCompileFile(const QString& fileName);

    void executeBuildDirectory(const QString& directoryName);

signals:
    void compileOutputChanged();

private slots:
    void updateOutputTextEdit();

private:
    Target* m_target;
    QString m_buildCommand;
};

#endif // BUILD_MODULE_H
