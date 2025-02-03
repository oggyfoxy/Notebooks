/*  In a two's complement number system, x &= (x-1) deletes the rightmost 1-bit in x.
Explain why. Use this observation to write a faster version of bitcount */

#include <stdio.h>

int bitcount(unsigned x);

int main(void)
{

    int count = bitcount(278);
    printf("count of 1's: %d\n", count);
    return 0;
}

// counts the number of 1-bits
int bitcount(unsigned x)
{
    int b;

    for (b = 0; x != 0; x &= (x - 1))
        b++;
    return b;
}

/* x &= (x-1) deletes the rightmost 1-bit because of the nature of the calculation

for example, in a two's complement number system, lets take x-1 = 1100.

- (x-1) + 1 = 1100 + 1 = 1101.

x = 1101
x - 1 = 1100

as you can see the LSB of x is 1. but when you compare it to x-1 it has a corresponding 0-bit.

*/