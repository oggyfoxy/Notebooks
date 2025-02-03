/*

ex 3-4
---

In a two's complement number representation, our version of i to a does not
handle the largest negative number, that is, the value of n equal to -(2**wordsize-1).
Explain why not. Modify it to print that value correctly, regardless of the
machine on which it runs.

*/

#include <stdio.h>
#include <string.h>

#define abs(x) ((x) > 0 ? (x) : -(x))
#define MAXSIZE 1000

void reverse(char s[]);
void itoa(int n, char s[]);

int main(void)
{

    char s[MAXSIZE];
    int n = -2147483648;

    printf("integer number as string: %d\n", n);

    itoa(n, s);

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

/* itoa: convert n to characters in s  */
void itoa(int n, char s[])
{
    int i, sign;

    if ((sign = n) < 0) /* record sign */
        n = -n;         /* make n positive */
    i = 0;
    do
    {                               /* generate digits in reverse order */
        s[i++] = abs(n % 10) + '0'; /* get next digit */
    } while ((n /= 10) > 0); /* delete it */

    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}

/*

-(2**wordsize-1) is not currently handle = -2147483648 because most positive is 2,147,483,647

(2**wordsize-1) -1 for wordsize = 32 is 2,147,483,647
-(2**wordsize-1) -1 for wordsize = 32 is -2,147,483,647 which is wrong off 1 bit

to handle this if we use

*/