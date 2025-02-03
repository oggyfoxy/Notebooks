#include <stdio.h>
#include <string.h>

#define MAXLINES 5000 /* max #lines to be sorted */

void qsort(char *v[], int left, int right);
int readlines(char *lineptr[], char linestor[], int maxlines);
void writelines(char *lineptr[], int nlines); 
int mygetline(char *, int);



/* qsort: sort v[left]...v[right] into increasing order */
void qsort(char *v[], int left, int right) {
    int i, last;
    void swap(char *v[], int i, int j);

    if (left >= right)  /* do nothing if array contains */
        return;          /* fewer than two elements */
    swap(v, left, (left + right) / 2);
    last = left;
    for (i = left + 1; i <= right; i++)
        if (strcmp(v[i], v[left]) < 0)
            swap(v, ++last, i);
    swap(v, left, last);
    qsort(v, left, last - 1);
    qsort(v, last + 1, right);
}

/* swap: interchange v[i] and v[j] */
void swap(char *v[], int i, int j) {
    char *temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}


/* getline: read a line into s, return length */
int mygetline(char s[], int lim) {
    int c, i;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;
    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}

#define ALLOCSIZE 10000

static char allocbuf[ALLOCSIZE]; // storage for alloc
static char *allocp = allocbuf; // next free position

char *alloc(int n) {
  if (allocbuf + ALLOCSIZE - allocp >= n) {
    allocp += n;
    return allocp - n;

  } else 
      return 0;
}



#define MAXLEN 1000  /* max length of any input line */
#define MAXSTOR 5000

char *lineptr[MAXLINES];

/* readlines: read input lines */
int readlines(char *lineptr[], char linestor[], int maxlines) {
    int len, nlines;
    char *p = linestor; /* points to first element of the line storage */
    char line[MAXLEN];
    char *linestop = linestor + MAXSTOR; /* points to the last element of storage */
    
    nlines = 0;
    while ((len = mygetline(line, MAXLEN)) > 0)
        if (nlines >= maxlines || linestop < len + p)
            return -1;
        else {
            line[len - 1] = '\0';  /* delete newline */
            strcpy(p, line);
            lineptr[nlines++] = p;
            p += len; // advances the pointers to the end of the line read.
        }
    return nlines;
}

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines) {
    while (nlines-- > 0)
        printf("%s\n",*lineptr++);
}


int main() {
    
    char *lineptr[MAXLINES];
    char storage[MAXSTOR];

    int nlines;     /* number of input lines read */

    if ((nlines = readlines(lineptr, storage, MAXLINES)) >= 0) {
        qsort(lineptr, 0, nlines - 1);
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("error: input too big to sort\n");
        return 1;
    }
}



