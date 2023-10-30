#ifndef TEST_H
#define TEST_H

#include <QThread>
#include <QNetworkAccessManager>
#include <QDebug>
#include <unistd.h>

class Worker : public QObject
{
    Q_OBJECT

public:

    Worker()
    {
        QNetworkAccessManager* manager = new QNetworkAccessManager(this);
    }
//    void run() override
//    {
//        int counter = 0;
//        while(1)
//        {
//            qDebug() << "Thread id: " << QThread::currentThreadId();
//            qDebug() << "counter from thread: " << counter;
//            counter++;
//            sleep(1);
//        }
//    }
};

#endif // TEST_H
