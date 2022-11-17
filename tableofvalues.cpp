#include "tableofvalues.h"
#include "ui_tableofvalues.h"

TableOfValues::TableOfValues(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TableOfValues)
{
    ui->setupUi(this);
    setWindowTitle("GROW");
    setFixedSize(QSize(650,400));
    ui->pushButton_3->setEnabled(false);
}

TableOfValues::~TableOfValues() {
    delete ui;
}

void TableOfValues::on_pushButton_2_clicked() {
    close();
}
void TableOfValues::SetAtributes() {
    int i;
    std::string std_str = ui->lineEdit_3->text().toStdString();
    int len = (int)std_str.length();
    for (i = 0; i < len; i++)
        str[i] = std_str[i];
    str[len] = '\0';
    trim(str);

    xmin = ui->lineEdit->text().toDouble(&ok_lg);
    xmax = ui->lineEdit_2->text().toDouble(&ok_rg);
    count = ui->lineEdit_4->text().toInt(&ok_count);
    if (ui->checkBox->isChecked()) {
        count = 1;
        xmax = xmin;
    }
}
void TableOfValues::calculateTable(int count, bool options) {
    int i = 0;
    ui->lineEdit->setReadOnly(true);
    ui->lineEdit_2->setReadOnly(true);
    ui->lineEdit_3->setReadOnly(true);
    ui->lineEdit_4->setReadOnly(true);

    double dx = (xmax - xmin) / (count - 1), x;

    Point point;
    model = new QStandardItemModel(count, 2, this);
    model->setHeaderData(0, Qt::Horizontal, "X");
    if (ui->radioButton_2->isChecked())
        model->setHeaderData(1, Qt::Horizontal, "f(x)'");
    else if(ui->radioButton->isChecked())
        model->setHeaderData(1, Qt::Horizontal, "Y");
    model->setRowCount(count);

    ui->tableView->setModel(model);
    ui->tableView->setEditTriggers(QTableView::NoEditTriggers);
    ui->tableView->setColumnWidth(0, 130);
    ui->tableView->setColumnWidth(1, 130);


    QModelIndex index;
    Point f1, f2;
    for (i = 0, x = xmin; i < count; ++i, x += dx) {
        index = model->index(i, 0);
        model->setData(index, x);
        index = model->index(i, 1);
        head = parse(str);
        tail = get_tail(head);
        if (options) {
            f1 = calculate(tail, (x + 0.000001));

            head = parse(str);
            tail = get_tail(head);
            f2 = calculate(tail, (x - 0.000001));

            point.y = (f1.y - f2.y) * 500000;
            if (f1.flag_division_by_zero ||
                f2.flag_scope_definition ||
                f2.flag_division_by_zero ||
                f1.flag_scope_definition) {
                    point.flag_division_by_zero = true;
            }
        } else {
            point = calculate(tail, x);
        }
        if (point.flag_division_by_zero || point.flag_scope_definition)
            model->setData(index, "Не определен");
        else
            model->setData(index, point.y);
    }
}
void TableOfValues::on_pushButton_clicked() {
    SetAtributes();
    bool flag = 0;
    transform(str, &flag);
    radioButtonChecked_1 = ui->radioButton->isChecked();
    radioButtonChecked_2 = ui->radioButton_2->isChecked();
    if (ok_lg && (ui->checkBox->isChecked() || (ok_rg && ok_count))) {
        if (valid_str(str) != 0 ||
            flag ||
            strlen(str) == 0) {
            QMessageBox msgBox(QMessageBox::Information,
                               "GROW", "Выражение содержит ошибку.\n"
                                       "Используйте функции, определенные в руководстве пользователя.",
                               QMessageBox::Ok);
            msgBox.exec();
        } else if (xmin > xmax ||
            (xmin == xmax && (count != 1))) {
            QMessageBox msgBox(QMessageBox::Information,
                               "GROW", "Неверно задан диапазон.\n"
                                       "Помните, что левая граница не может быть больше правой!",
                               QMessageBox::Ok);
            msgBox.exec();
        } else if (count <= 0) {
            QMessageBox msgBox(QMessageBox::Information,
                               "GROW", "Неверно задано количество.\n"
                                       "Помните, что количество задается положительным числом больше 0.",
                               QMessageBox::Ok);
            msgBox.exec();
        }  else if (!(ui->radioButton->isChecked() || ui->radioButton_2->isChecked())) {
            QMessageBox msgBox(QMessageBox::Information,
                               "GROW", "Не выбрана опция расчета таблицы.\nВыберите либо значение функции, либо значений производной фнкции.",
                               QMessageBox::Ok);
            msgBox.exec();
        } else {
            calculateTable(count, radioButtonChecked_2);
            ui->pushButton_3->setEnabled(true);
            ui->pushButton->setEnabled(false);
        }
    } else {
        QMessageBox msgBox(QMessageBox::Information,
                           "GROW", "Неверно задан диапазон или количество.\n"
                                   "Диапазон задается двумя вещественными числами, а количество - положительным число!",
                           QMessageBox::Ok);
        msgBox.exec();
    }
    ok_lg = ok_rg = ok_count = false;
}
void TableOfValues::clearWindow() {
    ui->lineEdit->setReadOnly(false);
    ui->lineEdit_2->setReadOnly(false);
    ui->lineEdit_3->setReadOnly(false);
    ui->lineEdit_4->setReadOnly(false);
    ui->lineEdit->setText("");
    ui->lineEdit_2->setText("");
    ui->lineEdit_3->setText("");
    ui->lineEdit_4->setText("");
    delete model;
    radioButtonChecked_1 = false;
    radioButtonChecked_2 = false;
    ui->pushButton->setEnabled(true);
    ui->pushButton_3->setEnabled(false);
}
void TableOfValues::on_pushButton_3_clicked() {
    clearWindow();
}

void TableOfValues::on_checkBox_stateChanged(int arg1) {
    if (arg1 == Qt::Checked) {
        ui->lineEdit_2->hide();
        ui->lineEdit_4->hide();
        ui->label->setText("Введите значение X");
        ui->label_2->hide();
        ui->label_3->hide();
    } else if (arg1 == Qt::Unchecked) {
        ui->lineEdit_2->show();
        ui->lineEdit_4->show();
        ui->label->setText("Левая граница");
        ui->label_2->show();
        ui->label_3->show();
    }
    if (radioButtonChecked_1 || radioButtonChecked_2) {
        ui->lineEdit->setReadOnly(false);
        ui->lineEdit_2->setReadOnly(false);
        ui->lineEdit_3->setReadOnly(false);
        ui->lineEdit_4->setReadOnly(false);
        ui->pushButton_3->setEnabled(false);
        ui->pushButton->setEnabled(true);
        delete model;
    }
}
// Выбрана функция
void TableOfValues::on_radioButton_clicked() {
    if (radioButtonChecked_2) {
        ui->radioButton_2->setChecked(Qt::Unchecked);
        calculateTable(count, Qt::Unchecked);
        radioButtonChecked_2 = false;
        radioButtonChecked_1 = true;
    }
}

// Выбрана производная
void TableOfValues::on_radioButton_2_clicked() {
    if (radioButtonChecked_1) {
        ui->radioButton->setChecked(Qt::Unchecked);
        calculateTable(count, Qt::Checked);
        radioButtonChecked_1 = false;
        radioButtonChecked_2 = true;
    }
}
