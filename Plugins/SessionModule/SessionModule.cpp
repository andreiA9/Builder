// local project headers
// ----------------------
#include "SessionModule.h"

// standard C/C++ headers
// ----------------------
#include <unistd.h>
#include <QDebug>

SessionModule::SessionModule(EventListener* eventListener)
    : m_eventListener(eventListener)
{
    m_projectInfo = new ProjectInfo;
    m_buildManager = new BuildManager(eventListener, m_projectInfo);
    m_projectManager = new ProjectManager(eventListener);
}

SessionModule::~SessionModule()
{
    delete m_buildManager;
    delete m_projectManager;
    delete m_projectInfo;
}

void SessionModule::setBuildCommand(const QString& buildCommand)
{
    qDebug() << "Build command:" << buildCommand;
    m_buildCommand = buildCommand;
}

void SessionModule::setUnitName(const QString& unitName)
{
    qDebug() << "Unit name:" << unitName;
    m_unitName = unitName;
}

void SessionModule::run()
{
    while (true)
    {
        checkForRequestsFromUi();

        checkForResponsesToUi();

        usleep(100);
    }
}

void SessionModule::checkForRequestsFromUi()
{
    // AICI iti TREBUIE ceva in EVENT LISTENER-CA CATEGORY
    // -> CATEGORY:BUILD
    // -> CATEGORY:PROJECT
    if (!m_eventListener->hasEvents())
    {
        return;
    }

    switch (m_uiRequest)
    {
        case UiRequest::BuildUiRequest:
        {
            m_buildManager->process(m_buildCommand, m_unitName);
            break;
        }
        case UiRequest::ProjectRequest:
        {
            m_projectManager->process();
            break;
        }
        default:
        {
            break;
        }
    }
}

void SessionModule::checkForResponsesToUi()
{
//    if (m_buildManager->isProcessReady())
//    {
//        qDebug() << "DA";
//        emit compileOutputReady(m_buildManager->getBashOutput());
//    }
    // this will emit the SIGNAL>to UPDATE the text edit in the EditorModule
}
