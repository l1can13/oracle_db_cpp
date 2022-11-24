#include "mainwindow.h"
#include <QApplication>
#include <QtSql>
#include <QDebug>
#include <QTableView>
#include <QHeaderView>
#include <QSqlTableModel>
#include <QTextCodec>
#include <windows.h>

int main(int argc, char *argv[])
{
    SetConsoleOutputCP(65001);
    QApplication a(argc, argv);

    MainWindow *w = new MainWindow();

    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    QString connectionTemplate = "DRIVER={Oracle in XE};SERVER=localhost;DATABASE=dblabs;Uid=sys;Pwd=Tybctqcrfz55 as sysdba;Trusted_Connection=Yes;";
    db.setDatabaseName(connectionTemplate);

    if (!db.open())
    {
        qDebug() << db.lastError();
    }
    else {
        qDebug() << "Wow opened";
    }

    QSqlTableModel *model = new QSqlTableModel(w, db);
    model->setTable("participants");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();
    qDebug() << model->lastError();

    QTableView *table = w->findChild<QTableView*>("table_view");
    table->setModel(model);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->resizeColumnsToContents();
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->show();

    w->show();

    return a.exec();
}
