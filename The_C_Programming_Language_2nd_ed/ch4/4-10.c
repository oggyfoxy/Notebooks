/*

4-10
---

Another organization uses getline to read an entire input line; makes getch and ungetch irrelevant.
Revise the calculator accordingly.

*/

#include <stdio.h>
#include <stdlib.h> /* for atof() */


#define MAXOP 100  /* max size of operand or operator */
#define NUMBER '0' /* signal that a number was found */


#define MAXLINE 100 /* max size for chars of line */


int getop(char[]);
void push(double);
double pop(void);
void mathfnc(char s[]);
void clear(void);

int mygetline(char s[], int lim);


/* reverse Polish calculator */
int main(void)
{
    int type;
    double op2;
    char s[MAXOP];
   

    while ((type = getop(s)) != EOF) {
        switch (type) {
            case NUMBER:
                push(atof(s));
                break;
            case '+':
                push(pop() + pop());
                break;
            case '*':
                push(pop() * pop());
                break;
            case '-':
                op2 = pop();
                push(pop() - op2);
                break;
            case '/':
                op2 = pop();
                if (op2 != 0.0)
                    push(pop() / op2);
                else
                    printf("error: zero divisor\n");
                break;
            case '\n':
                printf("\t%.9g\n", pop());
                break;
            default:
                printf("error: unknown command %s\n", s);
                break;
            }
    }
    return 0;
}

#define MAXVAL 100

int sp = 0;         /* next free stack position */
double val[MAXVAL]; /* value stack */

/* push: push f onto value stack */
void push(double f)
{
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can't push %g\n", f);
}

/* pop: pop and return top value from stack */
double pop(void)
{
    if (sp > 0)
        return val[--sp];
    else
    {
        printf("error: stack empty\n");
        return 0.0;
    }
}

#include <ctype.h> /* for isdigit()*/

char buf[MAXLINE];
int line_index = 0;

//* getop: get next operator or numeric operand */
int getop(char s[])
{
    int i, c;

    if (buf[line_index] == '\0') // if line_index is at end of buffer
        if (mygetline(buf, MAXLINE) == 0) // if no more lines
            return EOF; // call end of file
    else
        line_index = 0;
     

    while ((s[0] = c = buf[line_index++]) == ' ' || c == '\t')
        ;
    s[1] = '\0';

    if (!isdigit(c) && c != '.')
        return c; /* not a number */

    i = 0;

    if (isdigit(c)) /* collect integer part */
        while (isdigit(s[++i] = c = buf[line_index++]))
            ;

    if (c == '.') /* collect fraction part */
        while (isdigit(s[++i] = c = buf[line_index++]))
            ;

    s[i] = '\0';
    line_index--; /* pushes back the last non numeric character */
    return NUMBER;
}

/* mygetline: gets line from string*/
int mygetline(char s[], int lim)
{
    int i, c;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;

    if (c == '\n')
        s[i++] = c;

    s[i] = '\0';

    return i;
}