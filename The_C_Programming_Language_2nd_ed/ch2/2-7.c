/* Write a function invert(x,p,n) that returns x with the n bits that begin at position p inverted
(i.e., 1 changed into 0 and vice versa), leaving the others unchanged.*/

#include <stdio.h>

unsigned invert(unsigned x, int p, int n);

int main()
{

    unsigned int inv = invert(24, 4, 3);

    printf("inverted bits: %d\n", inv);
    return 0;
}

unsigned invert(unsigned x, int p, int n)
{

    unsigned mask = ~(~0 << n) << (p + 1 - n);
    return x ^= mask;
}

/*
steps:

1. gather n bits starting at position p
2. mask all the other bits to only change the selected bits
3. invert completely the n bit-field

*/