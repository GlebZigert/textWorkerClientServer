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

QString myserver::convertListdbEntityToJson(QList<db_entity>)
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
    if(socket->waitForConnected(5)){

        socket->waitForReadyRead(5);
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

              m_db.insert("\""+QDateTime::currentDateTime().toString()+"\"","\""+socket->peerAddress().toString()+"\"",data.count());



              qDebug()<<result;

              doc=QJsonDocument::fromJson( result.toUtf8(),&docError);
             if(docError.errorString().toInt()==QJsonParseError::NoError){
                  qDebug()<<"JSON success.";
                  socket->write(result.toUtf8());
              }else{
               qDebug()<<"Ошибки с форматом передачи данных"<<docError.errorString();
              }

            }
             if(doc.object().value("type").toString() == "connect"){
                  socket->write("{\"type\":\"connect\",\"status\":\"yes\"}");
             }
             if(doc.object().value("type").toString() == "request_db"){

                 QList<db_entity> list=m_db.read();

                 QString res=convertListdbEntityToJson(list);

                  socket->write(res.toUtf8());

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
