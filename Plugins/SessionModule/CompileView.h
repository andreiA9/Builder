#ifndef COMPILE_VIEW_H
#define COMPILE_VIEW_H

// local project headers
// ----------------------
#include "SessionModule.h"

// standard C/C++ headers
// ----------------------
#include <QWidget>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QTreeView>
#include <QTextEdit>
#include <QLabel>

class CompileView : public QWidget
{
    Q_OBJECT

public:
    CompileView(SessionModule* sessionModule);

    void initializeCompileTabs();

    void initializeTreeView();

    void getTreeViewSelection();

signals:
    void selectionChanged(QString selectionName);

private:
    // UI
    QGridLayout* m_compileWidgetGridLayout;
    QHBoxLayout* m_compileTabsLayout;
    QTreeView* m_projectTreeView;
    QTextEdit* m_compileOutput;

    SessionModule* m_sessionModule;
};

#endif // COMPILE_VIEW_H
