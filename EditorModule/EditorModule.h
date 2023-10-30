#ifndef EDITOR_MODULE_H
#define EDITOR_MODULE_H

#include "EditorView.h"

#include <QStackedWidget>

class EditorModule : public QObject
{
    // TODO: remove this once this line has been removed, and the implementation changed
    // connect(m_EditorModule, &EditorModule::compileOutputChanged, this, &ApplicationWindow::updateOutputTextEdit);
    Q_OBJECT

public:
    EditorModule(QStackedWidget* stackedWorkArea);

public slots:
    void updateOutputTextEdit(const QString& output);

private:
    EditorView* m_editorView = nullptr;
    QStackedWidget* m_stackedWorkArea;
};

#endif // EDITOR_MODULE_H
