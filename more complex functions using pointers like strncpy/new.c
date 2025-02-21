#include <stdio.h>
#include <stdlib.h>
void m_strncpy(char* s, char* t, int n) {
    int i = 0;
    if (n == 0) {
        printf("give a valid number to where you want to copy");
        return;
    }

    while (i < n && t[i] != '\0') {
        s[i] = t[i];
        i++;
    }
    while (i < n) {
        s[i++] = '\0';
    }
}
void my_strncpy(char* s, char* t, int n) {
    while (n > 0 && *t != '\0') {
        *s++ = *t++;
        n--;
    }
    while (n > 0) {
        *s++ = '\0';
        n--;
    }
}
void m_strncat(char* s, char* t, int n) {
    while (*s != '\0') {
        s++;
    }
    *s++ = ' ';
    while (n > 0 && *t != '\0') {
        *s++ = *t++;
        --n;
    }
    *s = '\0';  // here we are directly null terminating the string unlike
                // my_strncpy because here if n is more than t, while loop will
                // automatically fail as one condition will fail i.e. *t != '\0'
}
int main() {
    char arr1[] = "bro";
    char arr2[] = "hello";
    m_strncat(arr2, arr1, 1);
    printf("%s", arr2);
    return 0;
}