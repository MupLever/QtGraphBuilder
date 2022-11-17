#ifndef DERIVATIVEWINDOW_H
#define DERIVATIVEWINDOW_H

#include <QDialog>

#include "parse_str.h"
#include "calculate.h"
#include "deque.h"
#include "stack.h"

#include <QString>
#include <QList>
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
    void PlotGraph(char *str);

    void PlotGraphAxis(double x0, double y0);

    void SetStr();

private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::DerivativeWindow *ui;

    QGraphicsScene *scene;
    Deque *head, *tail;
    QPen pen;
    char str[50];
    Point points[SCREENW];
    double xmin = -10.0,
           xmax =  10.0,
           ymin = -10.0,
           ymax =  10.0;
    bool ok_lg =                false,
         ok_rg =                false,
         radioButtonChecked_1 = false,
         radioButtonChecked_2 = false;
};

#endif // DERIVATIVEWINDOW_H
