#include <stdio.h>

/* this program counts the freq of each characters form its input
(see 1-14 from K&R book)*/

int main()
{
    int c, i, nother, nwhite;
    int nletters[94];

    nother = nwhite = 0;

    for (i = 0; i < 94; i++)
        nletters[i] = 0;

    while ((c = getchar()) != EOF)
    {
        if (c >= ' ' && c <= '~')
            ++nletters[c - ' '];
        else if (c == ' ' || c == '\n' || c == '\t')
            ++nwhite;
        else
            ++nother;
    }

    printf("freq of chars = ");
    for (i = 0; i < 94; i++)
        printf(" %d", nletters[i]);
    printf(", white space = %d, other = %d\n",
           nwhite, nother);
}
