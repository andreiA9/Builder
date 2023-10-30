#ifndef PROCESS_H
#define PROCESS_H

// local project headers
// ----------------------
#include "Environment.h"

// standard C/C++ headers
// ----------------------
#include <QString>
#include <QObject>

class Process : public QObject
{
    Q_OBJECT

public:
    enum ProcesState
    {
        Waiting,
        Running,
        Stopped
    };
    Process();

    inline bool isProcessReady() { return m_processState == ProcesState::Stopped; }

    inline const QString& getBashOutput() { return m_bashOutput; }

    void setCommand(QString buildCommand);

    void run();

    // ASTA va GENERA COMANDA executata.in Bash
    void composeBashCommand() {};

    // va fi folosita pentru BUILD OUTPUT=adica este un ARGUMENT.pentru GCC
    void setWorkingDirectory(const QString& workingDirectory) {};

private:
    void executeCommand(const QString& command);

signals:
    void compileOutputChanged();

private:
    QString m_buildCommand;
    QString m_bashOutput;
    ProcesState m_processState;
    Environment m_environment;
};

#endif // PROCESS_H
