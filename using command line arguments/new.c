#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLINE 1000
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

int main(int argc, char* argv[]) {
    char  line[MAXLINE];
    int   found = 0;
    char* ffound;
    if (argc != 2) {
        printf("Usage: Find Pattern\n");
    } else {
        while ((mgetline(line, MAXLINE)) > 0) {
            ffound = strstr(line, argv[1]);
            if (ffound != NULL) {
                printf("%s", line);
                found++;
                printf("found at %d\n", ffound - line);
            }
        }
    }
    return 0;
}