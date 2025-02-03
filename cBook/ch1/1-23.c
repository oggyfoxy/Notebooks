/*
    Write a program to remove all comments from a C program.
    Don't forget to handle quoted strings and character constants properly.
    C comments do not nest.
*/

/*
- need to have a function that detects if a line is a comment or not
- need to have a function that trims the line if one is a command
- main func: gets user input, and outputs the text with no commands on EOF
*/

#include <stdio.h>

#define MAXLINE 1000

int my_getline(char line[], int maxline);
void trim(char line[], int length);

int main(void)
{
    int len;            /* current line length */
    char line[MAXLINE]; /* current input line */

    while ((len = my_getline(line, MAXLINE)) > 0)
    {
        trim(line, len);
        if (line[0] != '\n')
            printf("Output: [%s] \n", line);
    }
    return 0;
}

/* getline: read a line into s, return length */
int my_getline(char s[], int lim)
{
    int c, i;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;
    if (c == '\n')
    {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}

/* trim: each line, remove substring of comments if there is */
void trim(char line[], int length)
{
    int i = 0;
    for (i = length - 2; i >= 0 && ((line[i]) == "//" || (line[i]) == "/*" || (line[i]) == "*/");)
    {
        --i;
    }

    line[++i] = '\n';
    line[++i] = '\0';
}