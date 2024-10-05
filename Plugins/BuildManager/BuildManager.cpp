// local project headers
// ----------------------
#include "BuildManager.h"

// standard C/C++ headers
// ----------------------
#include <QDebug>

BuildManager::BuildManager(EventListener* eventListener, ProjectInfo* projectInfo)
{
    m_target = new Target(eventListener, projectInfo);
}

BuildManager::~BuildManager()
{
    delete m_target;
}

void BuildManager::process(const QString& buildCommand, const QString& unitName)
{
    m_target->process(buildCommand, unitName);
}

void BuildManager::executeCommand(const QString& command)
{
    m_target->executeCommand(command);
}
