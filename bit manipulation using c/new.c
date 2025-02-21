#include <stdio.h>
#include <stdlib.h>

unsigned getbits(unsigned x, int p, int n)
{
    return (x >> (p + 1 - n) & ~(~0 << n));
}
int main()
{
    unsigned result = 0;
    result = getbits(212, 4, 3);
    printf("the three bits are:%u", result);
}