#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
double m_atof(char s[])
{
    double val, power; // val to hold the buildup value, power to handle the decimal point
    int i, sign;       // i for indexing and sign to store the sign
    int exp_value = 0;
    int exp_sign = 1;

    for (i = 0; isspace(s[i]); i++) // skipping leading white space characters
        ;
    sign = (s[i] == '-') ? -1 : 1; // assigning sign to sign variable

    if (s[i] == '-' || s[i] == '+') // skipping sign as it is already stored in sign variable
    {
        i++;
    }
    for (val = 0.0; isdigit(s[i]); i++) // checking for the string until this loop finds digits it string
    {
        val = val * 10.0 + (s[i] - '0'); // s[i]-0 convert character into integer and val*10.0 will build up the number ex. 12345
    }
    if (s[i] == '.') // if decimal found, skipping it for now
    {
        i++;
    }
    for (power = 1.0; isdigit(s[i]); i++) // building up the number after decimal point, power is kept at 1.0 and is multiplied by 10.0 in each iteration to mark the decimal point position
    {
        val = val * 10.0 + (s[i] - '0');
        power *= 10.0;
    }
    if (s[i] == 'e' || s[i] == 'E')
    {
        i++;
        if (s[i] == '-')
        {
            exp_sign = -1;
            i++;
        }
        else if (s[i] == '+')
        {
            i++;
        }

        // Convert exponent value
        while (isdigit(s[i]))
        {
            exp_value = exp_value * 10 + (s[i] - '0');
            i++;
        }

        // Apply exponent to val
        if (exp_sign == -1)
        {
            val /= pow(10, exp_value); // For negative exponent
        }
        else
        {
            val *= pow(10, exp_value); // For positive exponent
        }
    } // Return the final result, including sign and power
    return sign * (val / power);
}
int main()
{
    char str[] = "123.45e-6"; // Example input for scientific notation
    double result = m_atof(str);
    printf("Converted value: %f\n", result);

    return 0;
}