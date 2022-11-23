#include "comparewindow.h"
#include "ui_comparewindow.h"

CompareWindow::CompareWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CompareWindow) {
    ui->setupUi(this);
    setWindowTitle("GROW");
    setFixedSize(QSize(820,580)); // фиксирование размеров окна

    ui->checkBox->setCheckState(Qt::Unchecked);
    ui->checkBox->setEnabled(false);

    scene = new QGraphicsScene;
    ui->graphicsView->setScene(scene);

    xmin = -10.0;
    xmax = 10.0;
    ymin = -10.0;
    ymax = 10.0;

    ok_lg = false;
    ok_rg = false;
    builtGraphFlag = false;

    ui->graphicsView->setRenderHint(QPainter::Antialiasing);

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

            plot.setXMin(xmin);
            plot.setXMax(xmax);

            plot.plotGraph(str_func1, scene, QPen(Qt::green), false);
            plot.plotGraph(str_func2, scene, QPen(Qt::blue), false);

            plot.plotGraphAxis(scene, pen);

            ui->checkBox->setEnabled(true);
            builtGraphFlag = true;
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
        scene->addRect(250, 0, 500, 510, QPen(Qt::white), QBrush(Qt::white));
        plot.setYMin(-10);
        plot.setYMax(10);
        if (arg1 == Qt::Unchecked) {
            plot.plotGraph(str_func1, scene, QPen(Qt::green), false);

        } else {
            plot.plotGraph(str_func1, scene, QPen(Qt::green), true);
        }
        plot.plotGraph(str_func2, scene, QPen(Qt::blue), false);
        plot.plotGraphAxis(scene, pen);
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

    ui->checkBox->setEnabled(false);

    ui->pushButton->setEnabled(true);
    ui->pushButton_2->setEnabled(false);
}

void CompareWindow::someLineEdited() {
    if (builtGraphFlag) {
        builtGraphFlag = false;
        scene->clear();
        ui->graphicsView->items().clear();
        ui->lineEdit_4->setText("");
    }
}
void CompareWindow::on_lineEdit_textEdited(const QString &arg1) {
    someLineEdited();
}

void CompareWindow::on_lineEdit_2_textEdited(const QString &arg1) {
    someLineEdited();
}

void CompareWindow::on_lineEdit_3_textEdited(const QString &arg1) {
    someLineEdited();
}

void CompareWindow::on_lineEdit_4_textEdited(const QString &arg1) {
    someLineEdited();
}
