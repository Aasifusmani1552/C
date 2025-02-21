#include <ctype.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define PERMS 0666
#define OPEN_MAX 20

typedef struct m_iobuf {
    int   cnt;
    char* ptr;
    char* base;
    int   flag;
    int   fd;
} FILED;
FILED m_iob[OPEN_MAX];

FILED* mm_fopen(char* name, char* mode);

int m_fillbuf(FILED* ptr);

#define m_getc(p) \
    (--(p)->cnt > 0 ? (unsigned char) *(++(p)->ptr) : m_fillbuf(p))

enum { _READ = 01, _WRITE = 02, _UNBUF = 04, _EOF = 010, _ERR = 020 };

int main(int argc, char* argv[]) {
    FILED* ptr = mm_fopen("myfile.txt", "r");
    int    x;
    while ((x = m_getc(ptr)) != EOF) {
        putc(x, stdout);
    }
    return 0;
}

FILED* mm_fopen(char* name, char* mode) {
    int    fd;
    FILED* fp;

    if (*mode != 'r' && *mode != 'w' && *mode != 'a')
        return NULL;

    for (fp = m_iob; fp < m_iob + OPEN_MAX; fp++) {
        if ((fp->flag & (_READ | _WRITE)) == 0)
            break;
    }
    if (fp >= m_iob + OPEN_MAX)
        return NULL;
    if (*mode == 'w')
        fd = creat(name, PERMS);
    else if (*mode == 'a') {
        if ((fd = open(name, O_WRONLY, 0)) == -1)
            fd = creat(name, PERMS);
        lseek(fd, 0, SEEK_END);
    } else
        fd = open(name, O_RDONLY, 0);

    if (fd == -1)
        return NULL;
    fp->fd   = fd;
    fp->cnt  = 0;
    fp->base = NULL;
    fp->flag = (*mode == 'r') ? _READ : _WRITE;
    return fp;
}

int m_fillbuf(FILED* ptr) {
    int bufsize;

    if ((ptr->flag & (_READ | _EOF | _ERR)) != _READ) {
        return EOF;
    }

    bufsize = (ptr->flag & _UNBUF) ? 1 : BUFSIZ;

    if (ptr->base == NULL) {
        ptr->base = (char*) malloc(bufsize);
        if (ptr->base == NULL) {
            return EOF;
        }
    }

    ptr->ptr = ptr->base;
    ptr->cnt = read(ptr->fd, ptr->ptr, bufsize);

    if (ptr->cnt <= 0) {
        free(ptr->base);
        ptr->base = NULL;
        if (ptr->cnt == 0) {
            ptr->flag |= _EOF;
        } else
            ptr->flag |= _ERR;

        ptr->cnt = 0;
        return EOF;
    }
    return (unsigned char) *ptr->ptr;
}