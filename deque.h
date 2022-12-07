#ifndef SRC_DEQUE_H_
#define SRC_DEQUE_H_
#include <stdio.h>
#include <stdlib.h>

// структура данных узел
typedef struct node {
    char sym;
    double num;
} Node;


// структура данных дек
typedef struct deque {
    Node data;
    struct deque *next;
    struct deque *prev;
} Deque;

// инициализация дека
Deque* init_deque(const Node* data);

// пуш в дек
Deque* push(Deque* head, const Node* data);

//поп из дека - не используется
// Deque* pop(Deque* head);

// получение хвоста дека
Deque* get_tail(Deque* head);

// замена всех переменых на определенное значение
void replace_x(Deque* tail, double x);

// вывод польской записи
 void output_deque(Deque* head);

// деструктор дека - не используется
// void destroy_deque(Deque* head);

#endif  // SRC_DEQUE_H_
