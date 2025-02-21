#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
/*basic recursive function: printd, which will change an int to an array just
 * like itoa function*/
void printd(int n) {
    if (n < 0) {
        putchar('-');
        n = -n;
    }
    if (n / 10) {
        printd(n / 10);
    }
    putchar(n % 10 + '0');
}
int fact(int n) {
    if (n == 0) {
        return 1;
    } else {
        return (n * fact(n - 1));
    }
}
int main() {
    int num;
    printf("Enter a number:");
    scanf("%d", &num);
    printf("the factorial of %d is %d", num, fact(num));
    return 0;
}