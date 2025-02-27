#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXWORD 100
#define BUFSIZE 100
#define NKEYS (sizeof(keytab) / sizeof(keytab[0]))
void ungetch(int c);
int  getch(void);
char buff[BUFSIZE];
int  bufp = 0;
struct key {
    char* word;
    int   count;
} keytab[] = {
    {"auto", 0},     {"break", 0},    {"case", 0},     {"char", 0},
    {"const", 0},    {"continue", 0}, {"default", 0},  {"for", 0},
    {"int", 0},      {"if", 0},       {"long", 0},     {"return", 0},
    {"struct", 0},   {"signed", 0},   {"unsigned", 0}, {"void", 0},
    {"volatile", 0}, {"while", 0},
};
int binsearch(char* word, struct key tab[], int n);
int n_strcmp(char* s, char* t);
int getword(char* word, int lim);

int main() {
    int  n;
    char word[MAXWORD];
    while (getword(word, MAXWORD) != EOF) {
        if (isalpha(word[0])) {
            if ((n = binsearch(word, keytab, NKEYS)) >= 0) {
                keytab[n].count++;
            }
        }
    }
    for (n = 0; n < NKEYS; n++) {
        if (keytab[n].count > 0) {
            printf("%4d %s\n", keytab[n].count, keytab[n].word);
        }
    }
    return 0;
}

int binsearch(char* word, struct key tab[], int n) {
    int cond;
    int low, mid, high;
    low  = 0;
    high = n - 1;
    while (low <= high) {
        mid = (low + high) / 2;
        if ((cond = n_strcmp(word, tab[mid].word)) < 0) {
            high = mid - 1;
        } else if (cond > 0) {
            low = mid + 1;
        } else
            return mid;
    }
    return -1;
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
void ungetch(int c) {
    if (bufp >= BUFSIZE) {
        printf("ERROR: ungetch: buffer is full\n");
    } else {
        buff[bufp++] = c;
    }
}

int getch(void) {
    return (bufp > 0) ? buff[--bufp] : getchar();
}
int getword(char* word, int lim) {
    int   c;
    char* w = word;
    while (isspace(c = getch()))
        ;
    if (c == '/') {
        if ((c = getch()) == '/') {
            while ((c = getch()) != '\n') {
                ;
            }
        } else if (c == '*') {
            while ((c = getch()) != EOF) {
                if (c == '*') {
                    if ((c = getch()) == '/') {
                        break;
                    } else
                        ungetch(c);
                }
            }
        }
    }
    if (c == '#') {
        while ((c = getch()) != '\n')
            ;
    }
    if (c != EOF) {
        *w++ = c;
    }
    if (c == '"') {
        while ((c = getch()) != '"')
            ;
    }
    if (!isalpha(c)) {
        *w = '\0';
        return c;
    }
    for (; --lim > 0; w++) {
        if (!isalnum(*w = getch()) && *w != '_') {
            ungetch(*w);
            break;
        }
    }
    *w = '\0';
    return word[0];
}
