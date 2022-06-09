#ifndef MYCLIENT_H
#define MYCLIENT_H

#include <QObject>
#include<QTcpSocket>

class myclient : public QObject
{
    Q_OBJECT
public:
    explicit myclient(QObject *parent = nullptr);

    QTcpSocket* socket;

public slots:
    void sockReady();
    void sockDisc();

signals:

};

#endif // MYCLIENT_H
