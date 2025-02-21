#include <stdio.h>
#define BUFSIZE 10
char buff[BUFSIZE];
int bufp = 0;
void ungetch(int c)
{
    if (bufp >= BUFSIZE)
    {
        printf("ERROR: ungetch: buffer is full\n");
    }
    else
    {
        buff[bufp++] = c;
    }
}

int getch(void)
{
    return (bufp > 0) ? buff[--bufp] : getchar();
}