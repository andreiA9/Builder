#ifndef GCC_INTERPRETER_H
#define GCC_INTERPRETER_H

#include <QString>

class GccInterpreter
{
public:
    GccInterpreter();

    void executeCommand(const QString& command, QString& bashOutput);

    QString generateOutputCommand(const char* outputFormat, QString &fileName);

    QString generateObjCommand(const char* objFileName, QString &fileName);

    QString generateExeFromObj(const QString &exeFormat, const QString &fileName);

    bool compileSourceFile(QString &fileName, QString* objFile);

    void linkObjFiles(const QString &exeName, const QString &objFilesString);

    void generateExeFromMultipleSources(QString &exeName, QString &fileName1, QString &fileName2);
};

#endif // GCC_INTERPRETER_H
