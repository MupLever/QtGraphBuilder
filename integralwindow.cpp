#include "integralwindow.h"
#include "ui_integralwindow.h"

IntegralWindow::IntegralWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IntegralWindow)
{
    ui->setupUi(this);
    setWindowTitle("GROW");
    ui->pushButton_2->setEnabled(false);
    ui->lineEdit_4->setReadOnly(true);
    scene = new QGraphicsScene;
    ui->graphicsView->setScene(scene);
    pen.setColor(Qt::red);
    pen.setWidth(2);

    ok_lg = false;
    ok_rg = false;

    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    setFixedSize(QSize(800, 550));
}

IntegralWindow::~IntegralWindow() {
    delete ui;
}
double IntegralWindow::IntegralCalculate(bool *flag) {
    double eps = 0.00001, s = 0, s1 = eps + 1, dx;
    Point point;
    int n = 2;
    while (fabs(s1 - s) > eps) {
        n *= 2;
        dx = (b - a) / n;
        s1 = s;
        s = 0;
        for (double x = a; x < b && !*flag; x+= dx) {
            head = parse(str);
            tail = get_tail(head);
            point = (calculate(tail, x));
            if (point.flag_division_by_zero || point.flag_scope_definition)
                *flag = true;
            else
                s += point.y;
        }
        s *= dx;
    }
    s = round(s * 10000) / 10000;
    return s;
}
void IntegralWindow::SetStr() {
    int i;
    std::string std_str = ui->lineEdit->text().toStdString();
    int len = (int)std_str.length();
    for (i = 0; i < len; ++i)
        str[i] = std_str[i];
    str[len] = '\0';

    trim(str);
}

void IntegralWindow::on_pushButton_3_clicked() {
    close();
}

void IntegralWindow::on_pushButton_clicked() {
    bool flag = 0;
    SetStr();
    transform(str, &flag);
    a = ui->lineEdit_2->text().toDouble(&ok_lg);
    b = ui->lineEdit_3->text().toDouble(&ok_rg);
    if (ok_lg && ok_rg) {
        if (valid_str(str) != 0 ||
            flag ||
            strlen(str) == 0 ||
            a >= b) {
            QMessageBox msgBox(QMessageBox::Information,
                               "GROW", "Неверное выражение либо неверно задан диапазон.",
                               QMessageBox::Ok);
            msgBox.exec();
        } else {
            bool flag = false;
            ui->lineEdit->setReadOnly(true);
            ui->lineEdit_2->setReadOnly(true);
            ui->lineEdit_3->setReadOnly(true);
            ui->pushButton->setEnabled(false);
            ui->pushButton_2->setEnabled(true);
            double result = IntegralCalculate(&flag);
            if (flag) {
                ui->lineEdit_4->setText("Не определен");
            } else {
                ui->lineEdit_4->setText(QString::number(result));

                plot.setXMin(a - 1);
                plot.setXMax(b + 1);

                plot.setKXY();
                plot.setXY();

                plot.plotGraph(str, scene, pen, true);
                plot.brushGraph(scene, a, b);
                plot.plotGraphAxis(scene, pen);
            }
        }
    } else {
        QMessageBox msgBox(QMessageBox::Information,
                           "GROW", "Неверно задан диапазон.",
                           QMessageBox::Ok);
        msgBox.exec();
    }
    ok_lg = ok_rg = false;
}

void IntegralWindow::on_pushButton_2_clicked() {
    scene->addRect(250, 0, 500, 500, QPen(Qt::white), QBrush(Qt::white));
    str[0] = '\0';
    ui->lineEdit->setText("");
    ui->lineEdit_2->setText("");
    ui->lineEdit_3->setText("");
    ui->lineEdit_4->setText("");
    ui->lineEdit->setReadOnly(false);
    ui->lineEdit_2->setReadOnly(false);
    ui->lineEdit_3->setReadOnly(false);
    ui->pushButton->setEnabled(true);

    plot.setXMin(-10);
    plot.setXMax(10);

    plot.setYMin(-10);
    plot.setYMax(10);
}
