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
}

IntegralWindow::~IntegralWindow()
{
    delete ui;
}
void IntegralWindow::IntegralCalculate() {
    double a = 0, b = 2, eps = 0.00001, s = 0, s1 = eps + 1, dx;
    int n = 2;
    while (fabs(s1 - s) > eps) {
        n *= 2;
        dx = (b - a) / n;
        s1 = s;
        s = 0;
        for (double x = a; x < b; x+= dx) {
            head = parse(str);
            tail = get_tail(head);
            s += calculate(tail, x);
        }
        s *= dx;
    }
    s = round(s * 10000) / 10000;
    ui->lineEdit_4->setText(QString::number(s));
}
void IntegralWindow::SetStr() {
    std::string std_str = ui->lineEdit->text().toStdString();
    int len = (int)std_str.length();
    for (int i = 0; i < len; i++)
        str[i] = std_str[i];
    str[len] = '\0';
    trim(str);
}

void IntegralWindow::PlotGraph(char *str) {
    double x, ky, kx = (xmax - xmin) / (SCREENW - 1);
    int i;
    //bool check = ui->checkBox->checkState();
    for (i = 0, x = xmin; i < SCREENW; ++i, x += kx) {
        head = parse(str);
        tail = get_tail(head);
        f[i] = calculate(tail, x);
    }
//    if (check) {
//        ymax = ymin = f[0];
//        for (i = 1; i < SCREENW; ++i){
//            if (ymax < f[i])
//                ymax = f[i];
//            if (ymin > f[i])
//                ymin = f[i];
//        }
//    }
    ky = (ymax - ymin) / (SCREENH - 1);
    for (i = 0, x = xmin; i < SCREENW; i++, x += kx) {
        screen[i].x = (round((x - xmin) / kx)) + 250;
        screen[i].y = SCREENH - (round((f[i] - ymin) / ky)) - 1;
    }
    double y0 = SCREENH - (int)(round((0 - ymin) / ky)) - 1,
            x0 = (int)(round((0 - xmin) / kx));
    QString str_value_point;

    int border = (round((2 - xmin) / kx));
    for (i = x0; i < border; ++i) {
        scene->addRect(screen[i].x, y0, screen[i + 1].x - screen[i].x, screen[i].y - y0, QPen(Qt::green), QBrush(Qt::green));
    }

    if (y0 >= 10 && y0 <= 495) {
        scene->addLine(250, y0, 750, y0, QPen(Qt::black));
        double dx = (xmax - xmin) / 20;
        for (i = 275, x = xmin + dx; i < 726; i += 25, x += dx) {
            QGraphicsTextItem *item = new QGraphicsTextItem;
            str_value_point.setNum(x);
            item->setHtml(str_value_point);
            item->setPos(i - 10, y0 - 5);
            if ((int)x) {
                scene->addItem(item);
                scene->addEllipse(i, y0, 2, 2, pen);
            }
        }
    }
    if (x0 >= 5 && x0 <= 495) {
        scene->addLine(x0 + 250, 0, x0 + 250, 500 , QPen(Qt::black));
        double y, dy = (ymax - ymin) / 20;
        for (i = 25, y = ymax - dy; i < 500; i += 25, y -= dy) {
            QGraphicsTextItem *item = new QGraphicsTextItem;
            str_value_point.setNum(y);
            item->setHtml(str_value_point);
            item->setPos(250 + x0, i - 12);
            if ((int)y) {
                scene->addItem(item);
                scene->addEllipse(250 + x0, i, 2, 2, pen);
            }
        }
    }
    for (i = 0; i < SCREENW - 1; ++i) {
        if (screen[i].y >= 0 && screen[i].y <= 500
                && screen[i + 1].y >= 0 && screen[i + 1].y <= 500
                && screen[i].x >= 250 && screen[i].x <= 750
                && screen[i + 1].x >= 250 && screen[i + 1].x <= 750)
            scene->addLine(screen[i].x, screen[i].y, screen[i + 1].x, screen[i + 1].y, pen);
    }
}

void IntegralWindow::on_pushButton_3_clicked() {
    close();
}

void IntegralWindow::on_pushButton_clicked() {
    bool flag = 0;
    SetStr();
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
        ui->pushButton->setEnabled(false);
//        ui->checkBox->setEnabled(true);
        ui->pushButton_2->setEnabled(true);
        PlotGraph(str);
        IntegralCalculate();
    }
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
