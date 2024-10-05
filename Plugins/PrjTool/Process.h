#ifndef PROCESS_H
#define PROCESS_H

// local project headers
// ----------------------

// standard C/C++ headers
// ----------------------
#include <QObject>

class Process : public QObject
{
    Q_OBJECT

public:
    Process() {}

    virtual ~Process() {}
};

#endif // PROCESS_H

