#include "header.h"
#define MAXLINE 5000
#define MAXLEN 1000

char* lineptr[MAXLINE];

int readlines(char* lineptr[], int maxlines) {
    int   len, nlines;
    char *p, lines[MAXLEN];
    nlines = 0;
    while ((len = mgetline(lines, MAXLEN)) > 0) {
        if (nlines >= maxlines || (p = alloc(len)) == NULL) {
            return -1;
        } else {
            lines[len - 1] = '\0';
            strcpy(p, lines);
            lineptr[nlines++] = p;
        }
    }
    return nlines;
}

void writelines(char* lineptr[], int nlines) {
    for (int i = 0; i < nlines; i++) {
        printf("%s\n", lineptr[i]);
    }
}

int m_readlines(char allocray[ALLOCSIZE], int maxlines) {
    int  len, nlines, i;
    char lines[MAXLEN];
    i      = 0;
    nlines = 0;
    while ((len = mgetline(lines, MAXLEN)) > 0) {
        if (nlines >= maxlines || i + len > ALLOCSIZE) {
            return -1;
        } else {
            lines[len - 1] = '\0';
            strcpy(allocray + i, lines);
            lineptr[nlines++] = &allocray[i];
            i += len;
        }
    }
    return nlines;
}
int main() {
    char allocray[ALLOCSIZE];
    int  nlines;
    if ((nlines = m_readlines(allocray, MAXLINE)) >= 0) {
        m_qsort(lineptr, 0, nlines - 1);
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("error: input too big to sort\n");
        return 1;
    }
}
