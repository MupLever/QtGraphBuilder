#include "calculate.h"

Point calculate(Deque* tail , double x) {
    Deque* temp = tail, *q, *p;
    Point result;
    double tmp_tan;
    result.x = x;
    replace_x(tail, x);
    while (temp->prev != NULL) {
        if ((is_operator(temp->prev->data.sym) || temp->prev->data.sym == '~') && (temp->data.sym == ' ')) {
            if (temp->prev->data.sym == 's')
                temp->data.num = sin(temp->data.num);
            else if (temp->prev->data.sym == 'S') {
                if (temp->data.num < 0)
                    result.flag_scope_definition = true;
                else
                    temp->data.num = sqrt(temp->data.num);
            } else if (temp->prev->data.sym == 'c')
                temp->data.num = cos(temp->data.num);
            else if (temp->prev->data.sym == 't')
                temp->data.num = tan(temp->data.num);
            else if (temp->prev->data.sym == 'l') {
                if (temp->data.num < 0)
                    result.flag_scope_definition = true;
                else
                    temp->data.num = log(temp->data.num);
            } else if (temp->prev->data.sym == 'C') {
                tmp_tan = tan(temp->data.num);
                if (fabs(tmp_tan) < 0.000001) {
                    result.flag_division_by_zero = true;
                    if (tmp_tan < 0)
                        result.flag_sign = true;
                } else
                    temp->data.num = 1.0 / tmp_tan;
            } else
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
            else if (temp->prev->data.sym == '/') {
                if (fabs(temp->data.num) < 0.000001) {
                    result.flag_division_by_zero = true;
                    if (temp->data.num < 0)
                        result.flag_sign = true;
                } else
                    temp->next->data.num = temp->next->data.num / temp->data.num;
            }
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
    result.y = temp->data.num;
    delete temp;
    return result;
}
