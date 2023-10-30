#include "BuildManager.h"

#include <QDebug>

BuildManager::BuildManager()
{
    m_target = new Target;

    QObject::connect(m_target, &Target::compileOutputChanged, this,
                     &BuildManager::updateOutputTextEdit);

    /*
    se va rula
    BuildManager::build()
     |
     |---------------------------|
    \ /                         \ /
    GET STEPS from              BuildSystem::
    BuildStep                   build() -> adica se va face BUILD
                                 |
     |---------------------------|
     |
    \ /
    Target::build()
     |
    \ /
    IEI OUTPUT-ul din BuildSystem cu FUNCTIILE.de mai JOS
    BuildSystem::getProjectIssues()
    BuildSystem::getCompileOutput()

    !!!! pentru CONVENIENTA BUILD MODULE este APELAT de EDITOR MODULE
     = ca sa iti fie tie mai USOR
     |
     \
     |
    INSA pe VIITOR SESSION MANAGER va CONTROLA BUILD-ul
     <= din CAUZA ca din ProjectSettings din ProjectManager se va lua
     BuildSystemType>incat sa fie INITIALIZATA clasa BuildSystem
    !!!! NU se poate asta pentru ca BUILD OUTPUT este luat din BuildManager>
    incat sa fie pus in QTextEdit-ul.din EditorModule
    */
}

void BuildManager::executeCommand(const QString& command)
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

    m_target->executeCommand(command);
    m_buildCommand = command;
}

void BuildManager::executeCompileFile(const QString& fileName)
{
    // workaround because QLineEdit::editingFinished is emitted twice
    if (m_buildCommand == fileName)
    {
        return;
    }
    else
    {
        m_buildCommand.clear();
    }

    m_target->executeCompileFile(fileName);
    m_buildCommand = fileName;
}

void BuildManager::executeBuildDirectory(const QString& directoryName)
{
    // workaround because QLineEdit::editingFinished is emitted twice
    if (m_buildCommand == directoryName)
    {
        return;
    }
    else
    {
        m_buildCommand.clear();
    }

    m_target->executeBuildDirectory(directoryName);
    m_buildCommand = directoryName;
}

void BuildManager::updateOutputTextEdit()
{
    emit compileOutputChanged();
}
