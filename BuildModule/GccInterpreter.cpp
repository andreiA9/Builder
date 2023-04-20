#include "GccInterpreter.h"

#include <QDir>
#include <QDebug>
#include <QProcess>

static const char *COMMAND_GCC = "gcc";
static const char *WARNINGS_ON = "-Wall";
static const char *WARNING_UNUSED = "Wunused";

GccInterpreter::GccInterpreter()
{

}

void GccInterpreter::executeCommand(const QString& command, QString& bashOutput)
{
    QProcess bashProcess;

    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    // VEZI ca ASTA trebuie sa fie THREAD<
    // pentru ca BUILD-ul va DURA.mult>incat iti va BLOCA UI-ul
    bashProcess.start(command);
    // this ensures that the application will wait until the process is ended
    bashProcess.waitForFinished(-1);

    // VEZI ca iti TREBUI DOCUMENTATIE si pentru "qDebug().noquote()"
    if(bashProcess.exitCode() != 0)
    {
        qDebug().noquote() << " Error " << bashProcess.exitCode()
                           << "\n" << bashProcess.readAllStandardError();
        bashOutput = bashProcess.readAllStandardError();
    }
    else
    {
        // this clears the stderr
        QString errorMessages = bashProcess.readAllStandardError();
        qDebug().noquote() << " Ok " << bashProcess.readAllStandardOutput()
                           << "\n" << errorMessages;
        bashOutput = errorMessages;
    }

//    ::system(command.toStdString().c_str());
//    ::system("gcc -Wall -o hello.o .\\Resources\\1-hello.c &> output1.txt");
}

QString GccInterpreter::generateOutputCommand(const char* outputFormat, QString &fileName)
{
//    QString command = QString("%1 %2 %3/%4 -o %5")
//                .arg(COMMAND_GCC)
//                .arg(WARNINGS_ON)
//                .arg(QDir::currentPath())
//                .arg(fileName.toStdString().c_str())
//                .arg(outputFormat);
//    qDebug() << "Executing command: " << command;
//    return command;
    QString command = QString("%1 %2 %3 -o %4")
                .arg(COMMAND_GCC)
                .arg(WARNINGS_ON)
                .arg(fileName.toStdString().c_str())
                .arg(outputFormat);
    qDebug() << "Executing command: " << command;
    return command;
}

QString GccInterpreter::generateObjCommand(const char* objFileName, QString &fileName)
{
    QString command = QString("%1 %2 -c %3/%4 -o %5")
                                .arg(COMMAND_GCC)
                                .arg(WARNINGS_ON)
                                .arg(QDir::currentPath())
                                .arg(fileName.toStdString().c_str())
                                .arg(objFileName);
    qDebug() << "Executing command: " << command;
    return command;
}

QString GccInterpreter::generateExeFromObj(const QString &exeFormat, const QString &fileName)
{
    QString command = QString("%1 %2 -o %3")
                                .arg(COMMAND_GCC)
                                .arg(fileName)
                                .arg(exeFormat.toStdString().c_str());
    qDebug() << "Executing command: " << command;
    return command;
}

bool GccInterpreter::compileSourceFile(QString &fileName, QString* objFile)
{
    const int extensionLength = 1;

    *objFile = fileName.left(fileName.length() - extensionLength);
    objFile->append('o');
    QString newCommand = generateObjCommand(objFile->toStdString().c_str(), fileName);

    int errorCode = system(newCommand.toStdString().c_str());
    if (errorCode == ENOEXEC)
    {
        qDebug() << "The command-interpreter file cannot be executed because the format is not valid.";
        return false;
    }

    return true;
}

void GccInterpreter::linkObjFiles(const QString &exeName, const QString &objFilesString)
{
    QString newCommand = generateExeFromObj(exeName, objFilesString);
    ::system(newCommand.toStdString().c_str());
}

void GccInterpreter::generateExeFromMultipleSources(QString &exeName, QString &fileName1, QString &fileName2)
{
    QString objFile1;
    if (!compileSourceFile(fileName1, &objFile1))
    {
        qDebug() << "Failed to compile file " << fileName1;
        return;
    }

    QString objFile2;
    if (!compileSourceFile(fileName2, &objFile2))
    {
        qDebug() << "Failed to compile file " << fileName2;
        return;
    }

    linkObjFiles(exeName, objFile1 + " " + objFile2);
}
