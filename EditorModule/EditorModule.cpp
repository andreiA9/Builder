// local project headers
// ----------------------
#include "EditorModule.h"
#include "ProjectSettings.h"
#include "Project.h"

// standard C/C++ headers
// ----------------------
#include <QDebug>

EditorModule::EditorModule(QStackedWidget* stackedWorkArea)
    : m_stackedWorkArea(stackedWorkArea)
{
    m_editorView = new EditorView(m_stackedWorkArea);
//    m_buildManager = new BuildManager;

//    QObject::connect(m_buildManager, &BuildManager::compileOutputChanged, this,
//                     &EditorModule::updateOutputTextEdit);
}

void EditorModule::updateOutputTextEdit(const QString& output)
{
    m_editorView->updateOutputTextEdit(output);
}
