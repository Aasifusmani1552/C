#include <stdio.h>
#include <stdlib.h>
unsigned char rightrot(unsigned char x, char n) // declaring the function(it will rotate n bits from the rightmost part of a number).
{
    unsigned char y = 0;    // declaring a local variable for combining the bits
    y = x & ((1 << n) - 1); // extracting the n bits from the rightmost part of x and storing them
    x = (x >> n);           // right shifting x to n number of bits
    y = y << (8 - n);       // aligning the mask with the right shifted x to put the extracted bits at the leftmost part of the number(basically rotating the bits)
    return x | y;           // combining the mask and the number
}

int main()
{
    int result = 0;
    result = rightrot(212, 2);
    printf("the rotated number is:%d", result); // we will have our rotated number

    return 0;
}