#include "algoritmcontroller.h"

AlgoritmController::AlgoritmController(QObject *parent) : QObject(parent)
{

    //  list.append(new Algoritm());
    //  list.append(new simbolCount());
    list.append(new wordLength());
    list.append(new simbolCount());
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
     res+="{";
      res+="\"type\":\"result\",";
      res+="\"res\":[";
    foreach(auto algo, list){


       res+="{";
        res+=algo->work_with(data);

         res += "},";
    }
    res.remove(res.count()-1,1);
      res+="]";
       res+="}";

    return res;
}
