#include <stdio.h>

int main() {
  
  int i = 0;
  char *days[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};
  
  for (; i < 5; i++) {
    printf("%s\n", days[i]); 
  }
  return 0;
}
