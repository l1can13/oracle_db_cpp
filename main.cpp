#include "mainwindow.h"

#include <QApplication>
#include <QtSql>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("DRIVER={Oracle in XE};Server=LOCALHOST\\SQLEXPRESS");
    db.setUserName("system");
    db.setPassword("Tybctqcrfz55");
    if (!db.open())
    {
        qDebug() << db.lastError().text();
    }
    else {
        qDebug() << "Wow opened";
    }

    QSqlQuery query;
    query.exec("insert into section values(1, 's5', 'd5')");

    MainWindow w;
    w.show();
    return a.exec();
}
