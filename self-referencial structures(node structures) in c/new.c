#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFSIZE 1000
#define MAXWORD 100
void ungetch(int c);
int  getch(void);
char buff[BUFSIZE];
int  bufp = 0;
struct tnode {
    char*         word;
    int           count;
    struct tnode* left;
    struct tnode* right;
};
int           getword(char*, int);
int           n_strcmp(char*, char*);
struct tnode* talloc();
char*         m_strdup(char*);
void          treeprint(struct tnode*);
struct tnode* addtree(struct tnode*, char*);

int main() {
    struct tnode* root;
    char          word[MAXWORD];
    root = NULL;
    while ((getword(word, MAXWORD)) != EOF) {
        if (isalpha(word[0])) {
            root = addtree(root, word);
        }
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
void treeprint(struct tnode* p) {
    if (p != NULL) {
        treeprint(p->left);
        printf("%d %s\n", p->count, p->word);
        treeprint(p->right);
    }
}
struct tnode* addtree(struct tnode* p, char* w) {
    int cond;
    if (p == NULL) {
        p        = talloc();
        p->word  = m_strdup(w);
        p->count = 1;
        p->left = p->right = NULL;
    } else if ((cond = n_strcmp(w, p->word)) == 0) {
        p->count++;
    } else if (cond < 0) {
        p->left = addtree(p->left, w);
    } else {
        p->right = addtree(p->right, w);
    }
    return p;
}
