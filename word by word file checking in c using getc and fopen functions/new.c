#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ARRSIZE 100
int  m_getline(char* line, int max);
void getcontent(FILE* p1, FILE* p2, char* t, char* s);

int main() {
    FILE* ptr1 = fopen("n.txt", "r");
    FILE* ptr2 = fopen("m.txt", "r");
    if (ptr1 == NULL || ptr2 == NULL) {
        printf("Error opening files.\n");
        return 1;
    }
    char arr1[ARRSIZE];
    char arr2[ARRSIZE];
    getcontent(ptr1, ptr2, arr1, arr2);
    fclose(ptr1);
    fclose(ptr2);
    return 0;
}
void getcontent(FILE* p1, FILE* p2, char* t, char* s) {
    int c1, c2;
    int nline = 0;
    while ((c1 = getc(p1)) && (c2 = getc(p2)) != EOF) {
        *t++ = c1;
        *s++ = c2;
        if (c1 == '\n' && c2 == '\n') {
            nline++;
        }
        if (c1 != c2) {
            break;
        }
    }
    *t = '\0';
    *s = '\0';

    if (c1 == EOF && c2 == EOF) {
        printf("Successful checking of files!!\n");
    } else {
        printf(
            "Files are different at character %c from file 1 and character %c "
            "from file two at line %d.\n",
            (c1 == EOF) ? *--t : c1, (c2 == EOF) ? *--s : c2, nline);
    }
}
int m_getline(char* line, int max) {
    if (fgets(line, max, stdin) == NULL) {
        return 0;
    } else {
        return strlen(line);
    }
}