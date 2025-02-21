#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "calc.h"
#define BUFSIZE 100
#define MAXOP 100
void          clear_stack();
void          print_top();
void          swap();
void          duplicate();
void          triggers();
extern double val[];
extern int    stack_pointer;

double variables[26];

int main() {
    int    type;
    double temp = 0;
    double op2;
    double op1;
    char   main_source[MAXOP];
    triggers();
    while (((type = getop(main_source)) != EOF)) {
        if (isalpha(type) && main_source[1] == '=') {
            int var_index        = type - 'a';
            variables[var_index] = atof(main_source + 2);
            printf("Assigned %g to variable %c\n", variables[var_index], type);
            continue;
        }
        switch (type) {
            case NUMBER:
                push(atof(main_source));
                break;
            case 'a' ... 'z':
                push(variables[type - 'a']);
                printf("pushed value %g from variable %c\n",
                       variables[type - 'a'], type);
                break;
            case '+':
                push(pop() + pop());
                break;
            case '*':
                if (stack_pointer > 1) {
                    op2 = pop();
                    op1 = pop();
                    push(op1 * op2);
                } else
                    printf("not enough values in stack\n");
                break;
            case '-': {
                op2  = pop();
                op1  = pop();
                temp = op1 - op2;
                if (op1 == 0.0 && temp == -op2) {
                    push(-temp);
                } else
                    push(temp);
                break;
            }
            case '/':
                op2 = pop();
                op1 = pop();
                if (op2 != 0.0 && op1 != 0.0) {
                    push(op1 / op2);
                } else if (op1 == 0.0) {
                    push(op2);
                } else {
                    printf("ERROR: the divisor is %g", op2);
                    push(op1);
                }
                break;
            case '%': {
                op2 = pop();
                op1 = pop();
                if (op2 != 0.0 && op1 != 0.0) {
                    temp = (int) op1 % (int) op2;
                    push(temp);
                } else if (op1 == 0.0) {
                    push(op2);
                } else {
                    printf("ERROR: the divisor is %g", op2);
                    push(op1);
                }
                break;
            }
            case '\n':
                for (int z = 0; z < stack_pointer; z++) {
                    printf("|\t%g\t|", val[z]);
                }
                printf("\n");
                break;
            case '@':
                clear_stack();
                printf("stack is cleared\n");
                break;
            case '!':
                duplicate();
                break;
            case '#':
                swap();
                break;
            case '~':
                print_top();
                break;
            default:
                printf("unknown or invalid command %s\n", main_source);
                break;
        }
    }

    return 0;
}

void clear_stack() {
    stack_pointer = 0;
}
void duplicate() {
    if (stack_pointer > 0 && stack_pointer < MAXVAL) {
        val[stack_pointer] = val[stack_pointer - 1];
        stack_pointer++;
    } else {
        printf(
            "ERROR: Cannot duplicate element, stack is either empty or "
            "full.\n");
    }
}
void swap() {
    if (stack_pointer > 1) {
        double temp            = val[stack_pointer - 1];
        val[stack_pointer - 1] = val[stack_pointer - 2];
        val[stack_pointer - 2] = temp;
    } else
        printf("ERROR: Not Enough Elements To Swap\n");
}
void print_top() {
    if (stack_pointer > 0) {
        printf("Top value %g\n", val[stack_pointer - 1]);
    } else
        printf("ERROR: Stack Is Empty\n");
}
void triggers() {
    printf("PRESS @ TO CLEAR STACK\n");
    printf("PRESS ! TO DUPLICATE A NUMBER\n");
    printf("PRESS # TO SWAP TOP TWO NUMBERS\n");
    printf("PRESS ~ TO PRINT TOP MOST NUMBER\n");
    printf("TO ASSIGN A VALUE TO AN ALPHABET, USE FORMAT EX. a=anynumber\n");
    printf(
        "!! WHILE ASSIGNING VALUES TO ALPHABETS, DON'T USE SPACES BETWEEN "
        "ALPHABETS AND = SIGN !!\n");
}