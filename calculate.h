#ifndef SRC_CALCULATE_H_
#define SRC_CALCULATE_H_
#include "deque.h"
#include "parse_str.h"
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

struct Point {
    double x;
    double y;
    bool flag_scope_definition = false;
    bool flag_division_by_zero = false;
    bool flag_sign = false;
};

Point calculate(Deque* tail, double x);
#endif  // SRC_CALCULATE_H_
