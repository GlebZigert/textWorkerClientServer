#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHostAddress>
#include <QFile>
#include <QFileDialog>

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



    QFile file(fileName); // создаем объект класса QFile

    QByteArray data; // Создаем объект класса QByteArray, куда мы будем считывать данные

    if (!file.open(QIODevice::ReadOnly)){ // Проверяем, возможно ли открыть наш файл для чтения
        qDebug()<<"file not open";
        // если это сделать невозможно, то завершаем функцию
        return;
    }

    data = file.readAll(); //считываем все данные с файла в объект data

    qDebug()<<"Data: "<<(QString)data;   socket->write("{\"type\":\"text\",\"text\":\""+data +"\"}");
}


void MainWindow::on_pushButton_3_clicked()
{



   // fileName= QFileDialog::getOpenFileName(this, tr("Open Image"), "", "*txt");

    fileName= QFileDialog::getOpenFileName(this, tr("Open Image"), "", "*txt");


    qDebug()<<fileName;


}

