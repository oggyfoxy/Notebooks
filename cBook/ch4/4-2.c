/*

ex 4-2
---

handle scientific notation

*/

#include <stdio.h>
#include <ctype.h>
#include <math.h>

#define MAXLINE 100

/* rudimentary calculator */
int main(void)
{
    double sum, atof(char[]);
    char line[MAXLINE];
    int mygetline(char line[], int max);

    sum = 0;
    while (mygetline(line, MAXLINE) > 0)
        printf("\t%g\n", sum += atof(line));
    return 0;
}

/* getline: get line into s, return length */
int mygetline(char s[], int lim)
{
    int c, i;

    i = 0;
    while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
        s[i++] = c;
    if (c == '\n')
        s[i++] = c;
    s[i] = '\0';
    return i;
}

/* atof: convert string s to double */
double atof(char s[])
{
    double val, power, exp;
    int i, sign, sign_exp;

    for (i = 0; isspace(s[i]); i++) /* skip white space */
        ;
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
        i++;
    for (val = 0.0; isdigit(s[i]); i++) // check the value and add it
        val = 10.0 * val + (s[i] - '0');
    if (s[i] == '.')
        i++;
    for (power = 1.0; isdigit(s[i]); i++) // check the decimal point and add it
    {
        val = 10.0 * val + (s[i] - '0');
        power *= 10.0;
    }

    sign_exp = (s[i] == '-') ? -1 : 1;

    if (s[i] == 'e' || s[i] == 'E')
    {
        i++;
        if (s[i] == '-')
        {
            sign_exp = -1;
            i++;
        }
        else if (s[i] == '+')
        {
            sign_exp = 1;
            i++;
        }
        else
        {
            sign_exp = 1;
        }
    }
    exp = 0;
    while (isdigit(s[i]))
    {
        exp = 10.0 * exp + (s[i] - '0');
        i++;
    }

    if (sign_exp == -1)
        val /= pow(10, exp);
    else
        val *= pow(10, exp);

    return sign * val / power;
}

/*

idea
---

if more than 2

*/