#include "Instance.h"

#include <QFile>
#include <QTextStream>
#include <QDebug>

static QString changeExtensionToObj(const QString &filename)
{
    if (filename.endsWith(".cpp", Qt::CaseInsensitive))
    {
        return filename.left(filename.length() - 4) + ".o";
    }
    else
    {
        return filename; // Return the original if it doesn't end with .cpp
    }
}

static void generateMakefile(const QString& outputFile, const QStringList& sourceFiles)
{
    QFile makefile("Makefile");
    if (!makefile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << "Failed to create Makefile.";
        return;
    }

    QTextStream makefileContent;
    makefileContent.setDevice(&makefile);

    makefileContent << "CC = g++" << endl;
    makefileContent << endl;

    makefileContent << "TARGET = " << outputFile << endl;
    makefileContent << endl;

    // Create the list of .obj files, by replacing the
    // extensions of the sources from sourceFiles
    // OBJECTS = main.o PrintMessage.o
    makefileContent << "OBJECTS = ";
    for (const QString& source : sourceFiles)
    {
        makefileContent << changeExtensionToObj(source) << " ";
    }
    makefileContent << endl << endl;

    makefileContent << "$(TARGET): $(OBJECTS)" << endl;
    // Do not delete the tabs
    makefileContent << "\t$(CC) -o $(TARGET) $(OBJECTS)" << endl;
    makefileContent << endl;

    makefileContent << "%.o : %.cpp" << endl;
    makefileContent << "\t$(CC) -o $@ -c $<" << endl;
    makefileContent << endl;

    makefileContent << "clean:" << endl;
    makefileContent << "\trm -rf $(OBJECTS) $(TARGET)" << endl;

    makefileContent.flush();  // Flushes any buffered data to the file
    makefile.close();
    qDebug() << "Makefile generated successfully!";
}

Instance::Instance(EventListener* eventListener)
    : m_eventListener(eventListener)
{
}

Instance::~Instance()
{
}

void Instance::execute(int selection)
{
    PrjParser::PrjFileType event = static_cast<PrjParser::PrjFileType>(selection);

    QString workingDir;
    if (!m_prjPerformer.findResourceDirectory(event, workingDir))
    {
        qDebug() << "Could not find resource directory!";
        return;
    }
    PrjTemplate prjTemplate;
    if (!m_prjPerformer.parseProjectFile(event, workingDir, prjTemplate))
    {
        qDebug() << "Could not perform requested operation!";
    }

    if (!m_prjPerformer.handle(prjTemplate, workingDir))
    {
        qDebug() << "Could not handle requested operation!";
    }
}
