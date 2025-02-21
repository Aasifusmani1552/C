#include <stdio.h>
#include "calc.h"
#define MAXVAL 100
double val[MAXVAL];
int    stack_pointer = 0;
void   push(double f) {
    if (stack_pointer < MAXVAL) {
        val[stack_pointer++] = f;
    } else
        printf("stack is full can't push %g\n", f);
}

double pop(void) {
    if (stack_pointer > 0) {
        double value = val[--stack_pointer];
        return value;
    } else {
        printf("Stack is empty\n");
        return 0.0;
    }
}
