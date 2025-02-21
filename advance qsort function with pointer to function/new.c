#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLINE 500
#define MAXLEN 1000
#define ALLOCSIZE 1000
int   m_readlines(char allocray[ALLOCSIZE], int maxlines);
void  swap(void* v[], int i, int j);
int   n_strcmp(char* s, char* t);
void  m_qsort(void* v[], int left, int right, int (*comp)(void*, void*));
void  writelines(char* lineptr[], int nlines);
int   numcmp(char* s1, char* s2);
int   mgetline(char* s, int limit);
char* lineptr[MAXLINE];
int   fold      = 0;
int   directory = 0;

int main(int argc, char* argv[]) {
    char  allocray[ALLOCSIZE];
    int   nlines;
    int   reverse = 0;
    int   numeric = 0;
    char* arg     = argv[1];
    char  c;
    while (--argc > 0 && (*++argv)[0] == '-') {
        while ((c = *++arg)) {
            switch (c) {
                case 'n':
                    numeric = 1;
                    break;
                case 'r':
                    reverse = 1;
                    break;
                case 'f':
                    fold = 1;
                    break;
                case 'd':
                    directory = 1;
                    break;
                default:
                    printf(
                        "invalid argument\n"
                        "Usage: prgm -\"flags\"\n"
                        "default-sorting: Strings\n");
                    break;
            }
        }
    }
    if ((nlines = m_readlines(allocray, MAXLINE)) >= 0) {
        m_qsort((void**) lineptr, 0, nlines - 1,
                (int (*)(void*, void*))(numeric ? numcmp : n_strcmp));
        if (reverse) {
            int temp_lines = nlines;
            for (int i = 0; i < nlines / 2; i++, temp_lines--) {
                char* temp;
                temp                    = lineptr[i];
                lineptr[i]              = lineptr[temp_lines - 1];
                lineptr[temp_lines - 1] = temp;
            }
        }
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("error: input too big to sort\n");
        return 1;
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
void swap(void* v[], int i, int j) {
    void* temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}
int n_strcmp(char* s, char* t) {
    if (directory) {
        while (*s != '\0' && (!isalnum(*s) || isspace(*s))) {
            s++;
        }
        while (*t != '\0' && (!isalnum(*t) || isspace(*t))) {
            t++;
        }
    }
    while (*s != '\0' && *t != '\0') {
        char s_char = (*s >= 'a' && *s <= 'z' && fold) ? *s - 'a' + 'A' : *s;
        char t_char = (*t >= 'a' && *t <= 'z' && fold) ? *t - 'a' + 'A' : *t;
        if (s_char != t_char) {
            return s_char - t_char;
        }
        s++;
        t++;
    }
    return *s - *t;
}
int numcmp(char* s1, char* s2) {
    int v1, v2;
    v1 = atoi(s1);
    v2 = atoi(s2);
    if (v1 > v2) {
        return 1;
    } else if (v1 < v2) {
        return -1;
    } else
        return 0;
}
void m_qsort(void* v[], int left, int right, int (*comp)(void*, void*)) {
    int last, i;
    if (left >= right) {
        return;
    }
    swap(v, left, (left + right) / 2);
    last = left;
    for (i = left + 1; i <= right; i++) {
        if ((*comp)(v[i], v[left]) < 0) {
            swap(v, ++last, i);
        }
    }
    swap(v, left, last);
    m_qsort(v, left, last - 1, comp);
    m_qsort(v, last + 1, right, comp);
}
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
void writelines(char* lineptr[], int nlines) {
    for (int i = 0; i < nlines; i++) {
        printf("%s\n", lineptr[i]);
    }
}