/*

TODO: Define a macro swap(t,x,y) that interchanges two arguments of type t.
(Block structure will help.) 

ex 4-14
---

*/

#include <stdio.h>
#define swap(t,x,y) { t _z; \
                      _z = x; \
                         x = y; \
                      y = _z; } 

int main(void) {
  
  float a = -3.14;
  float b = 6;
  swap(float, a, b);

  printf("a: %f, b: %f\n", a, b);


  return 0;
}


