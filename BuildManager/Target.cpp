// local project headers
// ----------------------
#include "Target.h"

// standard C/C++ headers
// ----------------------
#include <QDir>
#include <QDebug>

static const char *COMMAND_GCC = "gcc";
static const char *WARNINGS_ON = "-Wall";

static bool getFileNameWithoutExtension(const QString& fileName, QString& fileNameWithoutExtension)
{
    const char* dotSeparator = ".";
    int pos = fileName.lastIndexOf(dotSeparator);
    if (pos == -1)
    {
        return false;
    }
    fileNameWithoutExtension = fileName.left(pos);

    return true;
}

Target::Target()
{
    m_process = new Process;
    m_process->moveToThread(&m_workerThread);
    QObject::connect(&m_workerThread, &QThread::started, m_process, &Process::run);
    QObject::connect(&m_workerThread, &QThread::finished, m_process, &QObject::deleteLater);
    m_workerThread.start();

    QObject::connect(m_process, &Process::compileOutputChanged, this,
                     &Target::updateOutputTextEdit);
}

static bool getFilesFromDirectory(const QString& directoryName, QList<QFileInfo>& fileList)
{
    QFileInfo fileInfo(directoryName);
    if (!fileInfo.isDir())
    {
        return false;
    }

    QDir directory(directoryName);
    fileList= directory.entryInfoList();
    for (int i=0; i< fileList.size(); i++)
    {
        if (fileList.at(i).isFile())
        {
            qDebug() << "File: " << fileList.at(i).absoluteFilePath();
        }
    }

    return true;
}

void Target::executeBuildDirectory(const QString& directoryName)
{
    QList<QFileInfo> fileList;
    if (!getFilesFromDirectory (directoryName, fileList))
    {
        return;
    }

    /*
    COMPILEZI.cu
    gcc -Wall main.cpp print.cpp -o multipleFiles
    */
    QString filesString;
    for (QFileInfo file : fileList)
    {
        // skip header files
        if (file.fileName().endsWith(".h"))
        {
            continue;
        }

        fileList += ' ' + file.absoluteFilePath();
    }

    QString command = QString("%1 %2 %3 -o %4")
                .arg(COMMAND_GCC)
                .arg(WARNINGS_ON)
                .arg(filesString.toStdString().c_str())
                .arg("main");
    qDebug() << "Executing command: " << command;
    m_process->setCommand(command);
}

bool Target::executeCompileFile(const QString& fileName)
{
    QString fileNameWithoutExtension;
    if (!getFileNameWithoutExtension(fileName, fileNameWithoutExtension))
    {
        return false;
    }

    QString command = QString("%1 %2 %3 -o %4")
                .arg(COMMAND_GCC)
                .arg(WARNINGS_ON)
                .arg(fileName.toStdString().c_str())
                .arg(fileNameWithoutExtension);
    qDebug() << "Executing command: " << command;
    m_process->setCommand(command);

    return true;
}

void Target::executeCommand(const QString& command)
{
    m_process->setCommand(command);
}

void Target::updateOutputTextEdit()
{
    emit compileOutputChanged();
}

// ASTA a fost MUTATA.in executeCompileFile()
QString Target::generateOutputCommand(const char* /*outputFormat*/, QString& /*fileName*/)
{

}

QString Target::generateObjCommand(const char* objFileName, QString& fileName)
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

QString Target::generateExeFromObj(const QString& exeFormat, const QString& fileName)
{
    QString command = QString("%1 %2 -o %3")
                                .arg(COMMAND_GCC)
                                .arg(fileName)
                                .arg(exeFormat.toStdString().c_str());
    qDebug() << "Executing command: " << command;
    return command;
}

bool Target::compileSourceFile(QString& fileName, QString* objFile)
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

void Target::linkObjFiles(const QString& exeName, const QString& objFilesString)
{
    QString newCommand = generateExeFromObj(exeName, objFilesString);
    ::system(newCommand.toStdString().c_str());
}

void Target::generateExeFromMultipleSources(QString& exeName, QString& fileName1, QString& fileName2)
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
