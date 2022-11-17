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
void IntegralWindow::PlotGraphAxis(double x0, double y0) {
    QString str_value_point;
    int i = 0;
    double x;
    if (y0 >= 5 && y0 <= SCREENH - 5) {
        scene->addLine(260, y0, 742, y0, QPen(Qt::black));
        double dx = (xmax - xmin) / 20;
        for (i = 260, x = xmin; i < 742; i += 24, x += dx) {
            QGraphicsTextItem *item = new QGraphicsTextItem;
            str_value_point.setNum((int)x);
            item->setHtml(str_value_point);
            item->setPos(i - 10, y0 - 5);
            scene->addItem(item);
            scene->addEllipse(i, y0, 2, 2, pen);
        }
    }
    if (x0 >= 5 && x0 <= SCREENW - 5) {
        double y, dy = (ymax - ymin) / 20;
        scene->addLine(x0 + 250, 10, x0 + 250, 492 , QPen(Qt::black));
        for (i = 10, y = ymax; i < 492; i += 24, y -= dy) {
            QGraphicsTextItem *item = new QGraphicsTextItem;
            str_value_point.setNum((int)y);
            item->setHtml(str_value_point);
            item->setPos(250 + x0, i - 12);
            if (round(y * 1000) / 1000 != 0) {
                scene->addItem(item);
                scene->addEllipse(250 + x0, i, 2, 2, pen);
            }
        }
    }
}
void IntegralWindow::PlotGraph(char *str) {
    xmin = xmin - (int)fabs(b - a);
    xmax = xmax + (int)fabs(b - a);
    double x, ky, kx = (xmax - xmin) / 479;
    int i;
    for (i = 0, x = xmin; i < SCREENW; ++i, x += kx) {
        head = parse(str);
        tail = get_tail(head);
        points[i] = calculate(tail, x);
    }
    ymax = ymin = points[0].y;
    for (i = 0; i < SCREENW - 1; ++i) {
        if (!points[i].flag_division_by_zero && !points[i].flag_scope_definition) {
            if (ymax < points[i].y)
                ymax = points[i].y;
            if (ymin > points[i].y)
                ymin = points[i].y;
        }
    }
    ky = (ymax - ymin) / 479;
    for (i = 0, x = xmin; i < SCREENW - 1; ++i, x += kx) {
        points[i].x = (round((x - xmin) / kx)) + 260;
        points[i].y = 490 - (round((points[i].y - ymin) / ky));
    }

    double y0 = 490 - (int)(round((0 - ymin) / ky)),
            x0 = (round((0 - xmin) / kx)) + 10;

    int right_border = (round((b - xmin) / kx)), left_border = (round((a - xmin) / kx));


    for (i = left_border; i < right_border && i < 490; ++i) {
        if (points[i].y >= 0 && points[i].y <= 500
                && points[i + 1].y >= 0 && points[i + 1].y <= 500)
            scene->addRect(points[i].x, y0, points[i + 1].x - points[i].x, points[i].y - y0, QPen(Qt::green), QBrush(Qt::green));
    }
    PlotGraphAxis(x0, y0);
    for (i = 0; i < SCREENW - 1; ++i) {
        if (!points[i].flag_scope_definition &&
            !points[i].flag_division_by_zero &&
            !points[i + 1].flag_scope_definition &&
            !points[i + 1].flag_division_by_zero &&
            (fabs(points[i].y - points[i + 1].y) < 100) &&
            points[i].y >= 0 && points[i].y <= 500 &&
            points[i + 1].y >= 0 && points[i + 1].y <= 500 &&
            points[i].x >= 250 && points[i].x <= 750 &&
            points[i + 1].x >= 250 && points[i + 1].x <= 750) {
                scene->addLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y, pen);
        }
    }
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
    //        ui->checkBox->setEnabled(true);
            ui->pushButton_2->setEnabled(true);
            double result = IntegralCalculate(&flag);
            if (flag) {
                ui->lineEdit_4->setText("Не определен");
            } else {
                ui->lineEdit_4->setText(QString::number(result));
                PlotGraph(str);
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
//    ui->checkBox->setEnabled(false);
}
