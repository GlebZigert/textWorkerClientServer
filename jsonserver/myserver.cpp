#include "myserver.h"
#include <QDebug>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>

myserver::myserver(QObject *parent)
{
// connect(this,SIGNAL(newConnection()),this,SLOT(newConnection()));
}

myserver::~myserver()
{

}

void myserver::startServer()
{
    if(this->listen(QHostAddress::Any,5555)){
        qDebug()<<"listening";
    }   else{
        qDebug()<<"not listening";
    }
}

void myserver::incomingConnection(qintptr socketDescriptor)
{
    socket = new QTcpSocket(this);
    socket->setSocketDescriptor(socketDescriptor);

    connect(socket,SIGNAL(readyRead()),this,SLOT(sockReady()));
    connect(socket,SIGNAL(disconnected()),this,SLOT(sockDisc()));

    qDebug()<<socketDescriptor<<" Client connected";
    socket->write("{\"type\":\"connect\",\"status\":\"yes\"}");



}

void myserver::sockReady()
{
    if(socket->waitForConnected(500)){

        socket->waitForReadyRead(500);
        Data = socket->readAll();

         qDebug()<<(QString)Data;

        QJsonDocument doc;
        QJsonParseError docError;

         doc=QJsonDocument::fromJson( Data,&docError);

        if(docError.errorString().toInt()==QJsonParseError::NoError){

            qDebug()<<"JSON success.";

            if(doc.object().value("type").toString() == "text"){
              qDebug()<<"Запрос на анализ текста:";
              qDebug()<<doc.object().value("text").toString();

              QByteArray data = doc.object().value("text").toString().toUtf8();

             AlgoritmController *worker=new AlgoritmController();
              QString result = worker->work(&data);
              worker->deleteLater();

              qDebug()<<result;

              doc=QJsonDocument::fromJson( result.toUtf8(),&docError);

              if(docError.errorString().toInt()==QJsonParseError::NoError){

                  qDebug()<<"JSON success.";



                  socket->write(result.toUtf8());

              }else{

               qDebug()<<"Ошибки с форматом передачи данных"<<docError.errorString();
              }





            }

        }else{
           qDebug()<<"Ошибки с форматом передачи данных"<<docError.errorString();
        }
    }
}

void myserver::sockDisc()
{
    qDebug()<<"disconnected";
    socket->deleteLater();
}

void myserver::newConnection()
{
    qDebug()<<"newConnection";
}
