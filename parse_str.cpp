#include "parse_str.h"
char *trim(char *str) {
    int length = strlen(str);
    int i = 0;
    while (str[0] == ' ') {
        for (i = 0; i < length; i++) {
            str[i] = str[i + 1];
        }
        --length;
    }
    while (i < length) {
        if (str[i] == ' ') {
            for (int j = i; j < length; j++) {
                str[j] = str[j + 1];
            }
            --length;
        }
        ++i;
    }
    str[length] = '\0';
    return str;
}

int str_to_int(char c) {
    bool flag = 0;
    short int i;
    for (i = 0; i < 10 && !flag; i++) {
        if (c == (char)(48 + i)) {
            flag = 1;
        }
    }
    --i;
    if (flag == 0)
        i = -1;
    return i;
}

bool is_number(char sym) {
    bool result = 0;
    if (sym >= '0' && sym <= '9')
        result = 1;
    return result;
}

double get_number(char* str, int *index) {
    int num = 0, length = strlen(str);
    double result = 0;
    bool flag_negative = false;
    if (str[0] == '-') {
        *index = *index + 1;
        flag_negative = true;
    }
    while ((num = str_to_int(str[*index])) != -1 && *index < length) {
        result = result * 10 + num;
        *index = *index + 1;
    }
    if (*index < length && str[*index] == '.') {
        *index = *index + 1;
        double q_part = 0, k = 10.0;
        while ((num = str_to_int(str[*index])) != -1 && *index < length) {
            q_part = q_part + num / k;
            k *= 10.0;
            *index = *index + 1;
        }
        result += q_part;
    }
    if (flag_negative)
        result *= -1;
    return result;
}

/*
short int is_str_to_float(const std::string str) {
    int i = 0;
    unsigned short int flag_point = 0;
    if (str[i] == '-') i++;
    for (; str[i] != 0; i++)
        if (!(str[i] >= '0' && str[i] <= '9')) {
            if (str[i] == '.' && !flag_point)
                flag_point = 1;
            else
                return 0;
        }
    if (i == 1 && str[0] == '-') return 0;
    return 1;
}
*/

bool is_operation_for_transform(char c) {
    const char opertations[] = {'*', '/', '+', '-', '~', '(', ')', 'x', '.'};
    bool flag = 0;
    for (int i = 0; i < 9 && !flag; i++) {
        if (c == opertations[i])
            flag = 1;
    }
    return flag;
}

bool is_binary_operator(char c) {
    const char opertations[] = {'*', '/', '+', '-'};
    bool flag = 0;
    for (int i = 0; i < 4 && !flag; i++) {
        if (c == opertations[i])
            flag = 1;
    }
    return flag;
}
bool is_operator(char c) {
    const char opertations[] = {'l', 't', 'c', 'C', 's', 'S'};
    bool flag = 0;
    for (int i = 0; i < 6 && !flag; i++) {
        if (c == opertations[i])
            flag = 1;
    }
    return flag;
}
bool is_operation_for_parse(char c) {
    const char opertations[] = {'*', '/', '+', '-', '~', '(', 'l', 't', 'c', 'C', 's', 'S', '.'};
    bool flag = 0;
    for (int i = 0; i < 13 && !flag; i++) {
        if (c == opertations[i])
            flag = 1;
    }
    return flag;
}

bool valid_str(char* str) {
    int length = strlen(str), i = 0, count = 0;
    while (i < length) {
        if (str[i] == '(')
            count++;
        if (str[i] == ')')
            count--;
        ++i;
    }
    return count;
}
char* transform(char* str, bool *flag) {
    int length = strlen(str), i = 0, j;
    bool flag_num_op = 0, flag_un_op = 0;
    while (i < length && *flag == 0) {
        while (is_operation_for_transform(str[i]) || is_number(str[i])) {
            ++i;
            flag_num_op = 1;
        }
        if (!flag_num_op && str[i] == 's' && str[i + 1] == 'q' && str[i + 2] == 'r' && str[i + 3] == 't') {
            str[i] = 'S';
            for (j = i + 1; j < length; j++) {
                str[j] = str[j + 3];
            }
            length -= 3;
            ++i;
            flag_un_op = 1;
        }
        if (!flag_num_op && ((str[i] == 'c' && str[i + 1] == 'o' && str[i + 2] == 's')
            || (str[i] == 's' && str[i + 1] == 'i' && str[i + 2] == 'n')
            || (i + 2 < length && str[i] == 'c' && str[i + 1] == 't' && str[i + 2] == 'g'))) {
            if (str[i] == 'c' && str[i + 1] == 't')
                str[i] = 'C';
            for (j = i + 1; j < length; j++) {
                str[j] = str[j + 2];
            }
            length -= 2;
            ++i;
            flag_un_op = 1;
        }
        if (!flag_num_op && ((str[i] == 't' && str[i + 1] == 'g') || (str[i] == 'l' && str[i + 1] == 'n'))) {
            for (j = i + 1; j < length; j++) {
                str[j] = str[j + 1];
            }
            length -= 1;
            ++i;
            flag_un_op = 1;
        }
        if (flag_num_op == 0 && flag_un_op == 0)
            *flag = 1;
        flag_num_op = 0;
        flag_un_op = 0;
    }
    str[length + 1] = '\0';
    return str;
}
bool cmp_priority(char sym1, char sym2) {
    const int matrix[2][6] = {{'(', '+', '-', '/', '*', '~'}, {'0', '1', '1', '2', '2', '3'}};
    bool result = 0;
    for (int i = 0; i < 6; i++) {
        if (sym1 == matrix[0][i])
            sym1 = matrix[1][i];
        if (sym2 == matrix[0][i])
            sym2 = matrix[1][i];
    }
    if ((int)sym1 >= (int)sym2)
        result = 1;
    return result;
}
Deque* parse(char* str) {
    Node data;
    data.num = 0;
    std::stack<char> operations;
    Deque* head = NULL;
    int length = strlen(str), i = 0;
    bool flag_error = 0;
    while (i < length && !flag_error) {
        // добавление в выходную строчку x
        if (str[i] == 'x') {
            data.sym = 'x';
            data.num = 0;
            head = push(head, &data);
            ++i;
        }
        // добавление в выходную строку числа
        if (is_number(str[i])) {
            data.sym = ' ';
            data.num = get_number(str, &i);
            head = push(head, &data);
            data.num = 0;
        }
        // закидывание в стек операции
        if (is_operation_for_parse(str[i])) {
            if (!operations.empty() && (cmp_priority(operations.top(), str[i]) && str[i] != '(')) {
                data.sym = operations.top();
                head = push(head, &data);
                operations.pop();
            }
            operations.push(str[i]);
            ++i;
            data.sym = ' ';
        }
        // если встретилась закрыв. скобка, то ищем откр. скобку
        if (str[i] == ')') {
            while (!operations.empty() && operations.top() != '(') {
                data.sym = operations.top();
                head = push(head, &data);
                operations.pop();
            }
            if (operations.top() != '(') {
                flag_error = 1;
            }
            operations.pop();
            if (!operations.empty() && is_operator(operations.top())) {
                data.sym = operations.top();
                head = push(head, &data);
                operations.pop();
            }
            ++i;
            data.sym = ' ';
        }
        // есил токены закончились, то выкидываем все операции из стека в выходную строчку
        if (i >= length) {
            while (!operations.empty()) {
                data.sym = operations.top();
                head = push(head, &data);
                operations.pop();
            }
        }
    }
    return head;
}
