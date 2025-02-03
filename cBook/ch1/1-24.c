/*
Write a program to check a C program for rudimentary syntax errors like unbalanced parentheses,
brackets and braces. Don't forget about quotes, both single and double, escape sequences, and comments.
(This program is hard if you do it in full generality.)
*/

/*
TODO:
- make function to check balance (++ opened and closed)
- make function for handling quotes, escape sequences and comments
*/

#include <stdio.h>

int brace = 0, brack = 0, paren = 0;

void check(int c);     /* check syntax errors */
void in_comment(void); /* check if we're in a comment*/
void in_quote(int c);  /* check if we're in an quote or an escape seqences*/

int main(void)
{
    int c;

    printf("Checking syntax: \n");
    while ((c = getchar()) != EOF)
    {
        check(c);
    }

    if (brace != 0 || brack != 0 || paren != 0)
        printf("Braces off: %d\n Brackets off: %d\n Parenthesises off: %d\n", brace, brack, paren);
    else
        printf("No unbalanced syntax\n");

    return 0;
}

void check(int c)
{
    if (c == '{')
        ++brace;
    else if (c == '}')
        --brace;
    else if (c == '[')
        ++brack;
    else if (c == ']')
        --brack;
    else if (c == '(')
        ++paren;
    else if (c == ')')
        --paren;
    else if (c == '\'')
        in_quote(c);
    else if (c == '\"')
        in_quote(c);
    else if (c == '/')
    {
        if ((c = getchar()) == '/')
            while ((c = getchar()) != '\n' && c != EOF)
                ;
        else if (c == '*')
        {
            in_comment();
        }
        else
        {
            putchar('/');
            putchar(c);
        }
    }
}

/* Skip over escape sequences (character constants, double quotes, etc.) */

void in_quote(int c)
{
    int d;

    while ((d = getchar()) != c)
        if (d == '\\')
            getchar();
}

/* Skip over a multi-line comment */
void in_comment(void)
{
    int c, d;
    c = getchar();
    d = getchar();
    while (c != '*' || d != '/')
    {
        c = d;
        d = getchar();
    }
}