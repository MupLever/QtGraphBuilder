#ifndef SRC_PARSE_STR_H_
#define SRC_PARSE_STR_H_
#include "deque.h"
#include "calculate.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <stack>
char *trim(char *str);
bool valid_str(char* str);
int str_to_int(char c);
bool is_number(char sym);
short int is_str_to_float(const std::string str);
double get_number(char* str, int *index);
bool is_operator(char c);
bool is_binary_operator(char c);
bool is_operation_for_parse(char c);
bool is_operation_for_transform(char c);
bool cmp_priority(char sym1, char sym2);
char* transform(char* str, bool *flag);
Deque* parse(char* str);
#endif  //  SRC_PARSE_STR_H_
