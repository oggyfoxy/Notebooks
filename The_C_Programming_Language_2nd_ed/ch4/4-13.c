/*

ex 4-13
---

TODO: make reverse(s) recursive.

*/

#include <stdio.h>
#include <string.h>

void reverse(char s[], int i, int j);

void reverse(char s[], int i, int j) {

  char temp;

  if (i < j) {
    temp = s[i];
    s[i] = s[j];
    s[j] = temp;
    reverse(s, i+1, j-1);
    }
  else 
    return;

}

int main(void) {

  char s[100] = "Abcdefghijklmnopqrstuvwxyz";
  int i = 0;
  int j = strlen(s) - 1;
  
  reverse(s, i, j);
  printf("%s\n", s);
  return 0;
}
