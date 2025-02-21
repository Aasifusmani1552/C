#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define HASHSIZE 101
#define MAXWORD 100
#define BUFSIZE 1000

void ungetch(int c);
int  getch(void);
char buff[BUFSIZE];
int  bufp = 0;

struct nlist {
    struct nlist* next;
    char*         name;
    char*         defn;
};
static struct nlist* hashtab[HASHSIZE];

unsigned      hash(char* s);
struct nlist* lookup(char* s);
char*         m_strdup(char* s);
int           getword(char* word, int lim);
struct nlist* m_install(char* name, char* defn);
void          free_hash();

int main() {
    printf("Enter any 5 words to store in table and search with keywords\n");
    char       maxword[MAXWORD] = {0};
    static int w_counter        = 0;
    char*      keywords[5]      = {"dd", "ak", "vk", "bs", "sj"};
    while (getword(maxword, MAXWORD) != EOF) {
        if (w_counter < 5) {
            m_install(keywords[w_counter], maxword);
            printf("%d of 5\n", w_counter + 1);
            w_counter++;
        } else {
            struct nlist* ptr = lookup(maxword);
            if (ptr != NULL) {
                printf("found:%s || %s\n", ptr->name, ptr->defn);
            } else {
                printf("keyword %s not found\n", maxword);
            }
        }
    }
    free_hash();
    return 0;
}

int getword(char* word, int lim) {
    int   c;
    char* w = word;
    while (isspace(c = getch()))
        ;

    if (c != EOF) {
        *w++ = c;
    } else
        return EOF;
    if (!isalpha(c)) {
        *w = '\0';
        return c;
    }
    for (; --lim > 0; w++) {
        if (!isalnum(*w = getch()) && *w != '_' && *w != ' ') {
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

char* m_strdup(char* s) {
    char* p;
    p = (char*) malloc(strlen(s) + 1);
    if (p != NULL) {
        strcpy(p, s);
    }
    return p;
}

unsigned hash(char* s) {
    unsigned hashval;
    for (hashval = 0; *s != '\0'; s++) {
        hashval = *s + 31 * hashval;
    }
    return hashval % HASHSIZE;
}

struct nlist* lookup(char* s) {
    struct nlist* np;
    for (np = hashtab[hash(s)]; np != NULL; np = np->next) {
        if ((strcmp(s, np->name)) == 0) {
            return np;
        }
    }
    return NULL;
}

struct nlist* m_install(char* name, char* defn) {
    struct nlist* np;
    unsigned      hashval;
    if ((np = lookup(name)) == NULL) {
        np = (struct nlist*) malloc(sizeof(*np));
        if (np == NULL || (np->name = m_strdup(name)) == NULL) {
            return NULL;
        }
        hashval          = hash(name);
        np->next         = hashtab[hashval];
        hashtab[hashval] = np;
    } else {
        free(np->defn);
    }
    if ((np->defn = m_strdup(defn)) == NULL) {
        return NULL;
    }
    return np;
}

void free_hash() {
    for (int i = 0; i < HASHSIZE; i++) {
        struct nlist* np = hashtab[i];
        while (np != NULL) {
            struct nlist* temp = np;
            np                 = np->next;
            free(temp->defn);
            free(temp->name);
            free(temp);
        }
        hashtab[i] = NULL;
    }
}
