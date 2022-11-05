#include "deque.h"

Deque* init_deque(const Node* data) {
    Deque *head = new Deque;
    head->data = *data;
    head->next = NULL;
    head->prev = NULL;
    return head;
}

Deque* push(Deque* head, const Node* data) {
    if (head == NULL) {
        head = init_deque(data);
    } else {
        Deque *elem = new Deque;
        head->prev = elem;
        elem->prev = NULL;
        elem->next = head;
        elem->data = *data;
        head = elem;
    }
    return head;
}

// Deque* pop(Deque* head) {
//     if (head != NULL) {
//         Deque *temp = head;
//         head = head->next;
//         delete temp;
//     }
//     return head;
// }
Deque* get_tail(Deque* head) {
    while (head->next != NULL) {
        head = head->next;
    }
    return head;
}
void output_deque(Deque* tail) {
    while (tail != NULL) {
        if (tail->data.sym == ' ')
            printf("%.2lf ", tail->data.num);
        else
            printf("%c ", tail->data.sym);
        tail = tail->prev;
    }
}

// void destroy_deque(Deque* head) {
//     while (head->next != NULL) {
//         head = pop(head);
//     }
//     free(head);
// }

void replace_x(Deque* tail, double x) {
    while (tail != NULL) {
        if (tail->data.sym == 'x') {
            tail->data.num = x;
            tail->data.sym = ' ';
        }
        tail = tail->prev;
    }
}
