#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "fileworker.h"
#include "plot.h"


#include "derivativewindow.h"
#include "secondwindow.h"
#include "comparewindow.h"
#include "tableofvalues.h"
#include "integralwindow.h"


#include <QMainWindow>
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
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();
private:
    // инициализирует массив символов
    void SetStr();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_14_clicked();

    void on_checkBox_stateChanged(int arg1);

    void on_lineEdit_textEdited(const QString &arg1);

private:
    Ui::MainWindow *ui;
    TableOfValues *tableOfValuesWindow;
    CompareWindow *compareWindow;
    IntegralWindow *integralWindow;
    DerivativeWindow *derivativeWindow;

    QGraphicsScene *scene; // сцена отрисовеи графиков
    QPen pen;
    char str[50]; // массив символов (функция)
    Plot plot; // объект класса построения графика
    FILE* f_logs; // файл кэша

    bool builtGraphFlag; // ставится в 1, если график построен
};
#endif // MAINWINDOW_H
