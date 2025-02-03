/*

TODO: Modify the sort program to handle a -r flag, which indicates sorting in reverse
(decreasing) order. Be sure that -r works with -n. 

*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NUMERIC 1 /* numeric sort */
#define DECR 2 /* sort decreasing order */
#define MAXLINES 100 /* max #lines to be sorted */

char *lineptr[MAXLINES];   /* pointers to text lines */

int readlines(char *lineptr[], int maxlines);
void writelines(char *lineptr[], int nlines, int decr);
void quicksort(void *lineptr[], int left, int right,
               int (*comp)(void *, void *));
int num_cmp(void *a, void *b);
int str_cmp(void *a, void *b); // Wrapper for strcmp

static char option = 0;

/* sort input lines */
int main(int argc, char *argv[])
{
    char line[MAXLINE];
    int nlines;
    int c, rc = 0;

    while (--argc > 0 && (*++argv)[0] == '-')
        while (c = *++argv[0])
            switch (c) {
            case 'r':
                option |= DECR;
                break;
            case 'n':
                option |= NUMERIC;
                break;
            default:
                printf("find: illegal option %c\n", c);
                argc = 0;
                break;
            }

    if (argc)
        printf("Usage: find -n -r pattern\n");
    else
        if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
          if (option & NUMERIC) 
            quicksort((void **)lineptr, 0, nlines - 1,
                      (int (*)(void *, void *))numcmp);
          else
            quicksort((void **)lienptr, 0, nline -1, 
                      (int (*)(void *, void *))strcmp);
          writelines(lineptr, nlines, option & DECR);            
        } else {
            printf("input too big to sort\n");
            return 1;
         }
}


#define MAXLEN 1000    /* max length of any input line */
int my_getline(char *, int); // Renamed getline
char *alloc(int);

/* readlines: read input lines */
int readlines(char *lineptr[], int maxlines)
{
    int len, nlines;
    char *p, line[MAXLEN];

    nlines = 0;
    while ((len = my_getline(line, MAXLEN)) > 1) {
        if (nlines >= maxlines || (p = alloc(len)) == NULL)
            return -1;
        else {
            line[len - 1] = '\0'; /* delete newline */
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    }
    return nlines;
}

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines, int decr)
{
    int i;

    if (decr)
      for (i = nlines-1; i >= 0; i--)
        printf("%s\n", lineptr[i]);
    else 
      for (i = 0; i < nlines; i++)
        printf("%s\n", lineptr[i]);
}

/* my_getline: read a line into s, return length */
int my_getline(char *s, int lim)
{
    int c, i;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++)
        s[i] = c;
    if (c == '\n') {
        s[i] = c;
        i++;
    }
    s[i] = '\0';
    return i;
}

#define ALLOCSIZE 10000    /* size of available space */
static char allocbuf[ALLOCSIZE]; /* storage for alloc */
static char *allocp = allocbuf;  /* next free position */

/* alloc: return pointer to n characters */
char *alloc(int n)
{
    if (allocbuf + ALLOCSIZE - allocp >= n) {
        allocp += n;
        return allocp - n;
    } else
        return 0;
}

/* quicksort: sort v[left]...v[right] into increasing order */
void quicksort(void *v[], int left, int right,
               int (*comp)(void *, void *))
{
    int i, last;
    void swap(void *v[], int, int);

    if (left >= right) /* do nothing if array contains */
        return;        /* fewer than two elements */
    swap(v, left, (left + right) / 2);
    last = left;
    for (i = left + 1; i <= right; i++)
        if ((*comp)(v[i], v[left]) < 0)
            swap(v, ++last, i);
    swap(v, left, last);
    quicksort(v, left, last - 1, comp);
    quicksort(v, last + 1, right, comp);
}

/* numcmp: compare s1 and s2 numerically */
int numcmp(char *s1, char *s2)
{
    double v1, v2;

    v1 = atof(s1);
    v2 = atof(s2);
    if (v1 < v2)
        return -1;
    else if (v1 > v2)
        return 1;
    else
        return 0;
}

/* str_cmp: wrapper for strcmp with void * */
int str_cmp(void *a, void *b)
{
    return strcmp((char *)a, (char *)b);
}

int num_cmp(void *a, void *b) {
  return numcmp((char *)a, (char *)b);
}
/* swap: interchange v[i] and v[j] */
void swap(void *v[], int i, int j)
{
    void *temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

