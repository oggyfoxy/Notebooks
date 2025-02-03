/*
Write the function htoi(s), which converts a string of hexadecimal digits (including an optional 0x or 0X) into its equivalent integer value.
The allowable digits are 0 through 9, a through f, and A through F.
*/

#define IN 1
#define OUT 0

#include <stdio.h>

int htoi(char s[]); /* converts hex string s to int */

int htoi(char s[])
{
    int i, n, ishex, hexdigit;

    i = n = 0;
    ishex = IN;
    for (; ishex == IN; ++i)
    {
        if (s[i] >= '0' && s[i] <= '9')
            hexdigit = s[i] - '0';
        else if (s[i] >= 'A' && s[i] <= 'F')
        {
            hexdigit = s[i] - 'A' + 10;
        }
        else
        {
            ishex = OUT;
        }
        if (ishex == IN)
            n = 16 * n + hexdigit;
    }
    return n;
}

int main()
{
    int integer;
    integer = htoi("1A3");

    printf("%d\n", integer);

    return 0;
}
