/*

ex 3-3
---

Write a function expand(s1,s2) that expands shorthand notations like a-z in
the string s1 into the equivalent complete list abc...xyz in s2 . Allow for
letters of either case and digits, and be prepared to handle cases like a - b - c and
a-z0-9 and -a-z. Arrange that a leading or trailing - is taken literally.

*/

void expand(char s1[], char s2[]);

#include <stdio.h>
#include <ctype.h>

int main(void)
{
    char c;

    char s1[100] = "-a-z";
    char s2[100];

    expand(s1, s2); // always call the function.   lo l  i tend to forget it

    printf("%s\n", s2);

    return 0;
}

void expand(char s1[], char s2[])
{
    int i = 0, j = 0;
    char c;

    while ((c = s1[i++]) != '\0')           // while the last character is not the null terminator
        if (s1[i] == '-' && s1[i + 1] >= c) // if the  character is a hyphen and the the next one is bigger than c
        {
            i++;              // skip the hyphen
            while (c < s1[i]) // c is currently 'a' and it goes until 'z'
            {
                s2[j++] = c++; // add c to s2, increment position and go to next character
            }
        }
        else
        {
            s2[j++] = c; // just add the character to the next position (no incrementation for c)
        }
    s2[j] = '\0'; // null terminate the output string
}
/*

TODO

- noob case: just expand a-z
- easy case: expand a-z into s2.
- hard case: expand digits, a-z0-9 and -a-z


*/