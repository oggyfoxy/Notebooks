/*

find -x -n pattern

*/

#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

int mygetline(char *line, int max);  // Function prototype for custom getline

/* find: print lines that match pattern from 1st argument */
int main(int argc, char *argv[]) {
    char line[MAXLINE];
    long lineno = 0;
    int c, except = 0, number = 0, found = 0;

    // Process command-line options
    while (--argc > 0 && (*++argv)[0] == '-') {
        while (c = *++argv[0]) {
            switch (c) {
                case 'x':
                    except = 1;
                    break;
                case 'n':
                    number = 1;
                    break;
                default:
                    printf("find: illegal option %c\n", c);
                    argc = 0;
                    found = -1;
                    break;
            }
        }
    }

    // Check if pattern is provided
    if (argc != 1) {
        printf("Usage: find -x -n pattern\n");
    } else {
        // Read lines and find the pattern
        while (mygetline(line, MAXLINE) > 0) {
            lineno++;
            if ((strstr(line, *argv) != NULL) != except) {
                if (number) {
                    printf("%ld:", lineno);
                }
                printf("%s", line);
                found++;
            }
        }
    }

    return found;
}

/* Custom getline function: read a line into s, return length */
/* Custom getline function: read a line into s, return length */
int mygetline(char *s, int lim) {
    int c, i;
    
    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i) {
        s[i] = c;
    }
    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}

