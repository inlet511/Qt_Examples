#include "sendfile.h"
#include <QHostAddress>
#include <QFile>
#include <QFileInfo>
#include <QDebug>

SendFile::SendFile(QObject *parent) : QObject(parent)
{

}

void SendFile::connectServer(unsigned short port, QString ip)
{
    client = new QTcpSocket();
    client->connectToHost(QHostAddress(ip),port);
    qDebug() << "connecting to host";
    connect(client,&QTcpSocket::connected,this,&SendFile::connectOK);
    connect(client,&QTcpSocket::disconnected, this, [=](){
       client->close();
       client->deleteLater();
       emit disconnected();
    });
}

void SendFile::sendFile(QString path)
{
    QFile file(path);
    QFileInfo info(path);
    int fileSize = info.size();

    file.open(QFile::ReadOnly);

    while(!file.atEnd())
    {
        static int num = 0;
        if(num==0)
        {
            client->write((char*)&fileSize,4);
        }
        QByteArray line = file.readLine();

        num += line.size();
        int percent = (num*100/fileSize);
        emit percentUpdate(percent);
        client->write(line);
    }
}
