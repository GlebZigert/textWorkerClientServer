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
        qDebug() <<"Data: "<< (QString)(*data); // Выводим данные в консоль, предварительно создав строку из полученных данных



    return ar;
}



simbolCount::simbolCount(QObject *parent)
{

}

QJsonArray simbolCount::work_with(QByteArray *data)
{
    QString res="";

    QJsonArray ar{};

    qDebug()<<" ";

    res+="\"type\":\"Распределение символов\",";

    qDebug()<<"wordLength:";
     res+="\"first\":\"Символ\",";
      res+="\"second\":\"Количество повторений\",";
    qDebug() <<"Data: "<< (QString)(*data);
   qDebug() <<"count: "<< data->count();



    QMap<QString, int> map;
    QString current="";


    QString str = QString::fromUtf8(*data);

    if(str.count()==0){
    res+="\"values\":[]";
    return ar;
    }


     for(int i=0;i<str.length();i++){
         //qDebug()<<str[i];




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

    res+="\"values\":[";

    QJsonObject obj;

    QJsonObject m_obj;
    m_obj.insert("len","символ");
    m_obj.insert("count","Количество повторений");
    ar.append(m_obj);

    foreach(auto one, map.keys()){
        res += "{";

        res += "\"";
        res += "len";
        res += "\"";

        res += ":";

        res += "\"";
        res += one;
        res += "\"";

        res += ",";

        res += "\"";
        res += "";
        res += "\"";

        res += ":";

        res += "\"";
        res += QString::number(map.value(one));
        res+=+ "\"";

        res += "},";

        QJsonObject m_obj;
        m_obj.insert("len",one);

        m_obj.insert("count",QString::number(map.value(one)));

        ar.append(m_obj);



        qDebug()<<one<<" "<<map.value(one);
    }


    res.remove(res.count()-1,1);

    res+="]";





    return ar;


/*
     res+="\"values\":[";

    foreach(auto one, simbolCount.keys()){


        qDebug()<<"len: "<<one<<"  count: "<<simbolCount.value(one);

       res += "{";

       res += "\"";
       res += "len";
       res += "\"";

       res += ":";

       res += "\"";
       res += QString::number(one);
       res += "\"";

       res += ",";

       res += "\"";
       res += "count";
       res += "\"";

       res += ":";

       res += "\"";
       res += QString::number(simbolCount.value(one));
       res+=+ "\"";

       res += "},";
    }

    res.remove(res.count()-1,1);

    res+="]";

    res+="}";

   return  res;
   */
}

wordLength::wordLength(QObject *parent)
{

}

QJsonArray wordLength::work_with(QByteArray *data)
{

    QJsonArray ar={};
    QString res="";

    qDebug()<<" ";

    res+="\"type\":\"Распределение слов по их длинам\",";

    qDebug()<<"wordLength:";
     res+="\"first\":\"Длина слова\",";
      res+="\"second\":\"Количество слов\",";
    qDebug() <<"Data: "<< (QString)(*data);
   qDebug() <<"count: "<< data->count();



    QString current="";


    QString str = QString::fromUtf8(*data);


    if(str.count()==0){
    res+="\"values\":[]";
    return ar;
    }

    QString name("United1St!ates");
    QStringList list =str.split(QRegExp("[\\W]"), QString::SkipEmptyParts);

    foreach(auto one,list){
        qDebug()<<one;
    }
    /*
    for(int i=0;i<data->count();i++){


        qDebug()<<i<<" "<<data->at(i)<<" "<<(int)(data->at(i))<<"\n";

        bool word=false;

        if(((int)(data->at(i))==32)||((int)(data->at(i))==10)){

        word=true;
        //    qDebug()<<"новое слово:";
        }else{
            current+=data->at(i);

        }
        if(i==data->count()-1){
            word=true;
        }

        if(word){
            qDebug()<<current;
            list.append(current);
            current="";

        }

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



     res+="\"values\":[";

     QJsonObject m_obj;
     m_obj.insert("len","Длина слова");
     m_obj.insert("count","Количество слов");
     ar.append(m_obj);
    foreach(auto one, simbolCount.keys()){


        qDebug()<<"len: "<<one<<"  count: "<<simbolCount.value(one);

       res += "{";

       res += "\"";
       res += "len";
       res += "\"";

       res += ":";

       res += "\"";
       res += QString::number(one);
       res += "\"";

       res += ",";

       res += "\"";
       res += "count";
       res += "\"";

       res += ":";

       res += "\"";
       res += QString::number(simbolCount.value(one));
       res+=+ "\"";

       res += "},";

       QJsonObject m_obj;
       m_obj.insert("len",QString::number(one));

       m_obj.insert("count",QString::number(simbolCount.value(one)));

       ar.append(m_obj);
    }

    res.remove(res.count()-1,1);

    res+="]";



   return  ar;
}
