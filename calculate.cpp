#include "calculate.h"

double calculate(Deque* tail , double x) {
    Deque* temp = tail, *q, *p;
    double result = 0;
    replace_x(tail, x);
    while (temp->prev != NULL) {
        if ((is_operator(temp->prev->data.sym) || temp->prev->data.sym == '~') && (temp->data.sym == ' ')) {
            if (temp->prev->data.sym == 's')
                temp->data.num = sin(temp->data.num);
            else if (temp->prev->data.sym == 'S')
                temp->data.num = sqrt(temp->data.num);
            else if (temp->prev->data.sym == 'c')
                temp->data.num = cos(temp->data.num);
            else if (temp->prev->data.sym == 't')
                temp->data.num = tan(temp->data.num);
            else if (temp->prev->data.sym == 'l')
                temp->data.num = log(temp->data.num);
            else if (temp->prev->data.sym == 'C')
                temp->data.num = 1.0 / tan(temp->data.num);
            else
                temp->data.num = -temp->data.num;
            q = temp->prev;
            if (q->prev != NULL) {
                temp->prev = q->prev;
                q->prev->next = temp;
            } else {
                temp->prev = NULL;
            }
            delete q;
            continue;
        } else if (is_binary_operator(temp->prev->data.sym)) {
            if (temp->prev->data.sym == '+')
                temp->next->data.num = temp->data.num + temp->next->data.num;
            else if (temp->prev->data.sym == '-')
                temp->next->data.num = temp->next->data.num - temp->data.num;
            else if (temp->prev->data.sym == '*')
                temp->next->data.num = temp->data.num * temp->next->data.num;
            else if (temp->prev->data.sym == '/')
                temp->next->data.num = temp->next->data.num / temp->data.num;
            temp = temp->next;
            q = temp->prev;
            p = q->prev;
            delete q;
            if (p->prev != NULL) {
                temp->prev = p->prev;
                p->prev->next = temp;
            } else {
                temp->prev = NULL;
            }
            delete p;
            continue;
        }
            temp = temp->prev;
    }
    result = temp->data.num;
    delete temp;
    return result;
}
