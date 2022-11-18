#include "derivativewindow.h"
#include "ui_derivativewindow.h"

DerivativeWindow::DerivativeWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DerivativeWindow)
{
    ui->setupUi(this);
    setWindowTitle("GROW");
    ui->pushButton_2->setEnabled(false);
    scene = new QGraphicsScene;
    ui->graphicsView->setScene(scene);
    pen.setColor(Qt::red);
    pen.setWidth(2);
    setFixedSize(QSize(850,530));
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
}

DerivativeWindow::~DerivativeWindow() {
    delete ui;
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

    if (result.flag_division_by_zero || result.flag_scope_definition)
        ui->lineEdit_4->setText("Нет");
    else
        ui->lineEdit_4->setText(QString::number(round(1000000 * result.y) / 1000000));
}


void DerivativeWindow::SetStr() {
    string std_str = ui->lineEdit->text().toStdString();
    int len = (int)std_str.length();
    for (int i = 0; i < len; i++)
        str[i] = std_str[i];
    str[len] = '\0';
    trim(str);
}
void DerivativeWindow::PlotGraphAxis(double x0, double y0) {
    QString str_value_point;
    int i = 0;
    double x, temp;
    if (y0 >= 5 && y0 <= SCREENH - 5) {
        scene->addLine(260, y0, 742, y0, QPen(Qt::black));
        double dx = (xmax - xmin) / 20;
        for (i = 260, x = xmin; i < 742; i += 24, x += dx) {
            QGraphicsTextItem *item = new QGraphicsTextItem;
            str_value_point.setNum(round(x * 10) / 10);
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
            temp = round(y * 1000) / 1000;
            str_value_point.setNum(temp);
            item->setHtml(str_value_point);
            item->setPos(250 + x0, i - 12);
            if (temp != 0) {
                scene->addItem(item);
                scene->addEllipse(250 + x0, i, 2, 2, pen);
            }
        }
    }
}
void DerivativeWindow::PlotGraph(char *str) {
    double x, ky, kx = (xmax - xmin) / 479;
    int i;
    bool check = Qt::Unchecked; //ui->checkBox->checkState();
    for (i = 0, x = xmin; i < SCREENW - 1; ++i, x += kx) {
        head = parse(str);
        tail = get_tail(head);
        points[i] = calculate(tail, x);
    }
    if (check) {
        double temp;

        for (i = 0; points[i].flag_division_by_zero || points[i].flag_scope_definition; ++i);

        ymax = ymin = points[i].y;
        for (i = 0; i < SCREENW; ++i) {
            if (!points[i].flag_division_by_zero && !points[i].flag_scope_definition) {
                temp = points[i].y;
                if (ymax < temp)
                    ymax = temp;
                if (ymin > temp)
                    ymin = temp;
            }
        }
    }
    ky = (ymax - ymin) / 479;
    for (i = 0, x = xmin; i < SCREENW - 1; ++i, x += kx) {
        points[i].x = (round((x - xmin) / kx)) + 260;
        points[i].y = 490 - (round((points[i].y - ymin) / ky));
    }
    double y0 = 490 - (int)(round((0 - ymin) / ky)),
            x0 = (round((0 - xmin) / kx)) + 10;
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
//            calculateTable(count, radioButtonChecked_2);
            PlotGraph(str);
            ui->lineEdit->setReadOnly(true);
            ui->lineEdit_2->setReadOnly(true);
            ui->lineEdit_3->setReadOnly(true);
            ui->pushButton_2->setEnabled(true);
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
    scene->addRect(250, 0, 500, 500, QPen(Qt::white), QBrush(Qt::white));
    str[0] = '\0';
    ui->lineEdit->setText("");
    ui->lineEdit_2->setText("");
    ui->lineEdit_3->setText("");
    ui->lineEdit->setReadOnly(false);
    ui->lineEdit_2->setReadOnly(false);
    ui->lineEdit_3->setReadOnly(false);
    ui->pushButton->setEnabled(true);
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
