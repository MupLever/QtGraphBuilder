#ifndef SRC_STACK_H_
#define SRC_STACK_H_
#include <stdio.h>
#include <stdlib.h>

typedef struct stack {
    char data;
    struct stack *next;
} Stack;

Stack*init_stack(const char data);
Stack* push_front(Stack* head, const char data);
Stack* pop_front(Stack* head);
// void output_stack(Stack* head);
// void destroy_stack(Stack* head);

#endif  // SRC_STACK_H_
