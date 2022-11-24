#include "mainwindow.h"

#include <QApplication>
//#include <Qsql>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    QSqlDatabase db = QsqlDatabase::addDatabase("QMYSQL", "mydb");
//    db.setHostName("bigblue");
//    db.setDatabaseName("flightdb");
//    db.setUserName("acarlson");
//    db.setPassword("1uTbSbAs");

    MainWindow w;
    w.show();
    return a.exec();
}
