/*

ex 3-2
---

Write a function escape(s,t) that converts characters like newline and tab
into visible escape sequences like \n and \t as it copies the string t to s. Use
a switch. Write a function for the other direction as well, converting escape
sequences into the real characters.

*/

#include <stdio.h>

void escape(char s[], char t[]);
void unescape(char s[], char t[]);

int main(void)
{

    char original[1000]; // input string
    char copied[1000];   // string with escape sequences

    int c, i = 0;

    while ((c = getchar()) != EOF)
        original[i++] = c;

    original[i] = '\0';

    unescape(copied, original);

    printf("copied string: %s\n", copied);
    return 0;
}

/* copy the string t to s p rinting the escape seq*/
void escape(char s[], char t[])
{

    int i, j;

    for (i = j = 0; t[i] != '\0'; i++)
        switch (t[i])
        {
        case '\n':
            s[j++] = '\\';
            s[j++] = 'n';
            break;
        case '\t':
            s[j++] = '\\';
            s[j++] = 't';
            break;
        default:
            s[j++] = t[i];
            break;
        }
    s[j] = '\0';
}

void unescape(char s[], char t[])
{

    int i, j;

    for (i = j = 0; t[i] != '\0'; i++)
        switch (t[i])
        {
        case '\\':
            switch (t[++i])
            {
            case 'n':
                s[j++] = '\n';
                break;
            case 't':
                s[j++] = '\t';
                break;
            default:
                s[j++] = '\\';
                s[j++] = t[i];
                break;
            }
            break;
        default:
            s[j++] = t[i];
            break;
        }
    s[j] = '\0';
}