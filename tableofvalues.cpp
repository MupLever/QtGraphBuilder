#include "tableofvalues.h"
#include "ui_tableofvalues.h"

TableOfValues::TableOfValues(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TableOfValues)
{
    ui->setupUi(this);

    setWindowTitle("GROW");
    setFixedSize(QSize(650,400)); // фиксирует размер окна

    ok_lg =                false;
    ok_rg =                false;
    ok_count =             false;
    radioButtonChecked_1 = false;
    radioButtonChecked_2 = false;
    builtTableFlag = false;
    head = nullptr;
    tail = nullptr;

    xmin = -10.0;
    xmax =  10.0;

    count = 20;

    str[0] = '\0';
}

void TableOfValues::load(QString _lineEdit) {
    ui->lineEdit_3->setText(_lineEdit);
}

TableOfValues::~TableOfValues() {
    clearWindow();
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

    xmin = ui->lineEdit->text().toDouble(&ok_lg); // преобразование из строки в вещественное число
    xmax = ui->lineEdit_2->text().toDouble(&ok_rg); // преобразование из строки в вещественное число
    count = ui->lineEdit_4->text().toInt(&ok_count); // преобразование из строки в целое число

    // если нажат checkbox, то вычисляется всего одно значение
    if (ui->checkBox->isChecked()) {
        count = 1;
        xmax = xmin;
    }
}
void TableOfValues::calculateTable(int count, bool options) {
    int i = 0;

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

        // если выбрано значние производной функции
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
            builtTableFlag = true;
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
    ui->lineEdit->setText("");
    ui->lineEdit_2->setText("");
    ui->lineEdit_3->setText("");
    ui->lineEdit_4->setText("");
    if (builtTableFlag)
        delete model;
    radioButtonChecked_1 = false;
    radioButtonChecked_2 = false;
    builtTableFlag = false;
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
}
// Выбрана функция
void TableOfValues::on_radioButton_clicked() {
    if (radioButtonChecked_2) {
        ui->radioButton_2->setChecked(Qt::Unchecked);
        if (builtTableFlag)
            calculateTable(count, false);
        radioButtonChecked_2 = false;
        radioButtonChecked_1 = true;
    }
}

// Выбрана производная
void TableOfValues::on_radioButton_2_clicked() {
    if (radioButtonChecked_1) {
        ui->radioButton->setChecked(Qt::Unchecked);
        if (builtTableFlag)
            calculateTable(count, false);
        radioButtonChecked_1 = false;
        radioButtonChecked_2 = true;
    }
}
void TableOfValues::someLineEdited() {
    if (builtTableFlag) {
        builtTableFlag = false;
        delete model;
    }
}
void TableOfValues::on_lineEdit_3_textEdited(const QString &arg1) {
    someLineEdited();
}

void TableOfValues::on_lineEdit_textEdited(const QString &arg1) {
    someLineEdited();
}

void TableOfValues::on_lineEdit_2_textEdited(const QString &arg1) {
    someLineEdited();
}

void TableOfValues::on_lineEdit_4_textEdited(const QString &arg1) {
    someLineEdited();
}
