#ifndef EDITOR_VIEW_H
#define EDITOR_VIEW_H

// local project headers
// ----------------------
#include "TextEditor.h"

// standard C/C++ headers
// ----------------------
#include <QPushButton>
#include <QStackedWidget>
#include <QTextEdit>
#include <QMap>

class EditorView : public QObject
{
    Q_OBJECT

public:
    EditorView(QStackedWidget* stackedWorkArea);
    ~EditorView();

    void initializeTabs();

    void updateOutputTextEdit(const QString& text);

    void openEditorForDocument(QString& document) {};

    bool closeEditor() {};

    bool saveDocument(QString& document) {};

    bool closeDocument(QString& document) {};

    bool closeAllDocuments() {};

    // TODO: this function will be executed, when a tab was pressed
    // to open the editor in the m_editors map
    void openEditorAt(int index) {};

    // TODO: this function will be executed, when a source file is
    // loaded into the text edit
    void activateEditor() {};

private:
    QPushButton* tab0 = nullptr;
    QPushButton* tab1 = nullptr;
    QPushButton* tab2 = nullptr;
    QPushButton* tab3 = nullptr;
    QPushButton* tab4 = nullptr;

    QStackedWidget* m_stackedWorkArea = nullptr;
    QTextEdit* m_outputTextEdit = nullptr;
    QMap<QString, TextEditor*> m_editors;
};

#endif // EDITOR_VIEW_H
