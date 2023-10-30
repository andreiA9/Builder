#ifndef TARGET_H
#define TARGET_H

#include "Process.h"

#include <QString>
#include <QThread>

class Target : public QObject
{
    Q_OBJECT

public:
    Target();

    inline bool isProcessReady() { return m_process->isProcessReady(); }

    inline const QString& getBashOutput() { return m_process->getBashOutput(); }

    void executeBuildDirectory(const QString& directoryName);

    bool executeCompileFile(const QString& fileName);

    void executeCommand(const QString& command);


    // for the new classes for: qmake, cmake, prjmake
    virtual void build() {};

    virtual void clean() {};


    // !!!!
    // FROM HERE UNSORTED
    QString generateOutputCommand(const char* outputFormat, QString &fileName);

    QString generateObjCommand(const char* objFileName, QString &fileName);

    QString generateExeFromObj(const QString &exeFormat, const QString &fileName);

    bool compileSourceFile(QString &fileName, QString* objFile);

    void linkObjFiles(const QString &exeName, const QString &objFilesString);

    void generateExeFromMultipleSources(QString &exeName, QString &fileName1, QString &fileName2);

signals:
    void compileOutputChanged();

private slots:
    void updateOutputTextEdit();

private:
    Process* m_process;
    QThread m_workerThread;
    QString m_command;
};

#endif // TARGET_H
