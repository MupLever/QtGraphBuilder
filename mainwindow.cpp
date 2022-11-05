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
    double x;
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
        double y, dy = (ymax - ymin) / 20;
        scene->addLine(x0 + 250, 0, x0 + 250, 500 , QPen(Qt::black));
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
}
void MainWindow::PlotGraph(char *str) {
    double x, ky, kx = (xmax - xmin) / (SCREENW - 1);
    int i;
    bool check = ui->checkBox->checkState();
    for (i = 0, x = xmin; i < SCREENW; ++i, x += kx) {
        head = parse(str);
        tail = get_tail(head);
        f[i] = calculate(tail, x);
    }
    if (check) {
        ymax = ymin = f[0];
        for (i = 1; i < SCREENW; ++i){
            if (ymax < f[i])
                ymax = f[i];
            if (ymin > f[i])
                ymin = f[i];
        }
    }
    ky = (ymax - ymin) / (SCREENH - 1);
    for (i = 0, x = xmin; i < SCREENW; i++, x += kx) {
        screen[i].x = (round((x - xmin) / kx)) + 250;
        screen[i].y = SCREENH - (round((f[i] - ymin) / ky)) - 1;
    }
    double y0 = SCREENH - (int)(round((0 - ymin) / ky)) - 1,
            x0 = (int)(round((0 - xmin) / kx));
   PlotGraphAxis(x0, y0);
    for (i = 0; i < SCREENW - 1; ++i) {
        if (screen[i].y >= 0 && screen[i].y <= 500
                && screen[i + 1].y >= 0 && screen[i + 1].y <= 500
                && screen[i].x >= 250 && screen[i].x <= 750
                && screen[i + 1].x >= 250 && screen[i + 1].x <= 750)
            scene->addLine(screen[i].x, screen[i].y, screen[i + 1].x, screen[i + 1].y, pen);
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
                           "GROW", "Invalid expression entered.",
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
    TableOfValues window;
    window.setModal(true);
    window.exec();
}

void MainWindow::on_pushButton_11_clicked() {
    CompareWindow window;
    window.setModal(true);
    window.exec();
}

void MainWindow::on_pushButton_13_clicked() {
    IntegralWindow window;
    window.setModal(true);
    window.exec();
}
