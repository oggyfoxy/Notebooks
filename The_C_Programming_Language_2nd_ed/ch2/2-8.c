/* Write a function rightrot(x,n) that returns
the value of the integer x rotated to the right by n bit positions.
*/

#include <stdio.h>

#define INT_SIZE 32 // size of unsigned int on most machines

unsigned rightrot(unsigned int x, unsigned int n);

int main()
{
    unsigned int rot = rightrot(0b11011011, 3);
    printf("rotated x: %u\n", rot);
    return 0;
}

/* rotate x bits n positions */
unsigned rightrot(unsigned int x, unsigned int n)
{
    n = n % INT_SIZE;
    return (x >> n) | (x << (INT_SIZE - n));
}

/* need to come back to this exercise later and actually understand how to do it properly.
for the moment ill just assume n < 32 would work on most machines.


ill come back to this when ill be learning more deeply about bitwise operations. (should ask mani if i should or not.)

*/