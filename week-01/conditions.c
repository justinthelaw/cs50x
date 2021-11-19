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

  char answer[1] = "n";

  if (answer == "y" || answer == "Y")
  {
    printf("Answer: %s, which means YES\n", answer);
  }
  else
  {
    printf("Answer: %s, which means NO\n", answer);
  }
}