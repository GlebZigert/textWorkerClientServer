#include "algoritmcontroller.h"

AlgoritmController::AlgoritmController(QObject *parent) : QObject(parent)
{

    //  list.append(new Algoritm());
    //  list.append(new simbolCount());
     list.append(new wordLength());
}

QString AlgoritmController::work(QByteArray *data)
{
    QString res;
    foreach(auto algo, list){

        res+=algo->work_with(data);
    }

    return res;
}
