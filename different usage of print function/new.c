#include <stdio.h>
#include <stdlib.h>
#define MAX 3

int main() {
    int  c, pos;
    char s[] = "%hello, world";
    char str[20];
    printf("|%-10s|", "hello");   // Left-justified
    printf("|%10s|\n", "hello");  // Right-justified

    printf("%s\n", s);
    printf("%10s\n", s);
    printf("%.10s\n", s);
    printf("%-10s\n", s);
    printf("%.15s\n", s);
    printf("%-15s\n", s);
    printf("%15.10s\n", s);
    printf("%-15.10s\n", s);
    sprintf(str, "%s", s);

    return 0;
}
