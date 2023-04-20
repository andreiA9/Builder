#include "BuildModule.h"

BuildModule::BuildModule(QStackedWidget* stackedWorkArea)
    : m_stackedWorkArea(stackedWorkArea)
{

}

void BuildModule::executeCommand(const QString& command, QString& bashOutput)
{
    // workaround because QLineEdit::editingFinished is emitted twice
    if (m_buildCommand == command)
    {
        return;
    }
    else
    {
        m_buildCommand.clear();
    }

    m_gccInterpreter.executeCommand(command, bashOutput);
    m_buildCommand = command;
}
