// local project headers
// ----------------------
#include "EditView.h"

// standard C/C++ headers
// ----------------------
#include <QFileSystemModel>
#include <QDir>
#include <QDebug>

EditView::EditView(SessionModule* sessionModule)
    : m_sessionModule(sessionModule)
{
    qDebug() << "EditView::EditView()";

    m_editWidgetGridLayout = new QGridLayout;

    initializeFileTabs();
    initializeTreeView();

    m_textEditor = new QTextEdit;
    m_textEditor->setPlaceholderText("Edit");

    m_editWidgetGridLayout->addWidget(m_textEditor, 1, 1);
    m_editWidgetGridLayout->setColumnStretch(0, 30); // Tree view gets 30% of width
    m_editWidgetGridLayout->setColumnStretch(1, 70); // Text edit gets 70% of width

    setLayout(m_editWidgetGridLayout);
}

void EditView::initializeFileTabs()
{
    QStringList colors = {"red", "green"};
    // for the first widget
    QLabel *label1 = new QLabel(QString("Label 1"));
    QLabel *label2 = new QLabel(QString("Label 2"));
    label1->setStyleSheet(QString("background-color: %1").arg(colors[0]));
    label2->setStyleSheet(QString("background-color: %1").arg(colors[1]));

    // AICI CREEZI un LAYOUT pentru label-uri
    m_editTabsLayout = new QHBoxLayout;
    m_editTabsLayout->addWidget(label1, 1);
    m_editTabsLayout->addWidget(label2, 1);
    m_editWidgetGridLayout->addLayout(m_editTabsLayout, 0, 1);
}

void EditView::initializeTreeView()
{
    // create the tree view model
    const QString resourcesPath = QDir::currentPath() + "/PrjResources";
    // create the file system model
    QFileSystemModel* model = new QFileSystemModel;
    // set root path for file system model, to be: build folder + "/Resources"
    model->setRootPath(resourcesPath);
    model->setFilter(QDir::AllDirs | QDir::AllEntries | QDir::NoDotAndDotDot);
    QStringList filter;
    filter << "*.c";
    filter << "*.h";
    filter << "*.cpp";
    // for Prj projects
    filter << "*.prj";
    // for Pro projects
    filter << "*.pro";
    // for Cmake projects
    filter << "*.txt";
    model->setNameFilters(filter);

    // create the file tree view associated to that model
    m_filesTreeView = new QTreeView;
    m_filesTreeView->setModel(model);
    m_filesTreeView->setRootIndex(model->index(resourcesPath));
    m_editWidgetGridLayout->addWidget(m_filesTreeView, 1, 0);
}
