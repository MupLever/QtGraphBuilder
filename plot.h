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
class Plot {
public:
    Plot() :x0(0), y0(0), xmin(-10), ymin(-10), xmax(10), ymax(10), kx(1), ky(1) {}
    void plotGraphAxis(QGraphicsScene *scene, QPen pen);
    void plotGraph(char *str, QGraphicsScene *scene, QPen pen, bool check);
    void brushGraph(QGraphicsScene *scene, double a, double b);

    void setXMin(const double xmin) { this->xmin = xmin; }
    void setYMin(const double ymin) { this->ymin = ymin; }
    void setXMax(const double xmax) { this->xmax = xmax; }
    void setYMax(const double ymax) { this->ymax = ymax; }


    double getXMin() { return xmin; }
    double getYMin() { return ymin; }
    double getXMax() { return xmax; }
    double getYMax() { return ymax; }
    double getX0() { return x0; }
    double getY0() { return y0; }

    void setXY();
    void setKXY();
private:

    Deque *head, *tail;
    Point points[SCREENW];
    double x0, y0, xmin, ymin, xmax, ymax, kx, ky;
};
#endif // PLOT_H
