#include <stdio.h>
#include <stdlib.h>
int m_strcmp(char* s, char* t) {
    int i = 0;
    for (i = 0; s[i] == t[i];
         i++) {  // writing pointers like s[i] is equal to writing *(s+i), so no
                 // need to dereference a pointer when written like this.
        if (s[i] == '\0') {
            return 0;
        }
    }
    return s[i] - t[i];
}
int mm_strcmp(char* s, char* t) {
    for (; *s == *t; s++, t++) {
        if (*s == '\0') {
            return 0;
        }
    }
    return *s - *t;
}
int n_strcmp(char* s, char* t) {
    while (*s == *t) {
        if (*s == '\0') {
            return 0;
        }
        s++;
        t++;
    }
    return *s - *t;
}
void m_strcat(char* s, char* t) {
    int i = 0, j = 0;

    for (i = 0; s[i] != '\0'; i++)
        ;
    s[i++] = ' ';
    while ((s[i++] = t[j++]) != '\0')
        ;
}
void mm_strcat(char* s, char* t) {
    while (*s != '\0') {
        s++;
    }
    if (s != '\0') {
        *s++ = ' ';
    }
    while (*s++ = *t++)  // not equating to '\0' because its value is 0, and
                         // arguments given to function works on booleon logic
                         // so when \0 encountered, the loop will terminate
                         // automatically
        ;
}
/*Funtion to check if a string t is present at the end ot string s*/
int mm_strend(char* s, char* t) {
    char* s_end = s;
    char* t_end = t;
    while (*s_end++)  // getting *s_end to the end element(loop will
                      // automatically terminate on \0 as it evaluates to 0)
        ;
    while (*t_end++)  // //   //  //  //
        ;
    int s_len = s_end - s;  // calculating the length of s
    int t_len = t_end - t;  //          //
    if (s_len < t_len) {    // checking if s is bigger than t
        return 0;
    }
    s_end -= t_len;          // adjusting end equal to the end of t where it can
                             // possibly occur
    while (*s_end && *t) {   // checking for the similar elements
        if (*s_end != *t) {  // return 0 if the characters don't match
            return 0;
        }
        s_end++;  // incrementing both to match all the elements
        t++;
    }
    return 1;  // return 1 if whole t lies in s
}
int main() {
    char arr1[] =
        "hello world";  // arr1 is the pointer to a i.e. is first element,
                        // so writiing arr1[i], will automatically
                        // dereference it like *(arr1 + i).
    char arr2[] = "orld";
    mm_strcat(arr2, arr1);
    printf("%s", arr2);
    return 0;
}