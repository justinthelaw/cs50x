#include <stdio.h>

int main(void)
{
  float x = 1;
  float y = 20;

  printf("Default decmial places: %f\n", x / y);
  printf("10 decimal places (not precise): %.10f\n", x / y);
}