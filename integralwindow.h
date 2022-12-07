#ifndef INTEGRALWINDOW_H
#define INTEGRALWINDOW_H

#include "plot.h"

#include <QDialog>
#include <QString>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QMessageBox>

#define SCREENW 500
#define SCREENH 500
namespace Ui {
    class IntegralWindow;
}

class IntegralWindow : public QDialog
{
    Q_OBJECT

public:
    explicit IntegralWindow(QWidget *parent = nullptr);

    // загрузка строки
    void load(QString _lineEdit);

    ~IntegralWindow();

private slots:

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_lineEdit_textEdited(const QString &arg1);

    void on_lineEdit_2_textEdited(const QString &arg1);

    void on_lineEdit_3_textEdited(const QString &arg1);

private:
    //вычисление интеграла путем разбиения отрезка на
    //множество подотрезков и выисления площади прямугольников
    double IntegralCalculate(bool *flag);

    // инициализирует строку после пользовательского ввода
    void SetStr();

    // вызывается при редактировании полей ввода
    void someLineEdited();

    Ui::IntegralWindow *ui;
    QGraphicsScene *scene; // сцена отрисовеи графиков
    Deque *head, *tail;
    QPen pen;
    char str[50]; // массив символов (функция)
    bool ok_lg, // ставится в 1, если вернулось корректное значение левой границы
         ok_rg,// ставится в 1, если вернулось корректное значение правой границы
         builtGraphFlag;
    double a, // левая граница интегрирования
           b; // правая граница интегрирования
    Plot plot; // объект класса построения графиков
};

#endif // INTEGRALWINDOW_H
