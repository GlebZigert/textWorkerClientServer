#include "myserver.h"
#include <QDebug>


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
    socket->write("You are connect");

}

void myserver::sockReady()
{

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
