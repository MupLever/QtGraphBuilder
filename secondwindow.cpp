#include "secondwindow.h"
#include "ui_secondwindow.h"

SecondWindow::SecondWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SecondWindow)
{
    ui->setupUi(this);
    setWindowTitle("GROW");
    setFixedSize(QSize(450,450));

    page = 0;

    model = new QStandardItemModel(10, 2, this);
    ui->tableView->setModel(model);

    model->setHeaderData(0, Qt::Horizontal, "Дата");
    model->setHeaderData(1, Qt::Horizontal, "Функция");

    ui->tableView->setEditTriggers(QTableView::NoEditTriggers);
    ui->tableView->setColumnWidth(0, 140);
    ui->tableView->setColumnWidth(1, 230);
    buidTable();

}
void SecondWindow::buidTable() {
    if ((f_logs = fopen("./cache", "r+b")) != NULL && !FileEmpty(f_logs)) {
        Record record;
        int count = GetRecordsCountInFile(f_logs);
        for (int i = count - (1 + page * 10), j = 0 ; i >= 0 && j < model->rowCount(); --i, ++j) {
            record = ReadRecordFromFile(f_logs, i);
            index = model->index(j, 0);
            model->setData(index, record.date);
            index = model->index(j, 1);
            model->setData(index, record.func);
        }
        fclose(f_logs);
    }
}
SecondWindow::~SecondWindow() {
    delete model;
    delete ui;
}

void SecondWindow::on_pushButton_clicked() {
    close();
}

void SecondWindow::on_pushButton_2_clicked() {
    if (page > 0) {
        --page;
        buidTable();
    }

}

void SecondWindow::on_pushButton_3_clicked() {
    if ((f_logs = fopen("./cache", "r+b")) != NULL && !FileEmpty(f_logs)) {
        int count = GetRecordsCountInFile(f_logs);
        fclose(f_logs);
        if (count - page * 10 > 10) {
            for (int i = 0 ; i < model->rowCount(); ++i) {
                index = model->index(i, 0);
                model->setData(index, "");
                index = model->index(i, 1);
                model->setData(index, "");
            }
            ++page;
            buidTable();
        }

    }
}
