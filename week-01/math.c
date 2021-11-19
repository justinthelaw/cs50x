#include <stdio.h>

int main(void)
{
  // int is 32 bits, so –2,147,483,648 to 2,147,483,647
  int x = 5;
  int y = 3;
  // if variables are larger in value, declare the variable as a "long"
  // long is 64 bits, so –9,223,372,036,854,775,808 to 9,223,372,036,854,775,807
  long a = 30000000000;
  long b = 50000000000;

  // if variables have decimal places, declare the variable as a "float"
  float e = 20;
  float r = 2.5;

  // if the declared variables are long, use "%li"
  printf("%i + %i = %i\n", x, y, x + y);
  printf("%li + %li = %li\n", a, b, a + b);
  printf("%f / %f = %f\n", e, r, e / r);
}