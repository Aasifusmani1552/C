#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* reverse function using recursion*/
void re_reverse(char s[]) {
    static int i =
        0;  // static used here as it doesn't reinitialize after every recursion
    int start = 0;          // starting point of string
    int len   = strlen(s);  // gives the length of the string
    int end   = len - 1;  // ending point of the string(len-1, because indexing
                          // starts at 0 not 1)
    static int j;
    char       temp;  // temporary variable for swapping
    if (i == 0) {
        j = end;  // dynamically initializing j to end only if i is 0 i.e. only
                  // in first recursion
    }
    if (i == ((start + end) /
              2)) {  // base case, if i comes equal to half of the string
        return;
    } else {
        temp = s[i];
        s[i] = s[j];
        s[j] = temp;
        i++;
        j--;
        re_reverse(s);
    }
}
int main() {
    char str[]  = "abcde";
    int  length = strlen(str);
    re_reverse(str);
    printf("%s\n", str);
    printf("%d", length);

    return 0;
}