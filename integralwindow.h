#ifndef INTEGRALWINDOW_H
#define INTEGRALWINDOW_H
#include "parse_str.h"
#include "calculate.h"
#include "deque.h"
#include "stack.h"
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
    void PlotGraph(char *str);
    void PlotGraphAxis(double x0, double y0);
    double IntegralCalculate(bool *flag);
    void SetStr();
    Ui::IntegralWindow *ui;
    QGraphicsScene *scene;
    Deque *head, *tail;
    QPen pen;
    char str[50];
    bool ok_lg = false, ok_rg = false;
    Point points[SCREENW];
    double xmin = -10.0, xmax = 10.0, ymin = -10.0, ymax = 10.0, a, b;
};

#endif // INTEGRALWINDOW_H
