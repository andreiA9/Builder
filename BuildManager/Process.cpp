// local project headers
// ----------------------
#include "Process.h"

// standard C/C++ headers
// ----------------------
#include <unistd.h>
#include <QProcess>
#include <QDebug>

Process::Process()
{
    m_buildCommand = "";
    m_processState = ProcesState::Waiting;
}

void Process::setCommand(QString buildCommand)
{
    m_buildCommand = buildCommand;
    m_processState = ProcesState::Running;
}

void Process::run()
{
    while (m_processState == ProcesState::Running)
    {
        if (!m_buildCommand.isEmpty())
        {
            executeCommand(m_buildCommand);
            // this is to prevent executing again the same command
            emit compileOutputChanged();
            m_buildCommand = "";
            m_processState = ProcesState::Stopped;
        }
        usleep(300);
    }
}

void Process::executeCommand(const QString& command)
{
    QProcess bashProcess;

    bashProcess.start(command);
    // this ensures that the application will wait until the process is ended
    bashProcess.waitForFinished(-1);

    // TODO: ca iti TREBUI DOCUMENTATIE si pentru "qDebug().noquote()"

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

