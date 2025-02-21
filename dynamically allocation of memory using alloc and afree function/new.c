#include <stdio.h>
#include <stdlib.h>
#define ALLOCSIZE 10000
static char  allocbuf[ALLOCSIZE];
static char* allocp = allocbuf;
char*        alloc(int n) {
    if (allocbuf + ALLOCSIZE - allocp >= n) {
        allocp += n;
        return allocp - n;
    } else
        return 0;
}
void afree(char* p) {
    if (p >= allocbuf && p < allocbuf + ALLOCSIZE) {
        allocp = p;
    }
}
int main() {
    char* p1 = alloc(500);
    if (p1 != NULL) {
        printf("successfully allocated 500 bytes\n");
    } else
        printf("not enough storage left");
    afree(p1);
    printf("%d", *allocp);
    return 0;
}