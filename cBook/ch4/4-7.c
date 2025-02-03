/*

ex 4-7
---
Write a routine ungets(s) that will push back an entire string onto the input.
Should ungets know about buf and bufp, or should it just use ungetch?


*/

#include <stdio.h>
#include <string.h>

#define BUFSIZE 100
#define MAXLINE 100

char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0;      /* next free position in buf */

int mygetline(char line[], int max);
void ungetch(int c);
void ungets(char s[]);

int main(void)
{
    char line[MAXLINE];
    while (mygetline(line, MAXLINE) > 0)
    {

        ungets(line);
        printf("%s", line);
    }

    return 0;
}

int mygetline(char s[], int lim)
{
    int i, c;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;

    if (c == '\n')
        s[i++] = c;

    s[i] = '\0';
}

void ungetch(int c) /* push character back on input */
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

void ungets(char s[])
{
    int len = strlen(s);
    while (len > 0)
        ungetch(s[--len]);
}
