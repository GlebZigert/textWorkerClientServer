#include "algoritmcontroller.h"
#include <QDebug>

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

QJsonObject AlgoritmController::work(QByteArray *data)
{

    QJsonObject obj;
    QJsonArray ar;

    obj.insert("type","result");

    QString res;
     res+="{";
      res+="\"type\":\"result\",";
      res+="\"res\":[";


    foreach(auto algo, list){

        QJsonObject m_obj;
        m_obj.insert("type",algo->getType());
          m_obj.insert("values",algo->work_with(data));


            ar.append(m_obj);
       res+="{";
      //  res+=algo->work_with(data);

         res += "},";
    }
    res.remove(res.count()-1,1);
      res+="]";
       res+="}";

       obj.insert("res",ar);

    return obj;
}
