#include "consumer.h"

Consumer::Consumer(QObject *parent)
    : QObject{parent}
{

}

void Consumer::setData(QList<int> *data)
{
    this->data = data;
}

void Consumer::setMutex(QMutex *mutex)
{
    this->mutex = mutex;
}

void Consumer::setCondition(QWaitCondition *condition)
{
    this->condition = condition;
}

void Consumer::start()
{
    qInfo() << "Start consuming on:" << this->thread();
    while(true)
    {
        qInfo() << " Consuming on: " << this->thread();
        QMutexLocker locker(mutex);
        data->clear();

        condition->wait(mutex);

    }
}
