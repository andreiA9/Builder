#ifndef BUILD_PROCESS_H
#define BUILD_PROCESS_H

// local project headers
// ----------------------

// standard C/C++ headers
// ----------------------
#include <QString>
#include <QVector>
#include <QObject>

class BuildStep : public QObject
{
    Q_OBJECT

public:
    enum ProcesState
    {
        Waiting,
        Running,
        Stopped
    };

    BuildStep();

    inline bool isProcessReady() { return m_processState == ProcesState::Stopped; }

    inline const QString& getBashOutput() { return m_bashOutput; }

    // Sets the command to be executed in bash, then takes the process into Running state
    void setCommand(const QString& workingDirectory, const QString& buildCommand);

    // Sets the command queue to be executed in bash, then takes the process into Running state
    void setCommandQueue(const QString& workingDirectory,
                         const QVector<QString>& commandQueue);

    // This process should execute a command as long as it is in
    // the Running state; otherwise the process is idle
//    void run();

    // ASTA va GENERA COMANDA executata.in Bash
    void composeBashCommand() {};

private:
    // Executes the current command that was set
    void executeCommand();

//signals:
//    void compileOutputChanged();

public slots:
    void run();

private:
    QString m_buildCommand;
    QVector<QString> m_commandQueue;
    QString m_workingDirectory;
    QString m_bashOutput;
    ProcesState m_processState;
};

#endif // BUILD_PROCESS_H
