/* 

TODO: Write the function strend(s,t), which returns 1 if the string t occurs at the
end of the string s, and zero otherwise. 
---
ex 5-4

*/

#include <stdio.h>
#include <string.h>

int strend(char *s, char *t);

/* strend: checks if t occurs at end of s */
int strend(char *s, char *t) {

  if (strlen(t) > strlen(s))
    return 0;
  
  s = s + (strlen(s) - strlen(t));

  while (*t) {
    if (*s++ != *t++)
      return 0;
  }
  return -1;

}




int main() {

  char* s1 = "Hello man im weird";
  char* s2 = "weird";

  if (strend(s1, s2))
    printf("yay\n");
  else
    printf("rip\n");


  return 0;
}
