#include "dbcontroller.h"
#include <QDebug>

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

    //create  a table
    QString tblFileCreate = "CREATE TABLE IF NOT EXISTS files("
                            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                            "filePath STRING,"
                            "fileSize BIGINT,"
                            "fileMTime BIGINT,"
                            "fileLastCheck BIGINT"
                            ")";

    QSqlQuery query;
    query.exec(tblFileCreate);

    if(query.lastError().isValid()){
        qDebug()<<" CREATE TABLE "<<db.lastError().text();
       return  false;
    }
    return true;
}

bool dbController::insert()
{
    QSqlQuery query;
    const int INSERT_COUNT = 10;

    for(int i=0;i<INSERT_COUNT;i++){
        QString sqlinsert = "INSERT INTO files(filePath,fileSize,fileMtime,fileLastCheck)"+
         QString("VALUES('file%1',%1,%1,%1)").arg(i);

        query.exec(sqlinsert);
        if(query.lastError().isValid()){
            qDebug()<<"INSERT "<<query.lastError().text();
            return false;
        }
    }
    return true;
}

bool dbController::read()
{
    QSqlQuery query;
    QString sqlSelect = "SELECT * FROM files";
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

    }

    return true;
}

bool dbController::update()
{
    QSqlQuery query;
    QString sqlUpdate = "UPDATE files SET filePath='TESTME' WHERE id=1";
    query.exec(sqlUpdate);

    if(query.lastError().isValid()){
        qDebug()<<"UPDATE "<<query.lastError().text();
        return false;
    }

    //check the update

    QString sqlSelect = "SELECT * FROM files WHERE id=1";
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
     query.exec("DROP TABLE files");

     if(query.lastError().isValid()){
         qDebug()<<"DROP TABLE "<<query.lastError().text();
         return false;
     }
     return true;
}
