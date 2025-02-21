#include <stdio.h>
#include <stdlib.h>
void swap(int* px, int* py) {
    int temp;
    temp = *px;
    *px  = *py;
    *py  = temp;
}
int main() {
    int  a = 10, b = 5;
    int *pa = &a, *pb = &b;
    swap(pa, pb);
    printf("%d and %d", a, b);
    return 0;
}