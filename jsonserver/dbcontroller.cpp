#include "dbcontroller.h"
#include <QDebug>

#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>

dbController::dbController(QObject *parent) : QObject(parent)
{

create_db();
}

dbController::~dbController()
{

}

bool dbController::create_db()
{
    db = QSqlDatabase::addDatabase("QSQLITE");

    if(db.lastError().isValid()){
        qDebug()<<" addDataBase "<<db.lastError().text();
        return false;
    }

    //Getting system applicaton data folder
    QString appDataLocation = QStandardPaths::writableLocation(QStandardPaths::ApplicationsLocation);
    qDebug()<<"appDataLocation: "<<appDataLocation;

    //Create the application data folder if not exists
    QDir dir(appDataLocation);

    if(!dir.exists()){
        dir.mkdir(appDataLocation);
        qDebug()<<"mkdir "<<appDataLocation;
    }

    //Setup the db file name and open db
    QString dbPath = appDataLocation + "/testdb.db";
    qDebug()<<"dbPath: "<<dbPath;

    db.setDatabaseName(dbPath);

    if(!db.open()){
        qDebug()<<" Unable to open db "<<db.lastError().text()<<" "<<dbPath;
        return  false;
    }

        //drop_db();
        //create  a table
    QString tblFileCreate = "CREATE TABLE IF NOT EXISTS mydb("
                            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                            "dt STRING,"
                            "ipaddr STRING,"
                            "count BIGINT"
                            ")";

    QSqlQuery query;
    query.exec(tblFileCreate);

    if(query.lastError().isValid()){
        qDebug()<<" CREATE TABLE "<<db.lastError().text();
        return  false;
    }

    return true;
}

bool dbController::insert(QString dt, QString ipaddr, uint count)
{
    qDebug()<<"dbController::insert(QString dt, QString ipaddr, uint count)";
    QSqlQuery query;

    QString sqlinsert = "INSERT INTO mydb(dt,ipaddr,count)"+
    QString("VALUES(%1,%2,%3)").arg(dt).arg(ipaddr).arg(count);
    qDebug()<<"sqlinsert: "<<sqlinsert;
    query.exec(sqlinsert);

    if(query.lastError().isValid()){
        qDebug()<<"INSERT "<<query.lastError().text();
        return false;
    }

    return true;
}



QList<db_entity> dbController::read()
{
    QList<db_entity> list;
    qDebug()<<"dbController::read()";
    QSqlQuery query;
    QString sqlSelect = "SELECT * FROM mydb";
    query.exec(sqlSelect);

    if(query.lastError().isValid()){
        qDebug()<<"SELECT "<<query.lastError().text();
        return list;
    }


    while(query.next()){
        uint    id        =query.value("id").toUInt();
        QString dt        =query.value("dt").toString();
        QString ipaddr    =query.value("ipaddr").toString();
        uint    count     =query.value("count").toUInt();

qDebug()<<id<<" "<<dt<<" "<<ipaddr<<" "<< count;



      db_entity entity;
      entity.dt=dt;
      entity.ipaddr=ipaddr;
      entity.count=count;
      list.append(entity);

    }

    return list;


}

bool dbController::update()
{
    QSqlQuery query;
    QString sqlUpdate = "UPDATE mydb SET filePath='TESTME' WHERE id=1";
    query.exec(sqlUpdate);

    if(query.lastError().isValid()){
        qDebug()<<"UPDATE "<<query.lastError().text();
        return false;
    }

    //check the update

    QString sqlSelect = "SELECT * FROM mydb WHERE id=1";
    query.exec(sqlSelect);

    if(query.lastError().isValid()){
        qDebug()<<"SELECT "<<query.lastError().text();
        return false;
    }

    while(query.next()){
        uint    id              =query.value("id").toUInt();
        QString filePath        =query.value("filePath").toString();
        uint    fileSize        =query.value("fileSize").toUInt();
        uint    fileMTime       =query.value("fileMTime").toUInt();
        uint    fileLastCheck   =query.value("fileLastCheck").toUInt();
      qDebug()<<id<<" "<<filePath<<" "<<fileSize<<" "<< fileMTime<<" "<<fileLastCheck;

      if(filePath=="TESTME"){
          qDebug()<<"UPDATE SUCSESS";
          return true;

      }else{

          qDebug()<<"UPDATE FAILS";
          return false;
      }
    }

    return true;
}

bool dbController::drop_db()
{
     QSqlQuery query;
     query.exec("DROP TABLE mydb");

     if(query.lastError().isValid()){
         qDebug()<<"DROP TABLE "<<query.lastError().text();
         return false;
     }
     return true;
}

db_entity::db_entity(QObject *parent)
{

}

db_entity::db_entity(const db_entity &parent)
{
    dt=parent.dt;
    ipaddr=parent.ipaddr;
    count=parent.count;
}

db_entity::~db_entity()
{

}
