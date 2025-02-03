/*
TODO
Write an alternate version of squeeze(s1,s2) that deletes each character in
s1 that matches any character in the string s2.
*/

#include <stdio.h>

void squeeze(char s1[], char s2[])
{

    int i, j, k;
    i = j = k = 0;

    for (i = k = 0; s1[i] != '\0'; i++)
    {
        for (j = 0; s2[j] != '\0' && s2[j] != s1[i]; j++)
            ;
        if (s2[j] == '\0')
            s1[k++] = s1[i];
    }
    s1[k] = '\0';
}

int main()
{
    char s1[] = "This is a story about kids and floppy disks.";
    char s2[] = "isk";

    squeeze(s1, s2);
    printf("Resulting string: %s\n", s1);

    return 0;
}
