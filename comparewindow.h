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
    ~CompareWindow();

private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

    void on_checkBox_stateChanged(int arg1);

    void on_pushButton_2_clicked();

    void on_lineEdit_textEdited(const QString &arg1);

    void on_lineEdit_2_textEdited(const QString &arg1);

    void on_lineEdit_3_textEdited(const QString &arg1);

    void on_lineEdit_4_textEdited(const QString &arg1);

private:
    // инициализирует строку после пользовательского ввода
    void SetStr();

    //
    void someLineEdited();

    Ui::CompareWindow *ui;

    char str_func1[50], str_func2[50];

    QGraphicsScene *scene;

    double xmin,
           xmax,
           ymin,
           ymax;

    bool ok_lg, // ставится в 1, если вернулось корректное значение левой границы
         ok_rg, // ставится в 1, если вернулось корректное значение правой границы
         builtGraphFlag;
    QPen pen;
    Plot plot;
};

#endif // COMPAREWINDOW_H
