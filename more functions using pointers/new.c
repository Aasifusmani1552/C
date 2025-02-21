#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
int m_atoi(char* s) {
    int number = 0;
    int sign   = 1;
    while (isspace(*s)) {
        s++;
    };
    if (*s == '-' || *s == '+') {
        sign = (*s == '-') ? -1 : 1;
        s++;
    }
    while (isdigit(*s)) {
        number = 10 * number + (*s - '0');
        s++;
    }
    return number * sign;
}
void m_itoa(char* s, int t) {
    int sign;

    if (t < 0) {
        sign = -1;
        *s++ = '-';
        t    = t * -1;
    }
    if (t / 10) {
        m_itoa(s, t / 10);
        while (*s) {
            s++;
        }
    }
    *s++ = t % 10 + '0';
    *s   = '\0';
}
void m_reverse(char* s) {
    char* s_start = s;
    while (*s) {
        s++;
    }
    char* s_end = s - 1;
    while (s_start != s_end) {
        char temp = *s_start;
        *s_start  = *s_end;
        *s_end    = temp;
        s_start++;
        s_end--;
    }
}
void mm_reverse_recurs(char* s) {
    static char* s_start;
    static char* s_end;
    if (s_start == 0) {
        s_start = s;
        while (*s)
            s++;
        s_end = s - 1;
    }

    if (s_start == s_end) {
        s_start = 0;
        s_end   = 0;
        return;
    } else {
        char temp = *s_start;
        *s_start  = *s_end;
        *s_end    = temp;
        s_start++;
        s_end--;
        mm_reverse_recurs(s);
    }
}
int m_strindex(char* s, char* t) {
    char* s_start = s;
    char* t_start = t;
    while (*s)
        s++;
    while (*t)
        t++;
    char* s_end = s - 1;
    char* t_end = t - 1;
    int   ocr   = (s_end - s_start) - (t_end - t_start);
    char* i     = s_start + ocr;

    if (ocr >= 0) {
        if (*i == *t_start) {
            while (*i == *t_start) {
                i++;
                t_start++;
            }
            if (*t == '\0') {
                return ocr;
            }
        }
    }
    return -1;
}
int mm_strindex(char* s, char* t) {
    char* s_temp;
    char* t_temp;
    int   index;
    while (*s) {
        s_temp = s;
        t_temp = t;
        while (*s_temp && *t_temp && *s_temp == *t_temp) {
            s_temp++;
            t_temp++;
        }
        if (*t_temp == '\0') {
            return index;
        }
        s++;
        index++;
    }

    return -1;
}
int main() {
    char arr1[] = "hello world world";
    char arr2[] = "world";
    int  result = mm_strindex(arr1, arr2);
    printf("%d", result);
    return 0;
}