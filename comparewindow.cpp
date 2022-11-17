#include "comparewindow.h"
#include "ui_comparewindow.h"

CompareWindow::CompareWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CompareWindow) {
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
    setFixedSize(QSize(820,580));
}

CompareWindow::~CompareWindow() {
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
void CompareWindow::PlotGraphAxis(double x0, double y0) {
    QString str_value_point;
    int i = 0;
    double x, temp;
    if (y0 >= 5 && y0 <= SCREENH - 5) {
        scene->addLine(260, y0, 742, y0, QPen(Qt::black));
        double dx = (xmax - xmin) / 20;
        for (i = 260, x = xmin; i < 742; i += 24, x += dx) {
            QGraphicsTextItem *item = new QGraphicsTextItem;
            str_value_point.setNum(x);
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
void CompareWindow::PlotGraph() {
    double x, ky, kx = (xmax - xmin) / 479;
    int i;
    bool check = ui->checkBox->checkState();
    for (i = 0, x = xmin; i < SCREENW; ++i, x += kx) {
        head1 = parse(str_func1);
        tail1 = get_tail(head1);
        screen_func1[i] = calculate(tail1, x);

        head2 = parse(str_func2);
        tail2 = get_tail(head2);
        screen_func2[i] = calculate(tail2, x);
    }
    if (check) {
        ymax = ymin = screen_func1[0].y;
        for (i = 1; i < SCREENW; ++i){
            if (ymax < screen_func1[i].y)
                ymax = screen_func1[i].y;

            if (ymin > screen_func1[i].y)
                ymin = screen_func1[i].y;

            if (ymax < screen_func2[i].y)
                ymax = screen_func2[i].y;

            if (ymin > screen_func2[i].y)
                ymin = screen_func2[i].y;
        }
    }
    ky = (ymax - ymin) / 479;
    for (i = 0, x = xmin; i < SCREENW; i++, x += kx) {
        screen_func1[i].x = (round((x - xmin) / kx)) + 260;
        screen_func1[i].y = 490 - (round((screen_func1[i].y - ymin) / ky));
        screen_func2[i].x = (round((x - xmin) / kx)) + 260;
        screen_func2[i].y = 490 - (round((screen_func2[i].y - ymin) / ky));
    }
    double y0 = 490 - (int)(round((0 - ymin) / ky)),
            x0 = (int)(round((0 - xmin) / kx)) + 10;
    PlotGraphAxis(x0, y0);
    for (i = 0; i < SCREENW - 1; ++i) {
        if (!screen_func1[i].flag_scope_definition &&
            !screen_func1[i].flag_division_by_zero &&
            !screen_func1[i + 1].flag_scope_definition &&
            !screen_func1[i + 1].flag_division_by_zero &&
            (fabs(screen_func1[i].y - screen_func1[i + 1].y) < 100) &&
            !screen_func2[i].flag_scope_definition &&
            !screen_func2[i].flag_division_by_zero &&
            !screen_func2[i + 1].flag_scope_definition &&
            !screen_func2[i + 1].flag_division_by_zero &&
            (fabs(screen_func2[i].y - screen_func2[i + 1].y) < 100) &&
            screen_func1[i].y >= 0 && screen_func1[i].y <= 500 &&
            screen_func1[i + 1].y >= 0 && screen_func1[i + 1].y <= 500 &&
            screen_func1[i].x >= 250 && screen_func1[i].x <= 750 &&
            screen_func1[i + 1].x >= 250 && screen_func1[i + 1].x <= 750 &&
            screen_func2[i].y >= 0 && screen_func2[i].y <= 500 &&
            screen_func2[i + 1].y >= 0 && screen_func2[i + 1].y <= 500 &&
            screen_func2[i].x >= 250 && screen_func2[i].x <= 750 &&
            screen_func2[i + 1].x >= 250 && screen_func2[i + 1].x <= 750) {
                scene->addLine(screen_func1[i].x, screen_func1[i].y, screen_func1[i + 1].x, screen_func1[i + 1].y, pen1);
                scene->addLine(screen_func2[i].x, screen_func2[i].y, screen_func2[i + 1].x, screen_func2[i + 1].y, pen2);
        }
    }
}
void CompareWindow::on_pushButton_clicked() {
    bool flag1 = false;
    bool flag2 = false;
    SetStr();
    transform(str_func1, &flag1);
    transform(str_func2, &flag2);
    xmin = ui->lineEdit_3->text().toDouble(&ok_lg);
    xmax = ui->lineEdit_4->text().toDouble(&ok_rg);
    if (ok_lg && ok_rg && xmax > xmin) {
        if (valid_str(str_func1) != 0 ||
            flag1 ||
            strlen(str_func1) == 0) {
            QMessageBox msgBox(QMessageBox::Information,
                               "GROW", "Первое выражение содержит ошибку!",
                               QMessageBox::Ok);
            msgBox.exec();
        } else if (valid_str(str_func2) != 0 ||
                   flag2 ||
                   strlen(str_func2) == 0) {
            QMessageBox msgBox(QMessageBox::Information,
                               "GROW", "Второе выражение содержит ошибку!",
                               QMessageBox::Ok);
            msgBox.exec();
        } else {
            PlotGraph();
            ui->lineEdit->setReadOnly(true);
            ui->lineEdit_2->setReadOnly(true);
            ui->lineEdit_3->setReadOnly(true);
            ui->lineEdit_4->setReadOnly(true);
            ui->checkBox->setEnabled(true);
            ui->pushButton->setEnabled(false);
            ui->pushButton_2->setEnabled(true);
        }
    } else {
        QMessageBox msgBox(QMessageBox::Information,
                           "GROW", "Неверно задан диапазон!\nПомните, что граница задаются вещественными числами и правая граница должна быть строго больше левой.",
                           QMessageBox::Ok);
        msgBox.exec();
    }
    ok_lg = ok_rg = false;
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
    ui->lineEdit_3->setText("");
    ui->lineEdit_4->setText("");
    ui->lineEdit->setReadOnly(false);
    ui->lineEdit_2->setReadOnly(false);
    ui->lineEdit_3->setReadOnly(false);
    ui->lineEdit_4->setReadOnly(false);
    ui->checkBox->setEnabled(false);
    ui->pushButton->setEnabled(true);
    ui->pushButton_2->setEnabled(false);
}
