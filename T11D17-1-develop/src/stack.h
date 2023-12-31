#ifndef SRC_STACK_H
#define SRC_STACK_H

#include <stdlib.h>

struct elem {
    int val;
    struct elem* next;
};

struct elem* init(int val);
void push(struct elem** head, int val);
int pop(struct elem** head);
void destroy(struct elem** head);

#endif  // SRC_STACK_H
