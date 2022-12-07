#ifndef SRC_CALCULATE_H_
#define SRC_CALCULATE_H_
#include "parse_str.h"
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// структура точки
struct Point {
    double x;
    double y;
    bool flag_scope_definition, // флаг ставится в 1, если х не входит в область определения
         flag_division_by_zero, // флаг ставится в 1, если деление на ноль в данной точке
         flag_sign;             // флаг ставится в 1, если число со знаком минус
    Point() : x(0.0), y(0.0),
              flag_scope_definition(false),
              flag_division_by_zero(false),
              flag_sign(false) {}
};

// вычисляет значение в конкретной точке
Point calculate(Deque* tail, double x);

#endif  // SRC_CALCULATE_H_
