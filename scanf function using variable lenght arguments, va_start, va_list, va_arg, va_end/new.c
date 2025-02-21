#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUM(x) ((x) * (x))
void m_scanf(char* fmt, ...);

int main(int argc, char* argv[]) {
    int x;
    m_scanf("%o", &x);
    printf("%o", x);
    return 0;
}

void m_scanf(char* fmt, ...) {
    va_list ap;
    char *  p, *sval, *character;
    int*    ival;
    double* dval;

    va_start(ap, fmt);
    for (p = fmt; *p; p++) {
        if (*p != '%') {
            printf("usage: (\"o/oid\"), variable!!\n");
            exit(0);
        }
        switch (*++p) {
            case 'd':
                ival = va_arg(ap, int*);
                scanf("%d", ival);
                break;
            case 'f':
                dval = va_arg(ap, double*);
                scanf("%lf", dval);
                break;
            case 's':
                sval = va_arg(ap, char*);
                scanf("%s", sval);
                break;
            case 'c':
                character = (char*) va_arg(ap, int);
                scanf("%c", character);
                break;
            case 'i':
                ival = va_arg(ap, int*);
                scanf("%i", ival);
                break;
            case 'x':
            case 'X':
                ival = va_arg(ap, int*);
                scanf("%x", ival);
                break;
            case 'o':
                ival = va_arg(ap, int*);
                scanf("%o", ival);
                break;
            default:
                printf("invalid conversion character!!\n");
                break;
        }
    }
    va_end(ap);
}