#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXBOT 3
#define MAXHDR 5
#define MAXLINE 100
#define MAXPAGE 15
void fileprint(FILE* fp, char* fname);
int  heading(char* fname, int pageno);

int main(int argc, char* argv[]) {
    FILE* fp;
    if (argc == 1) {
        fileprint(stdin, " ");
    } else {
        while (--argc > 0) {
            if ((fp = fopen(*++argv, "r")) == NULL) {
                fprintf(stderr, "print: can't open %s\n", *argv);
                exit(1);
            } else {
                fileprint(fp, *argv);
                fclose(fp);
            }
        }
    }

    return 0;
}

int heading(char* fname, int pageno) {
    int ln = 3;
    fprintf(stdout, "\n\n");
    fprintf(stdout, "%s     page %d\n", fname, pageno);
    while (ln++ < MAXHDR) {
        fprintf(stdout, "\n");
    }
    return ln;
}

void fileprint(FILE* fp, char* fname) {
    int  lineno = 0, pageno = 1;
    char line[MAXLINE];
    lineno = heading(fname, pageno);

    while (fgets(line, MAXLINE, fp) != NULL) {
        if (lineno > MAXPAGE - MAXBOT) {
            fprintf(stdout, "\n\n===End of Page %d===\n\n", pageno);
            pageno++;
            lineno = heading(fname, pageno);
        }
        fputs(line, stdout);
        lineno++;
    }
    fprintf(stdout, "\n\n===End of Page %d===\n\n", pageno);
}