#include "manager.h"

Manager::Manager(QObject *parent)
    : QObject{parent}
{
    connect(&producerThread,&QThread::started,&producer,&Producer::start,Qt::QueuedConnection);
    connect(&consumerThread,&QThread::started,&consumer,&Consumer::start,Qt::QueuedConnection);

    // 注意,不能waitcondition不能通过signal slot机制去wake其他线程，因为会有延迟。
    // 正确的处理方式就是如本例中，将condition 的指针传分别传递到consumer和producer中，需要时直接调用 condition.wakeAll

    producerThread.setObjectName("Producer Thread");
    consumerThread.setObjectName("Consumer Thread");
    this->thread()->setObjectName("Main Thread");

    producer.moveToThread(&producerThread);
    consumer.moveToThread(&consumerThread);
}

void Manager::start()
{
    producer.setMutex(&mutex);
    producer.setData(&data);
    producer.setCondition(&condition);

    consumer.setMutex(&mutex);
    consumer.setData(&data);
    consumer.setCondition(&condition);


    producerThread.start();
    consumerThread.start();
}
