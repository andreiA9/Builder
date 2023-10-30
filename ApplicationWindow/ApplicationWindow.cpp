#include "ApplicationWindow.h"

#include <QDebug>
#include <QFileSystemModel>
#include <QMessageBox>

ApplicationWindow::ApplicationWindow()
    : m_slotCall(SlotCall::NoCall)
{
    initializeComandEdit();
    initializeControlButtons();
    initializeBottomGrid();

    QStackedWidget* stackedWorkArea = new QStackedWidget(this);
    m_editorModule = new EditorModule(stackedWorkArea);
    initializeOutputBoardAndTreeView(stackedWorkArea);

    initializeConnects();

    // thread for SessionModule
    m_sessionModule.moveToThread(&m_workerThread);
    connect(&m_workerThread, &QThread::started, &m_sessionModule, &SessionModule::run);
    connect(&m_workerThread, &QThread::finished, &m_sessionModule, &QObject::deleteLater);
    m_workerThread.start();

    QObject::connect(&m_sessionModule, qOverload<const QString&>(&SessionModule::compileOutputReady),
                     m_editorModule, qOverload<const QString&>(&EditorModule::updateOutputTextEdit));
}

void ApplicationWindow::initializeConnects()
{
    connect(m_filesTreeView->selectionModel(), &QItemSelectionModel::selectionChanged,
                    this, &ApplicationWindow::getTreeViewSelection);
    connect(m_projectTreeView->selectionModel(), &QItemSelectionModel::selectionChanged,
                    this, &ApplicationWindow::getProjectTreeViewSelection);
    connect(m_projectTreeView, &QAbstractItemView::doubleClicked,
                    this, &ApplicationWindow::getProjectSelectionOnDoubleClick);

    connect(m_gccComandEdit, &QLineEdit::editingFinished, this, &ApplicationWindow::interpretCommand);

    connect(m_compileButton0, &QPushButton::pressed, this, &ApplicationWindow::doCompile);
    connect(m_linkButton1, &QPushButton::pressed, this, &ApplicationWindow::doLink);
    connect(m_buildButton2, &QPushButton::pressed, this, &ApplicationWindow::doBuild);
}

void ApplicationWindow::getTreeViewSelection()
{
    QModelIndexList indexes = m_filesTreeView->selectionModel()->selectedIndexes();
    QFileSystemModel* fileModel = static_cast<QFileSystemModel*>(m_filesTreeView->model());

    if (indexes.size() > 0)
    {
        QModelIndex selectedIndex = indexes.at(0);
        QString fileName = selectedIndex.data().toString();
        QString fileNameWithPath = fileModel->filePath(selectedIndex);
        // ASTA il PASTREZI pentru NUMELE TAB-ului
        qDebug() << "File name: " << fileName;
        // ASTA iti este FISIERUL
        qDebug() << "File path: " << fileNameWithPath;
        m_gccComandEdit->setText(fileNameWithPath);
    }
}

void ApplicationWindow::getProjectTreeViewSelection()
{
    QModelIndexList indexes = m_projectTreeView->selectionModel()->selectedIndexes();
    QFileSystemModel* fileModel = static_cast<QFileSystemModel*>(m_filesTreeView->model());

    if (indexes.size() > 0)
    {
        QModelIndex selectedIndex = indexes.at(0);
        QString fileName = selectedIndex.data().toString();
        QString fileNameWithPath = fileModel->filePath(selectedIndex);
        // ASTA il PASTREZI pentru NUMELE TAB-ului
        qDebug() << "File name: " << fileName;
        // ASTA iti este FISIERUL
        qDebug() << "File path: " << fileNameWithPath;
        m_gccComandEdit->setText(fileNameWithPath);
    }
}

void ApplicationWindow::getProjectSelectionOnDoubleClick()
{
    // !!!!
    // !!!! NU STERGE ASTA
    // workaround because QAbstractItemView::doubleClicked() is emitted twice
//    if (m_slotCall == SlotCall::SecondCall)
//    {
//        m_slotCall = SlotCall::NoCall;
//        return;
//    }
//    else if (m_slotCall == SlotCall::FirstCall)
//    {
//        m_slotCall = SlotCall::SecondCall;
//    }
//    else if (m_slotCall == SlotCall::NoCall)
//    {
//        m_slotCall = SlotCall::FirstCall;
//    }

    QModelIndexList indexes = m_projectTreeView->selectionModel()->selectedIndexes();
    QFileSystemModel* fileModel = static_cast<QFileSystemModel*>(m_filesTreeView->model());

    if (indexes.size() > 0)
    {
        QModelIndex selectedIndex = indexes.at(0);
        QString fileName = selectedIndex.data().toString();
        QUrl projectFileNameWithPath = fileModel->filePath(selectedIndex);
        // ASTA il PASTREZI pentru NUMELE TAB-ului
        qDebug() << "File name: " << fileName;
        // ASTA iti este FISIERUL
        qDebug() << "File path: " << projectFileNameWithPath;

        if (fileName.endsWith("prj") || fileName.endsWith("pro")
                || fileName.endsWith("txt"))
        {
            m_sessionModule.openProject(projectFileNameWithPath);
        }
        else
        {
            QByteArray buffer;
            if (m_sessionModule.openFile(projectFileNameWithPath, buffer))
            {
                m_editorModule->updateOutputTextEdit(buffer);
            }
        }
    }
}

void ApplicationWindow::interpretCommand()
{
    // INTRODU TEXTUL
    // gcc -Wall /home/andrei/Code/build-Builder-Qt_in_PATH_qt5-Debug/Application/Resources/Sources/0-unused-variable.c -o unused
    QString command = m_gccComandEdit->text();
    if (command.isEmpty())
    {
        return;
    }

    // workaround because QLineEdit::editingFinished is emitted twice
//    if (m_gccComandEdit->text().toDouble() < 1000)
//    {
//        m_gccComandEdit->blockSignals(true);
//        QMessageBox::information(this, "Information", "Incorrect value");
//        m_gccComandEdit->blockSignals(false);
//    }

    // inside there is a
    // workaround because QLineEdit::editingFinished is emitted twice
    m_sessionModule.setBuildCommand(Events::ExecuteCommand, command);
//    m_sessionModule.executeCommand(command);
}

void ApplicationWindow::doCompile()
{
    QString fileName = m_gccComandEdit->text();
    if (fileName.isEmpty())
    {
        return;
    }

    // workaround because QLineEdit::editingFinished is emitted twice
//    if (m_gccComandEdit->text().toDouble() < 1000)
//    {
//        m_gccComandEdit->blockSignals(true);
//        QMessageBox::information(this, "Information", "Incorrect value");
//        m_gccComandEdit->blockSignals(false);
//    }

    // inside there is a
    // workaround because QLineEdit::editingFinished is emitted twice
    m_sessionModule.setBuildCommand(Events::ExecuteCompileFile, fileName);
//    m_sessionModule.executeCompileFile(fileName);
}

void ApplicationWindow::doLink()
{
}

void ApplicationWindow::doBuild()
{
    QString directory = m_gccComandEdit->text();
    if (directory.isEmpty())
    {
        return;
    }

    // inside there is a
    // workaround because QLineEdit::editingFinished is emitted twice
    m_sessionModule.setBuildCommand(Events::ExecuteBuildDirectory, directory);
//    m_sessionModule.executeBuildDirectory(folder);
}
