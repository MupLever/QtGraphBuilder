#ifndef COMPAREWINDOW_H
#define COMPAREWINDOW_H

#include "plot.h"

#include <QDialog>
#include <QString>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QMessageBox>

#define SCREENW 500
#define SCREENH 500
namespace Ui {
class CompareWindow;
}

class CompareWindow : public QDialog
{
    Q_OBJECT

public:
    explicit CompareWindow(QWidget *parent = nullptr);

    // загрузка строки
    void load(QString _lineEdit);

    ~CompareWindow();

private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_lineEdit_textEdited(const QString &arg1);

    void on_lineEdit_2_textEdited(const QString &arg1);

    void on_lineEdit_3_textEdited(const QString &arg1);

    void on_lineEdit_4_textEdited(const QString &arg1);

private:
    // инициализирует строку после пользовательского ввода
    void SetStr();

    // вызывается при редактировании полей ввода
    void someLineEdited();

    Ui::CompareWindow *ui;

    char str_func1[50], // массив символов (первая функция)
         str_func2[50]; // массив символов (вторая функция)

    QGraphicsScene *scene; // сцена отрисовеи графиков

    double xmin, // левая граница
           xmax, // правая граница
           ymin, // нижняя граница
           ymax; // верхняя граница

    bool ok_lg, // ставится в 1, если вернулось корректное значение левой границы
         ok_rg, // ставится в 1, если вернулось корректное значение правой границы
         builtGraphFlag;
    QPen pen;
    Plot plot; // объект класса построения граифков
};

#endif // COMPAREWINDOW_H
