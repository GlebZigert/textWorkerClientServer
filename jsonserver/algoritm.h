#ifndef ALGORITM_H
#define ALGORITM_H

#include <QObject>
#include <QJsonObject>
#include <QString>
class Algoritm : public QObject
{
    Q_OBJECT
public:
    explicit Algoritm(QObject *parent = nullptr);

    virtual QString work_with(QByteArray *data);

signals:

};

class simbolCount : public Algoritm
{
    Q_OBJECT
public:
    explicit simbolCount(QObject *parent = nullptr);

    virtual QString work_with(QByteArray *data);

signals:

};

class wordLength : public Algoritm
{
    Q_OBJECT
public:
    explicit wordLength(QObject *parent = nullptr);

    virtual QString work_with(QByteArray *data);


signals:

};



#endif // ALGORITM_H
