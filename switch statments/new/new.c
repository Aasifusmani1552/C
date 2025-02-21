#include <stdio.h>
#include <stdlib.h>
void escape(char s[], const char t[])
{
    int i, j;
    for (i = 0, j = 0; t[i] != '\0'; i++)
    {
        switch (t[i])
        {
        case '\n':
            s[j++] = '\\';
            s[j++] = 'n';
            break;
        case '\t':
            s[j++] = '\\';
            s[j++] = 't';
            break;
        default:
            s[j++] = t[i];
            break;
        }
    }
    s[j] = '\0';
}
int main()
{
    char original[] = "Hello world\nhow are you\tare you alright";
    char modified[100];
    escape(modified, original);
    printf("the modified string is:%s", modified);
    return 0;
}