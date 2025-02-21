#include <stdio.h>
#include <stdlib.h>
void m_strcpy(char* s, char* t) {
    while ((*s = *t) != '\0') {
        s++;
        t++;
    }
}
void mm_strcpy(char* s, char* t) {
    int i = 0;
    while ((s[i] = t[i]) != '\0') {
        i++;
    }
}
void mmm_strcpy(char* s, char* t) {
    while ((*s++ = *t++) != '\0')
        ;
}
/*in this version of strcpy, we do not use a check for \0, because in c
arguments are evaluated as boolean value i.e. 0 or 1, so \0 is 0, when t copies
to s with \0 the compiler automatically evaluates \0 as 0 and loop exits.*/
void n_strcpy(char* s, char* t) {
    while (*s++ = *t++)
        ;
}
int main() {
    char tobecop[] = "hellow world";
    char intocop[15];
    n_strcpy(intocop, tobecop);
    printf("%s", intocop);
    return 0;
}