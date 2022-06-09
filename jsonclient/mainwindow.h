#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QTcpSocket* socket;

public slots:
    void sockReady();
    void sockDisc();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
    QByteArray Data;

    QString fileName;

   QJsonDocument doc;
   QJsonParseError docError;
};
#endif // MAINWINDOW_H
