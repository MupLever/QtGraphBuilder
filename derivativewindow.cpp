#include "derivativewindow.h"
#include "ui_derivativewindow.h"

DerivativeWindow::DerivativeWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DerivativeWindow)
{
    ui->setupUi(this);
    setWindowTitle("GROW");
    setFixedSize(QSize(850,530)); // фиксрование размеров окна

    ui->lineEdit_4->setReadOnly(true);
    ui->lineEdit_5->setReadOnly(true);
    scene = new QGraphicsScene;
    ui->graphicsView->setScene(scene);

    pen.setColor(Qt::red);
    pen.setWidth(2);

    ok_lg =                false;
    ok_rg =                false;
    radioButtonChecked_1 = false;
    radioButtonChecked_2 = false;
    builtGraphFlag = false;

    xmin = -10.0;
    xmax =  10.0;
    phi =   0.5 * (1.0 + sqrt(5.0));

    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
}

DerivativeWindow::~DerivativeWindow() {
    scene->clear();
    ui->graphicsView->items().clear();
    delete ui;
}

void DerivativeWindow::load(QString _lineEdit) {
    ui->lineEdit->setText(_lineEdit);
}

void DerivativeWindow::calculateDerivative() {
    double eps = 0.000001, a = xmin, b = xmax + 0.000002;
    Point point1, point2, result;
    while (fabs(b - a) > eps) {
        head = parse(str);
        tail = get_tail(head);
        point1 = calculate(tail,(b - (b - a) / phi));

        head = parse(str);
        tail = get_tail(head);
        point2 = calculate(tail, (a + (b - a) / phi));
        if (ui->radioButton->isChecked() == point1.y >= point2.y )
            a = point1.x;
        else
            b = point2.x;
    }
    head = parse(str);
    tail = get_tail(head);

    result = calculate(tail, 0.5 * (b + a));

    if (result.flag_division_by_zero || result.flag_scope_definition) {
        ui->lineEdit_4->setText("Нет");
        ui->lineEdit_5->setText("Нет");
    } else {
        plot.addCircle(scene, result.x, result.y);
        ui->lineEdit_4->setText(QString::number(round(100000 * result.x) / 100000));
        ui->lineEdit_5->setText(QString::number(round(1000000 * result.y) / 1000000));
    }
}


void DerivativeWindow::SetStr() {
    string std_str = ui->lineEdit->text().toStdString();
    int len = (int)std_str.length();
    for (int i = 0; i < len; i++)
        str[i] = std_str[i];
    str[len] = '\0';
    trim(str);
}

void DerivativeWindow::on_pushButton_3_clicked() {
    close();
}

// build
void DerivativeWindow::on_pushButton_clicked() {
    SetStr();
    bool flag = 0;
    transform(str, &flag);

    xmin = ui->lineEdit_2->text().toDouble(&ok_lg);
    xmax = ui->lineEdit_3->text().toDouble(&ok_rg);

    radioButtonChecked_1 = ui->radioButton->isChecked();
    radioButtonChecked_2 = ui->radioButton_2->isChecked();
    if (ok_lg && ok_rg) {
        if (valid_str(str) != 0 ||
            flag ||
            strlen(str) == 0) {
            QMessageBox msgBox(QMessageBox::Information,
                               "GROW", "Выражение содержит ошибку.\n"
                                       "Используйте функции, определенные в руководстве пользователя.",
                               QMessageBox::Ok);
            msgBox.exec();
        } else if (xmin >= xmax) {
            QMessageBox msgBox(QMessageBox::Information,
                               "GROW", "Неверно задан диапазон.\n"
                                       "Помните, что левая граница не может быть больше правой!",
                               QMessageBox::Ok);
            msgBox.exec();
        } else if (!(ui->radioButton->isChecked() || ui->radioButton_2->isChecked())) {
            QMessageBox msgBox(QMessageBox::Information,
                               "GROW", "Не выбрана опция поиска.\nУкажите, что вы хотите найти: максимум или минимум.",
                               QMessageBox::Ok);
            msgBox.exec();
        } else {
            plot.setXMin(xmin);
            plot.setXMax(xmax);
            plot.plotGraph(str, scene, pen, true);
            plot.plotGraphAxis(scene, pen);
            builtGraphFlag = true;
            calculateDerivative();
        }
    } else {
        QMessageBox msgBox(QMessageBox::Information,
                           "GROW", "Неверно задан диапазон или количество.\n"
                                   "Диапазон задается двумя вещественными числами!",
                           QMessageBox::Ok);
        msgBox.exec();
    }
    ok_lg = ok_rg = false;
}


// clear
void DerivativeWindow::on_pushButton_2_clicked() {
    scene->clear();
    ui->graphicsView->items().clear();
    str[0] = '\0';
    ui->lineEdit->setText("");
    ui->lineEdit_2->setText("");
    ui->lineEdit_3->setText("");
    ui->lineEdit_4->setText("");
    ui->lineEdit_5->setText("");
}

void DerivativeWindow::on_radioButton_clicked() {
    if (radioButtonChecked_2) {
        ui->radioButton_2->setChecked(Qt::Unchecked);
        calculateDerivative();
        radioButtonChecked_2 = false;
        radioButtonChecked_1 = true;
    }
}

void DerivativeWindow::on_radioButton_2_clicked() {
    if (radioButtonChecked_1) {
        ui->radioButton->setChecked(Qt::Unchecked);
        calculateDerivative();
        radioButtonChecked_1 = false;
        radioButtonChecked_2 = true;
    }
}

void DerivativeWindow::someLineEdited() {
    if (builtGraphFlag) {
        builtGraphFlag = false;
        scene->clear();
        ui->graphicsView->items().clear();
        ui->lineEdit_4->setText("");
        ui->lineEdit_5->setText("");
    }
}

void DerivativeWindow::on_lineEdit_textEdited(const QString &arg1) {
    someLineEdited();
}

void DerivativeWindow::on_lineEdit_2_textEdited(const QString &arg1) {
    someLineEdited();
}

void DerivativeWindow::on_lineEdit_3_textEdited(const QString &arg1) {
    someLineEdited();
}
