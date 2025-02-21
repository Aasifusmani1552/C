#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXVAL 100
double val[MAXVAL];
int    stack_pointer = 0;
void   push(double f);
double pop(void);

int main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("Usage: expr op1 op2 .... operator\n");
        return 0;
    }
    for (int i = 1; i < argc; i++) {
        char* arg = argv[i];
        if (isdigit(arg[0]) || (arg[0] == '-' && isdigit(arg[1]))) {
            push(atof(arg));
        } else if (strlen(arg) == 1) {
            double op2, op1;
            switch (arg[0]) {
                case '+':
                    push(pop() + pop());
                    break;
                case 'x':
                    if (stack_pointer > 1) {
                        op2 = pop();
                        op1 = pop();
                        push(op1 * op2);
                    } else
                        break;
                case '-': {
                    op2         = pop();
                    op1         = pop();
                    double temp = op1 - op2;
                    if (op1 == 0.0 && temp == -op2) {
                        push(-temp);
                    } else {
                        push(temp);
                        break;
                    }
                }
                case '/':
                    op2 = pop();
                    op1 = pop();
                    if (op2 != 0.0 && op1 != 0.0) {
                        push(op1 / op2);
                    } else if (op1 == 0.0) {
                        push(op2);
                    } else {
                        printf("ERROR: the divisor is %.2f\n", op2);
                        push(op1);
                    }
                    break;
                default:
                    printf("Error: invalid operator!!\n");
                    break;
            }
        } else
            printf("Error: invalid input %s\n", arg);
    }
    if (stack_pointer > 1) {
        printf(
            "Error: Not Enough Operands\nResult: %.2f\n"
            "Remaining: %.2f\n",
            val[--stack_pointer], val[0]);
    } else {
        printf("Result : %.2f\n", val[stack_pointer - 1]);
    }
}

void push(double f) {
    if (stack_pointer < MAXVAL) {
        val[stack_pointer++] = f;
    } else {
        printf("stack is full can't push %g\n", f);
        exit(0);
    }
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
