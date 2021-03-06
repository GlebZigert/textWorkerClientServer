#include "algoritm.h"
#include <QFile>
#include <QString>



Algoritm::Algoritm(QObject *parent) : QObject(parent)
{

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
 return "";

   /*

{"type":"simbolCount",
"values":
    [
        {"1":"1"},
       {"2":"2"}

        ]
}
    */
}

wordLength::wordLength(QObject *parent)
{

}

QString wordLength::work_with(QByteArray *data)
{
    QString res="";
    res+="{";
    qDebug()<<" ";

    res+="\"type\":\"Распределение слов по их длинам\",";

    qDebug()<<"wordLength:";
     res+="\"first\":\"Длина слова\",";
      res+="\"second\":\"Количество слов\",";
    qDebug() <<"Data: "<< (QString)(*data);
   qDebug() <<"count: "<< data->count();



    QStringList list;
    QString current="";

    for(int i=0;i<data->count();i++){


     //   qDebug()<<i<<" "<<data->at(i)<<" "<<(int)(data->at(i))<<"\n";

        if(((int)(data->at(i))==32)||((int)(data->at(i))==10)){

            qDebug()<<current;
            list.append(current);
            current="";
        //    qDebug()<<"новое слово:";
        }else{
            current+=data->at(i);

        }
    }

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

       res+="\""+(QString)one+"\""+":"+"\""+(QString)simbolCount.value(one)+"\"";
    }

    res+="]";

    res+="}";

   return  res;
}
