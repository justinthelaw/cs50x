#include <stdio.h>

int main(void)
{
  int height = 8;
  printf("The selected height of the pyramid is: %i\n", height);

  for (int i = 0; i <= height; i++)
  {
    if (i != 0 && i > 1)
    {
      printf("\n");
    }
    int x = i * 2;

    if (i != 0)
    {
      for (int j = 0; j < height - i; j++)
      {
        printf(" ");
      }
    }

    for (int k = 0; k < x; k++)
    {
      if (k == x / 2)
      {
        printf("  #");
      }
      else
      {
        printf("#");
      }
    }
  }

  printf("\n");
}