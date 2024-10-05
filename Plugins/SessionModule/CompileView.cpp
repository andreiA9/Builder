// local project headers
// ----------------------
#include "CompileView.h"

// standard C/C++ headers
// ----------------------
#include <QFileSystemModel>
#include <QDir>
#include <QDebug>

CompileView::CompileView(SessionModule* sessionModule)
    : m_sessionModule(sessionModule)
{
    qDebug() << "CompileView::CompileView()";

    m_compileWidgetGridLayout = new QGridLayout;

    initializeCompileTabs();
    initializeTreeView();

    m_compileOutput = new QTextEdit;
    m_compileOutput->setPlaceholderText("Compile");
    m_compileWidgetGridLayout->addWidget(m_compileOutput, 1, 1);

    m_compileWidgetGridLayout->setColumnStretch(0, 30); // Tree view gets 30% of width
    m_compileWidgetGridLayout->setColumnStretch(1, 70); // Text edit gets 70% of width

    setLayout(m_compileWidgetGridLayout);
}

void CompileView::initializeCompileTabs()
{
    QStringList colors = {"blue", "yellow"};
    QLabel *label3 = new QLabel(QString("Label 3"));
    QLabel *label4 = new QLabel(QString("Label 4"));
    label3->setStyleSheet(QString("background-color: %1").arg(colors[0]));
    label4->setStyleSheet(QString("background-color: %1").arg(colors[1]));

    // AICI CREEZI un LAYOUT pentru label-uri
    m_compileTabsLayout = new QHBoxLayout;
    m_compileTabsLayout->addWidget(label3, 1);
    m_compileTabsLayout->addWidget(label4, 1);
    m_compileWidgetGridLayout->addLayout(m_compileTabsLayout, 0, 1);
}

void CompileView::initializeTreeView()
{
    // create the tree view model
    const QString resourcesPath = QDir::currentPath() + "/Resources";
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
    m_projectTreeView = new QTreeView;
    m_projectTreeView->setModel(model);
    // LINIA.asta este EXTREM de IMPORTANTA
    m_projectTreeView->setRootIndex(model->index(resourcesPath));
    m_compileWidgetGridLayout->addWidget(m_projectTreeView, 1, 0);

    connect(m_projectTreeView->selectionModel(), &QItemSelectionModel::selectionChanged,
                    this, &CompileView::getTreeViewSelection);
}

void CompileView::getTreeViewSelection()
{
    QModelIndexList indexes = m_projectTreeView->selectionModel()->selectedIndexes();
    QFileSystemModel* fileModel = static_cast<QFileSystemModel*>(m_projectTreeView->model());

    if (indexes.size() > 0)
    {
        QModelIndex selectedIndex = indexes.at(0);
        QString fileName = selectedIndex.data().toString();
        QString fileNameWithPath = fileModel->filePath(selectedIndex);
        // ASTA il PASTREZI pentru NUMELE TAB-ului
        qDebug() << "File name: " << fileName;
        // ASTA iti este FISIERUL
        qDebug() << "File path: " << fileNameWithPath;

        emit selectionChanged(fileNameWithPath);
    }
}
