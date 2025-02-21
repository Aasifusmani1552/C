#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#ifdef DEBUG
#if DEBUG
#define DEBUG_PRINT printf("DEBUGGING MODE IS ON!");
#else
#define DEBUG_PRINT printf("DEBUGGING IS DISABLED AT RUNTIME!");
#endif
#else
#define DEBUG_PRINT
#endif

int main() {
    DEBUG_PRINT;
    printf("JUST CHECKING FOR DEBUGGING");
    return 0;
}