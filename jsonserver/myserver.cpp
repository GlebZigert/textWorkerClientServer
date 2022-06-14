#include "myserver.h"
#include <QDebug>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QDateTime>
#include <QJsonArray>

myserver::myserver(QObject *parent)
{
// connect(this,SIGNAL(newConnection()),this,SLOT(newConnection()));
}

myserver::~myserver()
{

}

QJsonArray myserver::convertListdbEntityToJson(QList<db_entity> list)
{
    QJsonObject obj;
    QJsonArray ar;

    foreach (auto one, list) {
        QJsonObject m_obj;
        m_obj.insert("dt",one.dt);
        m_obj.insert("ipaddr",one.ipaddr);
        m_obj.insert("count",QString::number(one.count));

        ar.append(m_obj);

    }

   // obj.insert("data",ar);
/*
 QJsonObject m1;
 m1.insert("one", QJsonValue::fromVariant(1));
  m1.insert("second", QJsonValue::fromVariant(2));

  QJsonObject m2;
  m2.insert("one", QJsonValue::fromVariant(3));
   m2.insert("second", QJsonValue::fromVariant(5));

    ar.append(m1);
      ar.append(m2);

    obj.insert("FirstName", QJsonValue::fromVariant("John"));
    obj.insert("LastName", QJsonValue::fromVariant("Doe"));
    obj.insert("Age", QJsonValue::fromVariant(43));
    obj.insert("Array", ar);

    qDebug()<<"obj: "<<obj;

*/

return ar;
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
            qDebug()<<doc.object();

            if(doc.object().value("type").toString() == "text"){
              qDebug()<<"Запрос на анализ текста:";
              qDebug()<<doc.object().value("text").toString();

              QByteArray data = doc.object().value("text").toString().toUtf8();

             AlgoritmController *worker=new AlgoritmController();
              QJsonObject result = worker->work(&data);
              worker->deleteLater();

              m_db.insert("\""+QDateTime::currentDateTime().toString()+"\"","\""+socket->peerAddress().toString()+"\"",data.count());


              QJsonDocument doc(result);


              qDebug()<<"doc: "<<doc;
              QByteArray jByte(doc.toJson(QJsonDocument::Compact));
              socket->write(jByte);




            }
             if(doc.object().value("type").toString() == "connect"){
                  socket->write("{\"type\":\"connect\",\"status\":\"yes\"}");
             }
             if(doc.object().value("type").toString() == "request_db"){

                 qDebug()<<"request_db";

                 QList<db_entity> list=m_db.read();

                 QJsonArray res=convertListdbEntityToJson(list);

                 QJsonObject jobj;


                 jobj.insert("data",res);

                jobj.insert("type","db");

                 QJsonDocument doc(jobj);


                 qDebug()<<"doc: "<<doc;
                 QByteArray jByte(doc.toJson(QJsonDocument::Compact));
                 socket->write(jByte);


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
