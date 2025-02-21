#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLEN 1000
#define MAXLINE 100
int mgetline(char* s, int limit);

void tail();

int main(int argc, char* argv[]) {
    char* arg = argv[1];
    int   default_lines;
    if (argc == 2) {
        if (*arg == '-' && isalpha(arg[1])) {
            printf(
                "Error: invalid argument %c\n"
                "Usage: prg name <-num>\n",
                arg[1]);
            exit(1);
        } else if (isdigit(*arg)) {
            printf("Error: use \"-\" symbol before the argument!!\n");
            exit(2);
        } else if (*arg == '-' && isdigit(arg[1])) {
            default_lines = atoi(arg + 1);
            printf("default line is %d\n", default_lines);
        } else if (*argv[1] == '-') {
            printf("Please provide character after '-' character\n");
            exit(3);
        } else if (isalpha(*arg)) {
            default_lines = 5;
            printf(
                "invalid input!!\n"
                "Taking Default lines %d\n",
                default_lines);
        }

    } else {
        if (argc == 1) {
            default_lines = 5;
            printf("No Arguments Provided, Taking Default Lines %d\n",
                   default_lines);
        }
        if (argc > 2) {
            default_lines = 5;
            printf(
                "Don't provide extra arguments!!\n"
                "Taking Default lines %d\n",
                default_lines);
        }
    }
    tail(default_lines);
    return 0;
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
void tail(int s) {
    int   len = 0, nlines = 0;
    char* lines[MAXLINE];
    char  temp[MAXLEN];
    char  array[MAXLEN];

    while ((len = mgetline(temp, MAXLEN)) > 0) {
        static int i = 0;
        if (nlines >= MAXLEN) {
            printf("error: not enough space for more lines!!\n");
            return;
        }
        temp[len - 1] = '\0';
        strcpy(array + i, temp);
        lines[nlines] = &array[i];
        i += len;
        nlines++;
    }
    if (nlines <= s) {
        printf("too less number of lines!!\n");
        for (int j = 0; j < nlines; j++) {
            printf("%s\n", lines[j]);
        }
    } else if (nlines > s) {
        for (int k = nlines - s; k < nlines; k++) {
            printf("%s\n", lines[k]);
        }
    }
}