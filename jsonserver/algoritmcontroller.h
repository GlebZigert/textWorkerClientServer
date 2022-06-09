#ifndef ALGORITMCONTROLLER_H
#define ALGORITMCONTROLLER_H

#include <QObject>
#include "algoritm.h"
#include <QList>

class AlgoritmController : public QObject
{
    Q_OBJECT
public:
    explicit AlgoritmController(QObject *parent = nullptr);
    ~AlgoritmController();

    QString work(QByteArray *data);

private:
    Algoritm *algo;

    QList<Algoritm*> list;



signals:

};

#endif // ALGORITMCONTROLLER_H
