#ifndef INTEGRALWINDOW_H
#define INTEGRALWINDOW_H
#include "parse_str.h"
#include "calculate.h"
#include "deque.h"

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
    ~IntegralWindow();

private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    double IntegralCalculate(bool *flag);
    void SetStr();
    Ui::IntegralWindow *ui;
    QGraphicsScene *scene;
    Deque *head, *tail;
    QPen pen;
    char str[50];
    bool ok_lg = false, ok_rg = false;
    double a, b;
    Plot plot;
};

#endif // INTEGRALWINDOW_H
