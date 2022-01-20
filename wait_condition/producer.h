#ifndef PRODUCER_H
#define PRODUCER_H

#include <QObject>
#include <QMutex>
#include <QRandomGenerator>
#include <QWaitCondition>
#include <QThread>
#include <QDebug>

class Producer : public QObject
{
    Q_OBJECT
public:
    explicit Producer(QObject *parent = nullptr);

    void setData(QList<int>* data);
    void setMutex(QMutex* mutex);
    void setCondition(QWaitCondition* condition);

signals:
    void ready();

public slots:
    void start();

private:
    QList<int>* data;
    QMutex* mutex;
    QWaitCondition* condition;
};

#endif
