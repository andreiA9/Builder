// local project headers
// ----------------------
#include "ProjectManager.h"

// standard C/C++ headers
// ----------------------
#include <QDebug>

ProjectManager::ProjectManager(EventListener* eventListener)
{
    m_instance = new Instance(eventListener);
}

void ProjectManager::process()
{
}
