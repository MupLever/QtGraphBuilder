#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);

    setWindowTitle("GROW");
    setFixedSize(QSize(950,550));
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);

    ui->checkBox->setCheckState(Qt::Unchecked);

    ui->checkBox->setEnabled(false);

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

    builtGraphFlag = false;
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

void MainWindow::on_pushButton_clicked() {
    bool flag = 0;
    char stroka[50];
    SetStr();
    strcpy(stroka, str);
    transform(str, &flag);
    if (valid_str(str) != 0 ||
        flag ||
        strlen(str) == 0) {
        QMessageBox msgBox(QMessageBox::Information,
                           "GROW", "Неверное выражение",
                           QMessageBox::Ok);
        msgBox.exec();
    } else {
        WriteFile(f_logs, stroka);
        ui->checkBox->setEnabled(true);

        ui->pushButton->setEnabled(false);

        ui->pushButton_3->setEnabled(true);
        ui->pushButton_4->setEnabled(true);
        ui->pushButton_5->setEnabled(true);
        ui->pushButton_6->setEnabled(true);
        ui->pushButton_7->setEnabled(true);
        ui->pushButton_8->setEnabled(true);

        //clock_t time_start = clock();

        plot.plotGraph(str, scene, pen, ui->checkBox->isChecked());
        plot.plotGraphAxis(scene, pen);
        builtGraphFlag = true;
        //clock_t time_end = clock();
        //double time_dif = (double)(time_end - time_start) / CLOCKS_PER_SEC;
        //printf("%lf\n", time_dif);
    }
}

void MainWindow::on_pushButton_2_clicked() {
    scene->clear();
    ui->graphicsView->items().clear();

    str[0] = '\0';
    ui->checkBox->setEnabled(false);
    ui->pushButton_3->setEnabled(false);
    ui->pushButton_4->setEnabled(false);
    ui->pushButton_5->setEnabled(false);
    ui->pushButton_6->setEnabled(false);
    ui->pushButton_7->setEnabled(false);
    ui->pushButton_8->setEnabled(false);
    ui->lineEdit->setText("");
}

// смещение графика по х влево
void MainWindow::on_pushButton_3_clicked() {
    scene->clear();
    ui->graphicsView->items().clear();

    plot.setXMin(plot.getXMin() - 1);
    plot.setXMax(plot.getXMax() - 1);

    plot.plotGraph(str, scene, pen, ui->checkBox->isChecked());
    plot.plotGraphAxis(scene, pen);
}

// смещение графика по х вправо
void MainWindow::on_pushButton_4_clicked() {
    scene->clear();
    ui->graphicsView->items().clear();

    plot.setXMin(plot.getXMin() + 1);
    plot.setXMax(plot.getXMax() + 1);

    plot.plotGraph(str, scene, pen, ui->checkBox->isChecked());
    plot.plotGraphAxis(scene, pen);
}
// смещение графика по у вверх
void MainWindow::on_pushButton_5_clicked() {
    scene->clear();
    ui->graphicsView->items().clear();

    plot.setYMin(plot.getYMin() + 1);
    plot.setYMax(plot.getYMax() + 1);

    plot.plotGraph(str, scene, pen, ui->checkBox->isChecked());
    plot.plotGraphAxis(scene, pen);
}

// смещение графика по у вниз
void MainWindow::on_pushButton_6_clicked() {
    scene->clear();
    ui->graphicsView->items().clear();

    plot.setYMin(plot.getYMin() - 1);
    plot.setYMax(plot.getYMax() - 1);

    plot.plotGraph(str, scene, pen, ui->checkBox->isChecked());
    plot.plotGraphAxis(scene, pen);
}

// увеличение графика
void MainWindow::on_pushButton_7_clicked(){
    scene->clear();
    ui->graphicsView->items().clear();
    if (plot.getYMax()- plot.getYMin() > 10) {
        plot.setYMin(plot.getYMin() + 1);
        plot.setYMax(plot.getYMax() - 1);
    }
    if (plot.getXMax()- plot.getXMin() > 10) {
        plot.setXMin(plot.getXMin() + 1);
        plot.setXMax(plot.getXMax() - 1);
    }
    plot.plotGraph(str, scene, pen, ui->checkBox->isChecked());
    plot.plotGraphAxis(scene, pen);
}

// отдаление от графика
void MainWindow::on_pushButton_8_clicked() {
    scene->clear();
    ui->graphicsView->items().clear();

    plot.setYMin(plot.getYMin() - 1);
    plot.setYMax(plot.getYMax() + 1);
    plot.setXMin(plot.getXMin() - 1);
    plot.setXMax(plot.getXMax() + 1);
    plot.plotGraph(str, scene, pen, ui->checkBox->isChecked());
    plot.plotGraphAxis(scene, pen);
}


// вывод файла в таблицу
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
        ui->graphicsView->items().clear();

        plot.setYMax(10);
        plot.setYMin(-10);
        plot.setXMax(10);
        plot.setXMin(-10);

        plot.plotGraph(str, scene, pen, ui->checkBox->isChecked());
        plot.plotGraphAxis(scene, pen);
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
    tableOfValuesWindow->load(ui->lineEdit->text());
    tableOfValuesWindow->show();
}

void MainWindow::on_pushButton_11_clicked() {
//    CompareWindow window;
//    window.setModal(true);
//    window.exec();
    compareWindow = new CompareWindow(this);
    compareWindow->load(ui->lineEdit->text());
    compareWindow->show();
}

void MainWindow::on_pushButton_13_clicked() {
//    IntegralWindow window;
//    window.setModal(true);
//    window.exec();
    integralWindow = new IntegralWindow(this);
    integralWindow->load(ui->lineEdit->text());
    integralWindow->show();
}

void MainWindow::on_pushButton_14_clicked() {
    derivativeWindow = new DerivativeWindow(this);
    derivativeWindow->load(ui->lineEdit->text());
    derivativeWindow->show();
}

void MainWindow::on_lineEdit_textEdited(const QString &arg1) {
    if (builtGraphFlag) {
        builtGraphFlag = false;
        scene->clear();
        ui->graphicsView->items().clear();

        ui->checkBox->setEnabled(false);

        ui->pushButton->setEnabled(true);

        ui->pushButton_3->setEnabled(false);
        ui->pushButton_4->setEnabled(false);
        ui->pushButton_5->setEnabled(false);
        ui->pushButton_6->setEnabled(false);
        ui->pushButton_7->setEnabled(false);
        ui->pushButton_8->setEnabled(false);
    }
}
