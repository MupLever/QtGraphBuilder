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
    bool flag_scope_definition = false; // флаг ставится в 1, если х не входит в область определения
    bool flag_division_by_zero = false;// флаг ставится в 1, если деление на ноль в данной точке
    bool flag_sign = false; // флаг ставится в 1, если число со знаком минус
};

Point calculate(Deque* tail, double x);
#endif  // SRC_CALCULATE_H_
