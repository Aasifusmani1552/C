#include <stdio.h>
#include <stdlib.h>
int main()
{
    int c, i, nwhite, nother, ndigits[10];
    nwhite = nother = 0;
    for (i = 0; i < 10; i++)
    {
        ndigits[i] = 0;
    }
    while ((c = getchar()) != EOF)
    {
        switch (c)
        {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            ndigits[c - '0']++;
            break;
        case ' ':
        case '\n':
        case '\t':
            nwhite++;
            break;
        default:
            nother++;
            break;
        }
    }
    printf("Total number of other characters:%d\n", nother);
    printf("Total number of white space characters:%d\n", nwhite);
    for (i = 0; i < 10; i++)
    {
        printf("total number of %d : %d\n", i, ndigits[i]);
    }

    return 0;
}