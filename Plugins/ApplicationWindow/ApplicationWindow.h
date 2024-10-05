#ifndef APPLICATION_WINDOW_H
#define APPLICATION_WINDOW_H

// local project headers
// ----------------------
#include "WindowContainer.h"
#include "SessionModule.h"
#include "EventListener.h"

// standard C/C++ headers
// ----------------------
#include <QThread>

class ApplicationWindow : public WindowContainer
{
    Q_OBJECT

public:
    enum ProjectTab
    {
        EditTab = 0,
        CompileTab = 1
    };

    ApplicationWindow();

    ~ApplicationWindow();

    void initializeConnects();

private slots:
    void onFunctionButton0Clicked();
    void onFunctionButton1Clicked();
    void onFunctionButton2Clicked();
    void onFunctionButton3Clicked();

public slots:
    void handleSelectionChanged(QString selectionName);

private:
    void interpretCommand();

    void doCompile();

    void doBuild();

    void doGenerateLib();

private:
    SessionModule* m_sessionModule;
    QThread m_workerThread;
    ProjectTab m_projectTab;
    EventListener* m_eventListener;
};

#endif // APPLICATION_WINDOW_H
