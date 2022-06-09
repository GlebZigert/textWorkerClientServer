#ifndef BACKEND_H
#define BACKEND_H

#include <QQuickItem>

class Backend : public QQuickItem
{
    Q_OBJECT

     Q_PROPERTY(QString data READ data )
public:
    Backend();

    QString data() const;


private:

    QString     m_data;

signals:

};

#endif // BACKEND_H
