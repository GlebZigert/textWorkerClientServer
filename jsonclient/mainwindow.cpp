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

        doc=QJsonDocument::fromJson(Data,&docError);

        if(docError.errorString().toInt()==QJsonParseError::NoError){


            qDebug()<<doc.object().value("type").toString();
            qDebug()<<doc.object().value("status").toString();

            if((doc.object().value("type").toString() == "connect")&&
               (doc.object().value("status").toString() == "yes")){

                QMessageBox::information(this,"Информация","Соединение установлено");

            }else{
                QMessageBox::information(this,"Информация","Соединение не установлено");
            }

        }else{
            QMessageBox::information(this,"Информация","Ошибки с форматом передачи данных"+docError.errorString());
        }

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


void MainWindow::on_pushButton_2_clicked()
{
    socket->write("Запрос на анализ текста");
}

