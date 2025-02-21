#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse(char s[]) // Function to reverse the string
{
    int i, j;
    int len = strlen(s);                      // Get the length of the string s
    char temp;                                // Temporary variable for swapping
    for (i = 0, j = len - 1; i < j; i++, j--) // Reverse the string
    {
        temp = s[i];
        s[i] = s[j];
        s[j] = temp;
    }
}

void itob(int n, char s[], int b) // Convert integer n to string s in base b
{
    unsigned int num = (unsigned int)n; // Treat n as unsigned for conversion
    int i = 0;
    char temp[50]; // Temporary storage for reversed string

    // If the number is negative, convert to its two's complement equivalent
    if (n < 0)
    {
        num = (unsigned int)(-n); // Take the absolute value for conversion
        num = ~num + 1;           // Get two's complement
    }

    // Convert the number to the specified base
    do
    {
        int remainder = num % b;
        if (remainder < 10)
        {
            temp[i++] = remainder + '0'; // Convert to character
        }
        else
        {
            temp[i++] = remainder - 10 + 'A'; // Convert 10-15 to A-F
        }
        num /= b; // Divide by base for next iteration
    } while (num != 0);

    // Add the null terminator and reverse the string
    temp[i] = '\0';
    reverse(temp);

    // Copy temp to s
    strcpy(s, temp); // Directly copy the temp string to s
}

int main()
{
    int num = 255;
    char result[50];
    itob(num, result, 16);                                                  // Convert to hexadecimal/ or octal or binary or into any base/radix you want.
    printf("The two's complement hexadecimal of %d is: %s\n", num, result); // Print the result

    return 0;
}
