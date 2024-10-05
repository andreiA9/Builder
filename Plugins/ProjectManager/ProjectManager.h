#ifndef PROJECT_MANAGER_H
#define PROJECT_MANAGER_H

// local project headers
// ----------------------
#include "Instance.h"

// standard C/C++ headers
// ----------------------

class ProjectManager
{
public:
    ProjectManager(EventListener* eventListener);

    void process();

private:
    Instance* m_instance;
};

#endif // PROJECT_MANAGER_H
