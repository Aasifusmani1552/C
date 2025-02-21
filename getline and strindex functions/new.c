#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define limit 1000
mgetline(char s[], int lim)
{
    int c, i;
    i = 0;
    while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
    {
        s[i++] = c;
    }
    if (c == '\n')
    {
        s[i++] = c;
    }
    s[i] = '\0';
    return i;
}
strindex(char s[], char t[])
{
    int i, j, k;
    for (i = 0; s[i] != '\0'; i++)
    {
        for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++)
        {
        }

        if (k > 0 && t[k] == '\0')
        {
            return i;
        }
    }
    return -1;
}
int main()
{
    char pattern[] = "world";

    char source[limit];
    int result = 0;
    while (mgetline(source, limit) > 0)
    {
        if ((result = strindex(source, pattern)) >= 0)
        {
            printf("%d", result);
        }
    }

    return 0;
}