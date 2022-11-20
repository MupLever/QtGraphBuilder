#include "plot.h"

void Plot::setKXY() {
    kx = (xmax - xmin) / 479;
    ky = (ymax - ymin) / 479;
}
void Plot::setXY() {
    y0 = SCREENH - 10 - (int)(round((0 - ymin) / ky));
    x0 = (round((0 - xmin) / kx)) + 10;
}

void Plot::plotGraphAxis(QGraphicsScene *scene, QPen pen) {
    QString str_value_point;
    int i = 0;
    double x, temp;
    if (y0 >= 10 && y0 <= SCREENH - 10) {
        scene->addLine(260, y0, 742, y0, QPen(Qt::black));
        double dx = (xmax - xmin) / 20;
        for (i = 260, x = xmin; i < 742; i += 24, x += dx) {
            QGraphicsTextItem *item = new QGraphicsTextItem;
            str_value_point.setNum(round(x * 10) / 10);
            item->setHtml(str_value_point);
            item->setPos(i - 10, y0 - 5);
            scene->addItem(item);
            scene->addEllipse(i, y0, 2, 2, pen);
        }
    }
    if (x0 >= 10 && x0 <= SCREENW - 10) {
        double y, dy = (ymax - ymin) / 20;
        scene->addLine(x0 + 250, 10, x0 + 250, 492 , QPen(Qt::black));
        for (i = 10, y = ymax; i < 492; i += 24, y -= dy) {
            QGraphicsTextItem *item = new QGraphicsTextItem;
            str_value_point.setNum(round(y * 1000) / 1000);
            item->setHtml(str_value_point);
            item->setPos(250 + x0, i - 12);
            if (i != 274) {
                scene->addItem(item);
                scene->addEllipse(250 + x0, i, 2, 2, pen);
            }
        }
    }
}

void Plot::plotGraph(char *str, QGraphicsScene *scene, QPen pen, bool check) {
    double x;
    kx = (xmax - xmin) / 479;
    int i;
    for (i = 0, x = xmin; i < SCREENW - 1; ++i, x += kx) {
        head = parse(str);
        tail = get_tail(head);
        points[i] = calculate(tail, x);
    }
    if (check) {
        double temp;

        for (i = 0; points[i].flag_division_by_zero || points[i].flag_scope_definition; ++i);

        ymax = ymin = points[i].y;
        for (i = 0; i < SCREENW; ++i) {
            if (!points[i].flag_division_by_zero && !points[i].flag_scope_definition) {
                temp = points[i].y;
                if (ymax < temp)
                    ymax = temp;
                if (ymin > temp)
                    ymin = temp;
            }
        }
    }
    ky = (ymax - ymin) / 479;
    for (i = 0, x = xmin; i < SCREENW - 1; ++i, x += kx) {
        points[i].x = (round((x - xmin) / kx)) + 260;
        points[i].y = 490 - (round((points[i].y - ymin) / ky));
    }
    setXY();
    for (i = 0; i < SCREENW - 1; ++i) {
        if (!points[i].flag_scope_definition &&
            !points[i].flag_division_by_zero &&
            !points[i + 1].flag_scope_definition &&
            !points[i + 1].flag_division_by_zero &&
            (fabs(points[i].y - points[i + 1].y) < 100) &&
            points[i].y >= 0 && points[i].y <= 500 &&
            points[i + 1].y >= 0 && points[i + 1].y <= 500 &&
            points[i].x >= 250 && points[i].x <= 750 &&
            points[i + 1].x >= 250 && points[i + 1].x <= 750) {
                scene->addLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y, pen);
        }
    }
}

void Plot::brushGraph(QGraphicsScene *scene, double a, double b) {
    int left_border = (round((a - xmin) / kx)),
         right_border = (round((b - xmin) / kx));
    for (int i = left_border; i < right_border && i < 498; ++i) {
        if (points[i].y >= 0 && points[i].y <= 500 &&
            points[i + 1].y >= 0 && points[i + 1].y <= 500) {
            scene->addRect(points[i].x, y0, points[i + 1].x - points[i].x, points[i].y - y0 + 2, QPen(Qt::green), QBrush(Qt::green));
        }
    }
}
