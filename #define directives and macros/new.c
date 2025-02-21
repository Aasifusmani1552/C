#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#define swap(t, x, y)  \
    {                  \
        t temp = x;    \
        x      = y;    \
        y      = temp; \
    }
#define concat(a, b) a##b
#define dprint(expre) printf(#expre "= %g\n", expre)
int main() {
    float a, b;
    a = 10;
    b = 20;
    dprint(a / b);
}