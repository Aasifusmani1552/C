#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFSIZE 1000
#define MAXWORD 100
#define YES 1
#define NO 0

void ungetch(int c);
int  getch(void);
char buff[BUFSIZE];
int  bufp = 0;

struct tnode {
    char*         word;
    int           match;
    struct tnode* left;
    struct tnode* right;
};

int           getword(char*, int);
struct tnode* talloc();
char*         m_strdup(char*);
struct tnode* m_addtree(struct tnode* p, char* w, int num, int* found);
int           compare(char* s, struct tnode* p, int num, int* found);
void          treeprint(struct tnode* p);

int main(int argc, char* argv[]) {
    struct tnode* root;  // root of binary search tree
    char          word[MAXWORD];
    int           found = NO;  // flag to show comparison
    int           num;

    num  = (argc > 1) ? atoi(argv[1])
                      : 6;  // dynamically setting comparison setting
    root = NULL;
    while (getword(word, MAXWORD) != EOF) {
        if (isalpha(word[0]) && strlen(word) >= num) {
            root = m_addtree(root, word, num, &found);
        }
        found = NO;
    }
    treeprint(root);
    return 0;
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
    if (c == '"' || c == '\'') {
        char next = (c == '"') ? '"' : '\'';
        while ((c = getch()) != next)
            ;
        ;
    }
    if (c != EOF) {
        *w++ = c;
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

struct tnode* talloc(void) {
    return (struct tnode*) (malloc(sizeof(struct tnode)));
}

char* m_strdup(char* s) {
    char* p;
    p = (char*) malloc(strlen(s) + 1);
    if (p != NULL) {
        strcpy(p, s);
    }
    return p;
}

struct tnode* m_addtree(struct tnode* p, char* w, int num, int* found) {
    int cond;
    if (p == NULL) {
        p        = talloc();
        p->word  = m_strdup(w);
        p->match = *found;
        p->left = p->right = NULL;
    } else if ((cond = compare(w, p, num, found)) < 0) {
        p->left = m_addtree(p->left, w, num, found);
    } else if (cond > 0) {
        p->right = m_addtree(p->right, w, num, found);
    }
    return p;
}

int compare(char* s, struct tnode* p, int num, int* found) {
    int   i;
    char* t = p->word;
    for (i = 0; *s == *t; i++, s++, t++) {
        if (*s == '\0') {
            return 0;
        }
    }
    if (i >= num) {
        *found   = YES;
        p->match = YES;
    }
    return *s - *t;
}

void treeprint(struct tnode* p) {
    if (p != NULL) {
        treeprint(p->left);
        if (p->match) {
            printf("%s\n", p->word);
        }
        treeprint(p->right);
    }
}