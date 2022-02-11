#include "filerecv.h"
#include <QFile>

fileRecv::fileRecv(QTcpSocket* client, QObject *parent) : QThread(parent)
{
    this->client = client;
}

void fileRecv::run()
{
    QFile* file = new QFile("recv.txt");
    file->open(QFile::WriteOnly);

    // 接收数据
    connect(client,&QTcpSocket::readyRead,this,[=](){
        static int count = 0;
        static int total = 0;
        if(count ==0)
        {
            client->read((char*)&total,4);
        }
        QByteArray byte = client->readAll();
        count += byte.size();

        file->write(byte);

        if(count == total)
        {
            client->close();
            client->deleteLater();
            file->close();
            file->deleteLater();

            emit over();
        }

    });

    exec();
}
