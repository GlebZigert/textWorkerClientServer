#include "algoritmcontroller.h"
#include <QDebug>

AlgoritmController::AlgoritmController(QObject *parent) : QObject(parent)
{

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

    foreach(auto algo, list){
        QJsonObject m_obj;
        m_obj.insert("type",algo->getType());
        m_obj.insert("values",algo->work_with(data));
        ar.append(m_obj);

    }

    obj.insert("res",ar);

    return obj;
}

bool AlgoritmController::work(QByteArray *data, QJsonObject *json)
{
    QJsonObject obj;
    QJsonArray ar;



    foreach(auto algo, list){
        QJsonObject m_obj;
        m_obj.insert("type",algo->getType());
        m_obj.insert("values",algo->work_with(data));
        ar.append(m_obj);

    }
    json->insert("type","result");
    json->insert("res",ar);

    return true;
}
