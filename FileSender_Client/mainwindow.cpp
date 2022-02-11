#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->ip->setText("127.0.0.1");
    ui->port->setText("8899");
    ui->progressBar->setRange(0,100);
    ui->progressBar->setValue(0);

    QThread* thread = new QThread();
    SendFile* sendFile=new SendFile();
    sendFile->moveToThread(thread);

    connect(this,&MainWindow::startConnect, sendFile, &SendFile::connectServer);
    connect(sendFile,&SendFile::connectOK,this,[=](){
       QMessageBox::information(this,"连接服务器","已经成功连接服务器");
    });

    connect(sendFile,&SendFile::disconnected,this,[=](){
        // 资源释放
        thread->quit();
        thread->wait();
        sendFile->deleteLater();
        thread->deleteLater();
    });
    connect(this,&MainWindow::sendFile,sendFile,&SendFile::sendFile,Qt::QueuedConnection    );
    connect(sendFile,&SendFile::percentUpdate,ui->progressBar,&QProgressBar::setValue,Qt::QueuedConnection);

    thread->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_connectButton_clicked()
{
    QString ip = ui->ip->text();
    unsigned short port = ui->port->text().toUShort();
    qDebug()<<QString("IP:%1, Port:%2").arg(ip).arg(ui->port->text());
    emit startConnect(port, ip);
}



void MainWindow::on_pushButton_2_clicked()
{
    QString path = QFileDialog::getOpenFileName();
    if(path.isEmpty())
    {
        return;
    }
    ui->file->setText(path);
}


void MainWindow::on_pushButton_3_clicked()
{
    if(ui->file->text().isEmpty())
        return;
    emit sendFile(ui->file->text());
}



