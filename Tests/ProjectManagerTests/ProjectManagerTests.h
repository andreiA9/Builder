#ifndef PROJECT_MANAGER_TESTS_H
#define PROJECT_MANAGER_TESTS_H

// local project headers
// ----------------------
#include "PrjMenu.h"
#include "Instance.h"
#include "EventListener.h"

// standard C/C++ headers
// ----------------------
#include <QtTest>

class ProjectManagerTests : public QObject
{
    Q_OBJECT

private slots:
    void execute();

private:
    PrjMenu m_prjMenu;
};

#endif // PROJECT_MANAGER_TESTS_H
