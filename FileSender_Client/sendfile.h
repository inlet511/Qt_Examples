#ifndef SENDFILE_H
#define SENDFILE_H

#include <QObject>
#include <QTcpSocket>

class SendFile : public QObject
{
    Q_OBJECT
public:
    explicit SendFile(QObject *parent = nullptr);

    void connectServer(unsigned short port, QString ip);




signals:
    void connectOK();
    void disconnected();
    void percentUpdate(int);

public slots:
    void sendFile(QString path);
private:
    QTcpSocket* client;

};

#endif // SENDFILE_H
