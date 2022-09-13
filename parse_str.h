#ifndef SRC_PARSE_STR_H_
#define SRC_PARSE_STR_H_
#include "deque.h"
#include "calculate.h"
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *trim(char *str);
int valid_str(char* str);
int str_to_int(char c);
int is_number(char sym);
int is_operator(char c);
int is_binary_operator(char c);
int is_operation_for_parse(char c);
int  is_operation_for_transform(char c);
double get_number(char* str, int *index);
int cmp_priority(char sym1, char sym2);
char* transform(char* str, bool *flag);
Deque* parse(char* str);
#endif  //  SRC_PARSE_STR_H_
