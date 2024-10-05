#ifndef PRJ_READER_H
#define PRJ_READER_H

// local project headers
// ----------------------
#include "Constants.h"

// standard C/C++ headers
// ----------------------
#include <QString>
#include <QStringList>

class PrjReader
{
public:
    PrjTemplate getTemplate();

    void assignTemplate(const QString& value);

    // Read a generic .prj file format
    bool readPrjFile(const QString& filename);

    void processLine(QString& line, QString& operatorUsed,
                     QMap<QString, QString>& fieldToValues);

private:
    PrjTemplate m_template;
    QString m_target;
    QStringList m_sources;
    QStringList m_libraries;
    QStringList m_includePaths;
};

#endif // PRJ_READER_H
