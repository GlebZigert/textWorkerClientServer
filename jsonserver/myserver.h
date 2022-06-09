#ifndef MYSERVER_H
#define MYSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

#include <algoritmcontroller.h>

class myserver : public QTcpServer
{
    Q_OBJECT
public:
    explicit myserver(QObject *parent = nullptr);
    ~myserver();

    QTcpSocket* socket;
    QByteArray Data;

 //   AlgoritmController worker;

public slots:
    void startServer();
    void incomingConnection(qintptr socketDescriptor) override;
    void sockReady();
    void sockDisc();
    void newConnection();



signals:

};

#endif // MYSERVER_H
