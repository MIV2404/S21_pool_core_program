#include "structure.h"

#include <math.h>
#include <stdlib.h>
#include <string.h>

struct Polish_notation* add(double num, char oper, struct Polish_notation* elem) {
    struct Polish_notation* new_elem = (struct Polish_notation*)malloc(sizeof(struct Polish_notation));
    new_elem->number = num;
    new_elem->operator= oper;
    new_elem->next = NULL;
    if (elem != NULL) {
        elem->next = new_elem;
    }

    return new_elem;
}

void free_formula(struct Polish_notation** polish_formula) {
    struct Polish_notation* tmp = NULL;
    while (*polish_formula != NULL) {
        tmp = *polish_formula;
        *polish_formula = (*polish_formula)->next;
        free(tmp);
    }
    free(*polish_formula);
}

struct Stack* push(char chr, struct Stack* top) {
    struct Stack* new_top = (struct Stack*)malloc(sizeof(struct Stack));
    new_top->value = chr;
    if (top == NULL) {
        new_top->prev = NULL;
    } else {
        new_top->prev = top;
    }
    return new_top;
}

struct Stack* pop(struct Stack* top, char* chr) {
    struct Stack* tmp = top;
    *chr = top->value;
    top = top->prev;
    free(tmp);
    return top;
}

void mult_pop(struct Stack** operators, struct Polish_notation** polish_formula) {
    while (*operators != NULL) {
        char tmp = ' ';
        *operators = pop(*operators, &tmp);
        *polish_formula = add(-1, tmp, *polish_formula);
    }
}

struct Calc_stack* push_calc(double number, struct Calc_stack* top) {
    struct Calc_stack* new_top = (struct Calc_stack*)malloc(sizeof(struct Calc_stack));
    new_top->value = number;
    if (top == NULL) {
        new_top->prev = NULL;
    } else {
        new_top->prev = top;
    }
    return new_top;
}

struct Calc_stack* pop_calc(struct Calc_stack* top, double* num) {
    struct Calc_stack* tmp = top;
    *num = top->value;
    top = top->prev;
    free(tmp);
    return top;
}