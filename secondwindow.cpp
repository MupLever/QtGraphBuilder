#include "secondwindow.h"
#include "ui_secondwindow.h"

SecondWindow::SecondWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SecondWindow)
{
    ui->setupUi(this);
    setWindowTitle("GROW");
    model = new QStandardItemModel(10, 2, this);
    ui->tableView->setModel(model);
    model->setHeaderData(0, Qt::Horizontal, "Date");
    model->setHeaderData(1, Qt::Horizontal, "Function");
    ui->tableView->setEditTriggers(QTableView::NoEditTriggers);
    ui->tableView->setColumnWidth(0, 140);
    ui->tableView->setColumnWidth(1, 230);
    Record record;
    QModelIndex index;
    FILE *f_logs;
    if ((f_logs = fopen("./cache", "r+b")) != NULL && !FileEmpty(f_logs)) {
        int count = GetRecordsCountInFile(f_logs);
        for (int i = count - 1, j =0 ; i >= 0 && j < model->rowCount(); --i, ++j) {
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
