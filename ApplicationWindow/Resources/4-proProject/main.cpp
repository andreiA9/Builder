#include <QCoreApplication>

#include "Test.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Worker worker;

    int counter = 0;
    while(1)
    {
        qDebug() << "Thread id: " << QThread::currentThreadId();
        qDebug() << "counter: " << counter;
        counter++;
        sleep(1);
    }

    return a.exec();
}
