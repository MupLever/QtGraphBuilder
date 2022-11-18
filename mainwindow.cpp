#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    setWindowTitle("GROW");
    ui->checkBox->setCheckState(Qt::Unchecked);
    ui->checkBox->setEnabled(false);
    ui->pushButton_2->setEnabled(false);
    ui->pushButton_3->setEnabled(false);
    ui->pushButton_4->setEnabled(false);
    ui->pushButton_5->setEnabled(false);
    ui->pushButton_6->setEnabled(false);
    ui->pushButton_7->setEnabled(false);
    ui->pushButton_8->setEnabled(false);
    scene = new QGraphicsScene;
    ui->graphicsView->setScene(scene);
    pen.setColor(Qt::red);
    pen.setWidth(2);
    setFixedSize(QSize(950,550));
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);

}

MainWindow::~MainWindow() {
    delete scene;
    delete ui;
}

void MainWindow::SetStr() {
    string std_str = ui->lineEdit->text().toStdString();
    int len = (int)std_str.length();
    for (int i = 0; i < len; i++)
        str[i] = std_str[i];
    str[len] = '\0';
    trim(str);
}
void MainWindow::PlotGraphAxis(double x0, double y0) {
    QString str_value_point;
    int i = 0;
    double x, temp;
    if (y0 >= 5 && y0 <= SCREENH - 5) {
        scene->addLine(260, y0, 742, y0, QPen(Qt::black));
        double dx = (xmax - xmin) / 20;
        for (i = 260, x = xmin; i < 742; i += 24, x += dx) {
            QGraphicsTextItem *item = new QGraphicsTextItem;
            str_value_point.setNum(round(x * 1000) / 1000);
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
void MainWindow::PlotGraph(char *str) {
    double x, ky, kx = (xmax - xmin) / 479;
    int i;
    bool check = ui->checkBox->checkState();
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

void MainWindow::on_pushButton_clicked() {
    bool flag = 0;
    char stroka[50];
    SetStr();
    strcpy(stroka, str);
    transform(str, &flag);
    if (valid_str(str) != 0 || flag || strlen(str) == 0) {
        QMessageBox msgBox(QMessageBox::Information,
                           "GROW", "Неверное выражение",
                           QMessageBox::Ok);
        msgBox.exec();
    } else {
        WriteFile(f_logs, stroka);
        ui->lineEdit->setReadOnly(true);
        ui->pushButton->setEnabled(false);
        ui->checkBox->setEnabled(true);
        ui->pushButton_2->setEnabled(true);
        ui->pushButton_3->setEnabled(true);
        ui->pushButton_4->setEnabled(true);
        ui->pushButton_5->setEnabled(true);
        ui->pushButton_6->setEnabled(true);
        ui->pushButton_7->setEnabled(true);
        ui->pushButton_8->setEnabled(true);
        //clock_t time_start = clock();
        PlotGraph(str);
        //clock_t time_end = clock();
        //double time_dif = (double)(time_end - time_start) / CLOCKS_PER_SEC;
        //printf("%lf\n", time_dif);
    }
}

void MainWindow::on_pushButton_2_clicked() {
    scene->clear();
    scene->addRect(250, 0, 500, 500, QPen(Qt::white), QBrush(Qt::white));
    str[0] = '\0';
    ui->checkBox->setEnabled(false);
    ui->lineEdit->setReadOnly(false);
    ui->pushButton->setEnabled(true);
    ui->pushButton_2->setEnabled(false);
    ui->pushButton_3->setEnabled(false);
    ui->pushButton_4->setEnabled(false);
    ui->pushButton_5->setEnabled(false);
    ui->pushButton_6->setEnabled(false);
    ui->pushButton_7->setEnabled(false);
    ui->pushButton_8->setEnabled(false);
    ui->lineEdit->setText("");
}

void MainWindow::on_pushButton_3_clicked() {
    scene->clear();
    scene->addRect(250, 0, 500, 500, QPen(Qt::white), QBrush(Qt::white));
    xmin -= 1;
    xmax -= 1;
    PlotGraph(str);
}

void MainWindow::on_pushButton_4_clicked() {
    scene->clear();
    scene->addRect(250, 0, 500, 500, QPen(Qt::white), QBrush(Qt::white));
    xmin += 1;
    xmax += 1;
    PlotGraph(str);
}

void MainWindow::on_pushButton_5_clicked() {
    scene->clear();
    scene->addRect(250, 0, 500, 500, QPen(Qt::white), QBrush(Qt::white));
    ymin += 1;
    ymax += 1;
    PlotGraph(str);
}

void MainWindow::on_pushButton_6_clicked() {
    scene->clear();
    scene->addRect(250, 0, 500, 500, QPen(Qt::white), QBrush(Qt::white));
    ymin -= 1;
    ymax -= 1;
    PlotGraph(str);
}

void MainWindow::on_pushButton_7_clicked(){
    scene->clear();
    scene->addRect(250, 0, 500, 500, QPen(Qt::white), QBrush(Qt::white));
    if (ymax - ymin > 10) {
        ymin += 1;
        ymax -= 1;
    }
    if (xmax - xmin > 10) {
        xmin += 1;
        xmax -= 1;
    }
    PlotGraph(str);
}

void MainWindow::on_pushButton_8_clicked() {
    scene->clear();
    scene->addRect(250, 0, 500, 500, QPen(Qt::white), QBrush(Qt::white));
    ymin -= 1;
    ymax += 1;
    xmin -= 1;
    xmax += 1;
    PlotGraph(str);
}

void MainWindow::on_pushButton_9_clicked() {
    SecondWindow second_window;
    second_window.setModal(true);
    second_window.exec();
    Record l_record;
    if ((f_logs = fopen("./logs", "r+b")) != NULL && !FileEmpty(f_logs)) {
        int count = GetRecordsCountInFile(f_logs);
        for (int i = 0; i < count; ++i) {
            l_record = ReadRecordFromFile(f_logs, i);
            printf("%s: %s\n", l_record.date, l_record.func);
        }
        fclose(f_logs);
    }
}
void MainWindow::on_pushButton_10_clicked() {
    exit(0);
}

void MainWindow::on_checkBox_stateChanged(int arg1) {
    if (ui->lineEdit->text().length() != 0) {
        scene->clear();
        scene->addRect(250, 0, 500, 500, QPen(Qt::white), QBrush(Qt::white));
        ymax = 10;
        ymin = -10;
        xmin = -10;
        xmax = 10;
        PlotGraph(str);
    }
    if (arg1 == Qt::Checked) {
        ui->pushButton_5->hide();
        ui->pushButton_6->hide();
    } else {
        ui->pushButton_5->show();
        ui->pushButton_6->show();
    }

}

/* ymax = ymin = f[0];
    for (i = 1; i < SCREENW; ++i) {
        if (ymax < f[i])
            ymax = f[i];
        if (ymin > f[i])
            ymin = f[i];
    }

    ky = (ymax - ymin) / (SCREENH - 1);
    kx = (xmax - xmin) / (SCREENW - 1);

*/

void MainWindow::on_pushButton_12_clicked() {
//    TableOfValues window;
//    window.setModal(true);
//    window.exec();
    tableOfValuesWindow = new TableOfValues(this);
    tableOfValuesWindow->show();
}

void MainWindow::on_pushButton_11_clicked() {
//    CompareWindow window;
//    window.setModal(true);
//    window.exec();
    compareWindow = new CompareWindow(this);
    compareWindow->show();
}

void MainWindow::on_pushButton_13_clicked() {
//    IntegralWindow window;
//    window.setModal(true);
//    window.exec();
    integralWindow = new IntegralWindow(this);
    integralWindow->show();
}

void MainWindow::on_pushButton_14_clicked() {
    derivativeWindow = new DerivativeWindow(this);
    derivativeWindow->show();
}
