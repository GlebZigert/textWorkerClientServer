#ifndef DBCONTROLLER_H
#define DBCONTROLLER_H

#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QStandardPaths>
#include <QDebug>
#include <QDir>
#include <QSqlQuery>

class dbController : public QObject
{
    Q_OBJECT
public:
    explicit dbController(QObject *parent = nullptr);
    ~dbController();

    bool create_db();

    bool insert(QString dt, QString ipaddr, uint count);



    bool read();

    bool update();

    bool drop_db();


private:

    QSqlDatabase db;






signals:

};

#endif // DBCONTROLLER_H
