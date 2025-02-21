#include <ctype.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define STDOUT 1
void filecopy(int, int);

int main(int argc, char* argv[]) {
    int fd;

    if (argc == 1) {
        int c;
        while ((c = getchar()) != EOF) {
            putchar(c);
        }
    } else {
        while (--argc > 0) {
            if ((fd = open(*++argv, O_RDONLY, 0)) < 0) {
                perror("can't open:");
                exit(1);
            } else {
                filecopy(fd, STDOUT);
                close(fd);
            }
        }
    }
    return 0;
}

void filecopy(int fd, int td) {
    char buf[BUFSIZ];
    int  c;
    while ((c = read(fd, buf, BUFSIZ)) > 0) {
        if (write(td, buf, c) != c) {
            perror("error writing file");
            exit(1);
        }
    }
    if (c < 0) {
        perror("error reading file");
        exit(1);
    }
}
