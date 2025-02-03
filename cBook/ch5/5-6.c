/*

TODO: Rewrite appropriate programs from earlier chapters and exercises with pointers
instead of array indexing. Good possibilities include getline (Chapters 1 and 4), atoi, itoa,
and their variants (Chapters 2, 3, and 4), reverse (Chapter 3), and strindex and getop
(Chapter 4).

---
ex 5-6

*/


#include <stdio.h>
#include <ctype.h>
#include <string.h>

int my_getline(char *s, int lim) {

  int c;
  
  char *t = s; // pointer to the start of the array

  while (--lim > 0 && (c=getchar()) != EOF && c != '\n')
    *s++ = c;
  if (c == '\n')
    *s++ = c;
  *s = '\0';

  printf("Adress stored in s: %p\n", (void *)s);
  printf("Adress stored in t: %p\n", (void *)t);
  printf("Value s points to: %c\n", *s);
  printf("Value t points to: %c\n", *t);
  return s - t; // length of the line
}


int atoi(char *s) { 

  int n, sign;

  for (; isspace(*s); s++)
    ;
  sign = (*s == '-') ? -1 : 1;
  if (*s == '+' || *s == '-')
    s++;
  for (n = 0; isdigit(*s); s++)
    n = 10 * n + (*s - '0');
  return sign * n;
}


/* reverse: reverse string s in place */
void reverse(char *s) {
  int c;
  char *t;

  for (t = s + (strlen(s)-1); s < t; s++, t--) {
    c = *s;
    *s = *t;
    *t = c;
  }
}  

void itoa(int n, char *s) {

  int sign;
  char *t = s;

  if ((sign = n) < 0)
    n = -n;
  do {
    *s++ = n % 10 + '0';
  } while ((n /= 10) > 0);
  if (sign < 0)
    *s++ = '-';
  *s = '\0';
  reverse(t);

}


int strindex(char *s, char *t) {
  
  char *b = s;
  char *p, *r; // *b = start of s; *p = i and *r = k;

  for (; *s != '\0'; s++) {
    for (p = s, r = t; *r != '\0' && *p == *r; p++, r++)
      ;
    if (r > t && *r == '\0')
      return s - b;
  }
  return -1;
}


double atof(char *s) {
  
  double val, power;
  int sign;

  for (; isspace(*s); s++) 
    ;
  sign = (*s == '-') ? -1 : 1;
  if (*s == '+' || *s == '-')
    s++;
  for (val = 0.0; isdigit(*s); s++)
    val = 10.0 * val + (*s - '0');
  if (*s == '.')
    s++;
  for (power = 1.0; isdigit(*s); s++) {
    val = 10.0 * val + (*s - '0');
    power *= 10;
  } 
  return sign * val / power;
}


int getch(void);
void ungetch(int);

int getop(char *s) {
  
  int c;
  while ((*s = c = getch() == ' ' || c == '\t'))
    ;
  *(s+1) = '\0';
  if (!isdigit(c) && c != '.')
    return c;
  if (isdigit(c))
    while (isdigit(*++s = c = getch()))
      ;
  if (c == '.')
    while (isdigit(*++s = c = getch()))
      ;
  *s = '\0';
  if (c != EOF)
    ungetch(c);
  return NUMBER;


}


int main() {
    char line[100];
    int length = my_getline(line, 100);
    // printf("Line: %s\n", line);
    // printf("Length: %d\n", length);
    

    char buffer[20];
    itoa(-12345, buffer);
    printf("Converted string: %s\n", buffer);  // Output: "-12345"

    itoa(6789, buffer);
    printf("Converted string: %s\n", buffer);  // Output: "6789"
    
    char test1[] = "OggyFoxy";
    reverse(test1);
    printf("%s\n", test1);
    return 0;
}

