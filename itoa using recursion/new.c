#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void itoa_recursive(int64_t n, char s[]) {  // itoa function using recursion.
    /*to handle smallest representable number in 64 bits*/
    int64_t    SMALLEST_REP_NUM = -9223372036854775807LL - 1;
    static int i =
        0;  // using static variable as it's value will not reinitialize in
            // every recursion but it will keep the value from the last
    if (n == SMALLEST_REP_NUM) {
        strcpy(s, "-9223372036854775808");
        return;
    }
    if (n < 0) {       // handling negative numbers
        s[i++] = '-';  // putting '-' at s[0]
        n      = -n;   // making the number negative
    }
    /*using recursion, the function will call itself until the base case i.e. if
     * n/10 comes zero that means if there is only one digit to copy*/
    if (n / 10) {
        itoa_recursive(n / 10, s);
    }
    s[i++] = n % 10 + '0';
    s[i]   = '\0';
}
int main() {
    int64_t num = -123545;
    char    str[1000];
    itoa_recursive(num, str);
    printf("%s\n", str);
    printf("%c", str[5]);
    return 0;
}