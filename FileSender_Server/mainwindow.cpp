#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "filerecv.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    server = new QTcpServer(this);
    connect(server,&QTcpServer::newConnection,this,&MainWindow::newConn);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_startListenBtn_clicked()
{
    unsigned short port = ui->port->text().toUShort();
    server->listen(QHostAddress::Any,port);
}

void MainWindow::newConn()
{
    client = server->nextPendingConnection();
    qDebug() << "New Connection established.";
    fileRecv* recv = new fileRecv(client);
    recv->start();

    connect(recv,&fileRecv::over,this,[=](){
       recv->exit();
       recv->wait();
       recv->deleteLater();
    });
}

