#include <ctype.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define PERMS 0666
#define OPEN_MAX 20

typedef struct flags_status {
    unsigned int _READ : 1;
    unsigned int _WRITE : 1;
    unsigned int _EOF : 1;
    unsigned int _ERR : 1;
    unsigned int _UNBUF : 1;
} bitflags;

typedef struct m_iobuf {
    int      cnt;
    char*    ptr;
    char*    base;
    bitflags flags;
    int      fd;
} FILED;
FILED m_iob[OPEN_MAX];

FILED* mm_fopen(char* name, char* mode);

int  m_fillbuf(FILED* ptr);
void m_fclose(FILED* ptr);

#define m_getc(p) \
    (--(p)->cnt > 0 ? (unsigned char) *(++(p)->ptr) : m_fillbuf(p))

int main() {
    FILED* ptr = mm_fopen("myfile.txt", "r");
    if (!ptr) {
        fprintf(stderr, "Failed to open file!\n");
        return 1;
    }
    int x;
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
        if (!fp->flags._READ || !fp->flags._WRITE)
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
    if (*mode == 'r') {
        fp->flags._READ = 1;
    } else {
        fp->flags._WRITE = 1;
    }
    return fp;
}

int m_fillbuf(FILED* ptr) {
    int bufsize;

    if (!ptr->flags._READ || ptr->flags._EOF || ptr->flags._ERR) {
        return EOF;
    }

    bufsize = (ptr->flags._UNBUF == 1) ? 1 : BUFSIZ;

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
            ptr->flags._EOF = 1;
        } else
            ptr->flags._ERR = 1;

        ptr->cnt = 0;
        return EOF;
    }
    return (unsigned char) *ptr->ptr;
}

void m_fclose(FILED* ptr) {
    if (!ptr) {
        return;
    }
    if (ptr->fd >= 0) {
        close(ptr->fd);
        ptr->fd = -1;
    }
    if (ptr->base) {
        free(ptr->base);
    }
    ptr->flags._EOF = ptr->flags._ERR = ptr->flags._READ = ptr->flags._UNBUF =
        ptr->flags._WRITE                                = 0;
    ptr->cnt                                             = 0;
    ptr->ptr                                             = NULL;
}
/* try to make m_fseek wholly manually (-_-!!)*/
// int m_fseek(FILED* ptr, long offset, long origin) {
//     if (ptr == NULL) {
//         return -1;
//     }
//     if (origin != SEEK_CUR && origin != SEEK_END && origin != SEEK_SET) {
//         return -1;
//     }

//     if (origin == SEEK_SET) {
//         if (offset < 0) {
//             printf("can't move beyond, already at start!!\n");
//             return -1;
//         }
//         if (offset >= ptr->cnt) {
//             ptr->ptr = ptr->base + ptr->cnt;
//         } else
//             ptr->ptr = ptr->base + offset;
//     }

//     if (origin == SEEK_END) {
//         if (offset > 0) {
//             printf("can't move forward, already at the end of file!!\n");
//             return -1;
//         } else {
//             ptr->ptr = ptr->base + ptr->cnt + offset;
//         }
//     }

//     if (origin == SEEK_CUR) {
//         if (offset < 0) {
//             if (ptr->ptr + offset < ptr->base) {
//                 ptr->ptr += offset;
//             } else
//                 ptr->ptr = ptr->base;
//         } else if (offset >= 0) {
//             if (ptr->ptr + offset <= (ptr->base + ptr->cnt)) {
//                 ptr->ptr += offset;
//             } else
//                 ptr->ptr = (ptr->base + ptr->cnt);
//         }
//     }
//     return 0;
// }
