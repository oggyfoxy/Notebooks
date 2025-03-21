#include <stdio.h>

#define MAXLENGTH 10

int main()
{
    int c, i = 0, j = 0, word = 0, tmp_length = 0;
    int len[MAXLENGTH];

    for (; i < MAXLENGTH; i++)
        len[i] = 0;
    while ((c = getchar()) != '\n')
    {
        printf("%d ", c);
        if (c == 32 || c == 10 || c == 9 || c == EOF)
        {
            len[tmp_length]++;
            printf(" [%d, %d]\n", tmp_length, len[tmp_length]);
            tmp_length = 0;
            continue;
        }
        tmp_length++;
    }
    len[tmp_length]++;
    printf("\n");
    for (i = 0; i < MAXLENGTH; i++)
    {
        printf("%d : ", i);
        for (j = 0; j < len[i]; j++)
        {
            printf("*");
            printf("\n");
        }
    }
}