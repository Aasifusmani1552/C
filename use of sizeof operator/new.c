#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main() {
    printf("Size of char*: %zu bytes\n", sizeof(char));
    printf("Size of int*: %zu bytes\n", sizeof(int));
    printf("Size of void*: %zu bytes\n", sizeof(void));
    return 0;
}
