#include "algoritmcontroller.h"

AlgoritmController::AlgoritmController(QObject *parent) : QObject(parent)
{

    //  list.append(new Algoritm());
    //  list.append(new simbolCount());
    list.append(new wordLength());
}

AlgoritmController::~AlgoritmController()
{
  qDebug()<<"AlgoritmController::~AlgoritmController()";
  foreach(auto one,list){

      one->deleteLater();
  }
}

QString AlgoritmController::work(QByteArray *data)
{
    QString res;
    foreach(auto algo, list){

        res+=algo->work_with(data);
    }

    return res;
}
