#include <stdio.h>
#include <stdlib.h>
int m_strlen(char s[]) // using s[] and *s both works as an array name is the pointer of its first element so s[10] is basically &s or char*s;
{
    int n;
    for (n = 0; *s != '\0'; s++)
        n++;
    return n;
}

int main()
{
    char greetings[5] = "hello";
    char *p = &greetings[2];
    printf("%d\n", m_strlen(greetings));
    printf("%d\n", greetings);
    printf("%c", *(p - 1));
    printf("%c", *(greetings));
    return 0;
}