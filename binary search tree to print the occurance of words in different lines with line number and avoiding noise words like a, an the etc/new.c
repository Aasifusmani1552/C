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

struct linklist {
    int              lnum;
    struct linklist* ptr;
};

struct tnode {
    char*            word;
    struct linklist* lines;
    struct tnode*    left;
    struct tnode*    right;
};

int              getword(char* word, int lim);
struct tnode*    talloc(void);
int              noiseword(char* w);
void             addln(struct tnode* p, int linenum);
struct linklist* lalloc(void);
void             treeprint(struct tnode* p);
struct tnode*    m_addtree(struct tnode* p, char* w, int linenum);
char*            m_strdup(char* s);

int main(int argc, char* argv[]) {
    struct tnode* root;
    char          word[MAXWORD];
    int           linenum = 1;
    root                  = NULL;
    while (getword(word, MAXWORD) != EOF) {
        if (isalpha(word[0]) && noiseword(word) == -1) {
            root = m_addtree(root, word, linenum);
        } else if (word[0] == '\n') {
            linenum++;
        }
    }
    treeprint(root);
    return 0;
}

int getword(char* word, int lim) {
    int   c;
    char* w = word;
    while (isspace(c = getch()) && c != '\n')
        ;

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

struct tnode* m_addtree(struct tnode* p, char* w, int linenum) {
    int cond;
    if (p == NULL) {
        p              = talloc();
        p->word        = m_strdup(w);
        p->lines       = lalloc();
        p->lines->lnum = linenum;
        p->lines->ptr  = NULL;
        p->left = p->right = NULL;
    } else if ((cond = strcmp(w, p->word)) == 0) {
        addln(p, linenum);
    } else if (cond < 0) {
        p->left = m_addtree(p->left, w, linenum);
    } else
        p->right = m_addtree(p->right, w, linenum);
    return p;
}

void treeprint(struct tnode* p) {
    struct linklist* temp;
    if (p != NULL) {
        treeprint(p->left);
        printf("%10s: ", p->word);
        for (temp = p->lines; temp != NULL; temp = temp->ptr) {
            printf("%4d ", temp->lnum);
        }
        printf("\n");
        treeprint(p->right);
    }
}

struct linklist* lalloc(void) {
    return (struct linklist*) malloc(sizeof(struct linklist));
}
void addln(struct tnode* p, int linenum) {
    struct linklist* temp;
    temp = p->lines;

    while (temp->ptr != NULL && temp->lnum != linenum) {
        temp = temp->ptr;
    }
    if (temp->lnum != linenum) {
        temp->ptr       = lalloc();
        temp->ptr->lnum = linenum;
        temp->ptr->ptr  = NULL;
    }
}
int noiseword(char* w) {
    static char* nw[] = {"a",  "an", "and",  "are", "in",   "is",
                         "of", "or", "that", "the", "this", "to"};
    int          cond, mid;
    int          low  = 0;
    int          high = sizeof(nw) / sizeof(char*) - 1;
    while (low <= high) {
        mid = (low + high) / 2;
        if ((cond = strcmp(w, nw[mid])) < 0) {
            high = mid - 1;
        } else if (cond > 0) {
            low = mid + 1;
        } else
            return mid;
    }
    return -1;
}