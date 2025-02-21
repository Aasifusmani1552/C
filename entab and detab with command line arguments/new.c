#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAB_WIDTH 8

int        tab_width(char s[]);
static int default_tabs = 8;

void detab();
void entab();

int main(int argc, char* argv[]) {
    if (argc > 1) {
        char* arg = argv[1];
        if (isdigit(*arg)) {
            default_tabs = tab_width(arg);
        }
    }
    detab();
}
int tab_width(char s[]) {
    return atoi(s);
}
void detab() {
    int c, pos = 0;
    while ((c = getchar()) != EOF) {
        if (c == '\t') {
            int spaces = default_tabs - (pos % default_tabs);
            for (int i = 0; i < spaces; i++) {
                putchar(' ');
                pos++;
            }

        } else {
            putchar(c);
            pos++;
        }
        if (c == '\n') {
            pos = 0;
        }
    }
}
void entab() {
    int c, pos = 0, space_count = 0;
    while ((c = getchar()) != EOF) {
        if (c == ' ') {
            space_count++;

            if (space_count == default_tabs) {
                putchar('\t');
                space_count = 0;
            }
            pos++;
        } else {
            while (space_count > 0) {
                putchar(' ');
                space_count--;
            }

            putchar(c);
            pos++;
            if (c == '\n') {
                pos = 0;
            }
        }
    }
}