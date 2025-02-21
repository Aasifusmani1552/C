#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
void reverse(char s[]);
void my_itoa(int n, char s[])
{
    int i = 0;
    int sign;
    if ((sign = n) < 0)
        n = -n;
    do
    {
        s[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);
    if (sign < 0)
    {
        s[i++] = '-';
    }
    s[i] = '\0';
    reverse(s);
}
void reverse(char s[])
{
    int i, j;
    int len = strlen(s);
    char temp; // very important to declare a temp variable to reverse the string
    for (i = 0, j = len - 1; i < j; i++, j--)
    {
        temp = s[i]; // ex. hello, temp contain h now
        s[i] = s[j]; // word looks like oello now
        s[j] = temp; // since temp contain h, so oello is now oellh, with the second iteration it will look like olleh, which is the reversed string
    }
}
int main()
{
    int num = 1458;
    char str_num[50];
    my_itoa(num, str_num);
    printf("the string from the integer looks like:%s", str_num);

    return 0;
}