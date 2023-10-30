// local project headers
// ----------------------
#include "ProjectImporter.h"

// standard C/C++ headers
// ----------------------
#include <QFile>
#include <QDebug>

Project* ProjectImporter::parsePrjFile(Project* project)
{
    QString projectFileName = project->getProjectFileName();

    QFile file(projectFileName);
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << QStringLiteral("Could not open %1 for reading, error: %2").arg(projectFileName, file.errorString());
    }

    QTextStream stream(&file);
    while (!stream.atEnd())
    {
        QString line = stream.readLine();
        QStringList fields = line.split(",");
    }

    file.close();
}
