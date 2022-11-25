#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qsqldatabase.h"
#include <QMainWindow>
#include <QDebug>
#include <QTableView>
#include <QHeaderView>
#include <QSqlTableModel>
#include <QTextCodec>
#include <QSqlQuery>
#include <QSqlError>
#include <QComboBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    QSqlTableModel *model;
    QTableView *table;
    QSqlQuery *query;
    QStringList table_list;
    QComboBox *combo_box;

private slots:
    void on_delete_button_clicked();
    void fill_table_list(QStringList &list);
    void on_combo_box_currentTextChanged(const QString &arg1);
    void change_current_table(QString table_name);
    void update_table_view();
    void on_update_button_clicked();
    void on_insert_button_clicked();

    void on_file_button_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
