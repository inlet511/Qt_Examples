#include "producer.h"

Producer::Producer(QObject *parent)
    : QObject{parent}
{

}

void Producer::setData(QList<int> *data)
{
    this->data = data;
}

void Producer::setMutex(QMutex *mutex)
{
    this->mutex = mutex;
}

void Producer::setCondition(QWaitCondition *condition)
{
    this->condition = condition;
}

void Producer::start()
{
    while(true)
    {
        int value = QRandomGenerator::global()->bounded(1000);
        mutex->lock();
        data->append(value);
        mutex->unlock();
        qInfo() << " Produced item on: " << this->thread();
        if(data->length()>=10)
        {
            condition->wakeAll();
        }

    }
}
