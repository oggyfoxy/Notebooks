/*

ex 3-5
---

Write the function itob(n,s.b) that converts the integer n into a base b
character representation in the string s. In particular, itob(n,s,16) formats
n as a hexadecimal integer in s.

*/

#include <stdio.h>
#include <string.h>

#define MAXSIZE 1000

void reverse(char s[]);
void itob(int n, char s[], int b);

int main(void)
{
    int n = 34;
    char s[MAXSIZE];

    itob(n, s, 16);
    printf("%s\n", s);

    return 0;
}

void reverse(char s[])
{
    int c, i, j;

    for (i = 0, j = strlen(s) - 1; i < j; i++, j--)
    {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

void itob(int n, char s[], int b)
{
    int i, j, sign;

    if ((sign = n) < 0) /* record sign */
        n = -n;
    i = 0;
    do
    {
        j = n % b;                                  // j is the remainder
        s[i++] = (j <= 9) ? j + '0' : j - 10 + 'A'; // if remainder is between 0-9 add '0' else do other op so it works for larger remainders
    } while ((n /= b) > 0); // while remainder is positive

    if (sign < 0)
        s[i++] = '-'; // informs that the original number was negative
    s[i] = '\0';
    reverse(s); // reverses strings so its readable
}