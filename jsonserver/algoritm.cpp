#include "algoritm.h"
#include <QFile>
#include <QString>
#include <QDebug>



Algoritm::Algoritm(QObject *parent) : QObject(parent)
{

}

Algoritm::~Algoritm()
{
    qDebug()<<"Algoritm::~Algoritm()";
}

QJsonArray Algoritm::work_with(QByteArray *data)
{
    QJsonArray ar={};
    return ar;
}



simbolCount::simbolCount(QObject *parent)
{

}

QJsonArray simbolCount::work_with(QByteArray *data)
{

QJsonArray ar{};
QMap<QString, int> map;
QString str = QString::fromUtf8(*data);

if(str.count()==0){

    return ar;
}


for(int i=0;i<str.length();i++){

if((QString)str[i]=="\n")
continue;

if(!map.contains((QString)str[i])){
map.insert((QString)str[i],1);

}else{

    int val = map.value((QString)str[i])+1;
    map.remove((QString)str[i]);
    map.insert((QString)str[i],val);

}

}


QJsonObject m_obj;
m_obj.insert("len","символ");
m_obj.insert("count","Количество повторений");
ar.append(m_obj);

foreach(auto one, map.keys()){

QJsonObject m_obj;
m_obj.insert("len",one);

m_obj.insert("count",QString::number(map.value(one)));

ar.append(m_obj);

}

return ar;



}

wordLength::wordLength(QObject *parent)
{

}

QJsonArray wordLength::work_with(QByteArray *data)
{
    QJsonArray ar={};
    QString str = QString::fromUtf8(*data);

    if(str.count()==0){
        return ar;
    }

    QStringList list =str.split(QRegExp("[\\W]"), QString::SkipEmptyParts);

    /*
    foreach(auto one,list){
            qDebug()<<one;
    }
    */


    QMap<int,int> simbolCount;

    foreach(auto one, list){

    int len = one.length();

        if(simbolCount.contains(len)){

            int val=simbolCount.value(len)+1;
            simbolCount.remove(len);
            simbolCount.insert(len,val);

            continue;

        }else{
            simbolCount.insert(len,1);
        }
    }

    QJsonObject m_obj;
    m_obj.insert("len","Длина слова");
    m_obj.insert("count","Количество слов");
    ar.append(m_obj);

    foreach(auto one, simbolCount.keys()){

        qDebug()<<"len: "<<one<<"  count: "<<simbolCount.value(one);

        QJsonObject m_obj;
        m_obj.insert("len",QString::number(one));
        m_obj.insert("count",QString::number(simbolCount.value(one)));
        ar.append(m_obj);
    }

    return  ar;
}
