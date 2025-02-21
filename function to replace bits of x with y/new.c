#include <stdio.h>
#include <stdlib.h>
unsigned setbits(unsigned x, int p, int n, unsigned y) // declaring the function and the parameters function would take
{
    y = ((y >> (p + 1 - n)) & ~(~0 << n));    // right shifting the bits at position p from y and then extracting them using the mask.
    y = y << (p + 1 - n);                     // shifting the bits to their position again to combine them with the x's bits.
    x = x & ~(((1 << n) - 1) << (p + 1 - n)); // clearing bits of x at position p using the mask(1 left shifted to n bits then -1 works like ~ and changes bits 0 to 1 and vice versa then left shifting the mask to align it with x's position p)
    return x | y;                             // combining them using or operator(one of the two bits should be true for the output to be 1, else it will be 0).
}
int main()
{
    unsigned result = 0;
    result = setbits(212, 4, 3, 210); // calling the function
    printf("the number after replacing the bits is:%u", result);

    return 0;
}