#ifndef EDIT_VIEW_H
#define EDIT_VIEW_H

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

class EditView : public QWidget
{
    Q_OBJECT

public:
    EditView(SessionModule* sessionModule);

    void initializeFileTabs();

    void initializeTreeView();

private:
    // UI
    QGridLayout* m_editWidgetGridLayout;
    QHBoxLayout* m_editTabsLayout;
    QTreeView* m_filesTreeView;
    QTextEdit* m_textEditor;

    SessionModule* m_sessionModule;
};

#endif // EDIT_VIEW_H
