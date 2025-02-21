#include <ctype.h>
#include <stdio.h>
#include "calc.h"
#define NUMBER '0'
int getop(char s[]) {
    int i, c;
    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    s[1] = '\0';
    i    = 0;
    if (c == '-') {
        int next = getch();
        if (isdigit(next) || next == '.') {
            s[++i] = c = next;
        } else {
            ungetch(next);
            return c;
        }
    }
    if (isdigit(c) || c == '.') {
        if (isdigit(c)) {
            while (isdigit(s[++i] = c = getch()))
                ;
        }
        if (c == '.') {
            while (isdigit(s[++i] = c = getch()))
                ;
        }
        s[++i] = '\0';
        if (c != EOF) {
            ungetch(c);
        }
        return NUMBER;
    }
    if (isalpha(c)) {
        if ((s[1] = c = getch()) == '=') {
            i = 2;
            while (isdigit(s[i] = c = getch()) || c == '.') {
                i++;
            }
            s[i] = '\0';
            return s[0];
        } else {
            ungetch(c);
            return s[0];
        }
    }
    if (ispunct(c)) {
        return c;
    }
    return c;
}