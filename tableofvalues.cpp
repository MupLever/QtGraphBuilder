#include "tableofvalues.h"
#include "ui_tableofvalues.h"

TableOfValues::TableOfValues(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TableOfValues)
{
    ui->setupUi(this);
    setWindowTitle("GROW");
}

TableOfValues::~TableOfValues()
{
    delete ui;
}

void TableOfValues::on_pushButton_2_clicked() {
    close();
}
void TableOfValues::SetStr() {
    std::string std_str = ui->lineEdit_3->text().toStdString();
    int len = (int)std_str.length();
    for (int i = 0; i < len; i++)
        str[i] = std_str[i];
    str[len] = '\0';
    trim(str);

}
void TableOfValues::on_pushButton_clicked() {
    SetStr();
    bool flag = 0;
    transform(str, &flag);
    if (valid_str(str) != 0 || flag || strlen(str) == 0) {
        QMessageBox msgBox(QMessageBox::Information,
                           "GROW", "Invalid expression entered.",
                           QMessageBox::Ok);
        msgBox.exec();
    } else {
        ui->lineEdit->setReadOnly(true);
        ui->lineEdit_2->setReadOnly(true);
        ui->lineEdit_3->setReadOnly(true);
        double xmin = -10.0, xmax = 10.0, dx = (xmax - xmin) / 20;
        model = new QStandardItemModel(10, 2, this);
        ui->tableView->setModel(model);
        model->setHeaderData(0, Qt::Horizontal, "X");
        model->setHeaderData(1, Qt::Horizontal, "Y");
        model->setRowCount(20);
        ui->tableView->setEditTriggers(QTableView::NoEditTriggers);
        ui->tableView->setColumnWidth(0, 140);
        ui->tableView->setColumnWidth(1, 230);
        QModelIndex index;
        for (int i = 0, x = xmin; i < 20; ++i, x += dx) {
            index = model->index(i, 0);
            model->setData(index, x);
            index = model->index(i, 1);
            head = parse(str);
            tail = get_tail(head);
            model->setData(index, calculate(tail, x));
        }
    }
}

void TableOfValues::on_pushButton_3_clicked() {
    ui->lineEdit->setReadOnly(false);
    ui->lineEdit_2->setReadOnly(false);
    ui->lineEdit_3->setReadOnly(false);
    ui->lineEdit->setText("");
    ui->lineEdit_2->setText("");
    ui->lineEdit_3->setText("");
}
