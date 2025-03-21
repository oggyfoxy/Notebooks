/*
TODO
for (i=0; i<lim-1 && (c=getchar()) != '\n' && c != EOF; ++i)
  s[i] = c;
*/

#include <stdio.h>

enum boolean
{
  NO,
  YES
};
int main(void)
{

  int c, lim;
  int i = 0;
  char s[1000];

  enum boolean goodLoop = YES;

  while (goodLoop == YES)
  {
    if (i >= lim - 1)
      goodLoop = NO;

    else if ((c = getchar()) == '\n')
      goodLoop = NO;

    else if (c == EOF)
      goodLoop = NO;

    else
    {
      s[i] = c;
      i++;
    }
  }

  return 0;
}
