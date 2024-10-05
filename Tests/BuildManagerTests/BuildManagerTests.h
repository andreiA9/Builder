#ifndef BUILD_MANAGER_TESTS_H
#define BUILD_MANAGER_TESTS_H

// local project headers
// ----------------------
#include "BuildMenu.h"
#include "Target.h"
#include "EventListener.h"

// standard C/C++ headers
// ----------------------
#include <QtTest>

class BuildManagerTests : public QObject
{
    Q_OBJECT

private slots:
    void execute();

private:
    BuildMenu m_buildMenu;
};

#endif // BUILD_MANAGER_TESTS_H
