// local project headers
// ----------------------
#include "BuildStep.h"

// standard C/C++ headers
// ----------------------
#include <unistd.h>
#include <QProcess>
#include <QDebug>
#include <QDir>

BuildStep::BuildStep()
{
    m_buildCommand = "";
    m_processState = ProcesState::Waiting;
}

void BuildStep::setCommand(const QString& workingDirectory, const QString& buildCommand)
{
    m_workingDirectory = workingDirectory;
    m_buildCommand = buildCommand;
    m_processState = ProcesState::Running;
}

void BuildStep::setCommandQueue(const QString& workingDirectory,
                                const QVector<QString>& commandQueue)
{
    m_workingDirectory = workingDirectory;
    m_commandQueue = commandQueue;
    m_processState = ProcesState::Running;
}

void BuildStep::run()
{
    qDebug() << "BuildStep::run()";
    fflush(stdout);
    while (m_processState != ProcesState::Stopped)
    {
        if (m_processState == ProcesState::Running)
        {
            foreach (const auto& command, m_commandQueue)
            {
                executeCommand(command);
            }
            m_processState = ProcesState::Waiting;
        }
        /*
        if (!m_buildCommand.isEmpty())
        {
            executeCommand();
            // this is to prevent executing again the same command
//            emit compileOutputChanged();
            m_buildCommand = "";
            m_processState = ProcesState::Stopped;
        }
        */
        usleep(300);
    }
}

void BuildStep::executeCommand(const QString& command)
{
    QProcess bashProcess;

    qDebug() << "Process working directory: " << m_workingDirectory;
    qDebug() << "Process command: " << command;
    fflush(stdout);

    bashProcess.setWorkingDirectory(m_workingDirectory);
    bashProcess.start(command);
    // this ensures that the application will wait until the process is ended
    bashProcess.waitForFinished(-1);

    // TODO: iti TREBUI DOCUMENTATIE si pentru "qDebug().noquote()"

    // ASTA e pe ERROR
    if(bashProcess.exitCode() != 0)
    {
        QString errorMessages = bashProcess.readAllStandardError();
        qDebug().noquote() << " Error " << bashProcess.exitCode()
                           << "\n" << errorMessages;
        m_bashOutput = errorMessages;
    }
    // ASTA e pe WARNING
    else
    {
        // this clears the stderr
        QString errorMessages = bashProcess.readAllStandardError();
        qDebug().noquote() << " Ok " << bashProcess.readAllStandardOutput()
                           << "\n" << errorMessages;
        m_bashOutput = errorMessages;
    }
}
