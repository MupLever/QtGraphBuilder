#ifndef COMPAREWINDOW_H
#define COMPAREWINDOW_H
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

private:
    Ui::CompareWindow *ui;
    char str_func1[50];
    char str_func2[50];
    QGraphicsScene *scene;
    Deque *head1, *tail1, *head2, *tail2;
    QPen pen1, pen2, pen3;
    Point screen_func1[SCREENW], screen_func2[SCREENW];
    double f1[SCREENW], f2[SCREENW], xmin = -10.0, xmax = 10.0, ymin = -10.0, ymax = 10.0;
    void SetStr();
    void PlotGraph();
};

#endif // COMPAREWINDOW_H