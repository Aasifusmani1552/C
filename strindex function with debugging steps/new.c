#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
int strindex(char s[], char t[])
{
    int i, j, k;
    int length_s = 0;
    int length_t = 0;
    int found = -1;
    for (i = 0; s[i] != '\0'; i++)
    {
        length_s++;
    }
    for (k = 0; t[k] != '\0'; k++)
    {
        length_t++;
    }
    printf("length of s is %d and length of t is %d", length_s, length_t);

    for (i = length_s - length_t; i >= 0; i--)
    {
        printf("Checking from index: %d\n", i);
        for (j = i, k = 0; k < length_t && s[j] == t[k]; j++, k++)
        {
            printf("Matching s[%d]: '%c' with t[%d]: '%c'\n", j, s[j], k, t[k]);
        }
        if (k == length_t)
        {
            found = i;
            printf("Found match at index: %d\n", found);
            break;
        }
    }
    return found;
}
int main()
{
    char source[] = "This is the world of fears, world is full of darkness and tears, we can't imagine a world without tears";
    char pattern[] = "world";
    int result = 0;
    result = strindex(source, pattern);
    printf("%d", result);

    return 0;
}