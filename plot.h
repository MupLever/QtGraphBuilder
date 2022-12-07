#ifndef PLOT_H
#define PLOT_H

#include "deque.h"
#include "parse_str.h"
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include <QString>
#include <QGraphicsItem>
#include <QGraphicsScene>

#define SCREENW 500
#define SCREENH 500
// класс, в котором все необходимое для построения графика
class Plot {
public:
    Plot() :x0(0), y0(0), xmin(-10), ymin(-10), xmax(10), ymax(10), kx(1), ky(1) {}

    // отрисовка осей
    void plotGraphAxis(QGraphicsScene *scene, QPen pen);

   // отрисовка графика функций
    void plotGraph(char *str, QGraphicsScene *scene, QPen pen, bool check);

    // закрашивание области под графиком
    void brushGraph(QGraphicsScene *scene, double a, double b);

    void addCircle(QGraphicsScene *scene, double x, double y);

    // устанавливает левую границу
    void setXMin(const double xmin) { this->xmin = xmin; }

    // устанавливает нижнюю границу
    void setYMin(const double ymin) { this->ymin = ymin; }

    // устанавливает правую границу
    void setXMax(const double xmax) { this->xmax = xmax; }

    // устанавливает верхнюю границу
    void setYMax(const double ymax) { this->ymax = ymax; }

    // возвращает левую границу
    double getXMin() { return xmin; }

    // возвращает нижнюю границу
    double getYMin() { return ymin; }

    // возвращает правую границу
    double getXMax() { return xmax; }

    // возвращает верхнюю границу
    double getYMax() { return ymax; }

    // возвращает центр координат по Х
    double getX0() { return x0; }

    // возвращает центр координат по У
    double getY0() { return y0; }

    // устанавливает х0 и у0
    void setXY();

    // устанавливает коэффициенты масштабирования
    void setKXY();

private:
    Deque *head,
          *tail;

    Point points[SCREENW];

    double x0, y0, // координата центра пересечения осей
           xmin, ymin, // левая и нижняя границы
           xmax, ymax, // правая и верхняя границы
           kx, ky; // коэфы масштабирования
};
#endif // PLOT_H
