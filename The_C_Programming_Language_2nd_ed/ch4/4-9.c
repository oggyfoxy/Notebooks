/*

ex 4-9
---
Handle EOF.


*/

#include <stdio.h>  


#define BUFSIZE 100


/* getch: get a (possibly pushed back) character */
int buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0;      /* next free position in buf */


int getch(void) /* get a (possibly pushed back) character */
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) /* push character back on input */
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}


int main(void)
{
    int c;
    c = '*';

    ungetch(c);

    while ((c = getch()) != EOF)
        putchar(c);

    return 0;
}