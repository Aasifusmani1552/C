#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 1000
#define MAXWORD 1000

void ungetch(int c);
int  getch(void);
char buff[BUFSIZE];
int  bufp = 0;

struct words {
    char* words_n[MAXWORD];
    int   count[MAXWORD];
};
struct words* ps;
int           w_counter = 0;

struct tnode {
    char*         word;
    int           count;
    struct tnode* left;
    struct tnode* right;
};

int           getword(char* word, int lim);
struct tnode* talloc(void);
void          extractor(struct tnode* p);
struct tnode* m_addtree(struct tnode* p, char* w);
char*         m_strdup(char* s);
void          treeprint(struct words* p);
void          n_swap(int* i, int* j);
void          s_swap(char** v, char** s);

int main(int argc, char* argv[]) {
    struct tnode* root;
    char          word[MAXWORD];
    ps = (struct words*) malloc(sizeof(struct words));
    if (ps == NULL) {
        printf("memory allocation failed!!\n");
        return 1;
    }
    root = NULL;
    while (getword(word, MAXWORD) != EOF) {
        if (isalpha(word[0])) {
            root = m_addtree(root, word);
        }
    }
    extractor(root);
    treeprint(ps);
    free(ps);
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

struct tnode* m_addtree(struct tnode* p, char* w) {
    int cond;
    if (p == NULL) {
        p        = talloc();
        p->word  = m_strdup(w);
        p->count = 1;
        p->left = p->right = NULL;
    } else if ((cond = strcmp(w, p->word)) == 0) {
        p->count++;
    } else if (cond < 0) {
        p->left = m_addtree(p->left, w);
    } else
        p->right = m_addtree(p->right, w);
    return p;
}

void extractor(struct tnode* p) {
    if (p != NULL) {
        extractor(p->right);
        ps->words_n[w_counter] = p->word;
        ps->count[w_counter]   = p->count;
        w_counter++;
        extractor(p->left);
    }
}
void s_swap(char** v, char** s) {
    char* temp;
    temp = *s;
    *s   = *v;
    *v   = temp;
}

void n_swap(int* i, int* j) {
    int temp;
    temp = *i;
    *i   = *j;
    *j   = temp;
}

void treeprint(struct words* p) {
    for (int i = 0; i < w_counter - 1; i++) {
        for (int j = i + 1; j < w_counter; j++) {
            if (p->count[i] < p->count[j]) {
                s_swap(&p->words_n[i], &p->words_n[j]);
                n_swap(&p->count[i], &p->count[j]);
            }
        }
    }
    for (int i = 0; i < w_counter; i++) {
        printf("%4d: %s\n", p->count[i], p->words_n[i]);
    }
}