#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
void expand(const char s1[], char s2[]) // function to expand shorthand notations like a-z and 0-9.
{
    int i, j = 0;                   // declaring indexing variables for both the strings
    for (i = 0; s1[i] != '\0'; i++) // iterating through the const string s1
    {
        if (s1[i] == '-' && i > 0 && s1[i + 1] != '\0') // checking if a hyphen occurs in the string which is not at zeroth position and not at the last position of the string
        {
            if ((isdigit(s1[i - 1]) && isdigit(s1[i + 1]) && s1[i - 1] <= s1[i + 1]) || (isalpha(s1[i - 1]) && isalpha(s1[i + 1]) && s1[i - 1] <= s1[i + 1]))
            /*using c standard library functions like isdigit and isalpha to check if the character before hyphen is a number or an alphabet and checking the valid range like
             a-z and 0-9 with this part s1[i - 1] <= s1[i + 1]*/
            {
                char start = s1[i - 1];                 // declaring variables to expand the range
                char end = s1[i + 1];                   //  to mark the end of expansion
                for (char c = start + 1; c <= end; c++) // this will iterate until the valid range expansion like a-z and 0-9 like start is a, so start+1 will be b, like that
                {
                    s2[j++] = c; // copying the input into the other string
                }
                i++; // skipping the last character of the range, like z in a-z, to get rid of duplication of end digits
            }
        }
        else
            s2[j++] = s1[i]; // if there is no hyphen or no valid range just copying the same into the other string
    }
    s2[j] = '\0'; // adding a null terminator to the s2
}
int main()
{
    const char s1[] = "a--b";
    char s2[50];
    expand(s1, s2);
    printf("the expanded array is:%s", s2);

    return 0;
}