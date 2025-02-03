#include <stdio.h>
#include <limits.h>
#include <float.h>

/*

Write a program to determine the ranges of char, short, int, and long
variables, both signed and unsigned by printing appropriate values from
standard headers and by direct computation. Harder if you compute them:
determine the ranges of the various floating-point types. (float, double, long double)

*/

int main(void)
{
    // char
    printf("signed char min: %d\n", (SCHAR_MIN));
    printf("signed char max: %d\n", (SCHAR_MAX));

    printf("range unsigned char: %u\n", UCHAR_MAX);

    // short
    printf("signed short min: %d\n", (SHRT_MIN));
    printf("signed short max: %d\n", (SHRT_MAX));

    printf("range unsigned short: %u\n", USHRT_MAX);

    // int
    printf("signed int min: %d\n", (INT_MIN));
    printf("signed int max: %d\n", (INT_MAX));

    printf("range unsigned int: %u\n", UINT_MAX);

    // long
    printf("long min: %ld\n", LONG_MIN);
    printf("long max: %ld\n", LONG_MAX);

    printf("unsigned long %lu\n", ULONG_MAX);

    // float

    printf("float min: %f\n", (FLT_MIN));
    printf("float max: %f\n", (FLT_MAX));

    // double

    printf("double min: %lf\n", (DBL_MIN));
    printf("double max: %lf\n", (DBL_MAX));

    // long double

    printf("long double min: %Lf\n", (LDBL_MIN));
    // printf("long double max: %Lf\n", (LDBL_MAX));

    return 0;
}
