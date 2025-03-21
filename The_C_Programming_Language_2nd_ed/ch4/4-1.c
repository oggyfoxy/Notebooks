/*

ex 4-1
---

*/

#include <stdio.h>
#define MAXLINE 1000 /* maximum input line length */

int mygetline(char line[], int max);
int strrindex(char source[], char searchfor[]);

char pattern[] = "ould"; /* pattern to search for */

/* find all lines matching pattern */
int main(void)
{
    char line[MAXLINE];
    int found = 0;
    int index = 0;

    while (mygetline(line, MAXLINE) > 0)
    {
        index = strrindex(line, pattern);

        if (index >= 0)
        {
            printf("%d", strrindex(line, pattern));
            found++;
        }
    }

    return found;
}

/* getline: get line into s, return length */
int mygetline(char s[], int lim)
{
    int c, i;

    i = 0;
    while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
        s[i++] = c;
    if (c == '\n')
        s[i++] = c;
    s[i] = '\0';
    return i;
}

int strrindex(char s[], char t[])
{

    int i, j, k;

    int temp = -1;

    for (i = 0; s[i] != '\0'; i++)
    {
        for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++)
            ;
        if (k > 0 && t[k] == '\0')
            temp = i; // updates temp each time it sees t[] in s[]
    }
    return temp;
}