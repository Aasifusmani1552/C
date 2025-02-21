#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFSIZE 100
#define MAXTOKEN 100
enum days { NAME, BRACKETS, PARENS };
int  gettoken(void);
void dirdcl(void);
void dcl(void);
int  n_strcmp(char* s, char* t);
int  tokentype;
char token[MAXTOKEN];
char name[MAXTOKEN];
char datatype[MAXTOKEN];
char out[1000];
char buff[BUFSIZE];
int  bufp          = 0;
char c_data[]      = "char";
char i_data[]      = "int";
char v_data[]      = "void";
int  bracket_count = 0;
int  paren_count   = 0;
int  temp_token    = 0;
void ungetch(int c);
int  getch(void);
int  main() {
    while (gettoken() != EOF) {
        strcpy(datatype, token);
        if (n_strcmp(datatype, i_data) != 0 &&
            n_strcmp(datatype, c_data) != 0 &&
            n_strcmp(datatype, v_data) != 0) {
            printf("Error: invalid datatype!!\n");
            return 0;
        }
        out[0] = '\0';
        dcl();

        if (tokentype != '\n') {
            if (tokentype != '(' && tokentype != ')') {
                printf("error: syntax mismatch because of %c\n", tokentype);
            } else {
                printf("error: syntax mismatch because of %c\n",
                        (tokentype - 1));
            }
            return 0;
        }
        printf("%s: %s %s \n", name, out, datatype);
    }

    return 0;
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
int gettoken(void) {
    int   c;
    char* p = token;
    while ((c = getch()) == ' ' || c == '\t')
        ;
    if (c == '(') {
        paren_count++;
        if ((c = getch()) == ')') {
            paren_count--;
            strcpy(token, "()");
            return tokentype = PARENS;
        } else {
            ungetch(c);
            return tokentype = '(';
        }
    } else if (c == '[') {
        bracket_count++;
        for (*p++ = c; (*p++ = getch()) != ']';) {
            if (*--p == '\n') {
                printf("error: unmatched '['\n");
                return 0;
            }
        }
        bracket_count--;
        *p               = '\0';
        return tokentype = BRACKETS;
    } else if (c == ']') {
        if (bracket_count == 0) {
            printf("error: unmatched ']'\n");
            exit(1);
        }
        bracket_count--;
        return tokentype = ']';
    } else if (isalpha(c)) {
        for (*p++ = c; isalnum(c = getch());) {
            *p++ = c;
        }
        *p = '\0';
        ungetch(c);
        return tokentype = NAME;
    } else
        return tokentype = c;
}
void dcl(void) {
    int ns;
    for (ns = 0; gettoken() == '*';) {
        ns++;
    }
    dirdcl();
    if (tokentype == '(') {
        printf("error: missing )\n");
        exit(4);
    }
    if (bracket_count > 0) {
        printf("error: missing ]\n");
        exit(1);
    }

    if (temp_token == BRACKETS && n_strcmp(name, token) != 0) {
        printf(
            "error: malformed declaration\n"
            "provide name %s before []\n",
            token);
        exit(2);
    }

    while (ns-- > 0) {
        strcat(out, " pointer to");
    }
}
void dirdcl(void) {
    int type;

    if (tokentype == '(') {
        dcl();
        if (tokentype != ')') {
            printf("error: missing )\n");
            exit(4);
        }
    } else if (tokentype == NAME) {
        strcpy(name, token);
    } else {
        temp_token = tokentype;
        printf("error:expected name or (dcl)\n");
        exit(3);
    }
    while ((type = gettoken()) == PARENS || type == BRACKETS) {
        if (type == PARENS) {
            strcat(out, " function returning");
        } else {
            strcat(out, " array");
            strcat(out, token);
            strcat(out, " of");
        }
    }
}
int n_strcmp(char* s, char* t) {
    while (*s == *t) {
        if (*s == '\0') {
            return 0;
        }
        s++;
        t++;
    }
    return 1;
}
