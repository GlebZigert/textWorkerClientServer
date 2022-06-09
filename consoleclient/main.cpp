#include <QCoreApplication>
#include <QTcpSocket>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QTcpSocket socket;

    qDebug()<<"argc: "<<argc;

    if(argc==3){

    qDebug()<<"argv[0] "<<argv[0];
    qDebug()<<"argv[1] "<<argv[1];

    QString ipaddr;
    quint16 port;

    ipaddr=(QString)argv[1];
    port = strtol(argv[2], NULL, 10);

    qDebug()<<ipaddr<<":"<<port;



    socket.connectToHost(ipaddr,port);



 //   socket.connectToHost("127.0.0.1",5555);


}else{
    qDebug()<<"введи ipaddr и порт";
    }



    return a.exec();
}
