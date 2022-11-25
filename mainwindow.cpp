#include "mainwindow.h"
#include "qsqlerror.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QInputDialog>
#include <QDir>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    fill_table_list(this->table_list);

    this->combo_box = this->findChild<QComboBox*>("combo_box");
    this->combo_box->addItems(this->table_list);

    this->db.setHostName("localhost");
    this->db.setDatabaseName("DRIVER={Oracle in XE};dblabs");
    this->db.setUserName("sys");
    this->db.setPassword("Tybctqcrfz55 as sysdba");
    this->db.setPort(8080);

    this->query = new QSqlQuery(this->db);

    if (!db.open())
    {
        qDebug() << this->db.lastError();
    }
    else {
        qDebug() << "Wow opened";
    }

    change_current_table("DBLABS." + this->combo_box->currentText().toUpper());
}

MainWindow::~MainWindow()
{
    delete ui;
    delete model;
    delete query;
    delete combo_box;
}

void MainWindow::on_delete_button_clicked()
{
    QModelIndexList indexes = this->table->selectionModel()->selection().indexes();
    QString curr_table = this->combo_box->currentText().toUpper();
    qDebug() << curr_table;
    if (!indexes.empty()) {
        int cur_id = indexes.at(0).data().toInt();

        QString str = "";
        if (curr_table == "PARTICIPANTS") {
            str = "DELETE FROM DBLABS." + curr_table + " WHERE ID = ?";
        }
        else if (curr_table == "PAPERS") {
            str = "DELETE FROM DBLABS." + curr_table + " WHERE ID_R = ?";
        }
        else if (curr_table == "SECTION") {
            str = "DELETE FROM DBLABS." + curr_table + " WHERE SECTION_NUM = ?";
        }
        else if (curr_table == "AWARD") {
            str = "DELETE FROM DBLABS." + curr_table + " WHERE ID = ?";
        }
        else if (curr_table == "PROGRAM") {
            str = "DELETE FROM DBLABS." + curr_table + " WHERE FNAME = ?";
        }

        qDebug() << str << cur_id;
        this->query->prepare(str);
        this->query->addBindValue(cur_id);
        if (!this->query->exec()) {
            QMessageBox::warning(this, "Внимание", "Произошла ошибка при удалении!");
        }
        else {
            QMessageBox::warning(this, "", "Удаление прошло успешно!");
        }

        update_table_view();
    }
    else {
        QMessageBox::warning(this, "Внимание", "Нужно выбрать строчку!");
    }
}

void MainWindow::fill_table_list(QStringList &list) {
    list.push_back("Participants");
    list.push_back("Papers");
    list.push_back("Section");
    list.push_back("Award");
    list.push_back("Program");
}

void MainWindow::change_current_table(QString table_name) {
    this->model = new QSqlTableModel(this, this->db);
    this->model->setTable(table_name);
    this->model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    this->model->select();

    this->table = this->findChild<QTableView*>("table_view");
    this->table->setModel(model);
    this->table->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->table->setSelectionMode(QAbstractItemView::SingleSelection);
    this->table->resizeColumnsToContents();
    this->table->show();
}

void MainWindow::on_combo_box_currentTextChanged(const QString &arg1)
{
    change_current_table("DBLABS." + this->combo_box->currentText().toUpper());
}

void MainWindow::update_table_view() {
    change_current_table("DBLABS." + this->combo_box->currentText().toUpper());
}

void MainWindow::on_update_button_clicked()
{
    if (!this->model->submitAll()) {
        qDebug() << this->query->lastError();
        QMessageBox::warning(this, "Внимание", "Произошла ошибка при обновлении!");
    }
    else {
        qDebug() << this->query->executedQuery();
        QMessageBox::warning(this, "", "Обновление прошло успешно!");
    }
    update_table_view();
}

void MainWindow::on_insert_button_clicked()
{
    QStringList headers;
    QStringList answers;

    for (int i = 0; i < this->table->model()->columnCount(); i++)
    {
      headers.append(this->table->model()->headerData(i, Qt::Horizontal).toString());
    }

    for (int i = 0; i < headers.size(); ++i) {
        QString ans = QInputDialog::getText(this, "Введите данные", headers[i], QLineEdit::Normal, QDir::home().dirName());
        answers.append(ans);
    }

    for (int i = 0; i < answers.size(); ++i) {
        qDebug() << answers[i];
    }

    QString str = "";
    QString curr_table = this->combo_box->currentText().toUpper();
    if (curr_table == "PARTICIPANTS") {
        str = "INSERT INTO DBLABS." + curr_table + " VALUES(?, ?, ?, ?, ?, ?, ?)";
        this->query->prepare(str);
        for (int i = 0; i < answers.size(); ++i) {
            if (i == 0) this->query->addBindValue(answers[i].toInt());
            else this->query->addBindValue(answers[i]);
        }
    }
    else if (curr_table == "PAPERS") {
        str = "INSERT INTO DBLABS." + curr_table + " VALUES(?, ?, ?, ?, ?, ?)";
        this->query->prepare(str);
        for (int i = 0; i < answers.size(); ++i) {
            if (i == 0) this->query->addBindValue(answers[i].toInt());
            else this->query->addBindValue(answers[i]);
        }
    }
    else if (curr_table == "SECTION") {
        str = "INSERT INTO DBLABS." + curr_table + " VALUES(?, ?, ?)";
        this->query->prepare(str);
        for (int i = 0; i < answers.size(); ++i) {
            if (i == 0) this->query->addBindValue(answers[i].toInt());
            else this->query->addBindValue(answers[i]);
        }
    }
    else if (curr_table == "AWARD") {
        str = "INSERT INTO DBLABS." + curr_table + " VALUES(?, ?)";
        this->query->prepare(str);
        for (int i = 0; i < answers.size(); ++i) {
            if (i == 1) this->query->addBindValue(answers[i].toInt());
        }
    }
    else if (curr_table == "PROGRAM") {
        str = "INSERT INTO DBLABS." + curr_table + " VALUES(?, ?)";
        this->query->prepare(str);
        for (int i = 0; i < answers.size(); ++i) {
            this->query->addBindValue(answers[i]);
        }
    }

    qDebug() << str;
    if (!this->query->exec()) {
        qDebug() << this->query->lastError();
        QMessageBox::warning(this, "Внимание", "Произошла ошибка при добавлении!");
    }
    else {
        qDebug() << this->query->executedQuery();
        QMessageBox::warning(this, "", "Добавление прошло успешно!");
        update_table_view();
    }
}

void MainWindow::on_file_button_clicked()
{
    QFile f("C:\\Users\\lican\\Downloads\\" + this->combo_box->currentText() + ".csv");

    if (f.open(QIODevice::WriteOnly))
    {
        QTextStream ts(&f);
        QStringList strList;

        strList << "\" \"";
        for (int c = 0; c < this->table->horizontalHeader()->count(); ++c)
            strList << "\"" + this->table->model()->headerData(c, Qt::Horizontal).toString() + "\"";
        ts << strList.join(";") + "\n";

        for (int r = 0; r < this->table->verticalHeader()->count(); ++r)
        {
            strList.clear();
            strList << "\"" + this->table->model()->headerData(r, Qt::Vertical).toString() + "\"";

            for (int c = 0; c < this->table->horizontalHeader()->count(); ++c)
            {
                strList << "\"" + this->table->model()->data(this->table->model()->index(r, c), Qt::DisplayRole).toString() + "\"";
            }
            ts << strList.join(";") + "\n";
        }
        f.close();

        QMessageBox::warning(this, "", "Файл сохранен в папку 'Загрузки'!");
    }
    else {
        QMessageBox::warning(this, "", "Ошибка выгрузки таблицы!");
    }
}

