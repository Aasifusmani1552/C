#include <ctype.h>
#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int m_getchar(void);
int main(int argc, char* argv[]) {
    int c;
    while ((c = m_getchar()) != EOF) {
        fprintf(stdout, "%c", c);
    }
    if (c == EOF) {
        fprintf(stderr, "error: end of file detected!!\n");
    }
    return 0;
}
int m_getchar(void) {
    static char  buf[BUFSIZ];
    static char* bufp = buf;
    static int   n    = 0;
    if (n == 0) {
        n    = read(0, buf, sizeof buf);
        bufp = buf;
    }
    return (--n >= 0) ? (unsigned char) *bufp++ : EOF;
}