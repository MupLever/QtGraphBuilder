#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "parse_str.h"
#include "calculate.h"
#include "deque.h"
#include "stack.h"
#include <QMainWindow>
#include <QGraphicsScene>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#define SCREENW 490
#define SCREENH 390
QT_BEGIN_NAMESPACE
using namespace std;
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

struct Point {
    int x;
    int y;
};

struct Record {
    char func[50];
    char date[20];
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    void PlotGraph(char *str);
    int GetFileSizeInBytes(FILE *pfile);
    int GetRecordsCountInFile(FILE *pfile);
    Record ReadRecordFromFile(FILE *pfile, int index);
    bool FileEmpty(FILE* f_param);
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QPen pen;
    char str[50];
    Point screen[SCREENW];
    double f[SCREENW], xmin = -10.0, xmax = 10.0, ymin = -6.0, ymax = 6.0;
    FILE* f_logs;
};
#endif // MAINWINDOW_H
