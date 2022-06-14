#ifndef ALGORITM_H
#define ALGORITM_H

#include <QObject>
#include <QJsonObject>
#include <QJsonArray>
#include <QString>
class Algoritm : public QObject
{
    Q_OBJECT
public:
    explicit Algoritm(QObject *parent = nullptr);
    ~Algoritm();

    virtual QJsonArray work_with(QByteArray *data);
    virtual QString getType(){return "type of algoritm";};

signals:

};

class simbolCount : public Algoritm
{
    Q_OBJECT
public:
    explicit simbolCount(QObject *parent = nullptr);

     QJsonArray work_with(QByteArray *data);
     QString getType(){return "Распределение символов";};

signals:

};

class wordLength : public Algoritm
{
    Q_OBJECT
public:
    explicit wordLength(QObject *parent = nullptr);

     QJsonArray work_with(QByteArray *data);
     QString getType(){return "Распределение слов по их длинам";};


};



#endif // ALGORITM_H
