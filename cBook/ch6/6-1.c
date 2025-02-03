/*

TODO: Our version of getword does not properly handle underscores, string constants,
comments, or preprocessor control lines. Write a better version. 
---
ex 6-1

*/


#include <stdio.h>
#include <ctype.h>

#define LENGTH 100
int main(int argc, char *argv[]) {

  getword(word, LENGTH);
  return 0;
}

struct point {
  int x;
  int y;
};

struct point makepoint(int x, int y) {

  struct point temp;

  temp.x = x;
  temp.y = y;
  return temp;
}

struct rect {
  struct point pt1;
  struct point pt2;
};

struct rect screen;

screen.pt1.x;


/* getword: get next word or character from input */
int getword(char *word, int lim)
{
    int c, getch(void);
    void ungetch(int);
    char *w = word;

    while (isspace(c = getch()))
        ;

    if (c != EOF)
        *w++ = c;

    if (!isalpha(c)) {
        *w = '\0';
        return c;
    }

    for (; --lim > 0; w++) {
        if (!isalnum(*w = getch())) {
            ungetch(*w);
            break;
        }
    }

    *w = '\0';
    return word[0];
}

