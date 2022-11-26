#include "integralwindow.h"
#include "ui_integralwindow.h"

IntegralWindow::IntegralWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IntegralWindow)
{
    ui->setupUi(this);
    setWindowTitle("GROW");
    scene = new QGraphicsScene;
    ui->graphicsView->setScene(scene);
    pen.setColor(Qt::red);
    pen.setWidth(2);
    builtGraphFlag = false;
    ok_lg = false;
    ok_rg = false;

    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    setFixedSize(QSize(800, 550));
    ui->progressBar->setValue(0);
    ui->lineEdit_4->setReadOnly(true);
}

IntegralWindow::~IntegralWindow() {
    delete ui;
}

void IntegralWindow::load(QString _lineEdit) {
    ui->lineEdit->setText(_lineEdit);
}

double IntegralWindow::IntegralCalculate(bool *flag) {
    double eps = 0.0001, s = 0, s1 = eps + 1, dx;
    Point point;
    int n = 16;
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
    s = round(s * 1000) / 1000;
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
            QMessageBox msgBox(QMessageBox::Warning,
                               "GROW", "Неверное выражение либо неверно задан диапазон.",
                               QMessageBox::Ok);
            msgBox.exec();
        } else {
            bool flag = false;
            builtGraphFlag = true;
            for (int i = 1; i < 51; ++i) {
                ui->progressBar->setValue(i);

            }
            double result = IntegralCalculate(&flag);

            if (flag) {
                ui->lineEdit_4->setText("Не определен");
                ui->progressBar->setValue(0);
            } else {
                ui->lineEdit_4->setText(QString::number(result));

                plot.setXMin(a - 1);
                plot.setXMax(b + 1);

                plot.setKXY();
                plot.setXY();

                plot.plotGraph(str, scene, pen, true);
                plot.brushGraph(scene, a, b);
                plot.plotGraphAxis(scene, pen);
                ui->progressBar->setValue(100);
            }
        }
    } else {
        QMessageBox msgBox(QMessageBox::Warning,
                           "GROW", "Неверно задан диапазон.",
                           QMessageBox::Ok);
        msgBox.exec();
    }
    ok_lg = ok_rg = false;
}

void IntegralWindow::on_pushButton_2_clicked() {
    scene->clear();
    ui->graphicsView->items().clear();
    str[0] = '\0';
    ui->lineEdit->setText("");
    ui->lineEdit_2->setText("");
    ui->lineEdit_3->setText("");
    ui->lineEdit_4->setText("");

    ui->progressBar->setValue(0);

    plot.setXMin(-10);
    plot.setXMax(10);

    plot.setYMin(-10);
    plot.setYMax(10);
}

void IntegralWindow::someLineEdited() {
    if (builtGraphFlag) {
        builtGraphFlag = false;
        scene->clear();
        ui->graphicsView->items().clear();
        ui->lineEdit_4->setText("");
        ui->progressBar->setValue(0);
    }
}
void IntegralWindow::on_lineEdit_textEdited(const QString &arg1) {
    someLineEdited();
}

void IntegralWindow::on_lineEdit_2_textEdited(const QString &arg1) {
    someLineEdited();
}

void IntegralWindow::on_lineEdit_3_textEdited(const QString &arg1) {
    someLineEdited();
}
