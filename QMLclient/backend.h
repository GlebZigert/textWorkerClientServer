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
     Q_PROPERTY(bool connection READ connection NOTIFY connectionIsCnanged)
public:
    Backend();

     Q_INVOKABLE void request(QString fileName);
     Q_INVOKABLE void start(QString fileName);

    QString data() const;
    bool connection(){return m_connection;};

public slots:
    void sockReady();
    void sockDisc();

private:

    QByteArray Data;

    QString     m_data;

    bool     m_connection;

     QTcpSocket* socket;

     QJsonDocument doc;
     QJsonParseError docError;

signals:
     void dataIsCnanged(QString );
     void connectionIsCnanged();
};

#endif // BACKEND_H
