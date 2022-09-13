#include "stack.h"

Stack* init_stack(const char data) {
    Stack *head = new Stack;
    head->data = data;
    head->next = NULL;
    return head;
}

Stack* push_front(Stack* head, const char data) {
    if (head == NULL) {
        head = init_stack(data);
    } else {
        Stack *elem = new Stack;
        elem->next = head;
        elem->data = data;
        head = elem;
    }
    return head;
}

Stack* pop_front(Stack* head) {
    if (head != NULL) {
        Stack *temp = head;
        head = head->next;
        delete temp;
    } else {
        head = NULL;
    }
    return head;
}

// void output_stack(Stack* head) {
//     while (head != NULL) {
//         if (head->data == ' ')
//             printf("%d ", head->data);
//         else
//             printf("%c ", head->data);
//         head = head->next;
//     }
//     printf("\n");
// }
// void destroy_stack(Stack* head) {
//     while (head->next != NULL) {
//         head = pop_front(head);
//     }
//     delete head;
// }
