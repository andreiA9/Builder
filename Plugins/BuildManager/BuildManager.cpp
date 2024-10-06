// local project headers
// ----------------------
#include "BuildManager.h"

// standard C/C++ headers
// ----------------------
#include <QDebug>

BuildManager::BuildManager(EventListener* eventListener, ProjectInfo* projectInfo)
    : m_eventListener(eventListener)
{
    m_target = new Target(projectInfo);
    m_buildStep = new BuildStep;

    m_buildStep->moveToThread(&m_workerThread);
    QObject::connect(&m_workerThread, &QThread::started, m_buildStep, &BuildStep::run);
    QObject::connect(&m_workerThread, &QThread::finished, m_buildStep, &QObject::deleteLater);
    m_workerThread.start();

//    QObject::connect(m_buildStep, &BuildStep::compileOutputChanged, this,
//                     &GccController::updateOutputTextEdit);
}

BuildManager::~BuildManager()
{
    delete m_target;
    delete m_buildStep;
    delete m_eventListener;

    m_workerThread.quit();
    m_workerThread.wait();
}

void BuildManager::process(const QString& /*unitName*/)
{
    BuildRequest event = m_eventListener->getRequestEvent();
    QString resourceDir;
    QVector<QString> commandQueue;
    m_target->handleOperation(event, resourceDir, commandQueue);

    m_eventListener->clearCurrentEvent();
    m_buildStep->setCommandQueue(resourceDir, commandQueue);
}
