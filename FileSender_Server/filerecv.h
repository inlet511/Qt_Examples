#ifndef FILERECV_H
#define FILERECV_H

#include <QThread>
#include <QTcpSocket>

class fileRecv : public QThread
{
    Q_OBJECT
public:
    explicit fileRecv(QTcpSocket* client, QObject *parent = nullptr);

signals:

    void over();
    // QThread interface
protected:
    void run() override;
private:
    QTcpSocket* client;
};

#endif // FILERECV_H
