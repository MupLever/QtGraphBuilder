#ifndef DERIVATIVEWINDOW_H
#define DERIVATIVEWINDOW_H

#include <QDialog>

#include "plot.h"

#include <QString>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QMessageBox>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define SCREENW 500
#define SCREENH 500

QT_BEGIN_NAMESPACE
using namespace std;

namespace Ui {
class DerivativeWindow;
}

class DerivativeWindow : public QDialog
{
    Q_OBJECT

public:
    explicit DerivativeWindow(QWidget *parent = nullptr);
    ~DerivativeWindow();
private:
    // инициализирует строку после пользовательского ввода
    void SetStr();

    // метод золотого сечения для нахождения экстремумов
    void calculateDerivative();


    void someLineEdited();

private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void on_lineEdit_textEdited(const QString &arg1);

    void on_lineEdit_2_textEdited(const QString &arg1);

    void on_lineEdit_3_textEdited(const QString &arg1);

private:
    Ui::DerivativeWindow *ui;

    QGraphicsScene *scene;
    Deque *head, *tail;
    QPen pen;
    char str[50];
    double xmin, //левая граница
           xmax, //правая граница
           phi; // пропорция золотого сечения

    bool ok_lg, // ставится в 1, если вернулось корректное значение левой границы
         ok_rg, // ставится в 1, если вернулось корректное значение правой границы
         radioButtonChecked_1, // ставится в 1, если нажат radio_button_1
         radioButtonChecked_2, // ставится в 1, если нажат radio_button_2
         builtGraphFlag;

    Plot plot;
};

#endif // DERIVATIVEWINDOW_H
