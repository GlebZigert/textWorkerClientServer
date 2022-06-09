#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QFileDialog>
#include <QDebug>

#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    algo = new Algoritm();

}

MainWindow::~MainWindow()
{
    delete ui;
}

class mData{

    QList<QPair<char,ulong>> simbolCount;
    QList<QPair<ulong,ulong>> wordLengthlCount;




};


void MainWindow::on_pushButton_clicked()
{

    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open Image"), "", "*txt");

    qDebug()<<fileName;

    QString res="";

    list.append(new Algoritm());
    list.append(new simbolCount());
    list.append(new wordLength());

    QFile file(fileName); // создаем объект класса QFile

    QByteArray data; // Создаем объект класса QByteArray, куда мы будем считывать данные

    if (!file.open(QIODevice::ReadOnly)){ // Проверяем, возможно ли открыть наш файл для чтения
        qDebug()<<"file not open";
        // если это сделать невозможно, то завершаем функцию
        return;
    }

    data = file.readAll(); //считываем все данные с файла в объект data

    qDebug()<<"Data: "<<(QString)data;

    file.close();



    foreach(auto algo, list){

        res+=algo->work_with(&data);
    }




    qDebug()<<res;





 /*
    QString val;
          QFile file;



          file.setFileName("/home/administrator/test.json");
          file.open(QIODevice::ReadOnly | QIODevice::Text);
          val = file.readAll();

          qDebug()<<val;
          qDebug()<<" \n";

          file.close();

          QJsonDocument doc = QJsonDocument::fromJson(val.toUtf8());
           QJsonObject json = doc.object();
           QString str = json["hello"].toString();
           bool t = json["t"].toBool();
           bool f = json["f"].toBool();
           bool n = json["n"].toBool();
           int  i = json["i"].toInt();
           double pi = json["pi"].toDouble();
           QJsonArray ar = json["a"].toArray();
           QList <QVariant> at = ar.toVariantList();



           qDebug()<<at;

           int len = ar.count();

           qDebug()<<"длина "<<len;


           for(int i=0;i<ar.count();i++){
               qDebug()<<ar[i].toDouble()<<"\n";

           }
           */


           qDebug()<<" \n";





}

