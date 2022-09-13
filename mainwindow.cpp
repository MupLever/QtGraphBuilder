#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
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
    //ui->graphicsView->setRenderHint(QPainter::Antialiasing);
}

MainWindow::~MainWindow() {
    delete scene;
    delete ui;
}

void MainWindow::PlotGraph(char *str) {
    Deque *head, *tail;
    double x, ky, kx = (xmax - xmin) / (SCREENW - 1);
    int i;
    for (i = 0, x = xmin; i < SCREENW; ++i, x += kx) {
        head = parse(str);
        tail = get_tail(head);
        f[i] = calculate(tail, x);
    }
    ky = (ymax - ymin) / (SCREENH - 1);
    for (i = 0, x = xmin; i < SCREENW; i++, x += kx) {
        screen[i].x = (int)(round((x - xmin) / kx)) + 245;
        screen[i].y = SCREENH - (int)(round((f[i] - ymin) / ky)) - 1;
    }
    double y0 = SCREENH - (int)(round((0 - ymin) / ky)) - 1, x0 = (int)(round((0 - xmin) / kx));
    if (y0 >= 0 && y0 <= 390)
        scene->addLine(245, y0, 735, y0, QPen(Qt::black));
    if (x0 >= 0 && x0 <= 490)
        scene->addLine(x0 + 245, 0, x0 + 245, 390 , QPen(Qt::black));
    for (i = 0; i < SCREENW - 1; ++i) {
        if (screen[i].y >= 0 && screen[i].y <= 390
                && screen[i + 1].y >= 0 && screen[i + 1].y <= 390
                && screen[i].x >= 245 && screen[i].x <= 735
                && screen[i + 1].x >= 245 && screen[i + 1].x <= 735)
            scene->addLine(screen[i].x, screen[i].y, screen[i + 1].x, screen[i + 1].y, pen);
    }
}

void MainWindow::on_pushButton_clicked() {
    QString buf = ui->lineEdit->text();
    string std_str = buf.toStdString();
    for (int i = 0; i < (int)std_str.length(); i++)
        str[i] = std_str[i];
    str[(int)std_str.length()] = '\0';
    trim(str);
    unsigned short int flag = 0;
    transform(str, &flag);
    if (valid_str(str) != 0 || flag || strlen(str) == 0) {
        printf("\n\t\tНеверное выражение либо, возможно, не хватает скобки!!!!\n");
    } else {
        ui->lineEdit->setEnabled(false);
        ui->pushButton->setEnabled(false);
        ui->pushButton_2->setEnabled(true);
        ui->pushButton_3->setEnabled(true);
        ui->pushButton_4->setEnabled(true);
        ui->pushButton_5->setEnabled(true);
        ui->pushButton_6->setEnabled(true);
        ui->pushButton_7->setEnabled(true);
        ui->pushButton_8->setEnabled(true);
        PlotGraph(str);
    }
}

void MainWindow::on_pushButton_2_clicked() {
    scene->addRect(245, 0, 490, 390, QPen(Qt::white), QBrush(Qt::white));
    str[0] = '\0';
    ui->graphicsView->repaint();
    ui->lineEdit->setEnabled(true);
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
void MainWindow::on_pushButton_5_clicked() {
    scene->addRect(245, 0, 490, 390, QPen(Qt::white), QBrush(Qt::white));
    ymin += 0.5;
    ymax += 0.5;
    PlotGraph(str);
}

void MainWindow::on_pushButton_6_clicked() {
    scene->addRect(245, 0, 490, 390, QPen(Qt::white), QBrush(Qt::white));
    ymin -= 0.5;
    ymax -= 0.5;
    PlotGraph(str);
}

void MainWindow::on_pushButton_3_clicked() {
    scene->addRect(245, 0, 490, 390, QPen(Qt::white), QBrush(Qt::white));
    xmin -= 1;
    xmax -= 1;
    PlotGraph(str);
}

void MainWindow::on_pushButton_4_clicked() {
    scene->addRect(245, 0, 490, 390, QPen(Qt::white), QBrush(Qt::white));
    xmin += 1;
    xmax += 1;
    PlotGraph(str);
}

void MainWindow::on_pushButton_7_clicked(){
    scene->addRect(245, 0, 490, 390, QPen(Qt::white), QBrush(Qt::white));
    if (ymax - ymin > 6) {
        ymin += 3;
        ymax -= 3;
    }
    if (xmax - xmin > 6) {
        xmin += 3;
        xmax -= 3;
    }
    PlotGraph(str);
}

void MainWindow::on_pushButton_8_clicked() {
    scene->addRect(245, 0, 490, 390, QPen(Qt::white), QBrush(Qt::white));
    ymin -= 3;
    ymax += 3;
    xmin -= 3;
    xmax += 3;
    PlotGraph(str);
}


/* ymax = ymin = f[0];
    for (i = 1; i < SCREENW; ++i) {
        if (ymax < f[i])
            ymax = f[i];
        if (ymin > f[i])
            ymin = f[i];
    }

    ky = (ymax - ymin) / (SCREENH - 1);
    kx = (4 * 3.14159265358 - 0) / (SCREENW - 1);
    for (i = 0, x = 0; i < SCREENW; i++, x += dx) {
        screen[i].x = (int)(round((x + 2 * 3.14159265358) / kx));
        screen[i].y = SCREENH - (int)(round((f[i] - ymin) / ky)) - 1;
    }
*/
