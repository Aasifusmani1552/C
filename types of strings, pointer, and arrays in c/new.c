#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    /* types of strings in c*/

    char name[10] = "the value";  // this is valid a name is an array of chars,
                                  // specifieing the size is not must
    name[1] = 'H';

    // char name = "the value"; this is not fine at all as char can only hold a
    // character at a time;
    /* best practise is if you want a string literal use :-*/

    char* pname = "some string";  // this is fine, the string is a string
                                  // literal and it's values can't be modified

    /* and if you want a modifieable string use:-*/

    char oname[] =
        "a string";  // this is perfectly fine and you can modify the values in
                     // it, the [] allocate enough amount of storage in ram

    /*same goes for multi dimension arrays like*/

    char* qmonth =
        "jan, fab, mar";  // this is fine to write but the string is saved as a
                          // whole and month is pointer to it's first element

    char* dmonth[] = {
        "jan", "feb",
        "mar"};  // this is an array of pointers to string literals,
                 // each element points to the first character of each string

    char amonth[] = "jan, feb, mar";  // this is a single string stored in ram,
                                      // and we can change its contents

    char* month[3][4] = {"jan", "fab", "mar"};
}