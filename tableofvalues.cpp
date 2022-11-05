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
    int i;
    std::string std_str = ui->lineEdit_3->text().toStdString();
    std::string std_str_lg = ui->lineEdit->text().toStdString();
    std::string std_str_rg = ui->lineEdit_2->text().toStdString();
    int len = (int)std_str.length();
    for (i = 0; i < len; i++)
        str[i] = std_str[i];
    str[len] = '\0';

    int len_lg = (int)std_str_lg.length();
    for (i = 0; i < len_lg; i++)
        str_lg[i] = std_str_lg[i];
    str_lg[len_lg] = '\0';

    int len_rg = (int)std_str_rg.length();
    for (i = 0; i < len_rg; i++)
        str_rg[i] = std_str_rg[i];
    str_rg[len_rg] = '\0';
    trim(str);
}
void TableOfValues::on_pushButton_clicked() {
    SetStr();
    int i;
    bool flag = 0;
    transform(str, &flag);
    if (isStrToFloat(str_lg) && isStrToFloat(str_rg)) {
        sscanf(str_lg, "%lf", &xmin);
        sscanf(str_rg, "%lf", &xmax);
        if (valid_str(str) != 0 || flag || strlen(str) == 0 || xmin >= xmax) {
            QMessageBox msgBox(QMessageBox::Information,
                               "GROW", "Invalid expression entered or incorrect range.",
                               QMessageBox::Ok);
            msgBox.exec();
        } else {
            ui->lineEdit->setReadOnly(true);
            ui->lineEdit_2->setReadOnly(true);
            ui->lineEdit_3->setReadOnly(true);
            double dx = (xmax - xmin) / 19, x;
            model = new QStandardItemModel(10, 2, this);
            ui->tableView->setModel(model);
            model->setHeaderData(0, Qt::Horizontal, "X");
            model->setHeaderData(1, Qt::Horizontal, "Y");
            model->setRowCount(20);
            ui->tableView->setEditTriggers(QTableView::NoEditTriggers);
            ui->tableView->setColumnWidth(0, 115);
            ui->tableView->setColumnWidth(1, 115);
            QModelIndex index;
            for (i = 0, x = xmin; i < 20; ++i, x += dx) {
                index = model->index(i, 0);
                model->setData(index, x);
                index = model->index(i, 1);
                head = parse(str);
                tail = get_tail(head);
                model->setData(index, calculate(tail, x));
            }
        }
    } else {
        QMessageBox msgBox(QMessageBox::Information,
                           "GROW", "Incorrect range.",
                           QMessageBox::Ok);
        msgBox.exec();
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
