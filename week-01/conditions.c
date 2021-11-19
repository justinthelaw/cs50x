#include <stdio.h>

int main(void)
{
  int x = 5;
  int y = 10;

  if (x < y)
  {
    printf("%i < %i\n", x, y);
  }
  else if (x > y)
  {
    printf("%i > %i\n", x, y);
  }
  else
  {
    printf("%i = %i\n", x, y);
  }
}