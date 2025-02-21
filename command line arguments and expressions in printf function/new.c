#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// int main(int argc, char* argv[]) {
//     int i;
//     for (i = 1; i < argc; i++)
//         printf("%s%s", argv[i], (i < argc - 1) ? " " : "");
//     printf("\n");
//     return 0;
// }
int main(int argc, char* argv[]) {
    while (--argc) {
        printf((argc > 1) ? "%s " : "%s", *++argv);
    }
    return 0;
}