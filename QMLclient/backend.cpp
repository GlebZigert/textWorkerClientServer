#include "backend.h"
#include <QHostAddress>

Backend::Backend()
{
  //  m_data="{\"type\":\"Распределение слов по их длинам\",\"first\":\"Длина слова\",\"second\":\"Количество слов\",\"values\":[{\"2\":\"1\"},{\"3\":\"1\"},{\"4\":\"1\"},{\"5\":\"1\"},{\"6\":\"2\"},]}";
      m_data="";

      socket = new QTcpSocket(this);


      connect(socket,SIGNAL(readyRead()),this,SLOT(sockReady()));
      connect(socket,SIGNAL(disconnected()),this,SLOT(sockDisc()));

       socket->connectToHost(QHostAddress("127.0.0.1"),5555);


}

void Backend::request(QString fileName)
{
    qDebug()<<"Backend::request "<<fileName;

    QFile file(fileName); // создаем объект класса QFile

    QByteArray data; // Создаем объект класса QByteArray, куда мы будем считывать данные

    if (!file.open(QIODevice::ReadOnly)){ // Проверяем, возможно ли открыть наш файл для чтения
        qDebug()<<"file not open";
        // если это сделать невозможно, то завершаем функцию
        return;
    }

    data = file.readAll(); //считываем все данные с файла в объект data

    qDebug()<<"Data: "<<(QString)data;   socket->write("{\"type\":\"text\",\"text\":\""+data +"\"}");

}

QString Backend::data() const
{
    return m_data;
}

void Backend::sockReady()
{
    if(socket->waitForConnected(500)){

        socket->waitForReadyRead(500);
        Data = socket->readAll();

        doc=QJsonDocument::fromJson(Data,&docError);

        if(docError.errorString().toInt()==QJsonParseError::NoError){


            qDebug()<<doc.object().value("type").toString();
            qDebug()<<doc.object().value("status").toString();

            if((doc.object().value("type").toString() == "connect")&&
               (doc.object().value("status").toString() == "yes")){

               qDebug()<<"Информация: Соединение установлено";

            }else{
                qDebug()<<"Информация: Соединение не установлено";
            }

        }else{
            qDebug()<<"Информация: Ошибки с форматом передачи данных"<<docError.errorString();
        }

        qDebug()<<(QString)Data;

        m_data=(QString)Data;

        qDebug()<<"m_data: "<<m_data;

        emit dataIsCnanged(m_data);
    }
}

void Backend::sockDisc()
{

}
