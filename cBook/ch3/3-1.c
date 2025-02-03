/*

ex 3-1
----

Our binary search makes two tests inside the loop, when one would suffice (at
the price of more tests outside). Write a version with only one test inside the
loop and measure the difference in run-time.

*/

#include <stdio.h>

int binsearch(int x, int v[], int n);

int main(void)
{

    int arr[] = {2, 3, 4, 7, 8, 11};

    int binary = binsearch(99, arr, 6);

    printf("%d\n", binary);
    return 0;
}

int binsearch(int x, int v[], int n)
{
    int low, high, mid;

    low = 0;
    high = n - 1;
    while (low <= high)
    {
        mid = (low + high) / 2;
        if (x < v[mid])
            high = mid - 1;
        else
            low = mid + 1;
    }
    if (x == v[mid])
        return mid;
    else
        return -1; /* no match */
}
