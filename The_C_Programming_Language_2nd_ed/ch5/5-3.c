/*

TODO: write alternative of strcat that uses pointers
ex 5-3

*/

#include <stdio.h>


void mystrcat(char *s, char *t);

int main(void)
{
  char s[100] = "This is the first string";
  char t[] = ", this second string!";

  mystrcat(s, t);

  printf("%s\n", s);

  return 0;
}
/* strcat: concatenate t to end of s; s must be big enough */
void mystrcat(char *s, char *t)
{
    while (*s)   /* find end of s */
        ++s;
    while ((*s++ = *t++) != '\0')   /* copy t */
        ;
}
