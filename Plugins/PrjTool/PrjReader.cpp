// local project headers
// ----------------------
#include "PrjReader.h"

// standard C/C++ headers
// ----------------------
#include <QFileInfo>
#include <QDebug>

PrjTemplate PrjReader::getTemplate()
{
    return m_template;
}

void PrjReader::assignTemplate(const QString& value)
{
    if (value == "app")
    {
        m_template = PrjTemplate::App;
    }
    else if (value == "lib")
    {
        m_template = PrjTemplate::Lib;
    }
    else if (value == "subdirs")
    {
        m_template = PrjTemplate::Subdirs;
    }
}

/*
ASTA este EXEMPLUL.de FISIER
TEMPLATE = app

# Specify the target name
TARGET = main

# Specify the source file
SOURCES += main.cpp

# Link the necessary library
LIBS += -L../plugins/firstLib/ -lfirstLib

INCLUDEPATH += ../plugins/firstLib/
INCLUDEPATH += ../plugins/secondLib/
*/
bool PrjReader::readPrjFile(const QString& filename)
{
    qDebug() << "filename: " << filename;

    // Open the file
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Cannot open file for reading:" << file.errorString();
        return false;
    }

    QTextStream in(&file);
    QMap<QString, QString> fieldToValues;

    while (!in.atEnd())
    {
        QString line = in.readLine();

        // Ignore comments
        if (line.startsWith('#') || line.contains('#'))
        {
            continue;
        }

        // Check if line contains '=' or '+='
        QString operatorUsed = "=";
        if (line.contains("+="))
        {
            operatorUsed = "+=";
        }

        processLine(line, operatorUsed, fieldToValues);
    }

    file.close();

    // Print the results
    qDebug() << "Fields and Values:";
    for (auto it = fieldToValues.begin(); it != fieldToValues.end(); ++it)
    {
        qDebug() << it.key() << "=" << it.value();
    }

    return true;
}

void PrjReader::processLine(QString& line, QString& operatorUsed,
                            QMap<QString, QString>& fieldToValues)
{
    QStringList parts = line.split(operatorUsed, QString::SkipEmptyParts);
    if (parts.size() == 2)
    {
        // Clean whitespaces
        QString field = parts[0].trimmed();
        QString value = parts[1].trimmed();

        if (field == "TEMPLATE")
        {
            assignTemplate(value);
        }
        else if (field == "TARGET")
        {
            m_target = value;
        }
        else if (field == "SOURCES")
        {
            m_sources << value;
        }
        else if (field == "LIBS")
        {
            m_libraries << value;
        }
        else if (field == "INCLUDEPATH")
        {
            m_includePaths << value;
        }

        // Detect and handle the '+=' operator
        if (operatorUsed == "+=" && fieldToValues.contains(field))
        {
            fieldToValues[field] += " " + value; // Append the value
        }
        else
        {
            fieldToValues[field] = value; // Add or update the entry in the map
        }
    }
}
