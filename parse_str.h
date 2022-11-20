#ifndef SRC_PARSE_STR_H_
#define SRC_PARSE_STR_H_
#include "deque.h"

#include "calculate.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <stack>

// функция удаления пробелов
char *trim(char *str);

// проверяет строку на равное количество скобок ( и )
bool valid_str(char* str);

// преобразует символ в число
int str_to_int(char c);

// проверяет, может ли символ быть преобразован в число
bool is_number(char sym);

// short int is_str_to_float(const std::string str); не используется

// получение числа из строки по индексу
double get_number(char* str, int *index);

// это унарная операция?
bool is_operator(char c);

// это бинарная операция?
bool is_binary_operator(char c);

// это операторы и функции для алгоритма сортировочной станции?
bool is_operation_for_parse(char c);

// это операторы для преобразования в строку токенов?
bool is_operation_for_transform(char c);

// сравнивает приоритеты операций
bool cmp_priority(char sym1, char sym2);

// трансформация строки в строку токенов
char* transform(char* str, bool *flag);

// алгоритм сортировочной станции
Deque* parse(char* str);

#endif  //  SRC_PARSE_STR_H_
