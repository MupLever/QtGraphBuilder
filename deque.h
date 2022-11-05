#ifndef SRC_DEQUE_H_
#define SRC_DEQUE_H_
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    char sym;
    double num;
} Node;

typedef struct deque {
    Node data;
    struct deque *next;
    struct deque *prev;
} Deque;

Deque* init_deque(const Node* data);
Deque* push(Deque* head, const Node* data);
// Deque* pop(Deque* head);
Deque* get_tail(Deque* head);
void replace_x(Deque* tail, double x);
 void output_deque(Deque* head);
// void destroy_deque(Deque* head);

#endif  // SRC_DEQUE_H_
