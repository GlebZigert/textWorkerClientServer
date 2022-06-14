#ifndef DBCONTROLLER_H
#define DBCONTROLLER_H

#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QStandardPaths>
#include <QDebug>
#include <QDir>
#include <QSqlQuery>

class db_entity : public QObject
{
    Q_OBJECT




public:

    explicit db_entity(QObject *parent = nullptr);
    db_entity(const db_entity & parent);
    ~db_entity();

 QString dt;
 QString ipaddr;
 uint count;

};


class dbController : public QObject
{
    Q_OBJECT
public:
    explicit dbController(QObject *parent = nullptr);
    ~dbController();

    bool create_db();

    bool insert(QString dt, QString ipaddr, uint count);

    QList<db_entity> read();

    bool update();

    bool drop_db();


private:

    QSqlDatabase db;






signals:

};

#endif // DBCONTROLLER_H
