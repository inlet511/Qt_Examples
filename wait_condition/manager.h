#ifndef MANAGER_H
#define MANAGER_H

#include <QObject>
#include <QMutex>
#include <QRandomGenerator>
#include <QThread>
#include <QDebug>
#include <QWaitCondition>
#include "producer.h"
#include "consumer.h"

class Manager : public QObject
{
    Q_OBJECT
public:
    explicit Manager(QObject *parent = nullptr);

public slots:
    void start();

private:
    QList<int> data;
    QMutex mutex;
    QThread producerThread;
    QThread consumerThread;
    QWaitCondition condition;
    Producer producer;
    Consumer consumer;

};

#endif // MANAGER_H
