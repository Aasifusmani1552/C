#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUM(x) ((x) * (x))
void m_minprintf(char* fmt, ...);

int main(int argc, char* argv[]) {
    int x = 077;
    m_minprintf("%o", x);
    return 0;
}

void m_minprintf(char* fmt, ...) {
    va_list ap;
    char *  p, *sval, character;
    int     ival;
    double  dval;

    va_start(ap, fmt);
    for (p = fmt; *p; p++) {
        if (*p != '%') {
            putchar(*p);
            continue;
        }
        switch (*++p) {
            case 'd':
                ival = va_arg(ap, int);
                printf("%d", ival);
                break;
            case 'f':
                dval = va_arg(ap, double);
                printf("%f", dval);
                break;
            case 's':
                for (sval = va_arg(ap, char*); *sval; sval++) {
                    putchar(*sval);
                }
            case 'c':
                character = va_arg(ap, int);
                putchar(character);
                break;
            case 'i':
                ival = va_arg(ap, int);
                printf("%i", ival);
                break;
            case 'x':
            case 'X':
                ival = va_arg(ap, int);
                printf("%x", ival);
                break;
            case 'o':
                ival = va_arg(ap, int);
                printf("%o", ival);
                break;
            default:
                putchar(*p);
                break;
        }
    }
    va_end(ap);
}