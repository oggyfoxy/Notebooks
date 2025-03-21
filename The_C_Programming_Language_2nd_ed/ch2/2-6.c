/*

Write a function setbits(x,p,n,y) that returns x with the n bits that begin
at position p set to the rightmost n bits of y, leaving the other bits unchanged.

*/

#include <stdio.h>

unsigned getbits(unsigned x, int p, int n); // sets bits
unsigned get_lowest_n_bits(unsigned x, int n);
unsigned set_bit(unsigned x, int p);
unsigned clear_bit(unsigned x, int p);

unsigned set_bits(unsigned x, int p, int n, unsigned y); // actual problem trying to solve

int main()
{
    unsigned int ans = getbits(24, 4, 3);
    unsigned int lowest = get_lowest_n_bits(29, 3);
    unsigned int clear = clear_bit(9, 3);

    unsigned int set = set_bits(0b11010, 2, 3, 0b10111);

    printf("ans is %d\n", ans);
    printf("lowest: %d\n", lowest);
    printf("clear: %d\n", clear);

    printf("bits after setting: %d\n", set);

    return 0;
}

/* K&R example exercise */
unsigned getbits(unsigned x, int p, int n)
{
    return (x << (p + 1 - n)) & ~(~0 << n);
}

/* ex 1: returns the lowest (rightmost) n bits of the number x */
unsigned get_lowest_n_bits(unsigned x, int n)
{

    return (x & ~(~0 << n));
}

/* ex 2: Write a function set_bit(x, p) that returns the number x with the bit at position p set to 1. */

unsigned set_bit(unsigned x, int p)
{

    return (x | (1 << p));
}

/* ex 3: Write a function clear_bit(x, p) that returns the number x with the bit at position p cleared to 0. */

unsigned clear_bit(unsigned x, int p)
{

    return (x & ~(1 << p));
}

unsigned set_bits(unsigned x, int p, int n, unsigned y)
{

    /*  intuitive implementation

        unsigned mask = ~(~0 << n) << (p + 1 - n); // creates a mask of 0's of size n at position p
        x &= ~mask;                                // mask x with 1-bits

        unsigned shifted_y = (y & ~(~0 << n)) << (p + 1 - n); // sets on x at position p the rightmost n bits of y.

        return x | shifted_y;
    }
    */

    return x & ~(~(~0 << n) << (p + 1 - n)) |
           (y & ~(~0 << n)) << (p + 1 - n);
}