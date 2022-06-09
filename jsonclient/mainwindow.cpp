#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHostAddress>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    socket = new QTcpSocket(this);


    connect(socket,SIGNAL(readyRead()),this,SLOT(sockReady()));
    connect(socket,SIGNAL(disconnected()),this,SLOT(sockDisc()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::sockReady()
{
    if(socket->waitForConnected(500)){

        socket->waitForReadyRead(500);
        Data = socket->readAll();
        qDebug()<<(QString)Data;
    }
}

void MainWindow::sockDisc()
{
    socket->deleteLater();
}


void MainWindow::on_pushButton_clicked()
{

    socket->connectToHost(QHostAddress("127.0.0.1"),5555);
}

