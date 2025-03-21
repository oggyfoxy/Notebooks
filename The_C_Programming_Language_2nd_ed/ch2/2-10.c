/*

ex 2-10
---

Rewrite the function lower, which converts upper case letters to lower case ,
with a conditional expression instead of if-else


*/

#include <stdio.h>

int lower(int c);

int main(void)
{
    int lowerThis = lower('E');
    printf("%c\n", lowerThis); // remember to use the %c format specifier if i want to ouput the actual char

    // use %d if i want to print out the ASCII value of the char

    return 0;
}

int lower(int c)
{
    return (c >= 'A' && c <= 'Z') ? c + 'a' - 'A' : c;
}