#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct define {
    unsigned int is_int : 1;
    unsigned int is_char : 1;
    unsigned int is_keyword : 1;
    unsigned int is_string : 1;
} flags;

int main() {
    union students {
        int  roll_n;
        char section;
        char name[20];
        int  id;
    };

    union students std;

    std.roll_n  = 1;
    std.section = 'c';
    strcpy(std.name, "Aasif");
    std.id       = 25;
    flags.is_int = 1;

    // printf("the std.id is %d\n", std.id);
    // printf("the std.roll_n is %d\n", std.roll_n);
    // printf("the std.section is %c\n", std.section);
    // printf("the std.name is %s\n", std.name);

    printf("%d", flags.is_int);
    return 0;
}