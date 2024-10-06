// local project headers
// ----------------------
#include "ApplicationWindow.h"

// standard C/C++ headers
// ----------------------
#include <QDebug>

ApplicationWindow::ApplicationWindow()
{
    createMenuBar();
    initializeMenuConnects();

    initializeComandEdit();

    initializeControlButtons();

    m_eventListener = new EventListener;
    m_sessionModule = new SessionModule(m_eventListener);
    m_sessionModule->moveToThread(&m_workerThread);
    QObject::connect(&m_workerThread, &QThread::started, m_sessionModule, &SessionModule::run);
    QObject::connect(&m_workerThread, &QThread::finished, m_sessionModule, &QObject::deleteLater);
    m_workerThread.start();

    m_editView = new EditView(m_sessionModule);
    m_compileView = new CompileView(m_sessionModule);
    initializeWorkArea();

    initializeConnects();
}

ApplicationWindow::~ApplicationWindow()
{
    m_workerThread.quit();
    m_workerThread.wait();

    delete m_eventListener;
}

void ApplicationWindow::initializeMenuConnects()
{
    connect(m_compileAction, &QAction::triggered, this, &ApplicationWindow::doCompile);
    connect(m_buildDirectoryAction, &QAction::triggered, this, &ApplicationWindow::doBuild);
    connect(m_generateLibraryAction, &QAction::triggered, this, &ApplicationWindow::doGenerateLib);

    connect(m_exitAction, &QAction::triggered, this, &QWidget::close);

//    connect(m_aboutAction, &QAction::triggered, this, &ApplicationWindow::showAbout);
}

void ApplicationWindow::initializeConnects()
{
    m_projectTab = CompileTab;
    QObject::connect(m_editProjectTab, &ClickableLabel::clicked, [&]()
    {
        qDebug() << "Edit label clicked!";
        m_stackedWorkArea->setCurrentWidget(m_editView);

        m_projectTab = EditTab;
        m_functionButton0->setText("New");
        m_functionButton1->setText("Open");
        m_functionButton2->setText("Save");
        m_functionButton3->setText("Undefined1");
        m_functionButton4->setText("Undefined2");
    });

    QObject::connect(m_compileProjectTab, &ClickableLabel::clicked, [&]()
    {
        qDebug() << "Compile label clicked!";
        m_stackedWorkArea->setCurrentWidget(m_compileView);

        m_projectTab = CompileTab;
        m_functionButton0->setText("Compile");
        m_functionButton1->setText("Recompile");
        m_functionButton2->setText("Build directory");
        m_functionButton3->setText("Generate library");
        m_functionButton4->setText("Undefined");
    });

    QObject::connect(m_gccComandEdit, &QLineEdit::editingFinished, this, &ApplicationWindow::interpretCommand);

    QObject::connect(m_functionButton0, &QPushButton::clicked, this, &ApplicationWindow::onFunctionButton0Clicked);
    QObject::connect(m_functionButton1, &QPushButton::clicked, this, &ApplicationWindow::onFunctionButton1Clicked);
    QObject::connect(m_functionButton2, &QPushButton::clicked, this, &ApplicationWindow::onFunctionButton2Clicked);
    QObject::connect(m_functionButton3, &QPushButton::clicked, this, &ApplicationWindow::onFunctionButton3Clicked);

    QObject::connect(m_compileView, &CompileView::selectionChanged, this, &ApplicationWindow::handleSelectionChanged);
}

void ApplicationWindow::onFunctionButton0Clicked() // ExecuteCompileFile
{
    if (m_projectTab == EditTab)
    {

    }
    else if (m_projectTab == CompileTab)
    {
        // Implement the Compile action
        m_eventListener->notifyEvent(BuildRequest::ExecuteCompileFile);
        doCompile();
    }
}

void ApplicationWindow::onFunctionButton1Clicked() // ExecuteRecompileFile
{
    if (m_projectTab == EditTab)
    {

    }
    else if (m_projectTab == CompileTab)
    {
        // Implement the Recompile action
        m_eventListener->notifyEvent(BuildRequest::ExecuteRecompileFile);
    }
}

void ApplicationWindow::onFunctionButton2Clicked() // ExecuteBuildDirectory
{
    if (m_projectTab == EditTab)
    {

    }
    else if (m_projectTab == CompileTab)
    {
        // Implement the Build action
        m_eventListener->notifyEvent(BuildRequest::ExecuteBuildDirectory);
        doBuild();
    }
}

void ApplicationWindow::onFunctionButton3Clicked() // ExecuteGenerateLib
{
    if (m_projectTab == EditTab)
    {

    }
    else if (m_projectTab == CompileTab)
    {
        // Implement the Generate lib action
        m_eventListener->notifyEvent(BuildRequest::ExecuteGenerateLib);
        doGenerateLib();
    }
}

void ApplicationWindow::handleSelectionChanged(QString selectionName)
{
    m_gccComandEdit->setText(selectionName);
    m_sessionModule->setUnitName(selectionName);
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
    m_sessionModule->setBuildCommand(command);
}

void ApplicationWindow::doCompile()
{
    QString fileName = m_gccComandEdit->text();
    if (fileName.isEmpty())
    {
//        return;
    }

    // inside there is a
    // workaround because QLineEdit::editingFinished is emitted twice
    m_sessionModule->setUnitName(fileName);
}

void ApplicationWindow::doBuild()
{
    QString directoryName = m_gccComandEdit->text();
    if (directoryName.isEmpty())
    {
//        return;
    }

    // inside there is a
    // workaround because QLineEdit::editingFinished is emitted twice
    m_sessionModule->setUnitName(directoryName);
}

void ApplicationWindow::doGenerateLib()
{
    QString directoryName = m_gccComandEdit->text();
    if (directoryName.isEmpty())
    {
//        return;
    }

    // inside there is a
    // workaround because QLineEdit::editingFinished is emitted twice
    m_sessionModule->setUnitName(directoryName);
}
