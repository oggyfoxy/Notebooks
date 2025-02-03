/*

ex 3-6
---

Write a version of itoa that acccpts three arguments instead of two. The third
argument is a minimum field width; the converted number must be padded with
blanks on the left if necessary to make it wide enough.


*/

#include <stdio.h>
#include <string.h>

#define abs(x) ((x) > 0 ? (x) : -(x))
#define MAXSIZE 1000

void reverse(char s[]);
void itoa(int n, char s[], int w);

int main(void)
{

    char s[MAXSIZE];
    int n = 5;
    int w = 4;

    printf("integer number as string: %*d\n", w, n);

    itoa(n, s, w);

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
void itoa(int n, char s[], int w)
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
    while (i < w)
        s[i++] = ' ';
    s[i] = '\0';
    reverse(s);
}
