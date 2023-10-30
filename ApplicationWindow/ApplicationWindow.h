#ifndef APPLICATION_WINDOW_H
#define APPLICATION_WINDOW_H

// local project headers
// ----------------------
#include "WindowContainer.h"
#include "EditorModule.h"
#include "SessionModule.h"

// standard C/C++ headers
// ----------------------
#include <QThread>

class ApplicationWindow : public WindowContainer
{
    Q_OBJECT

public:
    enum SlotCall
    {
        NoCall,
        FirstCall,
        SecondCall
    };

    ApplicationWindow();

private:
    void initializeConnects();

private slots:
    void interpretCommand();

    void getTreeViewSelection();

    void getProjectTreeViewSelection();

    void getProjectSelectionOnDoubleClick();

    void doCompile();

    void doLink();

    void doBuild();

private:
    EditorModule* m_editorModule;
    SessionModule m_sessionModule;
    QThread m_workerThread;
    SlotCall m_slotCall;
};

#endif // APPLICATION_WINDOW_H
