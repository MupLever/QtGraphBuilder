#ifndef SRC_CALCULATE_H_
#define SRC_CALCULATE_H_
#include "deque.h"
#include "parse_str.h"
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

struct Point {
    int x;
    int y;
};

double calculate(Deque* tail, double x);
#endif  // SRC_CALCULATE_H_
