#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QFileDialog>
#include <QBuffer>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget),
      sharedMemory("SharedMemoryDemoApp")
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_loadImage_clicked()
{
    if(sharedMemory.isAttached())
    {
        qDebug() << "Memory is attached, detaching";
        detach();
    }

    ui->image->setText(tr("Select and image file"));
    QString fileName = QFileDialog::getOpenFileName(nullptr,QString(),QString(),tr("Images (*.png *.xpm *.jpg)"));

    QImage image;
    if(!image.load(fileName))
    {
        ui->image->setText("Seleted file is not an image");
        return;
    }

    ui->image->setPixmap(QPixmap::fromImage(image));

    QBuffer buffer;
    buffer.open(QBuffer::ReadWrite);
    QDataStream out(&buffer);
    out<<image;
    int size = buffer.size();

    if(!sharedMemory.create(size))
    {
        ui->image->setText("Unable to create shared memory segment");
        return;
    }

    sharedMemory.lock();

    char * to = (char*)sharedMemory.data();
    const char* from = buffer.data().data();

    memcpy(to,from,qMin(sharedMemory.size(),size));


    sharedMemory.unlock();
}


void Widget::on_loadsharedMem_clicked()
{
    if(!sharedMemory.attach())
    {
        ui->image->setText("Unable to attach");
    }

    QBuffer buffer;
    QDataStream in(&buffer);
    QImage image;

    sharedMemory.lock();

    buffer.setData((char*)sharedMemory.constData(),sharedMemory.size());
    buffer.open(QBuffer::ReadOnly);
    in>>image;

    sharedMemory.unlock();

    sharedMemory.detach();

    ui->image->setPixmap(QPixmap::fromImage(image));

}

void Widget::detach()
{
    if(!sharedMemory.detach())
    {
        ui->image->setText("Cannot detach from the shared memory");
    }
}

