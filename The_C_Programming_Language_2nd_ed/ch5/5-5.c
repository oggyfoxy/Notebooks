/* 

TODO: Write versions of the library functions strncpy_n, strncat_n, and strncmp_n, which
operate on at most the first n characters of their argument strings. For example,
strncpy_n(s,t,n) copies at most n characters of t to s. 
---
ex 5-5

*/

#include <stdio.h>
#include <string.h>

void strncpy_n(char *s, char *t, int n);
void strncat_n(char *s, char *t, int n);
int strncmp_n(char *s, char *t, int n);


/* strncpy_n: copies n characters from t to s */
void strncpy_n(char *s, char *t, int n) {

  while (*t && n-- > 0)
    *s++ = *t++;
  
  while (n-- > 0)
    *s++ = '\0';

  // just writing in arrays to compare
  /*
  int i = j = 0;
  for (; t[j] != '\0' && n-- > 0; i++, j++)
    s[i] = [j];

  for (; n-- > 0; i++)
    s[i+] = '\0';;
  */

}

/* strncat_n: cats n characters from t to end of s */
void strncat_n(char *s, char *t, int n) {

  strncpy_n(s + strlen(s), t, n);

}

/* strncmp_n: conpares n characters from s and t */

int strncmp_n(char *s, char *t, int n) {

  for (; *s == *t; s++, t++) 
    if (*s == '\0' || --n <= 0)
      return 0;
  return *s - *t; 
}

int main() {

  char s[100] = "This is, a ";
  char t[] = "Sample string";

  int x = strncmp_n(s, t, 5); // source, dest
  printf("%d\n", x);

  return 0;
}


