#ifndef PROJECT_H
#define PROJECT_H

// local project headers
// ----------------------
#include "PrjPerformer.h"
#include "EventListener.h"

// standard C/C++ headers
// ----------------------
#include <QString>
#include <QStringList>
#include <QThread>
#include <QObject>

class Instance : public QObject
{
    Q_OBJECT

public:
    Instance(EventListener* eventListener);

    ~Instance();

    void execute(int selection);

private:
    PrjPerformer m_prjPerformer;
    QThread m_workerThread;
    EventListener* m_eventListener;
};

#endif // PROJECT_H
