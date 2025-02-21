#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ALLOCSIZE 10000
int mgetline(char* s, int limit) {
    int   c;
    char* s_start = s;
    while (limit > 0 && ((c = getchar())) != EOF && c != '\n') {
        *s++ = c;
        limit--;
    }
    if (c == '\n') {
        *s++ = c;
    }
    *s = '\0';
    return s - s_start;
}
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
void swap(char* v[], int i, int j) {
    char* temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}
int n_strcmp(char* s, char* t) {
    while (*s == *t) {
        if (*s == '\0') {
            return 0;
        }
        s++;
        t++;
    }
    return *s - *t;
}

void m_qsort(char* v[], int left, int right) {
    int last, i, res;
    if (left >= right) {
        return;
    }
    swap(v, left, (left + right) / 2);
    last = left;
    for (i = left + 1; i <= right; i++) {
        if ((res = n_strcmp(v[i], v[left])) < 0) {
            swap(v, ++last, i);
        }
    }
    swap(v, left, last);
    m_qsort(v, left, last - 1);
    m_qsort(v, last + 1, right);
}