#ifndef ALGORITMCONTROLLER_H
#define ALGORITMCONTROLLER_H

#include <QObject>
#include "algoritm.h"
#include <QList>
#include <QJsonObject>

class AlgoritmController : public QObject
{
    Q_OBJECT
public:
    explicit AlgoritmController(QObject *parent = nullptr);
    ~AlgoritmController();

    QJsonObject work(QByteArray *data);
    bool work(QByteArray *data, QJsonObject *json);
private:
    Algoritm *algo;

    QList<Algoritm*> list;



signals:

};

#endif // ALGORITMCONTROLLER_H
