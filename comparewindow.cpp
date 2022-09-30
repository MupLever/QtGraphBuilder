#include "comparewindow.h"
#include "ui_comparewindow.h"

CompareWindow::CompareWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CompareWindow)
{
    ui->setupUi(this);
    setWindowTitle("GROW");
    ui->checkBox->setCheckState(Qt::Unchecked);
    ui->checkBox->setEnabled(false);
    ui->pushButton_2->setEnabled(false);
    scene = new QGraphicsScene;
    ui->graphicsView->setScene(scene);
    pen1.setColor(Qt::green);
    pen1.setWidth(2);
    pen2.setColor(Qt::blue);
    pen2.setWidth(2);
    pen3.setColor(Qt::black);
    pen3.setWidth(2);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
}

CompareWindow::~CompareWindow()
{
    delete ui;
}

void CompareWindow::on_pushButton_3_clicked() {
    close();
}
void CompareWindow::SetStr() {
    std::string std_str_func1 = ui->lineEdit->text().toStdString();
    std::string std_str_func2 = ui->lineEdit_2->text().toStdString();
    int len_func1 = (int)std_str_func1.length(), len_func2 = (int)std_str_func2.length(), i;

    for (i = 0; i < len_func1; i++)
        str_func1[i] = std_str_func1[i];
    str_func1[len_func1] = '\0';
    trim(str_func1);

    for (i = 0; i < len_func2; i++)
        str_func2[i] = std_str_func2[i];
    str_func2[len_func1] = '\0';
    trim(str_func2);
}
void CompareWindow::PlotGraph() {
    double x, ky, kx = (xmax - xmin) / (SCREENW - 1);
    int i;
    bool check = ui->checkBox->checkState();
    for (i = 0, x = xmin; i < SCREENW; ++i, x += kx) {
        head1 = parse(str_func1);
        tail1 = get_tail(head1);
        f1[i] = calculate(tail1, x);

        head2 = parse(str_func2);
        tail2 = get_tail(head2);
        f2[i] = calculate(tail2, x);
    }
    if (check) {
        ymax = ymin = f1[0];
        for (i = 1; i < SCREENW; ++i){
            if (ymax < f1[i])
                ymax = f1[i];
            if (ymin > f1[i])
                ymin = f1[i];
            if (ymax < f2[i])
                ymax = f2[i];
            if (ymin > f2[i])
                ymin = f2[i];
        }
    }
    ky = (ymax - ymin) / (SCREENH - 1);
    for (i = 0, x = xmin; i < SCREENW; i++, x += kx) {
        screen_func1[i].x = (round((x - xmin) / kx)) + 250;
        screen_func1[i].y = SCREENH - (round((f1[i] - ymin) / ky)) - 1;
        screen_func2[i].x = (round((x - xmin) / kx)) + 250;
        screen_func2[i].y = SCREENH - (round((f2[i] - ymin) / ky)) - 1;
    }
    double y0 = SCREENH - (int)(round((0 - ymin) / ky)) - 1,
            x0 = (int)(round((0 - xmin) / kx));
    QString str_value_point;
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
                scene->addEllipse(i, y0, 2, 2, pen3);
            }
        }
    }
    if (x0 >= 5 && x0 <= 495) {
        double y, dy = (ymax - ymin) / 20;
        scene->addLine(x0 + 250, 0, x0 + 250, 500 , QPen(Qt::black));
        for (i = 25, y = ymax - dy; i < 500; i += 25, y -= dy) {
            QGraphicsTextItem *item = new QGraphicsTextItem;
            str_value_point.setNum(y);
            item->setHtml(str_value_point);
            item->setPos(250 + x0, i - 12);
            if ((int)y) {
                scene->addItem(item);
                scene->addEllipse(250 + x0, i, 2, 2, pen3);
            }
        }
    }
    for (i = 0; i < SCREENW - 1; ++i) {
        if (screen_func1[i].y >= 0 && screen_func1[i].y <= 500
                && screen_func1[i + 1].y >= 0 && screen_func1[i + 1].y <= 500
                && screen_func1[i].x >= 250 && screen_func1[i].x <= 750
                && screen_func1[i + 1].x >= 250 && screen_func1[i + 1].x <= 750 &&
                screen_func2[i].y >= 0 && screen_func2[i].y <= 500
                && screen_func2[i + 1].y >= 0 && screen_func2[i + 1].y <= 500
                && screen_func2[i].x >= 250 && screen_func2[i].x <= 750
                && screen_func2[i + 1].x >= 250 && screen_func2[i + 1].x <= 750) {
            scene->addLine(screen_func1[i].x, screen_func1[i].y, screen_func1[i + 1].x, screen_func1[i + 1].y, pen1);
            scene->addLine(screen_func2[i].x, screen_func2[i].y, screen_func2[i + 1].x, screen_func2[i + 1].y, pen2);
        }
    }
}
void CompareWindow::on_pushButton_clicked() {
    bool flag = 0;
    SetStr();
    transform(str_func1, &flag);
    transform(str_func2, &flag);
    if (valid_str(str_func1) != 0 || flag || strlen(str_func1) == 0 || valid_str(str_func2) != 0 || strlen(str_func2) == 0) {
        QMessageBox msgBox(QMessageBox::Information,
                           "GROW", "Invalid expression entered.",
                           QMessageBox::Ok);
        msgBox.exec();
    } else {
        PlotGraph();
        ui->lineEdit->setReadOnly(true);
        ui->lineEdit_2->setReadOnly(true);
        ui->checkBox->setEnabled(true);
        ui->pushButton->setEnabled(false);
        ui->pushButton_2->setEnabled(true);
    }

}

void CompareWindow::on_checkBox_stateChanged(int arg1) {
    if (ui->lineEdit->text().length() != 0) {
        scene->addRect(250, 0, 500, 500, QPen(Qt::white), QBrush(Qt::white));
        ymax = 10;
        ymin = -10;
        xmin = -10;
        xmax = 10;
        PlotGraph();
    }
}

void CompareWindow::on_pushButton_2_clicked() {
    scene->addRect(250, 0, 500, 500, QPen(Qt::white), QBrush(Qt::white));
    str_func1[0] = '\0';
    str_func2[0] = '\0';
    ui->lineEdit->setText("");
    ui->lineEdit_2->setText("");
    ui->lineEdit->setReadOnly(false);
    ui->lineEdit_2->setReadOnly(false);
    ui->checkBox->setEnabled(false);
}
