/* 

TODO: Write getfloat, the floating-point analog of getint. What type does getfloat return as its function value?
---
ex 5-2


*/


#include <stdio.h>
#include <ctype.h>

#define SIZE 10
#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

int getch();
void ungetch(int);
int getfloat(float*);

int getch(void) {
    return (bufp > 0) ? buf[--bufp] : getchar();
}


void ungetch(int c) {
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}


int getfloat(float *pn) {
    int c, sign;
    float pow;

    while (isspace(c = getch()));

    if (!isdigit(c) && c != EOF && c != '+' && c != '-' && c != '.') {
        ungetch(c); /* it's not a number */
        return 0; 
    }

    sign = (c == '-') ? -1 : 1;

    if (c == '+' || c == '-')
        c = getch();
    for (*pn = 0; isdigit(c); c = getch())
        *pn = 10 * *pn + (c - '0');

    if (c == '.')
      c = getch();

    for (pow = 1.0; c == '.'; c = getch()) {
      *pn = 10.0 * *pn + (c - '0');
      pow *= 10;
    }

    *pn *= sign / pow;

    if (c != EOF)
        ungetch(c);

    return c;
}

int main() {

  int n, getfloat(float *);
  float array[SIZE];

  for (n = 0; n < SIZE && getfloat(&array[n]) != EOF; n++)
    printf("n = %g\n", array[n]);


  return 0;


}

