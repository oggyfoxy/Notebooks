/*

ex 4-8
---
Suppose that there will never be more than one character of pushback.
Modify ungetch and getch accordingly.


*/

#include <stdio.h>

int getch(void);
void ungetch(int c);

char buf = 0;

/* getch: get a (possibly pushed back) character */
int getch(void)
{
    int c;

    if (buf != '\0')
        c = buf;
    else
        c = getchar();

    buf = 0;
    return c;
}

/* ungetch: push a character back into input */
void ungetch(int c)
{
    if (buf != '\0')
        printf("ungetch: error, buffer is full\n");
    else
        buf = c;
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