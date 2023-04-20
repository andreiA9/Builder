#ifndef APPLICATION_WINDOW_H
#define APPLICATION_WINDOW_H

#include "WindowContainer.h"
#include "BuildModule.h"

class ApplicationWindow : public WindowContainer
{
    Q_OBJECT

public:
    ApplicationWindow();

    void initializeConnects();

private slots:
    void interpretCommand();

    void getTreeViewSelection();

private:
    BuildModule* m_buildModule;
};

#endif // APPLICATION_WINDOW_H
