#ifndef PROJECTS_VIEW_H
#define PROJECTS_VIEW_H

#include "ProjectManager.h"

#include <QString>
#include <QListView>
#include <QWidget>

// !!!!
// THIS contains a list model with the projects
class ProjectsView : public QWidget
{
public:
    // this expands a project
    void onProjectDoubleClicked() {};

    // this opens a file in the text editor
    void onProjectFileDoubleClicked() {};

    // this will set the active project from the list of projects
    void setActiveProject();

private:
    // fiecare ItemModel din aceasta LISTA<
    // va deveni un PROIECT=TREE VIEW.separat;
    // la care vei putea sa ii faci EXPAND
    QListView m_projectsListView;

    ProjectManager m_projectManager;
};

#endif // PROJECTS_VIEW_H
