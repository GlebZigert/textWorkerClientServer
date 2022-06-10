#include "algoritm.h"
#include <QFile>
#include <QString>



Algoritm::Algoritm(QObject *parent) : QObject(parent)
{

}

Algoritm::~Algoritm()
{
    qDebug()<<"Algoritm::~Algoritm()";
}

QString Algoritm::work_with(QByteArray *data)
{


        qDebug() <<"Data: "<< (QString)(*data); // Выводим данные в консоль, предварительно создав строку из полученных данных



    return "1";
}



simbolCount::simbolCount(QObject *parent)
{

}

QString simbolCount::work_with(QByteArray *data)
{
    QString res="";

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
    return res;
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
        res += "count";
        res += "\"";

        res += ":";

        res += "\"";
        res += QString::number(map.value(one));
        res+=+ "\"";

        res += "},";

        qDebug()<<one<<" "<<map.value(one);
    }


    res.remove(res.count()-1,1);

    res+="]";





    return res;


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

QString wordLength::work_with(QByteArray *data)
{
    QString res="";

    qDebug()<<" ";

    res+="\"type\":\"Распределение слов по их длинам\",";

    qDebug()<<"wordLength:";
     res+="\"first\":\"Длина слова\",";
      res+="\"second\":\"Количество слов\",";
    qDebug() <<"Data: "<< (QString)(*data);
   qDebug() <<"count: "<< data->count();


    QStringList list;
    QString current="";


    QString str = QString::fromUtf8(*data);


    if(str.count()==0){
    res+="\"values\":[]";
    return res;
    }

     for(int i=0;i<str.length();i++){
         //qDebug()<<str[i];

         bool word=false;

         if((str[i]==" ")||(str[i]=='\xa')){

         word=true;
         //    qDebug()<<"новое слово:";
         }else{
             current+=str[i];

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



   return  res;
}
