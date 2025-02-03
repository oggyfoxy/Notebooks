/*


TODO: ex 4-12
---
make itoa recursive.


*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define MAXSIZE 1000

void itoa(int n, char s[]);

/* itoa: convert n to characters in s */
void itoa(int n, char s[])
{
    static int i;

    if (n / 10)
      itoa(n/10, s);
    else {
      i = 0;
      if (n < 0) 
        s[i++] = '-';
    }
    s[i++] = abs(n) % 10 + '0';   /* get next digit */
    s[i] = '\0';
}

int main(void) {

    int n = -123;
    char s[MAXSIZE];

    itoa(n, s);
    printf("%s\n", s);
    return 0;
}

