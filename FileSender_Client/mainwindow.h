#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include "sendfile.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void startConnect(unsigned short, QString);
    void sendFile(QString);

private slots:


    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_connectButton_clicked();

private:
    Ui::MainWindow *ui;


};
#endif // MAINWINDOW_H
