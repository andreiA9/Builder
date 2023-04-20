#include "ApplicationWindow.h"

#include <QDebug>
#include <QFileSystemModel>
#include <QMessageBox>

ApplicationWindow::ApplicationWindow()
{
    initializeComandEdit();
    initializeControlButtons();
    initializeBottomGrid();

    QStackedWidget* stackedWorkArea = new QStackedWidget(this);
    m_buildModule = new BuildModule(stackedWorkArea);
    initializeOutputBoardAndTreeView(stackedWorkArea);

    initializeConnects();
}

void ApplicationWindow::initializeConnects()
{
    connect(m_gccComandEdit, &QLineEdit::editingFinished, this, &ApplicationWindow::interpretCommand);

    connect(m_filesTreeView->selectionModel(), &QItemSelectionModel::selectionChanged,
                    this, &ApplicationWindow::getTreeViewSelection);
}

void ApplicationWindow::getTreeViewSelection()
{
    qDebug() << "DA";
    QModelIndexList indexes = m_filesTreeView->selectionModel()->selectedIndexes();
    QFileSystemModel* fileModel = static_cast<QFileSystemModel*>(m_filesTreeView->model());

    if (indexes.size() > 0)
    {
        QModelIndex selectedIndex = indexes.at(0);
        QString fileName = selectedIndex.data().toString();
        QString filePathWithName = fileModel->filePath(selectedIndex);
        // ASTA il PASTREZI pentru NUMELE TAB-ului
        qDebug() << "File name: " << fileName;
        // ASTA iti este FISIERUL
        qDebug() << "File path: " << filePathWithName;
        m_buildModule->setWorkingFile(filePathWithName);
        m_gccComandEdit->setText(filePathWithName);
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

    QString bashOutput;
    // inside there is a
    // workaround because QLineEdit::editingFinished is emitted twice
    m_buildModule->executeCommand(command, bashOutput);
    m_outputTextEdit->setText(bashOutput);
}
