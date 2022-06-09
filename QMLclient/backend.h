#ifndef BACKEND_H
#define BACKEND_H

#include <QQuickItem>

#include <QTcpSocket>

#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>

class Backend : public QQuickItem
{
    Q_OBJECT

     Q_PROPERTY(QString data READ data NOTIFY dataIsCnanged)
public:
    Backend();

     Q_INVOKABLE void request(QString fileName);

    QString data() const;

public slots:
    void sockReady();
    void sockDisc();

private:

    QByteArray Data;

    QString     m_data;


     QTcpSocket* socket;

     QJsonDocument doc;
     QJsonParseError docError;

signals:
     void dataIsCnanged(QString m_data);

};

#endif // BACKEND_H
