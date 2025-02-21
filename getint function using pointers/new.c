#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define size 10
#include "header.h" // this file contains prototypes for getch and ungetch functions
int getint(int *pn) // getint function to convert strings into integer values by taking pointer to an array to store int into the pointer location(dereferencing)
{
    int c, sign;                   // variable for input and sign
    while (isspace((c = getch()))) // skipping white space characters and initializing c variable
        ;
    if (!isdigit(c) && c != EOF && c != '+' && c != '-') // if c is not a digit or eof or -, + sign, send to buffer and return 0
    {
        ungetch(c);
        return 0;
    }
    sign = (c == '-') ? -1 : 1; // storing sign into sign variable
    if (c == '+' || c == '-')   // checking for signs
    {
        int next = getch();
        if (!isdigit(next))
        {
            *pn = c;
            ungetch(next);
            return 1;
        }
        else
            c = next;
    }

    for (*pn = 0; isdigit(c); c = getch()) // dereferencing pointer to element of array i.e. basically the value of the element of array and storing input into those
    {
        *pn = 10 * *pn + (c - '0'); // *pn in every iteration converts a string of numbers to integer like '123' to 123 by subtracting ASCII 0 from numbers
    }
    *pn *= sign;  // adding sign if present
    if (c != EOF) // if eof is not pressed to end the program, pushing it to buffer for precaution so we can use it later if want, pushing eof doesn't make sense
    {
        ungetch(c);
    }
    return c;
}
int main()
{
    int i, arr[size];
    printf("enter %d numbers to convert into integers(enter any non-digit to stop):\n", size);
    for (i = 0; i < size; i++)
    {
        if (getint(&arr[i]) == 0) // checking if getint return 0, break from the program
        {
            break;
        }
    }
    printf("the entered integers are: "); // printing all the elements of array
    for (int j = 0; j < i; j++)
    {
        if (arr[j] == '+' || arr[j] == '-')
        {
            printf("%c ", arr[j]);
        }
        else
            printf("%d ", arr[j]);
    }
    printf("\n");

    return 0;
}